# P500 NPROG Expanded Static Analysis — Phase 2D-3

## Scope and integrity

This was a bounded, read-only expansion of the P500 NPROG primary-section analysis. P500 firmware remains reference material only; none of these results establish P510 firmware behavior or compatibility.

| Item | Result |
|---|---|
| Source | `firmware/extracted/P500/sections/P500-NPROG-primary.bin` |
| Size | 7,471,104 bytes (`0x720000`) |
| SHA-256 | `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29` — verified |
| Ghidra language | `ARM:LE:32:v7` |
| Ghidra program | Existing `/ARM-Validation/P500-NPROG-primary.bin` analysis program |
| Mapping | `0x00000000`, retained as an offset-oriented temporary mapping |
| Image-base conclusion | UNKNOWN; no rebasing |
| Source changes / export | None |
| Emulation / hardware | None; no camera communication |

Analysis began from the 23 previously selected strong/likely code regions. The bounded call-expansion pass examined 35 targets, accepted 20 for further decoding, and rejected 15 when structural checks failed. Recursion was limited to depth 3 and instruction windows were bounded; this was not whole-image disassembly or full automatic analysis. In the Ghidra analysis copy only, byte-sized data units at `0x706C–0x70C7` were cleared and manually decoded after their source words were checked. The firmware source was not changed.

## Findings

### 1. Functions identified

Ghidra contains **45 function records** after adding a function boundary for the verified byte-copy loop at `0x70AC`. Empty or very short records created at unresolved call destinations are included in that count and are not validated functions.

**17** records meet the conservative inventory heuristic: at least eight instructions, a recognizable stack-frame/prologue pattern, and coherent terminal/return flow. This is a structural heuristic, not a count of semantically understood routines. Two additional short leaf routines at `0x70AC` and `0x70C8` are strong code/helper candidates despite lacking a stack prologue.

Generated function names were preserved. Descriptive names were not assigned.

### 2. Approximate instruction/code coverage

The bounded listing contains **3,872 instruction bytes**, approximately **0.0518%** of the 7,471,104-byte image. This is sparse coverage and does not imply the remaining bytes are data. The string pass identified 3,713 ASCII strings; 585 matched the targeted keyword expression. Ghidra reported **zero code xrefs** to those matched strings in this offset-mapped program. This may reflect unresolved references or the temporary mapping and does not prove that the strings are unused.

### 3. ARM/Thumb status

- **ARM32 little-endian remains STRONGLY SUPPORTED** by coherent startup, calls, conditional control flow, LDR/STR, STM/LDM, and returns across independent regions.
- **Thumb and ARM/Thumb interworking remain UNESTABLISHED.**
- `BLX r1` appears at `0xA7F0` and `0xABB4`, but neither target resolves statically. These instructions alone do not establish Thumb code.

### 4. Startup sequence

The vector-shaped branch words at file offsets `0x00–0x1C` lead into bounded startup/exception code. At `0x20`, startup changes ARM modes and loads mode-specific stack pointers before continuing through calls and code around `0x3D0`.

`FUN_0000700c` now decodes through `0x7090` as a 34-instruction routine with 16 direct calls. Its expanded tail includes calls to `0x7694`, `0x7948`, and `0x03CC`. The source word at `0x03CC` is `0xEAFFFFFE`, an ARM branch-to-self. Thus the call to `0x03CC` appears non-returning under the offset mapping, despite a return instruction later at `0x7090`; that control-flow anomaly remains unexplained and is not evidence for a runtime base.

The adjacent sequence at `0x7094–0x70A8` contains three calls and branches to `0x03E0`, whose source word is also a branch-to-self. Its boundary and purpose remain uncertain; it was not given a descriptive name.

### 5. Zero-fill routines

The previously validated startup routine at `0x60` initializes the interval **`[0x57EA0000, 0x57F14028)`** to zero. This is strong evidence for a writable work area, not for the firmware image base.

The short routine at `0x70C8` also implements a byte-zeroing loop and is called from structure/array initialization code, including bounded routines around `0x86E4` and `0x9A58`. This is a helper-level finding and is distinct from the startup fill of the large address interval above.

### 6. Stack initialization

Startup loads mode-specific SP values:

`0x57FCA000`, `0x57FCB000`, `0x57FCC000`, `0x57FCD000`, `0x57FCE000`, and `0x57FCF000`.

Their regular spacing supports a probable stack/RAM region around `0x57FCA000–0x57FD0000`; exact allocation boundaries and physical memory type remain unknown.

### 7. ROM-to-RAM copy evidence

No ROM-to-RAM source/destination pair, relocation loop, compressed-code loader, or initialization descriptor table was established.

The separate leaf routine at `0x70AC` is a strong byte-copy helper candidate: it loads a byte from the source pointer, advances it, stores the byte through a destination pointer, advances that pointer, decrements a positive count, loops, and returns. Its existence does **not** show that it participates in startup relocation; no source-address table or ROM-to-RAM call relationship was established.

### 8. Probable RAM ranges

| Range / values | Evidence and limits |
|---|---|
| `[0x57EA0000, 0x57F14028)` | Explicitly zero-filled at startup; probable writable RAM/work area |
| `0x57FCA000–0x57FD0000` | Six mode-specific SP values; probable stack/RAM range, exact boundaries unknown |
| `0x506ABA00` and nearby values | Used as absolute data/stack-related references in exception code; memory type and purpose unknown |

### 9. Possible MMIO ranges

