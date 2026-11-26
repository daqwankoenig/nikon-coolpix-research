# P510 Phase 3C-5A.1: Offline Build and Validation

**Status:** NOT READY for Phase 3C-5B. No executable was compiled.

**Safety status:** No camera communication, USB attachment, interface claim, or USB transfer was performed.

## Environment inspection

| Requirement | Result |
|---|---|
| WSL executable | Present as `C:\WINDOWS\system32\wsl.exe` |
| WSL distribution/runtime | **NOT INSTALLED**; `wsl.exe --status` returned “The Windows Subsystem for Linux is not installed.” |
| gcc | Not found on PATH or in inspected standard directories |
| clang | Not found on PATH or in inspected standard directories |
| make | Not found on PATH |
| pkg-config | Not found on PATH |
| MSVC `cl.exe` | Not found on PATH; no Microsoft Visual Studio installation directory was present in the standard locations inspected |
| libusb-1.0 development headers | Not found in inspected standard directories |
| libusb-1.0 development library | Not found in inspected standard directories |
| libusb-1.0 pkg-config metadata | Not available because pkg-config/libusb development files are missing |

## Missing items

The build/compile step requires, at minimum:

- a C compiler: gcc, clang, or MSVC
- libusb-1.0 development header `libusb-1.0/libusb.h`
- a libusb-1.0 development/import library
- optionally a compatible `make`/build environment

WSL, gcc/clang, make, pkg-config, and libusb-1.0 development files are missing or unavailable. No software was installed.

## Build attempt

No compile command was executed because no compiler and no libusb development environment were available.

The following phase-appropriate build command remains unexecuted:

```text
<compiler> -std=c11 -Wall -Wextra -Wpedantic -DP510_ALLOW_USB=0 \
  P510PTPGetDeviceInfo.c -o P510PTPGetDeviceInfo-offline
```

This offline build remains a future command only. `P510_ALLOW_USB=0` prevents the hardware branch from being compiled as active.

## libusb version

**UNKNOWN / NOT AVAILABLE.** No libusb headers or library were present.

## Compiler warnings and errors

**None generated.** Compilation was not attempted because the required compiler and libusb development files were missing.

## Source changes

No source changes were made for this build attempt.

Existing source remains hardware-disabled by default:

- `P510_ALLOW_USB=0`
- fixed VID `0x04B0`
- fixed PID `0x0223`
- fixed operation `0x1001`
- fixed operation limit `1`
- fixed transaction ID `1`
- no command-line operation argument

## Hardware-independent validation

The existing PowerShell validator was run:

```text
Offline packet validation passed
OutgoingContainer=12 0001 1001 01000000
NormalizedHex=0C 00 00 00 01 00 01 10 01 00 00 00
```

This validation constructs only a byte array and performs static safety checks. It does not enumerate, open, claim, or transfer to any USB device.

### Exact 12-byte request

| Offset | Hex | Field |
|---:|---|---|
| 0-3 | `0C 00 00 00` | Container length = 12 |
| 4-5 | `01 00` | Container type = command |
| 6-7 | `01 10` | Operation code = `0x1001` |
| 8-11 | `01 00 00 00` | Transaction ID = 1 |

Complete byte string:

```text
0C 00 00 00 01 00 01 10 01 00 00 00
```

The byte-for-byte result matches the Phase 3C-5A expected request exactly.

## Safety-control verification

| Control | Static result |
|---|---|
| Hardware disabled default | Present: `P510_ALLOW_USB=0` |
| Fixed VID | Present: `0x04B0` |
| Fixed PID | Present: `0x0223` |
| Fixed operation | Present: `0x1001` |
| Operation maximum | Present: `1` |
| Transaction ID | Fixed: `1` |
| Session ID | Fixed: `0` |
| Arbitrary command-line operation | Not implemented |
| Nikon vendor operation input | Not implemented |
| OpenSession | No implementation; source contains no transmitted `0x1002` operation |
| CloseSession | No implementation; source contains no transmitted `0x1003` operation |
| Storage/object/property/capture operations | No implementation or command-line route |
| Memory/firmware operations | No implementation |
| USB hardware branch | Guarded by `P510_ALLOW_USB`; default is disabled |

Static source inspection confirms that the only constructed PTP outgoing container is the 12-byte `GetDeviceInfo` command.

## Error-handling verification

The source was statically inspected for fail-closed behavior:

| Condition | Existing behavior |
|---|---|
| Missing/unexpected device | `matches` must equal exactly one; otherwise terminate |
| Wrong VID/PID | Device descriptor check rejects mismatch |
| Unexpected interface | Requires class 6/subclass 1/protocol 1 |
| Missing bulk IN or bulk OUT | Refuses before command transfer |
| USB open failure | Refuses and does not continue |
| Interface claim failure | Returns failure and releases/closes as applicable |
| Timeout | Bulk transfer failure/short transfer aborts |
| Malformed PTP response | Container length/type/code and parser checks reject |
| Mismatched transaction ID | Terminates immediately |
| Unexpected response code | Requires PTP OK `0x2001` |
| Oversized response | Raw buffer is bounded to 1 MiB |
| Truncated response | Short bulk read/no PTP OK terminates |

All hardware failures require an explicit return/termination before another PTP operation can be sent.

## Hashes

### Source

```text
P510PTPGetDeviceInfo.c
SHA-256: 949D57FAB8799BA56D6E847664A98A877FBBFF845EBDCB9F8FBFC485A4849144
```

### Existing validator

```text
Validate-P510PTPGetDeviceInfo.ps1
SHA-256: 19F59204B53ECFA6522C90220DE77F4FF317CF8C6344AB181512AD947C009B22
```

### Compiled executable

**NOT GENERATED; executable SHA-256 is unavailable.**

### Any other source incorporated

**None.** The offline client was not compiled or linked, and no external source was incorporated.

## Remaining risks

- No native C compiler or libusb development environment is available.
- No executable warning/build verification is possible in the current environment.
- WSL is not installed.
- The hardware-enabled branch has not been compiled.
- The P510 may require session management despite `GetDeviceInfo` being a standard PTP command; this remains unverified.
- The source's synthetic offline parser is not a replacement for raw PTP packet testing.

## Readiness

**NOT READY for Phase 3C-5B.**

Phase 3C-5B remains blocked until a compiler and libusb development environment are available, the hardware-disabled executable/source is compiled and reviewed, and separate authorization is given for camera/USB communication.
