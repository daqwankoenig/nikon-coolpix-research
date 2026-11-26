# P500 String-Reference and Base-Candidate Analysis — Phase 2D-4

## Scope, integrity, and limits

- **CONFIRMED** — Source: `firmware/extracted/P500/sections/P500-NPROG-primary.bin`, 7,471,104 bytes (`0x720000`).
- **CONFIRMED** — Source SHA-256: `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`, reverified for this phase.
- **CONFIRMED** — Existing Ghidra program: `/ARM-Validation/P500-NPROG-primary.bin`, language `ARM:LE:32:v7`. Its temporary image mapping remains `0x00000000`.
- **IMPORTANT** — Ghidra addresses in this report are file-offset-oriented offsets under that temporary mapping, not runtime-address claims. The source image was not modified, patched, exported, or emulated. No camera was contacted.
- **P510 BOUNDARY** — Nikon COOLPIX P510 Firmware Version 1.0 remains a separate confirmed owner observation. No P500 finding here establishes P510 architecture, behavior, compatibility, or firmware contents.

## Current P500 stopping point

**P500 reverse engineering is paused at Phase 2D-4.** ARM32 little-endian remains **STRONGLY SUPPORTED** for this P500 payload; the phase examined 25 high-value strings, found file-offset-valued matches for 21, and connected 15 to coherent ARM code. No tested runtime image base resolved exact string pointers. `0x57E70000` remains only **PLAUSIBLE**; `0x57EA0000` is associated with writable zero-fill and is not the firmware image base. Rebase is **NOT justified**. Do not resume broad P500 analysis unless the research scope is explicitly reopened.

The scan examined 25 selected high-value ASCII strings. Their exact string bytes, file offsets, lengths, local byte context, and nearby strings are cataloged below. A secondary UTF-16LE heuristic produced three short, non-meaningful fragments; no relevant readable UTF-16LE string was found.

## Method and aggregate results

The scan:

1. Searched the complete binary for the selected strings and recorded each string's file offset `O`.
2. Searched aligned little-endian words for exact file-offset values `O`.
3. Searched for ARM LDR-literal encodings whose literal-pool word equals a selected `O`.
4. Tested exact absolute string pointers `B + O` for each selected string under `B = 0x57E00000`, `0x57E70000`, `0x57E80000`, `0x57E90000`, and `0x57EA0000`.
5. Derived heuristic bases `P - O` from aligned `0x5xxxxxxx` words and inspected bounded ARM windows at promising literal-load sites.

Results:

- **31** aligned words equal selected string file offsets, covering **21 of 25** selected strings. These are offset-valued words; their runtime interpretation is not established.
- **36** ARM LDR-literal patterns load values equal to selected string offsets, covering **15 distinct strings**. Bounded decoding connected these 15 strings to coherent ARM instruction sequences, though some windows begin mid-routine and the called functions' semantics are often unknown.
- **0** exact `B + O` absolute pointer matches were found for any selected string at any of the five tested bases.
- The decoded code and descriptor data therefore show repeated offset-valued string references, but do not distinguish a zero-linked image, file-relative offsets, runtime relocation, or another translation scheme.
- Ghidra did not create ordinary string xrefs at the inspected locations: the relevant literal-pool words and descriptor entries remained byte-sized `DataDB` units. This is consistent with the temporary offset mapping and untyped data; it is not proof that the strings are unused.

## Catalog of 25 selected strings

`Context bytes` are the exact 16 bytes preceding and up to 16 bytes following the string, as available in the source. `Nearby strings` are other detected strings within 96 bytes. Confidence distinguishes direct string/reference evidence from subsystem interpretation; it does not imply anything about the P510.

