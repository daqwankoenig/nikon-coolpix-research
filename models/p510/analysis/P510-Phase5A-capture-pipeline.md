# P510 Phase 5A - Capture Pipeline Evidence

**Scope:** Static analysis of existing P500/P520 references, contrasted with already-recorded P510 evidence. No capture, camera operation, or firmware modification was performed.

## Pipeline model and findings

| Conceptual stage | Existing P500/P520 reference evidence | P510-specific evidence | Phase 5A result |
|---|---|---|---|
| Sensor acquisition / readout | P500 has `RAW_MODE=` and a `RAW DATA INFO` acquisition-size diagnostic. No sensor interface, readout routine, or stage transition was mapped. P520 provides no readable path. | None in the P510 firmware evidence base; no authentic P510 firmware is available. | **Not identified** |
| RAW/pre-JPEG storage buffer | P500 has a raw-size diagnostic and a separate JPEG-buffer diagnostic, but no RAW buffer structure, address, allocator, dimensions-to-buffer mapping, or ownership/lifetime was recovered. | Unknown. | **No raw/pre-JPEG buffer identified** |
| RAW/NRW processing | P500 contains `NRW (RAW) processing` and `RAW READ ERROR!!`; only the latter has a bounded reference to conditional code, which calls an unidentified routine. No complete process chain was traced. | Unknown. P510 code `0xB111` has no established RAW meaning. | **Possible P500 reference path; no P510 path** |
| JPEG quality or copy selection | P500 has `NRW (RAW) + Basic/Fine/Normal` and JPEG-copy text. Active menu/control-flow semantics were not mapped. | P510 DeviceInfo advertises the standard EXIF/JPEG format code `0x3801`; this is an object-format advertisement, not a capture-format selection or quality control. | **P500 string-level selection lead only** |
| JPEG buffer / encoding | P500 has `JpegBuffer_TopAddrW()` diagnostic text and `Photo - JPEG` labels. No JPEG encoder function or caller/callee chain was identified. P500 NDATA JPEG-like signatures were not validated as images. | No P510 encoder evidence. | **No encoder path identified** |
| NRW/NEF/JPEG file creation | P500 has NRW-processing and JPEG-copy labels, but no output-file creation path, extension writer, or complete file format evidence. P520 is opaque. | No P510 output-file evidence. | **NEF creation not identified** |
| PTP exposure of resulting objects | P500 has PTP/MTP object-file/property strings; they do not establish object contents or RAW capture. | P510 advertises object-read operations, but has an empty `CaptureFormats` array and does not advertise standard `InitiateCapture (0x100E)`. No object was fetched in the bounded Phase 3C exchange. | **No PTP RAW object established** |

## P500 reference chain: evidence versus missing links

The available P500 evidence is a set of related labels and a limited code reference:

1. `RAW_MODE=` and a raw acquisition-size diagnostic indicate RAW-related mode/diagnostic vocabulary.
2. `NRW (RAW) processing` and `NRW (RAW) + Basic/Fine/Normal` indicate NRW/RAW-related processing/quality labels.
3. `Create a JPEG copy...` and `create JPEG copies.` indicate JPEG-copy text.
4. `ERROR 3 : RAW READ ERROR!!` has a selected code link through a conditional path to an unidentified callee.
5. `JpegBuffer_TopAddrW()` mentions a JPEG buffer in diagnostic text.

The gaps between these items are substantial. No reviewed evidence connects a sensor readout to a RAW buffer, connects that buffer to the NRW-processing labels, identifies a JPEG encoder, or proves a completed NRW/NEF/JPEG output write. The terms may refer to menu resources, diagnostics, generic code, or a feature path that was not fully traced. Do not draw a complete pipeline from strings alone.

## P510 facts and limits

The P510's physical `GetDeviceInfo` response is direct P510 evidence, but only of the returned metadata and advertised code arrays:

- `CaptureFormats` is empty.
- `ImageFormats` includes standard EXIF/JPEG (`0x3801`) and unresolved `0xB111`.
- The advertised operation list does not include standard `InitiateCapture (0x100E)`.
- The exchange transmitted only `GetDeviceInfo (0x1001)`; it did not test capture, object retrieval, or any vendor operation.

This does not prove that the P510 cannot produce RAW data. It also does not establish a RAW path, RAW object, NEF/NRW creation, or capture feasibility. The P510 processor, firmware, image pipeline, and format meaning remain unknown.

## Answers for this pipeline checkpoint

- **Raw/pre-JPEG buffer identified:** No.
- **JPEG encoder path identified:** No.
- **NEF creation capability identified:** No.
- **P500 file-format selection beyond JPEG quality:** P500 strings suggest NRW/RAW plus Basic/Fine/Normal labels and JPEG-copy choices; an active selection/output path was not traced.
- **P520 pipeline evidence:** No validated RAW/JPEG processing path; high-entropy signatures are not sufficient.
- **P510 RAW feasibility:** Not established; this Phase 5A classification is reference-only.

## References

- [P510-Phase5A-RAW-architecture-analysis.md](P510-Phase5A-RAW-architecture-analysis.md)
- [P510-Phase5A-RAW-string-and-code-references.md](P510-Phase5A-RAW-string-and-code-references.md)
- [P500 string-reference analysis](../../p500/analysis/P500-string-reference-analysis.md)
- [P500 expanded Ghidra analysis](../../p500/analysis/P500-ghidra-expanded-analysis.md)
- [P500 section map](../../p500/analysis/P500-section-map.md)
- [P520 payload analysis](../../p520/analysis/P520-payload-analysis.md)
- [P510 Phase 3C DeviceInfo analysis](P510-Phase3C6-DeviceInfo-analysis.md)
