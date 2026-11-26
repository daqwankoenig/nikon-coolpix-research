# Nikon Firmware Tools — Phase 3A Source-Only PTP Audit

**Audit date:** 2026-11-19  
**Scope:** Static inspection only. No build, execution, USB/PTP connection, or camera interaction was performed.

## Repository provenance

- **Repository:** `https://github.com/simeonpilgrim/nikon-firmware-tools`
- **Public status:** Confirmed through GitHub's public repository API (`private: false`, owner `simeonpilgrim`, repository `nikon-firmware-tools`).
- **Branch audited:** `main`
- **Exact commit:** `89ad7354b6d721260b3e999061fefc51f3580ee0`
- **Authorized local clone:** `C:\GitHub\Tools\nikon-firmware-tools\`
- The GitHub API reported this commit for `main` before cloning; the clone's checked-out branch and `HEAD` were verified to match. No submodules were initialized.
- The repository includes prebuilt DLLs and Wireshark installer executables in addition to source. They were not opened, built, decompiled, or executed. The transport DLL implementations therefore remain opaque.

## Executive findings

1. **As checked in, `NikonDump.Main` performs no camera I/O.** Its first action is the local `EepromChecko()` routine, followed immediately by `return`. That routine parses hard-coded sample strings and writes diagnostic text to the console/debug output. The camera enumeration and all subsequent PTP calls in `Main` are unreachable as committed.
2. The unreachable intended path is **not device-identification-only**. After a successful standard `GetDeviceInfo`, it calls a routine that requests Nikon vendor property sets and reads 0x200 bytes of EEPROM. The EEPROM data is written as hexadecimal text to `eeprom_log_<serial>.txt`.
3. Separate, presently uncalled routines implement Nikon service-mode access, arbitrary address reads, broad memory-region dumps, and RAM/EEPROM writes. Thus “dump” in this repository can mean **configuration/property data, EEPROM, or address-space memory**; it does not mean only device information.
4. The code targets other Nikon DSLR models. There is **no P510, P500, or P520 CameraModels profile**. P510 occurs only in two duplicate Wireshark USB product tables; P5100 is listed separately.
5. The codebase is not safe to run as an identification utility: model discovery selects the first WPD device whose ID contains Nikon's VID, without a P510 PID/model check; intended paths enter Nikon service mode and include state-changing and write-capable code.
6. A separate minimal, standard-PTP `GetDeviceInfo (0x1001)`-only design is theoretically possible, but it is **not what `NikonDump` does** and must not be tested during this source-audit phase.

## Repository-wide search

Text search covered the cloned working tree (including hidden/ignored text files, excluding `.git`; binary blobs are not treated as source text). Counts below are case-insensitive occurrence counts. Duplicate Wireshark patches account for repeated product-table entries.

| Search term | Result |
|---|---|
| `P510` / `COOLPIX P510` | Two exact P510 entries, one in each duplicate USB patch: packed ID `0x04b00223`, label `Nikon Coolpix P510`. No P510 match in NikonDump or CameraModels. |
| `P5100` | Listed separately in the same patches as `0x04b00163`, `Nikon Coolpix P5100`; not the P510. |
| `COOLPIX` | 148 occurrences, all in the two USB patch files' camera-name table. |
| `P500` | Two exact entries, one per patch: `0x04b00184`, `Nikon Coolpix P500`. Other substring hits include PTP-property symbols such as `ptpGetProp5001`; these are not P500 camera profiles. |
| `P520` | No exact match. `D5200` does occur, but is a Nikon DSLR model and is not P520. |
| `SG583`, `NPROG`, `NLIPI` | No matches. |
| `NDATA` | 17 substring matches, in generic `...Data...` names such as `CleanDataStore` and `SessionData`; no P510 firmware/component identifier was found. |
| `SFIRM` | Seven matches, including emulator symbol names such as `Build_SFirmStr` and firmware write-protection preference identifiers; no P510 model association. |

The P510 USB-table entry is useful public identification evidence only. It does not imply firmware support, camera-model dispatch, compatibility, or a tested physical-camera VID/PID.

## NikonDump: actual entry point and meaning of “dump”

### Committed entry point

`Main` calls `EepromChecko()` and returns before `FindNikonCamera`, `BaseMTPCamera.Init`, or `ExecuteReadDataEx(0x1001)`. `EepromChecko` only converts hard-coded byte strings and reports comparison output. Therefore:

- **Operations sent by the executable as currently checked in:** none from the PTP code path.
- **Camera-side changes from the current `Main`:** none; it does not enumerate or open a camera.
- **No log file is produced by `EepromChecko`**; its output is console/debug text.

The remaining code is still important for safety review because it is present in the source and would become reachable if the early return were changed or the private routines were wired in.

### Unreachable intended EEPROM path

If execution proceeded past the early return, `FindNikonCamera` would enumerate Windows Portable Devices, select the first device ID matching a USB/compatible-device prefix and containing `vid_04b0`, then pass that ID to `BaseMTPCamera.Init`. It does not filter on product ID or P510 model. Following a successful `GetDeviceInfo`, `Main` calls `Dump_Eeprom_LANG_Test1`:

- Requests four sets through vendor operation `0xFEB1`: sets 1, 2, 3, and 4, with requested lengths `0x03`, `0x80`, `0x80`, and `0x80`.
- Reads EEPROM offsets `0x000`, `0x080`, `0x100`, and `0x180`, each for `0x80` bytes, using a command carried through vendor property `0xFDB2` and operation `0xFEB2`.
- Writes the returned set data and EEPROM bytes as hexadecimal text to `eeprom_log_<serial>.txt` in the process working directory.
- The EEPROM portion is 0x200 bytes. This output is a property/EEPROM log, **not a firmware image or arbitrary firmware-memory dump**.
- The EEPROM read helper first enters service mode and suspends the TMP19 task; the routine later resumes it and requests service-mode exit. These clean-up calls are not protected by `finally`, so an error or interruption could leave camera-side state changed.

### Other “dump” routines in source

These are not called by the committed `Main`:

- `FR_DumpMemory_xFE34` reads caller-supplied address/length ranges in chunks of up to `0x20000` bytes. Its callers include named ranges at `0x00000000`, `0x01000000`, `0x67000000`, `0x80000000`, and `0x90000000`; the larger routines write `.bin` files.
- `FR_DumpMemory_xFE31` reads address/offset ranges in chunks of up to `0x800` bytes. `FR_Dump_all_via_FE31` iterates 64-KiB blocks across a 32-bit address space, writing non-uniform blocks to files.
- `Tmp19_DumpEeprom` contains a separate EEPROM-to-binary routine. Its comment says the length differs between D7000 and D5100; it is not called by `Main`.
- `FR_DumpSet` reads indexed data sets; it is not by itself evidence that those sets are firmware.

The FE31/FE34 routines are genuine **address-space read/dump attempts**. If a target model and address window expose firmware bytes, they could theoretically retrieve some firmware memory. The source does not prove which ranges are ROM/flash, that a complete image is accessible, or that these operations work on any particular model. The implementations use model-specific DSLR addresses and cannot be presumed to work on P510.

## Explicit PTP operation-code inventory

“Read data” below means the source calls `ExecuteReadDataEx` and consumes `MTPDataResponse.Data`; that indicates the intended camera-to-host data direction at the wrapper API. The implementation of `CameraControl.Devices.dll` is unavailable, so the exact USB transaction/data-phase behavior cannot be independently confirmed. `ExecuteWithNoData` calls have operation parameters and a response code but no source-level data payload.

| Operation code | Source parameters and expected result | Classification | Notes / state implications |
|---|---|---|---|
| `0x1001` | No explicit operation parameters. `ExecuteReadDataEx` returns a response whose status is checked. | **STANDARD READ-ONLY PTP** | `GetDeviceInfo`; the only clearly standard identification operation in the C# source. It is after the early return in NikonDump. |
| `0xFC01` | `ExecuteWithNoData`; parameters are zero. Expects response `0x2001` or `0x201E` for the code to mark service mode entered. | **STATE-CHANGING** | Nikon service-mode entry, per source naming and state flag. Not a standard PTP command. |
| `0xFC02` | `ExecuteWithNoData`; parameters are zero. | **STATE-CHANGING** | Nikon service-mode exit. Not standard PTP. |
| `0xFE01`–`0xFE05` | `ExecuteReadDataEx`; `p1=0`, `p2=0x80`, remaining parameters zero; consumes up to 128 returned bytes as a C string. | **NIKON VENDOR READ-ONLY** | Source labels FE01 firmware version, FE02 camera model, FE03 Q-OS version, FE04 B-OS version, FE05 another version string. These are service extensions, not standard properties. |
| `0xFC44` | `ExecuteReadDataEx`; `p1=val`, `p2=0x80`, remaining parameters zero; caller uses the response code. | **UNKNOWN** | Helper is named `FR_FC44_Overscan`; the parameter and name could imply a setting. “ReadData” does not establish read-only behavior. |
| `0xFC46` | `ExecuteReadDataEx`; `p1=val`, other parameters zero; caller uses the response code. | **UNKNOWN** | Helper is named `FR_FC46_Compression`; semantics and side effects are not proven by this source. |
| `0xFEB1` | `ExecuteReadDataEx`; `p1=set ID`, `p2=length`, remaining parameters zero; returns set bytes. Used for sets 1–4 and set `0x34`. | **NIKON VENDOR READ-ONLY** | Set-data read request in the source. It is not a standard PTP operation. |
| `0xFEB2` | `ExecuteReadDataEx`; `p1=0`, `p2=response length`, remaining parameters zero. The preceding `0xFDB2` property payload determines the requested action. | **UNKNOWN** | Appears as a response/data phase for TMP19 RAM/EEPROM/control commands. It cannot be treated as read-only independently of the preceding property write. |
| `0xFE31` | `ExecuteReadDataEx`; `p1=address or model-relative offset`, `p2=length` (model helper chunks at `0x800`), remaining parameters zero; returns bytes. | **NIKON VENDOR READ-ONLY** | Arbitrary/model-mapped memory read interface. Read access may still have effects for memory-mapped hardware; no P510 support is shown. |
| `0xFE34` | `ExecuteReadDataEx`; `p1=address`, `p2=length` (bulk dump helper chunks at `0x20000`), remaining parameters zero; returns bytes. | **NIKON VENDOR READ-ONLY** | Arbitrary address-space read used for broad memory-dump routines. The readable region and whether it is firmware, RAM, or MMIO depend on the target. |
| `0x9201` | `ExecuteWithNoData`; no parameters. | **STATE-CHANGING** | Source calls it “start live view.” |
| `0x9202` | `ExecuteWithNoData`; no parameters. | **STATE-CHANGING** | Source calls it “end live view.” |
| `0x920A` | `ExecuteWithNoData`; no parameters. | **STATE-CHANGING** | Source calls it “start movie.” |
| `0xFDE1` | `ExecuteWithNoData`; first parameter is 1, then 0; remaining parameters zero. | **STATE-CHANGING** | Test helper brackets a delay with the two calls; exact function is undocumented in this source. |
| `0xFE91` | `ExecuteReadDataEx`; `p1=0`, `p2=4`, remaining parameters zero; returns four bytes. | **NIKON VENDOR READ-ONLY** | Screen-state helper. |
| `0xFE93` | `ExecuteReadDataEx`; `p1=0`, `p2=1`, remaining parameters zero; returns one byte. | **NIKON VENDOR READ-ONLY** | Camera-orientation helper. |
| `0xFE00` through `0xFFFE` | A dormant service scan calls `ExecuteWithNoData(code, 0, 0, 0, 0, 0)` for each value in the range and records non-`0x2005` responses. | **UNKNOWN** | Sends hundreds of undocumented operation codes; do not run. Some codes in the range overlap named extensions. |

No direct source call to standard `GetDevicePropValue (0x1015)` or `SetDevicePropValue (0x1016)` was found. The library's `SetProperty` calls are a separate wrapper API; because its implementation is in a binary DLL, this audit cannot establish which underlying PTP opcode(s) it emits.

## Property writes and other write-capable paths

The first argument to `cam.SetProperty` is a **property identifier**, not an operation code. The source passes byte arrays to the camera, so these calls are write operations regardless of the wrapper's hidden transport implementation.

| Property identifier | Source-level use | Classification |
|---|---|---|
| `0xFDB2` | TMP19 command/control mailbox used by the EEPROM/RAM helpers and suspend/resume handling. Payloads distinguish reads, writes, save, and control actions. | **WRITE OPERATION**; some payloads initiate state changes or memory writes. |
| `0xFD31` | Writes bytes to model-specific memory offsets; includes flag/RAM manipulation and other experimental routines. | **WRITE OPERATION** |
| `0xFD34` | Writes bytes to an absolute address in the D5200 DSLR model helper. | **WRITE OPERATION** |

Specific dormant helper code labels operations for EEPROM write, RAM write, and EEPROM save. A commented-out call is not sent by itself, but the callable helpers remain in source. The separate `NikonFlags` program has an interactive read/modify/write loop: it reads a flag byte, computes AND/OR/clear changes, then invokes a model's `WriteBytes` method. Those writes target model-specific RAM. Its service-exit helper is not called on the normal `Main` path.

No explicit CPU register API is present. FE31/FE34 accept addresses and could address MMIO if the target maps it there, but source comments do not establish register semantics.

## Camera models and P510/P500/P520 status

`CameraBase.GetCameraObject` dispatches only these model/version labels:

| Internal model/version | Mapping in source |
|---|---|
| `D7000_103a`, `D7000_104a` | Nikon D7000 firmware variants |
| `D600_101a` | Nikon D600 firmware variant |
| `Q0550_100e` | Nikon D3000 firmware variant |
| `D3100_101b` | Nikon D3100 firmware variant |
| `D5100_101b` | Nikon D5100 DSLR firmware variant |
| `D5200_102` | Nikon D5200 DSLR firmware variant |

There is no P510, P500, or P520 CameraModels dispatch/profile. **D5100 is not COOLPIX P510; D5200 is not COOLPIX P520.** The repo's USB patch lists P510 and P500 product IDs, but that is only a USB name table. The code's device discovery checks Nikon VID `04B0` and does not discriminate P510 PID `0223`.

## Transport, selection, and prerequisites

- **Transport path:** Source uses `PortableDeviceCollection`, `PortableDevice`, `DeviceDescriptor`, `BaseMTPCamera`, and `PortableDeviceLib`; the NikonCameraControl directory contains DLLs plus a readme pointing to Google Code SVN revision 701, but no transport source.
- **Device selection:** Enumerates Windows Portable Devices with auto-connect disabled, considers IDs beginning with `\\?\usb` or `\\?\comp`, then selects the first ID containing `vid_04b0`. It extracts a serial-number component by splitting the ID string. There is no P510 model or PID check.
- **Session behavior:** `BaseMTPCamera.Init` and any underlying PTP session/open/close operations are implemented in unavailable DLLs. Exact connection lifecycle and any hidden operations cannot be audited from source.
- **Properties:** No direct `GetDevicePropValue` call exists in the reviewed C# sources. `SetProperty` is used for camera-directed data writes.
- **Platform:** NikonDump and CameraModels target legacy **.NET Framework 4.0 Client Profile**, with NikonDump configured x86. They reference `CameraControl.Devices.dll`, `PortableDeviceLib.dll`, and Windows Portable Device COM interop DLLs.
- **Driver/privilege evidence:** The source points to the Windows Portable Devices/MTP stack. No libusb or WinUSB dependency, driver replacement procedure, or administrator-rights requirement is specified in the reviewed project files. Windows camera/WPD driver availability is an environmental prerequisite; the exact requirements of the binary wrapper are unknown.
- Git was installed only after explicit approval, to perform the requested clone. No Nikon utility, firmware tool, driver, or project/runtime prerequisite was installed. No project was built.

## Could this retrieve firmware memory?

**Theoretically, some code paths could retrieve bytes from an address range.** The FE31/FE34 helpers accept addresses and lengths and write returned data to binary files; the code includes broad memory scans. If an applicable model exposes executable flash/ROM through those address windows, some firmware bytes could be returned.

This is not evidence of a complete, exact firmware dump:

- no source proves the address windows map to firmware;
- code is tailored to DSLR models and contains no P510 profile;
- an address-space dump could include RAM, MMIO, unmapped ranges, or repeated/error data;
- the low-level transport and response handling are partly hidden in DLLs;
- other routines explicitly alter camera state or write RAM/EEPROM.

Accordingly, do not use these routines to acquire P510 firmware.

## Can a safe device-identification-only test be designed?

**In principle, yes:** a separately designed, minimal Windows PTP client could request only standard `GetDeviceInfo (0x1001)`, record the returned model/device-version/vendor-extension strings, and stop without issuing Nikon vendor operations or property writes. The repository's P510 USB-table entry suggests a candidate ID, but the physical P510's USB descriptors remain unverified.

**NikonDump itself is not that test.** Its committed entry point currently does nothing on the camera; its unreachable normal flow continues into vendor set/EEPROM reads and TMP19 state changes; its transport DLL internals are unavailable; and device selection is not P510-specific. No such test was created or run. Any physical connection remains subject to separate explicit approval.

## Recommendation

**STANDARD PTP IDENTIFICATION ONLY** — as a possible separately approved future experiment, using a minimal implementation limited to standard `GetDeviceInfo (0x1001)`. Do not run NikonDump, NikonFlags, the service scan, memory-dump helpers, or any SetProperty/vendor-operation path. **No camera test was performed during this audit.**

## Source references

All source references below are pinned to the audited commit:

- [NikonDump entry point and EEPROM routines](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/NikonDump/Program.cs)
- [CameraModels base, read/write helpers, and model dispatch](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/CameraModels/Base.cs)
- [Nikon vendor command helpers](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/CameraModels/PtpCommands.cs)
- [NikonFlags interactive tool](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/NikonFlags/NikonFlags.cs)
- [D3000/D3100 models](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/CameraModels/D3x00_models.cs), [D5100](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/CameraModels/D5100_models.cs), [D5200](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/CameraModels/D5200_model.cs), [D600](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/CameraModels/D600_models.cs), and [D7000](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/CameraModels/D7000_models.cs) profiles.
- [NikonCameraControl dependencies/readme](https://github.com/simeonpilgrim/nikon-firmware-tools/tree/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/NikonCameraControl)
- [USB/PTP Wireshark patch with P510/P500/P5100 IDs](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/USB/wireshark/release/wireshark_usb_ptp_20130305.patch)
- [NikonDump project target/dependencies](https://github.com/simeonpilgrim/nikon-firmware-tools/blob/89ad7354b6d721260b3e999061fefc51f3580ee0/PTP%20Tools/NikonDump/NikonDump.csproj)