| String | File offset | Length / encoding | Subsystem | Possible referencing value | Candidate base | Nearby code / context and confidence |
|---|---:|---|---|---|---|---|
| `===> NK_MTP_RAM_ADRS=%08x` | `0x6483F4` | 24 / ASCII | MTP initialization | `0x006483F4` at pool `0x49A5CC`; LDR at `0x499888` | None supported; offset value observed | Context: `73 5B 25 64 5D 0A 00 00 00 00 00 00 00 00 00 00 [string] 0A 00 00 00 41 44 44 52 45 53 53 5F 4D 54 50 5F`. Nearby: `z%s[%d]`, `ADDRESS_MTP_WORKAREA*4=%08x`, `yExifError`, `SET_Exif_ReadData_OEM`. **High** string and code-link confidence. |
| `>>>>> MTP:Init(%d) [START]` | `0x64848C` | 26 / ASCII | MTP initialization | `0x0064848C` at pool `0x49A5D8`; LDR at `0x4998D8` | None supported; offset value observed | Context: `66 6F 20 49 6E 69 74 20 5B 45 4E 44 5D 0A 00 3E 3E 3E 3E 3E [string] 0A 00 3C 3C 3C 3C 3C 20 4D 54 50 3A 41 6C`. Nearby: `<<<<< MTP:Init [END]`, `NK_MTP_Chk_ThumbnailObjFormat`, `<<<<< MTP:All Info Init [END]`, `>>>>> MTP:All Info Init [START]`. **High** string and code-link confidence. |
| `NK_MTP_GetObjPropValue` | `0x6485D8` | 22 / ASCII | MTP object properties | `0x006485D8` at pool `0x49A654`; LDR at `0x49A2CC` | None supported; offset value observed | Context: `20 43 4C 4F 53 45 44 21 21 21 21 0A 00 00 00 00 [string] 00 00 3C 3E 20 4F 62 6A 65 63 74 20 50 72 6F 70`. Nearby: `000====>File CLOSED!!!!`, `<> Object Property Code : %04x`, `PTP_MTP_RESP_INVALID_OBJ_PROP_CODE`, `-----> %s() [START]`. **High** string and code-link confidence. |
| `NK_MTP_SetObjPropValue` | `0x648628` | 22 / ASCII | MTP object properties | `0x00648628` at pool `0x49A65C`; LDRs at `0x49A2F4` and `0x49A33C` | None supported; offset value observed | Context: `73 28 29 20 5B 53 54 41 52 54 5D 0A 00 00 00 00 [string] 00 00 3C 3E 20 52 45 54 55 52 4E 20 56 61 6C 75`. Nearby: `-----> %s() [START]`, `<> RETURN Value`, `: %08x`, `<----- %s() [End]`. **High** string and code-link confidence. |
| `>>>>> MTP_Connect` | `0x649340` | 17 / ASCII | MTP connection | `0x00649340` at pool `0x49C998`; LDR at `0x49C440` | None supported; offset value observed | Context: `65 76 20 4F 70 65 6E 53 65 73 73 69 6F 6E 20 00 [string] 0A 00 00 5C 00 00 00 80 DE 28 00 80 3B 26 00`. Nearby: `>>>>> Receivev OpenSession`, AVI-file analysis and picture-type diagnostic strings. **High** string and code-link confidence. |
| `>>>>> CommonAPI_OpenFilePtp START (%d)` | `0x649064` | 38 / ASCII | PTP file access | `0x00649064` at pool `0x49C33C`; LDR at `0x49BB50` | None supported; offset value observed | Context: `56 69 64 65 6F 42 69 74 52 61 74 65 00 00 00 00 [string] 0A 00 [<<<<<< CommonAPI_OpenFilePtp END : CurrFileID %08x]`. Nearby: `NK_APLI_MtpObjPropValue_VideoBitRate`, `<<<<< CommonAPI_OpenFilePtp END : CurrFileID %08x`, `VideoBitRate=%d`, `CurrAudName=%s pictable.Audio=0x%08x`. **High** string and code-link confidence; callee semantics unknown. |
| `NIKON DSC COOLPIX P500-PTP` | `0x6497CC` | 26 / ASCII | PTP identity/model string | `0x006497CC` at pool `0x4C1748`; LDR at `0x4C16D8` | None supported; offset value observed | Context: `43 20 43 4F 4F 4C 50 49 58 20 50 35 30 30 00 00 [string] 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00`. Nearby: `NIKON DSC COOLPIX P500`, `NIKON`, `AUTPRINTMRK`, `MISC`. A conditional ARM path loads the string and passes it with a stack buffer to `0x536904`; exact helper purpose is unknown. **High** P500 identity and code-link confidence. |
| `CamUsbInitMode` | `0x61F654` | 14 / ASCII | Camera setting descriptor / USB mode | File-offset entries at `0x61D874`, `0x61E4D4`, `0x61EE64` | N/A: descriptor stores offsets | Context: `43 61 6D 54 6F 6E 65 43 75 72 76 65 00 00 00 00 [string] 00 00 [CamVideoSignalMode] 00 00 [CamMemoryFormat]`. Nearby: `CamToneCurve`, `CamVideoSignalMode`, `CamSpecialFunc`, `CamMemoryFormat`. No direct ARM code xref established. **High** string; **medium** descriptor/subsystem interpretation. |
| `CamDebugUsbMode` | `0x61FB28` | 15 / ASCII | Camera setting descriptor / USB diagnostics | File-offset entries at `0x61E9CC`, `0x61F224` | N/A: descriptor stores offsets | Context: `43 61 6D 47 50 53 53 6E 72 53 74 61 74 65 00 00 [string] 00 [CamLensAdjSize] 00 [CamDistortion] 00 [CamLensAdj]`. Nearby: `CamGPSSnrState`, `CamLensAdjSize`, `CamDistortion`, `CamLensAdj`. No direct ARM code xref established. **High** string; **medium** descriptor/subsystem interpretation. |
| `MTP_WORKAREA_SIZE=%d` | `0x648430` | 20 / ASCII | MTP memory/work-area diagnostics | `0x00648430` at pool `0x49A5C4`; LDR at `0x499878` | None supported; offset value observed | Context: `41 52 45 41 2A 34 3D 25 30 38 78 20 00 00 00 00 [string] 00 00 00 00 3E 3E 3E 3E 3E 20 4D 54 50 3A 41 6C`. Nearby: `ADDRESS_MTP_WORKAREA*4=%08x`, `>>>>> MTP:All Info Init [START]`, `===> NK_MTP_RAM_ADRS=%08x`, `<<<<< MTP:All Info Init [END]`. **High** string and code-link confidence. |
| `[STL:ERR] Virtual NAND Creation Error (Vol %d, Part %d)` | `0x5FE378` | 55 / ASCII | Storage / virtual NAND diagnostics | `0x005FE378` at pool `0xF51C4`; LDR at `0xF439C` | None supported; offset value observed | Context: `20 25 64 2C 20 50 61 72 74 20 25 64 29 0D 0A 00 [string] 0D 0A 00 00 00 5B 53 54 4C 3A 45 52 52 5D 20 47`. Nearby: `[STL:ERR] Sector Map Creation Error ...`, `[STL:ERR] Garbage Quque Creation Error ...`. ARM conditional flow loads it and calls `0x10A2EC`; exact logger/callee purpose unknown. **High** string; **medium-high** code-link confidence. |
| `[STL:ERR] Operation Queue Creation Error (Vol %d, Part %d)` | `0x5FE3F0` | 58 / ASCII | Storage / queue diagnostics | `0x005FE3F0` at pool `0xF51C0`; LDR at `0xF4350` | None supported; offset value observed | Context: `25 64 2C 20 50 61 72 74 20 25 64 29 0D 0A 00 00 [string] 0D 0A 00 00 00 00 5B 53 54 4C 3A 45 52 52 5D 20`. Nearby: `[STL:ERR] Garbage Quque Creation Error ...`, `[STL:ERR] Memory allocation for EUH Buffer error ...`. ARM conditional flow loads it and calls `0x10A2EC`; exact callee purpose unknown. **High** string; **medium-high** code-link confidence. |
| `MMemAlloc pStitch->ppImage error.` | `0x5202B0` | 33 / ASCII | Stitching / image-buffer allocation | No selected file-offset or LDR-literal reference found | None | Context: `50 72 6F 74 65 63 74 20 65 72 72 6F 72 2E 0A 00 [string] 0A 00 00 4D 4D 65 6D 41 6C 6C 6F 63 20 70 53 74`. Nearby: `Protect error.`, `MMemAlloc pStitch->ppImage[i] error.`, `Allocate pStitch->pFirstRectImage error.` No coherent code reference identified. **High** string; **low** code-link confidence. |
| `MMemAlloc pVideoCapture error.` | `0x51EDB4` | 30 / ASCII | Video capture / buffer allocation | No selected file-offset or LDR-literal reference found | None | Context: `72 65 61 74 65 20 65 72 72 6F 72 2E 0A 00 00 00 [string] 0A 00 [MMemAlloc pBufferHandle error.]`. Nearby: `MMemMgrCreate error.`, `MMemAlloc pBufferHandle error.`, `Protect input error.`, `APVC_InitialStitchParameter error.` No coherent code reference identified. **High** string; **low** code-link confidence. |
| `ERROR 3 : RAW READ ERROR!!` | `0x614818` | 26 / ASCII | RAW/file-read diagnostics | `0x00614818` at pool `0x1CFC10`; LDR at `0x1CF984` | None supported; offset value observed | Context: `5A 45 20 45 52 52 4F 52 21 21 0D 0A 00 00 00 00 [string] 0D 0A 00 00 00 00 45 52 52 4F 52 20 34 20 3A 20`. Nearby: `ERROR 2 : BUF SIZE ERROR!!`, `ERROR 4 : STATUS FOLDER READ ERROR!!`, `ERROR 1 : STATUS READ ERROR!! (%d)`, `ERROR 5 : STATUS FILE READ ERROR!!`. Coherent bit-test/control-flow path loads it and calls `0x537BB0`; exact callee purpose unknown. **High** string and code-link confidence. |
| `Focus Drive cre_sem` | `0x602C5C` | 19 / ASCII | Lens/focus task synchronization diagnostic | `0x00602C5C` at pool `0x106720`; LDR at `0x10622C` | None supported; offset value observed | Context: `00 00 00 00 01 00 00 00 00 00 00 00 00 00 00 00 [string] 00 [Other Drive cre_sem]`. Nearby: `lens/lens_dual_system.c`, `sta_tsk`, `Other Drive cre_sem`, `Zoom Sync cre_sem`. A repeated, coherent ARM diagnostic/setup sequence around `0x1061D8–0x106840` uses this and the lens-task string. **High** string; **medium-high** task/synchronization interpretation. |
| `lens_mtr_drv_master_task_start` | `0x602CD8` | 30 / ASCII | Lens-motor task diagnostics | `0x00602CD8` at pool `0x106718`; repeated LDRs from `0x1061E8` through later sites near `0x106920` | None supported; offset value observed | Context: `20 53 79 6E 63 20 63 72 65 5F 73 65 6D 00 00 00 [string] 00 00 [Focus Sync cre_sem]`. Nearby: `Data Sync cre_sem`, `Focus Sync cre_sem`, `Shutter Drive cre_sem`, `Zoom Drive cre_sem`. Multiple separated ARM sites use the same literal in coherent repeated control-flow/call sequences. **High** string and code-link confidence; exact task implementation not recovered. |
| `CamFocusMode` | `0x61F47C` | 12 / ASCII | Focus setting descriptor | File-offset entries at `0x61D5D4`, `0x61E24C`, `0x61EC3C` | N/A: descriptor stores offsets | Context: `43 61 6D 4C 69 67 68 74 50 61 72 61 6D 00 00 00 [string] 00 00 00 43 61 6D 46 6F 63 61 6C 4C 65 6E 67`. Nearby: `CamLightParam`, `CamFocalLength`, `CamManualFocus`. No direct ARM code xref established. **High** string; **medium** descriptor interpretation. |
| `CamManualFocus` | `0x61F49C` | 14 / ASCII | Manual-focus setting descriptor | File-offset entries at `0x61D604`, `0x61E27C`, `0x61EC6C` | N/A: descriptor stores offsets | Context: `43 61 6D 46 6F 63 61 6C 4C 65 6E 67 74 68 00 00 [string] 00 00 43 61 6D 4C 63 64 4D 6F 64 65 00 00 43 61`. Nearby: `CamFocalLength`, `CamLcdMode`, `CamLcdDateFormat`, `CamFocusMode`. No direct ARM code xref established. **High** string; **medium** descriptor interpretation. |
| `CamVideoSignalMode` | `0x61F664` | 18 / ASCII | Video-signal setting descriptor | File-offset entries at `0x61D88C`, `0x61E4EC`, `0x61EE7C` | N/A: descriptor stores offsets | Context: `43 61 6D 55 73 62 49 6E 69 74 4D 6F 64 65 00 00 [string] 00 00 43 61 6D 4D 65 6D 6F 72 79 46 6F 72 6D 61`. Nearby: `CamUsbInitMode`, `CamMemoryFormat`, `CamToneCurve`, `CamDiagInfo4Long`. No direct ARM code xref established. **High** string; **medium** descriptor interpretation. |
| `CamDownloadFirmwareHandle` | `0x61F53C` | 25 / ASCII | Firmware-related setting/handler descriptor | File-offset entries at `0x61D6F4`, `0x61E36C` | N/A: descriptor stores offsets | Context: `43 61 6D 44 69 61 67 44 6C 63 64 49 6E 66 6F 00 [string] 00 00 00 43 61 6D 41 75 64 69 6F 4D 6F 64 65 00`. Nearby: `CamDiagDlcdInfo`, `CamAudioMode`, `CamDiagInfo2`, `CamBackRushPulse`. No direct ARM code xref established; the name alone does not establish a working updater. **High** string; **low-medium** functional interpretation. |
| `FIRMWARE.BIN` | `0x620CB0` | 12 / ASCII | Firmware/update menu or file handling | `0x00620CB0` at pool `0x2E4954`; LDRs at `0x2E3CD0`, `0x2E3D30`, `0x2E3D90` | None supported; offset value observed | Context: `59 45 53 20 3E 00 00 00 44 4F 4E 45 00 00 00 00 [string] 00 00 00 00 57 52 49 54 45 20 20 45 58 45 43 55`. Nearby: `YES >`, `DONE`, `WRITE EXECUTION`, `COOLPIX P500`. Repeated code blocks load it and call `0x3A6C4C` with numeric arguments; helper semantics and actual update behavior are unknown. **High** string/code-link confidence; **low** updater-function confidence. |
| `Update to new firmware?` | `0x6E6448` | 23 / ASCII | Firmware-update menu text | No selected file-offset or LDR-literal reference found | None | Context: `35 20 66 70 73 00 00 00 00 00 00 00 00 00 00 00 [string] 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00`. Nearby: `5 fps`, `Image quality/size`, `Reset user settings`. No coherent code reference identified. **High** string; **low** code-link confidence. |
| `Firmware version` | `0x6ECB38` | 16 / ASCII | Firmware-version menu | No selected file-offset or LDR-literal reference found | None | Context: `00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 [string] 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00`. Nearby: `Reset`, `Current`, `Updating`, `AF assist`. No coherent code reference identified. **High** string; **low** code-link confidence. |
| `NK_APLI_MtpObjPropDesc_StorageId` | `0x648684` | 32 / ASCII | MTP object-property descriptor | `0x00648684` at pool `0x49A674`; LDR at `0x49A374` | None supported; offset value observed | Context: `3E 20 25 73 20 5B 53 54 41 52 54 5D 20 0A 00 00 [string] 00 00 00 00 2D 2D 2D 2D 3E 20 25 73 20 5B 53 54`. Nearby: `----> %s [START]`, `-----> %s [START]`, `<----- %s() [End]`, `: %08x`. Located in a coherent decoded property-handling sequence. **High** string and code-link confidence. |

