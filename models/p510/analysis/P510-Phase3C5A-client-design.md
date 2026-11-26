# P510 Phase 3C-5A: Minimal GetDeviceInfo Client Design

**Status:** Offline design and static validation complete. No camera, USB interface, PTP operation, or third-party USB tool was used.

## Client files

- [P510PTPGetDeviceInfo.c](../scripts/P510PTPGetDeviceInfo.c)
- [Validate-P510PTPGetDeviceInfo.ps1](../scripts/Validate-P510PTPGetDeviceInfo.ps1)

Source SHA-256:

- `949D57FAB8799BA56D6E847664A98A877FBBFF845EBDCB9F8FBFC485A4849144`

Validator SHA-256:

- `19F59204B53ECFA6522C90220DE77F4FF317CF8C6344AB181512AD947C009B22`

## Pinned upstream reference

- Repository: `https://github.com/gphoto/libgphoto2`
- Exact master commit used for offline source research: `31a2f4089f19aec6caca7920b03e3eb7a251c5b6`
- Commit date: 2026-11-13
- Pinned source URLs:
  - `https://github.com/gphoto/libgphoto2/blob/31a2f4089f19aec6caca7920b03e3eb7a251c5b6/camlibs/ptp2/ptp.h`
  - `https://github.com/gphoto/libgphoto2/blob/31a2f4089f19aec6caca7920b03e3eb7a251c5b6/camlibs/ptp2/ptp.c`
  - `https://github.com/gphoto/libgphoto2/blob/31a2f4089f19aec6caca7920b03e3eb7a251c5b6/camlibs/ptp2/ptp-pack.c`
  - `https://github.com/gphoto/libgphoto2/blob/31a2f4089f19aec6caca7920b03e3eb7a251c5b6/camlibs/ptp2/usb.c`

The client is derived conceptually from these structures and functions, but it is a purpose-built C implementation with no copied camera-specific fixup or vendor table.

## PTP structures and functions used

The upstream implementation establishes:

- `PTPUSBBulkContainer`
  - 32-bit container length
  - 16-bit container type
  - 16-bit operation or response code
  - 32-bit transaction ID
  - parameter or data payload
- `PTP_OC_GetDeviceInfo = 0x1001`
- `PTP_OC_OpenSession = 0x1002`
- `PTP_OC_CloseSession = 0x1003`
- `ptp_transaction_new`
  - assigns transaction ID and session ID
  - sends request
  - performs data direction
  - waits for response
- `ptp_unpack_DI`
  - decodes all standard `DeviceInfo` fields and arrays
- `ptp_unpack_string`
  - decodes PTP UCS-2 strings
- `ptp_unpack_uint16_t_array`
  - decodes arrays counted by a 32-bit element count

The source also shows PTP USB bulk containers use little-endian fields.

## GetDeviceInfo before OpenSession

The PTP required-command reference identifies `GetDeviceInfo (0x1001)` as a mandatory PTP command and separately identifies `OpenSession (0x1002)` as a session command.

The upstream libgphoto2 transaction mechanism can construct `GetDeviceInfo` with a zero-parameter command container and `SessionID=0`. This client does not add `OpenSession`.

This is not P510-specific evidence that pre-session `GetDeviceInfo` succeeds. The future execution must:

- send the command exactly once
- reject any unexpected data or response
- stop if PTP returns a session-required or unexpected response
- not retry with `OpenSession`

No source finding showed P510 requiring `OpenSession` for GetDeviceInfo, but P510 acceptance remains UNKNOWN.

## USB/PTP packet format

The outgoing command container is 12 bytes:

| Offset | Size | Little-endian value | Meaning |
|---|---:|---|---|
| 0 | 4 | `0x0000000C` | Container length |
| 4 | 2 | `0x0001` | Command container |
| 6 | 2 | `0x1001` | GetDeviceInfo |
| 8 | 4 | `0x00000001` | Transaction ID |

Raw normalized outgoing bytes:

```text
0C 00 00 00 01 00 01 10 01 00 00 00
```

There are no operation parameters.

Container values used during receive:

- `0x0002`: data container
- `0x0003`: response container
- `0x2001`: PTP OK

## Endpoint selection

The hardware-enabled source, compiled only with `P510_ALLOW_USB=1`, will:

1. Enumerate libusb devices.
2. Reject unless exactly one device has VID `04B0` and PID `0223`.
3. Inspect active USB configuration descriptors.
4. Accept only an interface with:
   - class `6`
   - subclass `1`
   - protocol `1`
