# Phase 5B - P500 NRW/NEF File-Path Analysis

**Scope:** Offline static examination of the P500 reference primary section  
**P510 findings:** None; no P510 firmware was available for this trace

## File-type and extension evidence

| Offset | Observed content | Bounded interpretation |
|---|---|---|
| `0x605EFC` onward | Type-name entries including `JPG`, `MOV`, `WAV`, `DPS`, `SXC`, `EXE`, `MRK`, `NEF`, `NONAME`, `THM` | String/data table; no direct code reference was recorded for the examined entries |
| `0x6465F8–0x646610` | `.TIF`, `.MOV`, `.AVI`, `.JPG`, followed by `P500` | Extension-like strings with literal-pool references from a candidate consumer near `0x3AEC40`; consumer semantics unresolved |
| `0x649400–0x649424` | `MOV`, `THM`, `JPE`, `MRW`, `MP4`, `M4A`, `RAW`, `ORF`, `NEF`, `NRW`, `RAF` | File-type/name table; literal loads near `0x4A24F8`, `0x4A2520`, and `0x4A2534` reach `RAW`, `NEF`, and `NRW` entries |
| `0x61B994` | `DSC00001.JPG` adjacent to `RIFF`/`data` text | Sample/resource filename; not evidence of a capture writer |

An exact `.NRW` string was not found in the primary section. The unprefixed `NRW` token is present in the type-name table and in NRW-related diagnostic/resource labels.

## Capture, file-open, and write path

The P500 section contains explicit menu/resource-like strings `NRW (RAW) + Basic/Fine/Normal`, `NRW (RAW) processing`, and `Create a JPEG copy at these`. They establish that the firmware image contains this text, but the inspected code did not map an active menu selection to a capture path or an output operation.

The separate PTP text `CommonAPI_OpenFilePtp` at `0x649064` has a literal reference near `0x49BB50` and is in a PTP/MTP object-access context. No verified connection ties it to the NRW table, the RAW-named routine, or an NRW/NEF writer. It must not be treated as proof of RAW-file creation.

No file-create/open/write chain was established for NRW, NEF, or a RAW output. No Nikon Electronic Format (NEF) creation capability was identified. The type tables could support recognition, listing, transfer, filtering, or another generic file-type operation; output semantics remain unknown.

## Format and quality selection

The `NRW (RAW) + Basic/Fine/Normal` strings are consistent with a selection or quality vocabulary, but no verified code/data chain establishes a user-visible option, its stored value, or its effect on capture/output. The extension tables are generic type-name evidence and do not establish a selectable format.

**Determination:** beyond-JPEG selection is a **P500 string-level lead only**. A live selection path and its output effect were not identified.

## Result

- NRW/NEF/file-type labels: **present in P500 reference data**.
- File-type table code references: **partially located**, semantics unknown.
- NRW/NEF output writer: **not identified**.
- JPEG encoder call path: **not identified**.
- NEF creation capability: **not identified**.
- P510 format or capture behavior: **unknown**.