## Candidate pointer tables and lookup representation

The exact file-offset matches occur in structured runs as well as literal pools. The selected strings expose only a subset of entries in the larger runs:

| File-offset range | Selected entries / distinct strings | Calculated base | Strings resolved | Nearby code evidence | Confidence |
|---|---:|---|---|---|---|
| `0x61D5D4–0x61D6F4` | 3 / 3 | N/A: values are string file offsets | `CamFocusMode`, `CamManualFocus`, `CamDownloadFirmwareHandle` | Part of the descriptor run at `0x61D5B4`; surrounding area remains byte-sized `DataDB`; no direct code xref | **Medium** — structured offset records; handler semantics unknown |
| `0x61D874–0x61D88C` | 2 / 2 | N/A | `CamUsbInitMode`, `CamVideoSignalMode` | Same descriptor family; no direct code xref | **Medium** |
| `0x61E24C–0x61E36C` | 3 / 3 | N/A | `CamFocusMode`, `CamManualFocus`, `CamDownloadFirmwareHandle` | Part of the descriptor run at `0x61E22C`; no direct code xref | **Medium** |
| `0x61E4D4–0x61E4EC` | 2 / 2 | N/A | `CamUsbInitMode`, `CamVideoSignalMode` | Same descriptor family; no direct code xref | **Medium** |
| `0x61EC3C–0x61EC6C` | 2 / 2 | N/A | `CamFocusMode`, `CamManualFocus` | Within the descriptor family; no direct code xref | **Medium-low** |
| `0x61EE64–0x61EE7C` | 2 / 2 | N/A | `CamUsbInitMode`, `CamVideoSignalMode` | Within the descriptor family; no direct code xref | **Medium-low** |
| `0x49A5C4–0x49A674` | 6 / 6 | N/A: literal-pool words contain string file offsets | MTP work-area/init, object-property, and descriptor strings | Multiple decoded LDR-literal instructions reference these pools from coherent ARM paths around `0x499860–0x4998C8` and `0x49A2B0–0x49A390` | **High** for pool/code relationship; runtime translation unknown |

