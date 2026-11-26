# P510 Phase 3C-5C: Passive USB Descriptor Analysis

**Final status: DESCRIPTORS MATCH EXPECTATIONS - FAILURE REQUIRES FURTHER OFFLINE ANALYSIS**

## Scope and safety

- The previous Phase 3C-5B failure report and transport log were reviewed.
- The PTP client was **not executed** in this phase.
- No PTP operation was transmitted; no PTP session was opened.
- A temporary libusb descriptor inspector enumerated descriptors and read USB string descriptors only. It did not claim an interface or use a PTP endpoint.
- `lsusb` was not installed. No software was installed; the inspector used the already-installed libusb-1.0 development package.
- The PTP client source and hardware executable were not modified or rebuilt.

## Prior selector failure and exact cause

The previous client invocation exited with:

```text
Refusing: expected exactly one 04B0:0223 Still Image/PTP interface
```

In the hardware path, the selector:

1. Enumerates devices and requires `idVendor == 0x04B0` and `idProduct == 0x0223`.
2. Calls `libusb_get_active_config_descriptor()` and inspects only the active configuration.
3. Iterates each interface and each alternate setting in that active configuration.
4. Requires class/subclass/protocol `06/01/01`.
5. Requires at least one bulk IN and one bulk OUT endpoint in a matching alternate setting; it records an interrupt endpoint if present but does not require one.
6. Calls `libusb_open()` after finding the interface and bulk endpoints. It returns a successful selector result only if this open succeeds.
7. Counts matching VID/PID devices, not matching interface alternate settings. If the interface helper fails, `main` forces the count to a failing value and prints the generic refusal.

The passive descriptor inspector, run as the same Linux account used by the failed client (`<LOCAL_USER>`), found:

```text
TARGET_MATCH_COUNT=1
TARGET_DESCRIPTOR_RESULT=0
ACTIVE_CONFIGURATION_SELECTOR_RESULT=0
ACTIVE_CONFIGURATION_VALUE=1
SELECTOR_CANDIDATE interface=0 alternate=0 class=06 subclass=01 protocol=01 endpoints=3 bulk_in=1 bulk_out=1
SELECTOR_MATCHED_ALTERNATES=1
libusb_open_result=-3 (LIBUSB_ERROR_ACCESS)
```

Thus the exact refusal cause was **`libusb_open()` returning `LIBUSB_ERROR_ACCESS` under `<LOCAL_USER>`**, after VID/PID, active configuration, interface tuple, and bulk endpoint checks had succeeded. A second passive descriptor inspection as root returned `libusb_open_result=0 (SUCCESS)` and retrieved the USB strings, confirming an account/device-node access restriction rather than a descriptor mismatch.

The source does not log the `libusb_open()` error; it silently treats any nonzero result as “no acceptable interface,” which explains why the client’s error message was generic. No permission rule or client change was made.

## Device descriptor

Windows and usbipd independently identified the camera as `P510`, VID/PID `04B0:0223`, bus ID `4-1`. WSL libusb identified one matching device at bus 1, address 2:

| Field | Observed value |
|---|---|
| `bLength` | 18 |
| `bDescriptorType` | 1 (Device) |
| `idVendor` | `0x04B0` |
| `idProduct` | `0x0223` |
| `bcdUSB` | `0x0200` |
| `bcdDevice` | `0x0100` |
| `bDeviceClass` | `0x00` |
| `bDeviceSubClass` | `0x00` |
| `bDeviceProtocol` | `0x00` |
| `bMaxPacketSize0` | 64 |
| `bNumConfigurations` | 2 |
| `iManufacturer` | 1, string `NIKON` |
| `iProduct` | 2, string `NIKON DSC COOLPIX P510-PTP` |
| `iSerialNumber` | 3, string `31100075` |

## Complete configuration/interface/endpoint topology

There are **two configurations**. Each contains one interface and one alternate setting. Both configurations advertise the same Still Image/PTP interface and endpoints.

### Configuration descriptor index 0

| Field | Value |
|---|---|
| `bLength` / descriptor type | 9 / 2 |
| `wTotalLength` | 39 |
| `bConfigurationValue` | 1 (active) |
| `bmAttributes` | `0x80` |
| `MaxPower` | 250 units = 500 mA |
| `bNumInterfaces` | 1 |
| `iConfiguration` | 0; no string |

### Configuration descriptor index 1

