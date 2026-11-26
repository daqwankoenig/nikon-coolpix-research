# P510 Phase 3C-5A.3: Hardware Build and Offline Validation

**Status: HARDWARE BUILD READY FOR PHASE 3C-5B**

**Execution boundary:** The hardware-capable executable was not run without `--dry-run`. No USB device was enumerated or opened by it. No USB interface was claimed and no USB transfer or camera communication occurred. usbipd-win was not installed or used.

## Source integrity and changes

Before the first hardware-enabled compile attempt, the source SHA-256 matched the required value:

```text
DE0B903F0A37E449857E3DFACF6E8F23A7999EE3ABFFE3545BE80E8CDCEAAA74
```

The initial `P510_ALLOW_USB=1` compile exposed libusb descriptor type-name errors, a signedness warning, and an unused offline validator. The source was then modified only to make the hardware build compile and provide a safe offline test path:

1. Use the `struct libusb_*` descriptor types required by the installed libusb headers.
2. Cast the already-validated nonnegative transfer length for the container-size comparison.
3. Add a fixed `--dry-run` option that invokes `offline_validate()` before any `libusb_init()` call. No arbitrary operation or device arguments were added.

No PTP operation code, operation-count limit, VID/PID, or USB-selection restriction was changed. The final source SHA-256 is:

```text
0EDEC20AC13B15776DD1E29358BA1301C843688ECFE6167FC2E53D46782D8D09
```

## Build configuration

- Ubuntu: `24.04.5 LTS`
- Execution account: `<LOCAL_USER>`
- GCC: `13.3.0-6ubuntu2~24.04.1`
- libusb-1.0: `1.0.27`
- `pkg-config --cflags --libs libusb-1.0`: `-I/usr/include/libusb-1.0 -lusb-1.0`
- `P510_ALLOW_USB`: `1`

Exact command:

```sh
cd '/mnt/c/GitHub/Nikon P510/scripts'
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -DP510_ALLOW_USB=1 \
  P510PTPGetDeviceInfo.c -o ../build/P510PTPGetDeviceInfo-hardware \
  $(pkg-config --cflags --libs libusb-1.0)
```

The initial attempt failed as noted above. After the narrow source fixes, the exact strict-warning build succeeded with no warnings or errors. The pre-existing offline executable was not overwritten.

## SHA-256

| File | SHA-256 |
|---|---|
| `scripts/P510PTPGetDeviceInfo.c` (final modified source) | `0EDEC20AC13B15776DD1E29358BA1301C843688ECFE6167FC2E53D46782D8D09` |
| `build/P510PTPGetDeviceInfo-offline` (preserved) | `E5F6305AF37809330FD294CC27B43BC39085F538086B8281BC7A1E067EEF4BB5` |
| `build/P510PTPGetDeviceInfo-hardware` | `1C8B778405C07B241AEA84F63C1B1F38E25C0F8E9E1A98B24C787755B93EDA13` |

The offline executable hash still matches its Phase 3C-5A.2 value.

## Operation and device restrictions

- Fixed VID: `0x04B0`
- Fixed PID: `0x0223`
- Required interface: class/subclass/protocol `06/01/01`
- Required endpoints: one bulk IN and one bulk OUT endpoint from the matching interface; the interrupt endpoint is recorded if present.
- Only transmitted PTP operation: `0x1001` GetDeviceInfo
- Maximum PTP operation count per execution: `1`
- No OpenSession, arbitrary operation-code argument, vendor operation, storage/object operation, capture, property write, object upload/delete, firmware, or memory-access path.
- The `0x1002` value is present only in the synthetic parser fixture as a sample supported-operation value; it is not transmitted.

The hardware-enabled executable links libusb. Its `--dry-run` branch calls the offline validator before `libusb_init()`, so command construction can be tested without USB enumeration or opening a device.

## Dry-run request validation

The hardware-enabled executable's `--dry-run` output reported:

```text
OperationCount=1
AllowedOperations=0x1001
OutgoingContainerLength=12
OutgoingContainerType=0x0001
OutgoingOperation=0x1001
OutgoingTransactionID=1
OutgoingBytes=0C 00 00 00 01 00 01 10 01 00 00 00
```

The hardware-enabled and preserved offline executables produced the same command bytes:

```text
0C 00 00 00 01 00 01 10 01 00 00 00
```

Byte-for-byte comparison: **PASS**. The existing PowerShell safety validator also passed. Parsed DeviceInfo values printed in dry-run output are synthetic test-fixture data, not camera-reported values.

## Fail-closed static review

Static inspection of the hardware code path confirms:

1. The device descriptor must match both VID `04B0` and PID `0223`; without exactly one successfully opened matching PTP device, execution exits before transmission.
2. The Still Image/PTP interface class, subclass, and protocol are checked before endpoint selection and before transmission.
3. Bulk IN and bulk OUT endpoints are required before the device is accepted for execution.
4. USB-open and interface-claim failures terminate without a PTP command.
5. Exactly one GetDeviceInfo command is constructed and submitted. A failed/short bulk OUT transfer exits without retry.
6. Bulk IN timeout, STALL, and other transfer errors terminate the attempt; there is no resend or recovery PTP command.
7. Malformed containers, mismatched transaction IDs, unexpected response codes, and parser failures terminate without another PTP operation.
8. The operation counter checks the limit before incrementing and refuses any count other than one.
9. After a successful interface claim, each error and success path calls `libusb_release_interface`; normal completion then closes the handle and exits libusb without a PTP cleanup command.
10. The only accepted command-line option is `--dry-run`; other arguments are rejected before USB initialization.

No mocked USB tests or physical USB tests were run. These findings are static review plus offline dry-run validation.

## Final status and boundary

**HARDWARE BUILD READY FOR PHASE 3C-5B**

This status means only that the separate USB-enabled executable compiled and passed hardware-independent checks. It is not authorization to run it. The executable was not run in hardware mode; usbipd-win was not installed; the P510 was not attached, claimed, or contacted. Stop here and await separate authorization before Phase 3C-5B.
