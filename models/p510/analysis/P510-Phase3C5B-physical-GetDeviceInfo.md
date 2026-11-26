# P510 Phase 3C-5B: Physical GetDeviceInfo Interrogation

**Current final status: GETDEVICEINFO SUCCEEDED - NO FURTHER COMMAND AUTHORIZED**

## Authoritative build and preflight

The authoritative baseline was `P510-Phase3C5A4-target-validation.md`.

| Item | Value |
|---|---|
| Hardware executable | `build/P510PTPGetDeviceInfo-hardware` |
| Source SHA-256 | `31A76A18943D416B24E0DF746DCF9E3E1ACFECC948D76B06E2A3C1A073FF11BE` |
| Hardware executable SHA-256 | `4CDAA7F497010A131419420C42D2A980100D21BBB69914482746C619172E6CAA` |
| `P510_ALLOW_USB` | `1` |
| Phase 3C-5A.4 status | `HARDWARE BUILD READY FOR PHASE 3C-5B` |

Both hashes matched the report before execution. The existing safety validator passed. The USB-free hardware dry run confirmed the compiled target `04B0:0223`, interface `06/01/01`, one allowed operation (`0x1001`), maximum count `1`, and the 12-byte request `0C 00 00 00 01 00 01 10 01 00 00 00`. Its byte sequence matched the previously validated reference.

## usbipd-win installation

- Method: `winget install --id dorssel.usbipd-win --exact --source winget --accept-source-agreements --accept-package-agreements --silent`
- Package version: `5.3.0`
- Runtime version: `5.3.0-54+Branch.master.Sha.aa3db8b82c4cb5071fd31bc54211606c70886912.aa3db8b82c4cb5071fd31bc54211606c70886912`
- Service: running, automatic start
- Windows restart requested: **No**

## Device identity and descriptors

Windows identified one matching device before attachment:

- Name: `P510`
- VID/PID: `04B0:0223`
- Instance ID: `USB\VID_04B0&PID_0223\31100075`
- usbipd bus ID: `4-1`

After attaching only bus `4-1`, WSL sysfs independently reported:

- VID/PID: `04b0:0223`
- Product: `NIKON DSC COOLPIX P510-PTP`
- Interface `1.0`: class `06`, subclass `01`, protocol `01`
- Endpoint `0x01`: bulk OUT, attributes `02`, max packet `0200`
- Endpoint `0x81`: bulk IN, attributes `02`, max packet `0200`
- Endpoint `0x82`: interrupt IN, attributes `03`, max packet `0008`

One matching WSL USB device was found.

## First execution attempt (2026-11-19)

The exact command was run once:

```text
wsl.exe --distribution Ubuntu-24.04 --user <LOCAL_USER> --cd '/mnt/c/GitHub/Nikon P510/analysis' --exec '../build/P510PTPGetDeviceInfo-hardware'
```

Captured process exit code: `2`

Captured stdout: empty.

Captured stderr:

```text
Refusing: expected exactly one 04B0:0223 Still Image/PTP interface
```

The client exited during device/interface selection. It did not print `USBDeviceSelected` and did not enter `execute_get_device_info`.

- PTP operations transmitted: **0**
- `GetDeviceInfo (0x1001)` transmitted: **No**
- PTP session opened: **No**
- Operation counter reached: **No; the operation function was not entered**
- Actual outgoing PTP container: **None**
- PTP response/container received: **None**
- Response code / transaction ID: **None**
- Raw DeviceInfo payload: **None**
- Decoded DeviceInfo: **None**
- Advertised operations, events, properties, formats, and vendor-extension fields: **Not obtained**
- Retry: **No**

The expected command from the successful dry run, not transmitted during this attempt, was:

```text
Length: 12
Bytes: 0C 00 00 00 01 00 01 10 01 00 00 00
Operation: 0x1001 GetDeviceInfo
Transaction ID: 1
```

The client supplied only a generic selection failure, so the exact reason it could not accept/open the matching PTP interface is **UNKNOWN**. No further USB/PTP diagnostic or retry was attempted.

## Cleanup and Windows ownership

- `usbipd detach --busid 4-1` completed successfully.
- usbipd now reports bus `4-1` as `Shared`, not `Attached`.
- WSL sysfs reports zero remaining `04b0:0223` devices.
- Windows again reports `P510`, status `OK`, class `WPD`.
- Windows service: `WUDFWpdMtp`; driver INF: `wpdmtp.inf`.
- The existing Windows camera driver was not replaced or modified.

No USB interface was successfully claimed, so no PTP interface release was needed. No successfully opened libusb handle was returned. Libusb context cleanup occurred on process exit.