The two larger descriptor runs previously identified contain 96 records beginning at `0x61D5B4` and 91 beginning at `0x61E22C`; records are 24 bytes each. This phase confirms several selected string-offset fields within them, but does not establish the full schema or show code consuming them.

## ARM code landmarks and subsystem assessment

### PTP/MTP

- **HIGH VALUE — P500 reference only.** Eight selected MTP/PTP diagnostic or symbol-like strings are loaded through ARM literal pools in coherent code: `MTP_WORKAREA_SIZE`, `NK_MTP_RAM_ADRS`, `MTP:Init`, `NK_MTP_GetObjPropValue`, `NK_MTP_SetObjPropValue`, `NK_APLI_MtpObjPropDesc_StorageId`, `CommonAPI_OpenFilePtp`, and `MTP_Connect`.
- Bounded regions around `0x499860–0x4998A8`, `0x49A2B0–0x49A390`, `0x49BB50–0x49BB6C`, and `0x49C420–0x49C450` show plausible ARM loads, calls, conditional flow, and returns. Several paths repeatedly call `0x49C494`; its role is not established.
- **HIGH VALUE — P500 identity evidence.** Code around `0x4C16D0–0x4C16E4` conditionally loads `NIKON DSC COOLPIX P500-PTP` and passes it with a stack buffer to `0x536904`. This is a P500 model/protocol identity landmark, not a P510 database entry.
- These findings do **not** reveal a complete PTP operation-code table, USB VID/PID, transport implementation, or update protocol. The names alone do not prove a specific operation's implementation.