5. Require one bulk IN endpoint and one bulk OUT endpoint.
6. Record an interrupt endpoint if present, but never read or write it.
7. Refuse if the interface is missing or ambiguous.
8. Claim only the selected interface.
9. Never detach a kernel driver; Phase 3C-5B will operate in WSL where Windows WPD ownership is already detached through a reversible USB forwarding step.

The default source build has `P510_ALLOW_USB=0`. It contains no USB hardware path and runs only its synthetic offline parser.

## Operation allowlist

The only allowed operation constant is:

```c
#define PTP_OC_GET_DEVICE_INFO 0x1001u
#define P510_OPERATION_LIMIT 1u
```

The utility source has no generic operation input, no arbitrary opcode parser, no Nikon vendor table, no session helper, and no object/storage/property/capture/memory/firmware interface.

The offline source intentionally includes no implementation of OpenSession, CloseSession, storage/object, property-write, capture, upload/download, deletion, memory, or firmware operations.

The hardware code increments an operation counter immediately before sending and refuses a second operation.

## Transaction construction

The fixed transaction uses:

- Session ID: `0`
- Transaction ID: `1`
- Data direction: device to host
- Operation parameters: zero
- Response: PTP OK `0x2001`

The data phase is expected to contain one or more PTP data containers with code `0x1001` and the fixed transaction ID. The response phase must then contain response container code `0x2001` and the fixed transaction ID.

The source rejects unexpected transaction IDs, unexpected container types, unexpected operation codes, oversized raw data, and missing PTP OK.

## DeviceInfo parser

The parser reproduces the relevant libgphoto2 `ptp_unpack_DI` field order:

1. 16-bit `StandardVersion`
2. 32-bit `VendorExtensionID`
3. 16-bit `VendorExtensionVersion`
4. PTP string `VendorExtensionDesc`
5. 16-bit `FunctionalMode`
6. 32-bit-counted array of 16-bit `OperationsSupported`
7. 32-bit-counted array of 16-bit `EventsSupported`
8. 32-bit-counted array of 16-bit `DevicePropertiesSupported`
9. 32-bit-counted array of 16-bit `CaptureFormats`
10. 32-bit-counted array of 16-bit `ImageFormats`
11. PTP UCS-2 string `Manufacturer`
12. PTP UCS-2 string `Model`
13. PTP UCS-2 string `DeviceVersion`
14. PTP UCS-2 string `SerialNumber`

The raw payload is saved before parsing as `P510-GetDeviceInfo.raw.bin`.

Output redacts `SerialNumber` in human-readable text. Vendor-specific operation/event/property codes are retained numerically and not interpreted or executed.

## Verbose logging

The source prints:

- selected USB identity
- selected interface number
- bulk IN address
- bulk OUT address
- interrupt address, if present
- operation count
- outgoing container length/type/code
- transaction ID
- session ID
- each received container length/type/code/transaction ID
- PTP response code
- parsed fields
- redacted serial number

## Expected successful transaction

```text
01. Bulk OUT command: GetDeviceInfo, transaction 1, zero parameters
02. Bulk IN data container(s): code 1001, transaction 1, raw DeviceInfo bytes
03. Bulk IN response container: code 2001, transaction 1
04. Save raw data
05. Parse and print fields
06. Release interface and close libusb
```

No PTP session is opened or closed.

## Expected failure cases

| Failure | Required action |
|---|---|
| VID/PID is not exactly 04B0:0223 | Refuse |
| Multiple matching devices | Refuse |
| No 06/01/01 interface | Refuse |
| Missing bulk IN or bulk OUT | Refuse |
| Unexpected transaction ID | Refuse |
| Unexpected container type/code | Refuse |
| Response not PTP OK | Refuse |
| DeviceInfo parser rejects structure | Save raw payload, report parse failure |
| Attempt to execute another operation | Operation counter refuses |
| libusb cannot claim interface | Refuse and close |

## Validation performed

The PowerShell validator:

- checked the fixed VID/PID/opcode/operation-limit constants
- checked the hardware-disabled default
- checked for forbidden PTP implementation names
- constructed the exact 12-byte little-endian command
- verified opcode `0x1001`
- verified transaction ID `1`

Result:

```text
Offline packet validation passed
OutgoingContainer=12 0001 1001 01000000
NormalizedHex=0C 00 00 00 01 00 01 10 01 00 00 00
```

No native C compiler or libusb development package was available locally. No compiler/package installation was performed. Therefore this is an offline source/static validation, not a compiled executable or hardware execution.

## Safety conclusion

The source is hardware-disabled by default, uses one fixed operation, sends no session command, and has no reachable generic/vendor operation interface. It is suitable for future source review and a separately approved build only.