## First-attempt artifacts and SHA-256 (historical snapshot)

Captured files:

| Artifact | Result | SHA-256 |
|---|---|---|
| `analysis/P510-GetDeviceInfo-transport.log` | Created | `2A933C5CC040F7B176419C22414E92D56E5651C417FEDD5B39382E1BF71561F2` |
| `analysis/P510-GetDeviceInfo.stdout.txt` | Created; empty stdout capture | `E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855` |
| `analysis/P510-GetDeviceInfo.stderr.txt` | Created | `67DC16377E03EAE025AD60D88C430E399EAD4D0673027A54652EEBAD76155414` |
| `analysis/P510-GetDeviceInfo-raw.bin` | Not created; no payload received | N/A |
| `analysis/P510-GetDeviceInfo-decoded.txt` | Not created; no payload received | N/A |

Final source and executable hashes:

| Artifact | SHA-256 |
|---|---|
| `scripts/P510PTPGetDeviceInfo.c` | `31A76A18943D416B24E0DF746DCF9E3E1ACFECC948D76B06E2A3C1A073FF11BE` |
| `build/P510PTPGetDeviceInfo-hardware` | `4CDAA7F497010A131419420C42D2A980100D21BBB69914482746C619172E6CAA` |

At the end of that initial attempt, the camera was detached and Windows ownership returned. No second GetDeviceInfo or other PTP operation was attempted during that attempt.

## Historical status of the first attempt

**GETDEVICEINFO FAILED - NO RETRY PERFORMED**

The first attempt exited before USBDeviceSelected and transmitted no PTP operation. Its files and hashes above are retained as historical evidence.

## Resumed Phase 3C-5B controlled execution (2026-11-20)

### Preflight and live device verification

The Phase 3C-5A.4 baseline hashes matched immediately before execution:

| Artifact | SHA-256 |
|---|---|
| `scripts/P510PTPGetDeviceInfo.c` | `31A76A18943D416B24E0DF746DCF9E3E1ACFECC948D76B06E2A3C1A073FF11BE` |
| `build/P510PTPGetDeviceInfo-hardware` | `4CDAA7F497010A131419420C42D2A980100D21BBB69914482746C619172E6CAA` |

The existing safety validator passed. The USB-free dry-run exited `0` and confirmed:

- Compiled target `04B0:0223`.
- Interface `06/01/01`.
- Allowed operation `0x1001 GetDeviceInfo`, maximum count `1`.
- USB hardware support `ENABLED`.
- No enumeration, open, claim, or transfer during dry-run.
- Command length 12 bytes and exact bytes `0C 00 00 00 01 00 01 10 01 00 00 00`, identical to the validated reference.

Windows identified one intended camera, P510 `04B0:0223`, BUSID `4-1`, initially `Shared`. usbipd-win runtime version was `5.3.0-54+Branch.master.Sha.aa3db8b82c4cb5071fd31bc54211606c70886912.aa3db8b82c4cb5071fd31bc54211606c70886912`.

The exact attach command was:

```powershell
& 'C:\Program Files\usbipd-win\usbipd.exe' attach --wsl --busid 4-1
```

Attach stdout was empty; stderr reported use of Ubuntu-24.04, loading `vhci_hcd`, NAT networking, and host IP `172.19.48.1`; exit code was `0`. usbipd then reported BUSID `4-1` as `Attached`.

The first immediate sysfs probe found no matching device; a passive recheck about two seconds later found exactly one P510. No second attach was performed. Immediately before execution, WSL reported:

| Check | Observed value |
|---|---|
| Execution user | `<LOCAL_USER>` |
| Physical VID/PID | `04b0:0223` |
| Current device node | `/dev/bus/usb/001/002` |
| Node owner/group/mode | `root:plugdev`, `0660` |
| Interface | number 0, alternate 0, class/subclass/protocol `06/01/01` |
| Endpoint `0x01` | Bulk OUT, `wMaxPacketSize=0x0200` |
| Endpoint `0x81` | Bulk IN, `wMaxPacketSize=0x0200` |
| Endpoint `0x82` | Interrupt IN, `wMaxPacketSize=0x0008`, interval `0x10` |

`<LOCAL_USER>` was a member of `plugdev`. The rule remained restricted to `04b0:0223`. Final checks also confirmed operation allowlist `0x1001` only, maximum `1`, no automatic command retry, no OpenSession implementation, and no vendor operation transmission path. Execution was as `<LOCAL_USER>`, not root.

### One physical execution

The exact execution command was run once:

```powershell
wsl.exe --distribution Ubuntu-24.04 --user <LOCAL_USER> --cd '/mnt/c/GitHub/Nikon P510/analysis' --exec '../build/P510PTPGetDeviceInfo-hardware'
```

Exit code: `0`. Stderr was empty. The outgoing command was transmitted once:

```text
OperationCount=1
OutgoingContainerLength=12
OutgoingContainerType=0x0001
OutgoingOperation=0x1001
OutgoingTransactionID=1
SessionID=0
OutgoingBytes=0C 00 00 00 01 00 01 10 01 00 00 00
```

The operation count reached `1`; `GetDeviceInfo (0x1001)` was transmitted. No PTP session was opened, no OpenSession was sent, and no second PTP operation or retry occurred.

Received containers, both with transaction ID `1`:

| Length | Type | Code | Result |
|---:|---:|---:|---|
| 305 | Data (`0x0002`) | `0x1001` | DeviceInfo payload |
| 12 | Response (`0x0003`) | `0x2001` | `PTP_OK` |

### Decoded DeviceInfo

The exact 293-byte DeviceInfo payload is preserved in [`P510-GetDeviceInfo.raw.bin`](./P510-GetDeviceInfo.raw.bin). Decoded text is in [`P510-GetDeviceInfo-decoded.txt`](./P510-GetDeviceInfo-decoded.txt); the serial number is redacted in text and remains in the raw payload.

| Field | Decoded value |
|---|---|
| StandardVersion | `0x0064` |
| VendorExtensionID | `0x00000006` |
| VendorExtensionVersion | `0x0064` |
| VendorExtensionDesc | `microsoft.com: 1.0; Nikon PTP Extensions` |
| FunctionalMode | `0x0000` |
| CaptureFormats | Empty |
| ImageFormats | `0x3801 0x3001 0x3006 0x3008 0x300D 0xB111 0x3000` |
| Manufacturer | `Nikon Corporation` |
| Model | `P510` |
| DeviceVersion | `V1.00` |
| SerialNumber | Redacted in text; present in raw payload |

Complete `OperationsSupported`, preserved in device-reported order:

**STANDARD PTP OPERATIONS**

`0x1001 0x1002 0x1003 0x1004 0x1005 0x1006 0x1007 0x1008 0x1009 0x100A 0x100C 0x100D 0x101B 0x100B 0x100F 0x1023 0x1014 0x1015 0x1016`

`0x1001` is GetDeviceInfo. `0x1002` is OpenSession, advertised but not transmitted. Other meanings are not expanded here.

**VENDOR-SPECIFIC OPERATIONS**

`0x9801 0x9802 0x9803 0x9805 0x90A1 0x90A2 0x90A3`

All are marked `UNKNOWN`; no vendor-specific operation was invoked or assigned an undocumented meaning.

Complete `EventsSupported` raw values:

`0x4001 0x4002 0x4003 0x4004 0x4005 0x4006 0x4007 0x4008 0x4009 0x400A 0x400C`

All event values remain unmapped/`UNKNOWN`.

Complete `DevicePropertiesSupported` raw values:

`0x5001 0x5011 0xD280 0xD303 0xD406 0xD407`

All property values remain unmapped/`UNKNOWN`.

### Result artifacts and cleanup

| Artifact | SHA-256 |
|---|---|
| `P510-GetDeviceInfo.raw.bin` (293 bytes) | `E867C4FEE60CE314FC6DFF9D9A3300FA950136A279484DB13EADFE2E7C17EF96` |
| `P510-GetDeviceInfo-decoded.txt` | `599FECA3CAA14F4BB4369CEE88791FE8ABCAC28FFDD979E3A1FCF49D332622FB` |
| `P510-GetDeviceInfo-transport.log` (updated; contains prior attempt and this execution) | `149A647852B5E5A2D9B10B2292FEE603D76093FF130F3DFDB68D47C065AB4A7F` |

The transport log was appended with this execution's stdout/stderr, command, identity, endpoints, received containers, operation count, and cleanup record. The source and hardware executable hashes remained unchanged after execution.

After the one execution, `usbipd detach --busid 4-1` completed with exit code `0`. WSL reported zero remaining `04b0:0223` devices. Windows again reported P510 status `OK`, class `WPD`, service `WUDFWpdMtp`. The interface was released and libusb handle/context were closed by the client. No retry occurred.

## Final status

**GETDEVICEINFO SUCCEEDED - NO FURTHER COMMAND AUTHORIZED**

Stop here. Do not send another PTP command or proceed to Phase 3C-6.