### USB and camera-setting descriptors

- `CamUsbInitMode` and `CamDebugUsbMode` occur as file-offset values in descriptor-like records. This is evidence of setting names in P500 data, not evidence that USB IDs or USB communication routines were recovered.
- `CamFocusMode`, `CamManualFocus`, and `CamVideoSignalMode` likewise occur in descriptor records, but this phase did not connect those entries to coherent ARM code.
- **No USB VID/PID was identified.** P500 model/protocol text is not a USB identifier.

### Firmware-related strings

- `FIRMWARE.BIN` is referenced by repeated LDR-literal sites at `0x2E3CD0`, `0x2E3D30`, and `0x2E3D90`. Bounded decoding shows repeated instruction sequences passing the loaded value and numeric arguments to `0x3A6C4C`. The helper's purpose is unresolved.
- `Update to new firmware?`, `Firmware version`, and `CamDownloadFirmwareHandle` are present, but were not connected to coherent code in this phase.
- Together these findings indicate firmware/update-related P500 strings and a P500 handler-like name. They do **not** establish an updater's behavior, cryptographic checks, supported models, or P510 compatibility.

### Lens/focus, imaging, storage, and diagnostics

- **POTENTIALLY USEFUL — lens tasking.** `lens_mtr_drv_master_task_start` is loaded from a literal pool at many sites in bounded regions around `0x1061D8–0x106920`; `Focus Drive cre_sem` is loaded at `0x10622C`. The sequences contain coherent conditionals, calls, and stack argument setup. This supports a P500 lens/task diagnostic or initialization context, but not a full lens-driver recovery.
- **POTENTIALLY USEFUL — storage diagnostics.** The virtual-NAND and operation-queue error strings are loaded in coherent conditional code near `0xF4350–0xF43A0`; RAW-read error text is loaded in a separate coherent path near `0x1CF984`.
- The selected stitch-allocation and video-capture allocation errors did not yield a matching selected offset/literal reference or coherent code link in this phase.
- Focus, manual-focus, video-signal, USB-mode, and firmware-handler setting names in the descriptor records may guide future targeted work, but are not themselves confirmed feature implementations.

