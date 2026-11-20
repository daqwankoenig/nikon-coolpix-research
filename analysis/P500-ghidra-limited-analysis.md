# P500 NPROG Limited Ghidra ARM Analysis — Phase 2D-2

## Scope and integrity

This was a bounded static analysis of the P500 NPROG primary section. P500 firmware is reference material only; none of these results establish P510 compatibility or P510 firmware behavior.

| Item | Result |
|---|---|
| Source | `firmware/extracted/P500/sections/P500-NPROG-primary.bin` |
| Source size | 7,471,104 bytes (`0x720000`) |
| SHA-256 | `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29` — matches the required hash after analysis |
| Ghidra program | Separate ARM analysis program in the existing P500 NPROG project |
| Language | `ARM:LE:32:v7` |
| Mapping | `0x00000000`, retained as an offset-oriented temporary mapping |
| Firmware changes | None; no patching, export, reassembly, or firmware modification |
| Hardware interaction | None |

Ghidra's analysis copy remains at offset zero. This is not a runtime-address claim, and the program was not rebased.

## Analysis method and coverage

The run used a conservative analyzer set on bounded, previously identified code/data regions. The enabled analyzers were:

- ARM Constant Reference Analyzer
- Data Reference
- Function Start Search
- Function Start Search After Code
- Reference
- Scalar Operand References
- Stack
- Subroutine References

ASCII Strings ran separately as a strings-only pass over the full image; no other analyzer was enabled for that pass. Emulation, debugging, speculative whole-image code discovery, and automatic rebasing were not used.

| Measure | Result |
|---|---:|
| Bytes in selected noncontiguous code/data regions | 2,236 |
| Instructions in selected regions | 332 |
| Bytes represented by those instructions | 1,328 |
| Approximate instruction-byte coverage of the image | 0.0178% |
| Ghidra function records after the limited run | 44 |
| Function entries in selected regions | 18 |
| High-confidence function bodies under the conservative criterion below | 9 |
| Direct call edges from selected functions | 14 |

The analyzer also created records at call destinations outside the seed regions. Many are one-instruction or empty records and should be treated as unresolved entry candidates, not as 44 validated functions. The 9 high-confidence bodies were selected for coherent ARM instruction flow plus a visible return or terminal path within the bounded body. Generated names were preserved; no descriptive renaming was performed.

High-confidence bodies reviewed:

| Generated name | File offset | Evidence |
|---|---:|---|
| `FUN_00000060` | `0x60` | Coherent zero-fill setup, loop, remainder handling, and return |
| `FUN_000006bc` | `0x6BC` | Prologue, coherent structure initialization, calls, and return |
| `FUN_000009ac` | `0x9AC` | Coherent control flow, data operations, calls, and return |
| `FUN_00000a6c` | `0xA6C` | Coherent control flow, data operations, calls, and return |
| `FUN_0000663c` | `0x663C` | Long coherent body with conditionals, calls, and return |
| `FUN_00009310` | `0x9310` | Coherent body with loops, calls, and return |
| `FUN_0000a43c` | `0xA43C` | Coherent body with data operations, calls, and return |
| `FUN_0000ab54` | `0xAB54` | Coherent loop, indirect call, and return |
| `FUN_0053b34c` | `0x53B34C` | Coherent shift/subtract loop and return; resembles an integer-division helper, but its purpose is not confirmed |

## Findings

### Startup sequence and zero-fill routine

- The first eight words retain the vector-table-shaped ARM branch pattern documented in Phase 2D-1. Their file-relative targets lead to startup and exception-entry code within the extracted section.
- Startup code at file offset `0x20` switches ARM modes and loads mode-specific stack pointers from literals at `0xFC–0x110`. It then continues through startup calls and transfers to code around `0x3D0`.
- `FUN_00000060` provides direct evidence for a zero-fill operation. It loads `0x57EA0000` and `0x57F14028`, computes their difference (`0x74028`), initializes store registers to zero, and performs block stores followed by word/byte remainder handling.
- The zero-fill interval is **`[0x57EA0000, 0x57F14028)`**. This supports a writable RAM/work-area interpretation for the range; it does not make `0x57EA0000` the image base.

### Stack initialization

The startup sequence loads six mode-specific SP values:

`0x57FCA000`, `0x57FCB000`, `0x57FCC000`, `0x57FCD000`, `0x57FCE000`, and `0x57FCF000`.

These are spaced by `0x1000` and support a probable stack/RAM region around `0x57FCA000–0x57FD0000`. The exact allocation boundaries and physical memory type are not established. These stack values are not useful image-base discriminators.

### ROM-to-RAM copying, relocation, and startup tables