No probable MMIO address range was established. CP15 operations and constants such as `0x40000037`, `0x50000037`, and `0x60000000` occur in startup/system-control code, but they are not evidence of peripheral mappings. No repeated fixed-address peripheral access pattern was validated.

### 10. Important strings and code references

Strings are P500-section evidence only. Selected examples and file offsets include:

- **Model/protocol identity:** `COOLPIX P500` (`0x649470`), `NIKON DSC COOLPIX P500` (`0x6497B4`), and `NIKON DSC COOLPIX P500-PTP` (`0x6497CC`).
- **PTP/MTP:** `CommonAPI_OpenFilePtp` (`0x649064`), `Ptp_ObjectFileOpenForImageInfo` (`0x649244`), `MTP_Connect` (`0x649340`), and a cluster of `NK_APLI_MtpObjPropDesc_*` / `NK_APLI_MtpObjPropValue_*` strings around `0x648684–0x64903C`.
- **Firmware-related:** `CamDownloadFirmwareHandle` (`0x61F53C`), `FIRMWAREBIN` (`0x6202F8`, `0x620324`), `FIRMWARE.BIN` (`0x620CB0`), `Update firmware to newer` (`0x6E4D80`), and `Firmware version` (`0x6ECB38`).
- **Storage/tasking:** `Virtual NAND Creation Error` (`0x5FE378`), `Operation Queue Creation Error` (`0x5FE3F0`), repeated semaphore acquisition/release diagnostics around `0x5FFxxx–0x601xxx`, and `lens_mtr_drv_master_task_start` (`0x602CD8`).
- **Image/video processing:** `MMemAlloc pStitch->ppImage error.` (`0x5202B0`), related stitch allocation errors nearby, `MMemAlloc pVideoCapture error.` (`0x51EDB4`), and video/JPEG/RAW-related strings elsewhere in the image.

The strings suggest P500 storage/NAND, tasking, camera-transfer, firmware-menu, and image-processing components, but the offset-mapped Ghidra program has no code xrefs to the matched-string set. They do not identify a particular caller, prove an update mechanism, or establish that a component is used by the P510.

### 11. Possible initialization tables

The aligned address table at file offset `0x74028` begins with values including `0x57EF0280`, `0x57EF0288`, `0x57EF0284`, and `0x57EF028C`. Under either prior base hypothesis, these values map to regions with plausible ARM-looking code, so the table does not distinguish the hypotheses. It is not confirmed as a startup copy table.

Several expanded routines initialize bounded arrays or records. Examples include a 64-entry loop using `0x74`-byte records near `0x86E4`, two structures near `0x9A58`, and loops around `0x8C58`, `0x9F80`, `0xA68C`, `0xA704`, and `0xAB0C`. Their higher-level purposes remain unknown.

### 12. Address clusters

- **Probable writable RAM:** `[0x57EA0000, 0x57F14028)`.
- **Probable stack region:** `0x57FCA000–0x57FD0000`.
- **Unknown absolute data/stack references:** `0x506ABA00` and nearby values.
- **ROM/code runtime range:** not established. Decoded branch destinations in the Ghidra program are file-offset-oriented addresses, not confirmed runtime addresses.
- **MMIO:** no range established.

### 13. BLX and function-pointer findings

At `0xA7F0`, `BLX r1` follows a load of a function-pointer-like field from `[r4+0x18]`. At `0xABB4`, `BLX r1` follows a load from `[r4+0x1C]` while traversing records. These patterns are consistent with callback/function-pointer slots, but their values are runtime-dependent and no target flow was resolved. They do not establish a function-pointer table, a Thumb target, or ARM/Thumb interworking.

### 14. Runtime image-base evidence

No new runtime image-base evidence was found.

- **`0x57E70000`:** remains a statistical candidate only. Address-table values can map to plausible ARM-looking regions under this base, but also under `0x57EA0000`; no independent startup reference selects it.
- **`0x57EA0000`:** evidence continues to support it as the start of the startup zero-filled writable range, not as the firmware image base.
- **Other candidates:** none earned support. Stack values and file-offset branch targets do not establish a ROM base.

The ROM/image base remains **UNKNOWN**. Do not rebase; retain the temporary mapping at `0x00000000`.

### 15. Subsystems suitable for targeted follow-up

The primary section has enough leads to begin **narrow, subsystem-specific P500 investigation**, but it is not globally understood. The most promising static leads are:

1. PTP/MTP transfer and object-property handling.
2. Storage/filesystem, virtual-NAND, queue, and semaphore code.
3. Stitching/panorama and video/JPEG/RAW processing.
4. Lens-motor task initialization.
5. Firmware-version and update-related strings.

Because string xrefs are unresolved and the image base remains unknown, follow-up should first map bounded code and data relationships around selected subsystems. Firmware/update strings alone do not demonstrate an exploitable or P510-compatible update path.

### 16. Whether SG583SLAVE should be next

**No—not as the immediate next analysis step.** Continue with a bounded P500 primary-section subsystem investigation to resolve references and identify what the new strings and callbacks actually connect to. SG583SLAVE may be considered later as a separate component; this phase did not analyze it.

## P510 boundary

The owner-observed **Nikon COOLPIX P510 Firmware Version 1.0** remains **CONFIRMED** and is recorded separately in [P510-physical-camera-observations.md](P510-physical-camera-observations.md). No P500 result here is transferred to the P510. The P510 was not updated, dumped, connected, or contacted.