## Ranked runtime image-base candidates

Exact string-pointer testing used the requested `B + O` calculation for every selected string and each listed base. **No candidate resolved any selected string by an exact absolute pointer.** Statistical in-image word counts below are from the earlier aligned-pointer scan and are weak heuristics, not confirmed pointer counts.

| Candidate base | Independent strings resolved | Other in-image words / pointers resolved | Code context | Evidence against | Classification |
|---:|---:|---:|---|---|---|
| `0x57E70000` | 0 exact `B + O` matches | 10,492 / 15,971 aligned `0x5xxxxxxx` words fell in the candidate image interval in the earlier scan; pointer status unverified | ARM code is coherent under the offset mapping, but no runtime-address references select this base | Tied with `0x57EA0000` statistically; no exact string references or independent memory-map corroboration | **PLAUSIBLE** statistical candidate only |
| `0x57EA0000` | 0 exact `B + O` matches | 10,492 / 15,971 in the earlier scan; pointer status unverified | Startup code uses it as the start of `[0x57EA0000, 0x57F14028)` zero-fill | Its direct code use is strong evidence for a writable-memory boundary, not a ROM/image base; statistically tied with `0x57E70000` | **REJECTED** as the current image-base choice; retain as probable writable-memory start |
| `0x57E80000` | 0 | 10,491 / 15,971 in the earlier scan; unverified | No string-specific code context | Falls on the same broad statistical plateau; no independent evidence | **WEAK** |
| `0x57E90000` | 0 | 10,491 / 15,971 in the earlier scan; unverified | No string-specific code context | Falls on the same broad statistical plateau; no independent evidence | **WEAK** |
| `0x57E00000` | 0 | 10,470 / 15,971 in the earlier scan; unverified | No string-specific code context | Similar statistical resolution without direct evidence | **WEAK** |
| `0x578A7664` | Not applicable as a whole-image base | Heuristic `P - O` arithmetic cluster: 8 distinct selected strings, 39 occurrences | No coherent runtime-address relationship; calculated targets fall within the known zero-filled work area | Not 64-KiB aligned; derived from raw words that may be data/descriptor values; target region is probable writable memory | **REJECTED** |
| `0x5787E63C` | Not applicable as a whole-image base | Heuristic cluster: 7 distinct selected strings, 80 occurrences | No independent code/data corroboration | Not 64-KiB aligned and derived by subtracting string offsets from raw words; target region is not credible string storage | **REJECTED** |