- No ROM-to-RAM copy source and destination pair was identified in the analyzed regions.
- No relocation loop, compressed-code loader, or copy descriptor table was confirmed.
- The observed zero-fill is a memory-initialization operation, not evidence of a source-to-destination copy.
- The table at file offset `0x74028` contains aligned address-like words. Their targets can map to coherent code under both leading base hypotheses, so the table does not distinguish them.
- `FUN_0000700c` has a stack-frame prologue followed by 13 direct calls. The analyzed body ends within the bounded region before a return or full continuation is visible. Its overall role and whether it is a complete startup/task-registration routine remain unknown.

### ARM, Thumb, calls, and control registers

- **ARM32 little-endian: STRONGLY SUPPORTED.** The analyzed code contains coherent ARM prologues/epilogues, LDR/STR, STM/LDM, comparisons, conditional branches, direct calls, and CP15 operations.
- CP15 reads/writes appear in code at `0x3F8–0x42C`, including writes using values such as `0x40000037`, `0x50000037`, and `0x60000000`. This supports ARM system/startup code, but does not independently identify a chipset or memory map.
- `BLX r1` appears at `0xA7F0` and `0xABB4`, showing indirect call sites. The called targets are dynamic and were not resolved to odd-valued pointers. These instructions leave ARM/Thumb interworking possible but do **not** establish Thumb code.
- The earlier tested regions were decoded in ARM state. No confirmed Thumb function, odd-valued function pointer, or ARM-to-Thumb transition was found.

### Strings and diagnostics

The strings-only pass found 3,713 ASCII strings, of which 93 matched the analysis search terms. Ghidra reported no code xrefs to the matched strings in this limited run. Because the program remains offset-mapped and indirect references may not resolve, this is not proof that the strings are unused.

Notable P500-section strings include:

- Identity/version: `NIKON DIGITAL CAMERA`, `NIKON CO.,LTD.`, `COOLPIX P500`, `COOLPIX P500V1.1`, `NIKON DSC COOLPIX P500`, and `NIKON DSC COOLPIX P500-PTP`.
- Firmware-related: `CamDownloadFirmwareHandle`, `FIRMWAREBIN`, `FIRMWARE.BIN`, `FIRMWARE`, `Update firmware to newer`, `Update to new firmware?`, `Firmware version`, and `Display the camera firmware version.`
- Errors/diagnostics: `Slave not boot`, `External DDR buffer address error!!!`, `_CopyValidScts : VN_Copy Error!!`, `System error`, `Interface error`, `Lens error`, and multiple `LENS INIT ERROR!` strings.

These are strings found in the P500 reference binary only. Without resolved xrefs, they do not prove a specific update path, loader implementation, or P510 capability.

### Address ranges and image-base hypotheses

| Address/range | Assessment |
|---|---|
| `[0x57EA0000, 0x57F14028)` | Strongly supported as a zero-filled writable work area; not an image-base confirmation |
| `0x57FCA000–0x57FD0000` | Probable mode-stack region based on six loaded SP values; exact bounds/type unknown |
| `0x506ABA00` and nearby values | Referenced as absolute data/stack-related addresses in earlier decoding; memory type and purpose unknown |
| `0x40000000`, `0x50000000`, `0x60000000` in CP15 setup | System-control values; not evidence of an MMIO map |
| ROM/image range | Not established |

No probable MMIO range was established. In particular, the absolute addresses above are not labeled MMIO without supporting register access patterns or documentation.

**`0x57E70000`:** remains a statistical candidate only. It ties the broad pointer scan, and the tested values can map to plausible code offsets under it, but the same references also fit `0x57EA0000`; there is no independent copy-source, string-reference, or memory-map evidence to select it.

**`0x57EA0000` as image base:** evidence weighs against interpreting it as the image base because startup uses it as the beginning of the zero-fill interval. The image-base hypothesis remains unproven; a relocation or aliasing scheme was not ruled out.

**Conclusion:** the ROM/image base remains **UNKNOWN**. No candidate is promoted to SUPPORTED. Keep the Ghidra mapping at `0x00000000`.

## Analyzer recommendation and limits

The limited analyzer set was sufficient for this stage. Additional broad analyzers are not recommended yet: the analyzed instruction coverage is very small, the mapping is offset-only, and the image base is unknown. A future bounded step could manually extend the startup trace or investigate a specific copy/relocation candidate if independent evidence identifies one.

The P510 owner-observed menu version is separately recorded as **Firmware Version 1.0 — CONFIRMED** in [P510-physical-camera-observations.md](P510-physical-camera-observations.md). This P500 analysis does not infer a P510 architecture, build identifier, compatibility, or update availability. The physical P510 was not connected to, updated, or dumped.
