# P510 Phase 3C-5A.4: Offline Target Identity Validation

**Status: HARDWARE BUILD READY FOR PHASE 3C-5B**

**Safety boundary:** No physical USB device was enumerated or accessed. The P510 was not connected to WSL, opened, claimed, or sent a transfer. usbipd-win was not installed or used.

## Why Phase 3C-5B previously stopped

The prior hardware-enabled `--dry-run` correctly avoided USB initialization and reported the exact GetDeviceInfo request, but it did not print the compiled VID/PID or interface configuration. Phase 3C-5B stopped before usbipd installation or camera access because its preflight required those values to be visible.

## Source review and historical hashes

Before editing, the current source and hardware executable matched the Phase 3C-5A.3 report:

| Artifact | Previous SHA-256 |
|---|---|
| `scripts/P510PTPGetDeviceInfo.c` | `0EDEC20AC13B15776DD1E29358BA1301C843688ECFE6167FC2E53D46782D8D09` |
| `build/P510PTPGetDeviceInfo-hardware` | `1C8B778405C07B241AEA84F63C1B1F38E25C0F8E9E1A98B24C787755B93EDA13` |
| `build/P510PTPGetDeviceInfo-offline` | `E5F6305AF37809330FD294CC27B43BC39085F538086B8281BC7A1E067EEF4BB5` |

The offline executable was not rebuilt or overwritten. Its current hash remains unchanged.

## Source modification

Added shared compile-time constants for the PTP USB interface:

```c
#define P510_PTP_INTERFACE_CLASS 0x06u
#define P510_PTP_INTERFACE_SUBCLASS 0x01u
#define P510_PTP_INTERFACE_PROTOCOL 0x01u
```

Runtime interface validation now uses these constants, and dry-run prints the same constants along with the existing VID, PID, operation, and operation-limit constants. The output also labels the physical-device observation as absent and states that enumeration, open, claim, and transfer did not occur. `P510_ALLOW_USB` controls the displayed hardware-support state.

No target identity, PTP operation, transaction construction, operation limit, retry behavior, endpoint validation, USB-selection behavior, response parsing, or error handling was changed. The synthetic parser fixture is explicitly labeled as nonphysical.

## Build and hashes

- Ubuntu: `24.04.5 LTS`
- GCC: `13.3.0-6ubuntu2~24.04.1`
- libusb-1.0: `1.0.27`
- `P510_ALLOW_USB`: `1`

Exact compile command:

```sh
cd '/mnt/c/GitHub/Nikon P510/scripts'
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -DP510_ALLOW_USB=1 \
  P510PTPGetDeviceInfo.c -o ../build/P510PTPGetDeviceInfo-hardware \
  $(pkg-config --cflags --libs libusb-1.0)
```

Compilation succeeded with no warnings or errors.

| Artifact | New/current SHA-256 |
|---|---|
| `scripts/P510PTPGetDeviceInfo.c` | `31A76A18943D416B24E0DF746DCF9E3E1ACFECC948D76B06E2A3C1A073FF11BE` |
| `build/P510PTPGetDeviceInfo-hardware` | `4CDAA7F497010A131419420C42D2A980100D21BBB69914482746C619172E6CAA` |
| `build/P510PTPGetDeviceInfo-offline` (preserved) | `E5F6305AF37809330FD294CC27B43BC39085F538086B8281BC7A1E067EEF4BB5` |

## Offline validation

The existing source/safety validator passed. The hardware-enabled executable was run only with `--dry-run`; it returned through `offline_validate()` before `libusb_init()`.

Complete dry-run output:

```text
Synthetic DeviceInfo fixture (not physical camera data):
StandardVersion=0x0064
VendorExtensionID=0xFFFFFFFF
VendorExtensionVersion=0x0064
VendorExtensionDesc=X
FunctionalMode=0x0000
OperationsSupported: 0x1001(GetDeviceInfo) 0x1002(STANDARD-PTP CODE NOT TRANSMITTED)
EventsSupported:
DevicePropertiesSupported:
CaptureFormats:
ImageFormats: 0x3801
Manufacturer=
Model=
DeviceVersion=UNKNOWN
SerialNumber=<REDACTED>
COMPILED TARGET CONFIGURATION
Target VID: 0x04B0
Target PID: 0x0223
Required USB interface class: 0x06
Required USB interface subclass: 0x01
Required USB interface protocol: 0x01
Allowed PTP operation: 0x1001 GetDeviceInfo
Maximum PTP operations: 1
USB hardware support: ENABLED

PHYSICAL DEVICE OBSERVATION
Physical device observation: NONE (dry-run)
Physical USB enumeration performed: NO
Physical USB device opened: NO
Physical interface claimed: NO
USB transfer performed: NO
OperationCount=1
OutgoingContainerLength=12
OutgoingContainerType=0x0001
OutgoingOperation=0x1001
OutgoingTransactionID=1
SessionID=0
OutgoingBytes=0C 00 00 00 01 00 01 10 01 00 00 00
```

The dry run reports the compiled configuration, not an observed physical device. The displayed DeviceInfo values are synthetic fixture values and are not camera-reported.

Expected request:

```text
0C 00 00 00 01 00 01 10 01 00 00 00
```

The request is exactly 12 bytes and encodes command container type `0x0001`, operation `0x1001`, and transaction ID `1`. It matches the previously validated Phase 3C-5A.3 offline request byte-for-byte: **PASS**. The preserved offline executable hash also remains unchanged.

## Physical-device validation remains mandatory

The compiled-target output is not evidence of physical device identity. At runtime, the hardware path must independently enumerate and verify an actual descriptor with VID `0x04B0` and PID `0x0223`, validate the physical interface as `06/01/01`, and require bulk IN and bulk OUT endpoints before transmission. An unexpected or missing physical identity/interface must terminate before any PTP transfer.

Any later Phase 3C-5B must require both:

1. Compiled target configuration `04B0:0223`.
2. Observed physical device identity `04B0:0223`.

## Final status

**HARDWARE BUILD READY FOR PHASE 3C-5B**

This report records offline validation only. It does not authorize or start Phase 3C-5B. Do not install usbipd-win or access the camera without separate authorization.