Other `P - O` clusters also recur, but vary by small unaligned offsets and map candidate string addresses into the known zero-fill/work-area interval. Their recurrence is therefore not independent evidence for a ROM base. Candidate arithmetic may result from descriptor values or unrelated data accidentally matching a selected string offset.

### Evidence for and against the named candidates

- **`0x57E70000`:** It remains the better of the named *image-base hypotheses* only in the sense that it is not contradicted by the startup zero-fill use. Its statistical pointer count ties `0x57EA0000`, and this phase found no string pointer resolving under it. It remains **PLAUSIBLE**, not **SUPPORTED**.
- **`0x57EA0000`:** The startup code's zero-fill of `[0x57EA0000, 0x57F14028)` is evidence for a writable-memory range beginning there. It is not independent evidence that the file's ROM image begins there. Keep it excluded as the current image-base choice.
- **New candidate:** None. Derived values such as `0x578A7664` are poor candidates and are rejected.
- **Decision:** No candidate reaches **SUPPORTED**. **Do not rebase.** Keep Ghidra at `0x00000000` for offset-oriented analysis.

## Reference mechanism and why Ghidra did not resolve strings

- **Observed:** Many string values appear as exact file offsets in ARM literal pools and descriptor-like tables. Fifteen strings have literal-load sites; twenty-one have at least one aligned file-offset-valued word.
- **Not established:** Whether these words are runtime pointers into a zero-linked image, file-relative offsets consumed through translation, relocated addresses, or another format. No relocation/copy mechanism was established by this phase.
- **Not observed in this selected set:** Exact absolute pointers under any tested base; a hash-based or indexed string lookup implementation; compressed string-resource encoding.
- **Likely contributors to missing Ghidra xrefs:** The Ghidra listing leaves inspected literal-pool and descriptor bytes as byte-sized `DataDB` units; the offset-oriented mapping is intentional and the actual image base remains unknown. Some strings may also be table/resource entries whose consumers were not analyzed.
- **Insufficient evidence:** Absence of xrefs is not evidence that a selected string is unused.