| Field | Value |
|---|---|
| `bLength` / descriptor type | 9 / 2 |
| `wTotalLength` | 39 |
| `bConfigurationValue` | 2 (not active during inspection) |
| `bmAttributes` | `0xC0` |
| `MaxPower` | 1 unit = 2 mA |
| `bNumInterfaces` | 1 |
| `iConfiguration` | 0; no string |

### Interfaces and alternate settings

| Configuration value | `bInterfaceNumber` | `bAlternateSetting` | `bNumEndpoints` | Class | Subclass | Protocol | `iInterface` |
|---:|---:|---:|---:|---:|---:|---:|---:|
| 1 (active) | 0 | 0 | 3 | `0x06` | `0x01` | `0x01` | 0; no string |
| 2 | 0 | 0 | 3 | `0x06` | `0x01` | `0x01` | 0; no string |

There is **one** `06/01/01` alternate setting in the active configuration and **two total** across both configurations. The client's active-configuration behavior does not create duplicates; it sees exactly one candidate.

### Endpoints in each configuration

| Address | Direction | `bmAttributes` | Transfer type | `wMaxPacketSize` | `bInterval` | `bRefresh` | `bSynchAddress` |
|---|---|---:|---|---:|---:|---:|---:|
| `0x01` | OUT | `0x02` | Bulk | `0x0200` (512) | 0 | 0 | `0x00` |
| `0x81` | IN | `0x02` | Bulk | `0x0200` (512) | 0 | 0 | `0x00` |
| `0x82` | IN | `0x03` | Interrupt | `0x0008` (8) | 16 | 0 | `0x00` |

The active PTP interface exposes the expected Bulk OUT, Bulk IN, and Interrupt IN endpoints. No endpoint was used for data transfer.

## Comparison with selector assumptions

| Candidate cause | Finding |
|---|---|
| A. Zero interfaces matched `06/01/01` | No; one matched in the active configuration. |
| B. More than one active interface/alternate matched | No; exactly one active alternate matched. |
| C. Interface values differ | No; active interface is `06/01/01`. |
| D. Required endpoints absent | No; bulk IN `0x81` and bulk OUT `0x01` are present. |
| E. Endpoint types/directions differ | No; bulk directions/types match; interrupt IN `0x82` is also present. |
| F. Alternate-setting handling caused duplicate/missing matches | No; one alternate exists per configuration; active configuration contains one match. |
| G. Configuration-selection logic disagrees with camera | No evidence; active configuration value 1 has the expected interface. Configuration 2 also has the same topology. |
| H. Linux descriptors differ from Windows PnP inference | No; Linux reports the expected `04b0:0223` device and PTP topology. |
| I. Other exact condition | **Yes; `libusb_open()` returned `LIBUSB_ERROR_ACCESS` as `<LOCAL_USER>`.** |

The selector's VID/PID, active-interface, and endpoint criteria are consistent with the observed descriptors. The refusal was caused by the failed device open, not by an incorrect interface or endpoint assumption. The generic selector message obscured the access error.

## Recommended minimum change

No selector relaxation or interface-selection source change is indicated. The minimum follow-up should be offline: improve diagnostics so a failed `libusb_open()` reports `libusb_error_name(rc)`. Separately resolve USB device-node permissions for the intended execution account before any future PTP attempt. Do not bypass identity/interface checks. No source modification was made in this phase.

## Cleanup and integrity

- The P510 was detached from WSL using usbipd bus ID `4-1`.
- WSL sysfs reported zero remaining `04b0:0223` devices.
- Windows again reported `P510`, status `OK`, class `WPD`, service `WUDFWpdMtp`, INF `wpdmtp.inf`.
- The Windows driver was not changed.
- No PTP client was run and no PTP command was sent in this phase.
- Client source SHA-256 remained `31A76A18943D416B24E0DF746DCF9E3E1ACFECC948D76B06E2A3C1A073FF11BE`.
- Raw descriptor capture: [`P510-USB-descriptors.txt`](./P510-USB-descriptors.txt)
- Descriptor file SHA-256: `D966A78CF419CF1428189ADBD9CAC7BBC035DB3A4EE8367869D1F5B46662CC42`

## Final status

**DESCRIPTORS MATCH EXPECTATIONS - FAILURE REQUIRES FURTHER OFFLINE ANALYSIS**

Stop here. Do not run the PTP client or attempt another physical PTP operation.
