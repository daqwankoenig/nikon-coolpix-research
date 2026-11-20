# P510 Phase 3C-5A.2: WSL Build Environment and Offline Validation

**Status: READY FOR PHASE 3C-5B**

**Safety boundary:** No camera communication, PTP command, USB attachment, USB binding, interface claim, or USB transfer was performed. Phase 3C-5B was not started.

## WSL and Linux environment

- Windows: Windows 10 Enterprise, build `26340.10013`
- WSL version: `3.0.5.0`
- WSL kernel: `6.18.58.1-1`
- Default WSL version: `2`
- Distribution: Ubuntu `24.04.5 LTS`
- Linux kernel reported by Ubuntu: `6.18.58.1-microsoft-standard-WSL2`
- Non-interactive command execution succeeded.
- Current Linux user: `<LOCAL_USER>` (`uid=1000`, `gid=1000`)

## Installed packages and toolchain

Only the authorized build dependencies were installed:

| Package/tool | Version |
|---|---|
| `build-essential` | `12.10ubuntu1` |
| `pkg-config` | `1.8.1-2build1` |
| `libusb-1.0-0-dev` | `2:1.0.27-1` |
| libc (`libc6`) | `2.39-0ubuntu8.12` |
| GCC | `13.3.0-6ubuntu2~24.04.1` |
| libusb-1.0 | `1.0.27` |

No gphoto2/libgphoto2 camera tools, libmtp, NikonDump, or usbipd-win were installed. `usbipd-win` was not found on the Windows command path.

## Source integrity and changes

Before editing or compiling, `P510PTPGetDeviceInfo.c` matched the required known SHA-256:

```text
949D57FAB8799BA56D6E847664A98A877FBBFF845EBDCB9F8FBFC485A4849144
```

The initial strict build exposed `strdup` declaration/type warnings. The following directly related changes were made:

1. Define `_POSIX_C_SOURCE 200809L` so `strdup` has its proper declaration under strict C11.
2. Increase the PTP UTF-16 string expansion buffer to allow six-character `\\uXXXX` escapes per input character.
3. Print the exact command bytes in dry-run and hardware-path logs.
4. Reject a `GetDeviceInfo` response container unless its declared and received lengths are exactly the 12-byte PTP header.
5. Classify MTP/vendor-specific operation values before the broader vendor-specific range.

No safety control was removed or weakened. The final source SHA-256 is:

```text
DE0B903F0A37E449857E3DFACF6E8F23A7999EE3ABFFE3545BE80E8CDCEAAA74
```

## Build

The executable was built in the ignored `build/` directory with USB support disabled:

```sh
cd '/mnt/c/GitHub/Nikon P510/scripts'
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -DP510_ALLOW_USB=0 \
  P510PTPGetDeviceInfo.c -o ../build/P510PTPGetDeviceInfo-offline
```

The final build completed with no warnings or errors. The earlier build, before the portability fix, produced `strdup` implicit-declaration and pointer-conversion warnings; those were resolved rather than suppressed.

Executable:

```text
build/P510PTPGetDeviceInfo-offline
SHA-256: E5F6305AF37809330FD294CC27B43BC39085F538086B8281BC7A1E067EEF4BB5
```

No additional project source files were linked. `ldd` showed only libc and the Linux loader; libusb is not a dynamic dependency of this USB-disabled executable.

## Hardware-independent validation

The compiled executable ran in offline mode. It reported one operation, the `0x1001` allowlisted operation, and a 12-byte command:

```text
OperationCount=1
AllowedOperations=0x1001
OutgoingContainerLength=12
OutgoingContainerType=0x0001
OutgoingOperation=0x1001
OutgoingTransactionID=1
SessionID=0
OutgoingBytes=0C 00 00 00 01 00 01 10 01 00 00 00
```

Expected request:

```text
0C 00 00 00 01 00 01 10 01 00 00 00
```

The executable's printed bytes were compared byte-for-byte with the expected request: **PASS**. The existing `Validate-P510PTPGetDeviceInfo.ps1` also passed and emitted the same normalized bytes.

The executable additionally parses a synthetic offline DeviceInfo fixture. Its displayed fields are test data, not camera-reported information.

## Safety-control verification

- VID remains fixed at `0x04B0`; PID remains fixed at `0x0223`.
- The only transmitted operation constant is `GetDeviceInfo`, `0x1001`.
- The operation limit remains `1`.
- Hardware access defaults to disabled and the build explicitly used `-DP510_ALLOW_USB=0`.
- USB code is excluded from this build; the executable has no libusb dependency.
- `main` accepts no operation-code arguments; no arbitrary-operation CLI exists.
- There is no reachable OpenSession, Nikon vendor operation, storage/object enumeration, capture, property write, object upload/delete, firmware, or memory-access route.
- The `0x1002` value appears only in the synthetic parser fixture as a sample supported-operation value; it is not transmitted.
- Static inspection confirms fail-closed handling for absent/mismatched devices, unsupported interfaces, missing bulk endpoints, USB open/claim/transfer failures, timeouts, malformed or oversized/truncated containers, transaction-ID mismatches, unexpected response codes, and DeviceInfo parser rejection. No hardware mocking or USB test was performed.

## Phase 3C-5B readiness and remaining risks

**READY FOR PHASE 3C-5B** means the client compiled cleanly and passed offline validation. It does not authorize or perform any camera interaction.

`usbipd-win` is not installed. Any required USB-forwarding setup remains for a separately authorized phase. The P510's actual DeviceInfo response and whether it accepts this standard operation without OpenSession remain unverified. No Phase 3C-5B action may occur without explicit authorization.