## Phase conclusions and recommendations

1. **High-value strings examined:** 25.
2. **Strings with probable offset/pointer-valued words:** 21 distinct strings; 31 aligned occurrences.
3. **Strings connected to coherent ARM code:** 15 distinct strings through ARM LDR-literal sites and bounded decoding.
4. **Best-supported image-base candidate:** None reaches **SUPPORTED**. `0x57E70000` remains **PLAUSIBLE** statistically; actual ROM/image base remains **UNKNOWN**.
5. **`0x57E70000`:** statistically plausible but lacks independent string or code/data address references.
6. **`0x57EA0000`:** remains excluded as the image base because its validated use is the start of a zero-filled writable-memory region.
7. **Reference mechanism:** offset-valued literal-pool and descriptor entries are observed; whether they are offsets, zero-linked addresses, or relocated references is unknown.
8. **PTP/MTP/USB landmarks:** coherent P500 MTP/PTP diagnostic/property paths and a P500 PTP identity string are present. No USB VID/PID or complete operation-code table was found.
9. **Imaging/lens/focus/video landmarks:** lens-task/semaphore diagnostics have coherent code context; focus/video setting names occur in descriptor data. Stitch/video allocation strings lack code links in this phase.
10. **Rebasing:** not justified.
11. **Further P500 work:** pause broad speculative string/base scanning. Any future P500 work should be narrowly scoped to resolving a specific MTP/PTP or firmware-related helper, not another broad disassembly expansion.
12. **Project direction:** pivot research toward identifying a safe, non-destructive, read-only way to acquire the physical P510's installed Firmware Version 1.0 image. This is a research objective only; it does not authorize connecting to, dumping, or communicating with the camera. Preserve the camera in its current state and do not infer P510 behavior from P500 results.
