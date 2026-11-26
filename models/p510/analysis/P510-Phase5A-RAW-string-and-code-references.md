# P510 Phase 5A - RAW String and Code References

**Scope:** Existing P500/P520 reference-firmware analysis and P510 DeviceInfo evidence only. These references do not establish P510 implementation.

## P500 primary-section strings

Offsets below are the recorded P500 NPROG-primary section/file offsets. No runtime image base is assigned. Exact strings are preserved as found.

| Offset | Exact string | Existing evidence | Interpretation limit |
|---:|---|---|---|
| `0x00614818` | `ERROR 3 : RAW READ ERROR!!` | The [P500 string-reference analysis](../../p500/analysis/P500-string-reference-analysis.md) records a selected literal-pool reference at `0x1CF984`; a coherent conditional path loads the message and calls `0x537BB0`. Nearby messages concern buffer-size, status, folder, and file-read errors. | Supports a P500 RAW-read/error-handling code path. The called routine's purpose and the input/output data are unknown; this is not sensor-acquisition or file-creation proof. |
| `0x00646216` | `ADDRESS_THUMBYUV2 %x JpegBuffer_TopAddrW() %x Buffer = %d byte` | Found in the P500 expanded inventory. | A JPEG-buffer diagnostic string; no buffer object/address allocation or encoder call chain was mapped. |
| `0x00666D78` | `RAW_MODE=` | Found in the P500 expanded inventory. | RAW-related text; no associated option table or code path identified here. |
| `0x00666F40` | ` -RAW DATA INFO- ACQUSITION SIZE(No.%d) (H,V) = (%5d,%5d)` | Found in the P500 expanded inventory. | Indicates RAW-related acquisition-size diagnostics; does not identify a buffer, sensor interface, or pixel data path. |
| `0x006EA87C` | `NRW (RAW) + Basic` | Found in the P500 expanded inventory. | P500 resource/UI label; active menu semantics not traced. |
| `0x006F0984` | `NRW (RAW) + Fine` | Found in the P500 expanded inventory. | P500 resource/UI label; active menu semantics not traced. |
| `0x006F09A8` | `NRW (RAW) + Normal` | Found in the P500 expanded inventory. | P500 resource/UI label; active menu semantics not traced. |
| `0x006F0B04` | `NRW (RAW) processing` | Found in the P500 expanded inventory. | Supports the presence of RAW/NRW-related processing text; no function/call chain or output format was identified. |
| `0x006F0B8C` | `Create a JPEG copy at these` | Found in the P500 expanded inventory. | P500 JPEG-copy text; does not identify an encoder or prove that it consumes a sensor-RAW buffer. |
| `0x006F0BC4` | `create JPEG copies.` | Found in the P500 expanded inventory. | P500 JPEG-copy text; caller and operation remain unknown. |

Other P500 strings include `Photo - JPEG` at `0x002809E8` and `0x002A3EA0`, and `jpeg` at `0x002A7584` in the section inventory. These are format/processing vocabulary only.

## Code-link assessment

### `RAW READ ERROR!!`

The strongest code-connected RAW-related item is `ERROR 3 : RAW READ ERROR!!`. The existing targeted string analysis records:

- message at section/file offset `0x00614818`;
- a literal load at `0x1CF984`;
- a bounded conditional/control-flow path loading the string; and
- a call to `0x537BB0`, whose function is not identified.

The adjacent status/folder/file error messages suggest a file-read/error-reporting context. The evidence is limited to this P500 path and does not identify the underlying data source, storage format, caller, or successful operation.

### Other RAW/NRW and JPEG labels

The `RAW_MODE=`, raw acquisition-size, NRW-processing, NRW-quality, and JPEG-copy strings were identified in Ghidra string-inventory output. They were not connected to a complete code path in the existing reports. The expanded analysis explicitly warns that matched strings do not identify callers or prove a feature implementation.

The `JpegBuffer_TopAddrW()` text is a diagnostic mention, not a recovered buffer structure. No RAW buffer address, allocator call, dimensions-to-buffer mapping, encoder entry point, or file writer was identified.

## P500 resource signatures

The P500 `NDATA` section contains repeated JPEG SOI-like byte patterns and printable JPEG-table-like fragments. The existing [section map](../../p500/analysis/P500-section-map.md) classifies these as probable resource/data content and explicitly says they were not carved, parsed, or validated as complete JPEG files. They are not evidence of a JPEG encoder path.

## P520 search result

The existing P520 payload scan records several JPEG SOI-like byte sequences in a high-entropy region, but none was validated as a complete stream. No readable P520 RAW/NEF strings, code references, or relevant format table were identified in the reviewed local analysis. The P520 payload's architecture and internal component boundaries remain unknown.

## P510 separation

The P510 DeviceInfo response advertises empty `CaptureFormats` and `ImageFormats` values `0x3801 0x3001 0x3006 0x3008 0x300D 0xB111 0x3000`. `0xB111` remains unresolved; it is not labeled NRW, NEF, or RAW. No standard `InitiateCapture (0x100E)` operation appears in the advertised operation list. These P510 facts do not confirm or rule out RAW imaging.

## Evidence classification

- **Confirmed P500 reference evidence:** the listed strings occur in the analyzed P500 firmware data.
- **Code-linked P500 evidence:** the `RAW READ ERROR!!` message is loaded in a bounded P500 conditional path and followed by a call to an unidentified routine.
- **Not established:** P500 end-to-end RAW acquisition/export, P500 NEF creation, P500 encoder implementation, any P520 RAW path, and any P510 RAW feature.

## Sources

- [P500 expanded Ghidra analysis](../../p500/analysis/P500-ghidra-expanded-analysis.md)
- [P500 string-reference analysis](../../p500/analysis/P500-string-reference-analysis.md)
- [P500 section map](../../p500/analysis/P500-section-map.md)
- [P520 payload analysis](../../p520/analysis/P520-payload-analysis.md)
- [P510 Phase 3C DeviceInfo analysis](P510-Phase3C6-DeviceInfo-analysis.md)
