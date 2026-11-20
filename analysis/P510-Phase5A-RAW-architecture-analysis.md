# P510 Phase 5A - RAW Architecture Analysis

**Status:** COMPLETE - existing local evidence only  
**Research date:** 2026-11-20  
**Reference models:** P500 and P520; not P510 firmware  
**Physical P510 operations:** None

## Executive determination

The P500 firmware reference contains a cluster of explicit RAW/NRW strings, including RAW-mode/acquisition diagnostics, NRW processing and quality labels, and JPEG-copy text. Separately, a `RAW READ ERROR!!` message is connected to a bounded P500 conditional code path. Together these are evidence of a **possible P500 RAW/NRW-related data/processing path**.

The available P500 analysis does not trace a complete sensor acquisition, RAW buffer, processing, JPEG encoding, and output-file chain. P520's extracted payload is high-entropy and has no readable RAW/NEF or image-pipeline string evidence in the reviewed analysis; its JPEG-like byte sequences were not validated as files.

> **REFERENCE ARCHITECTURE SHOWS POSSIBLE RAW DATA PATH**
>
> This classification is P500-reference-only. It does not establish that the P510 can capture RAW, NRW, or NEF. P510 RAW feasibility remains **UNKNOWN / NOT ESTABLISHED**.

## Evidence provenance

| Model/source | Existing record | Relevant integrity/provenance |
|---|---|---|
| P500 updater package | [`F-P500-V11W.exe`](../firmware/reference/P500/F-P500-V11W.exe) | Recorded SHA-256 `CA83DDCCD4B3E4CEBAA5C72BD65959F70C1138E3E6E2A273E14DF142C31C99CD` |
| P500 extracted payload | [`firmware.bin`](../firmware/extracted/P500/P500Update/firmware/firmware.bin) | Recorded SHA-256 `80A297C8B4B77731EB2B3B5DC23D905D557A0052049402364B11A1F7849779B4` |
| P500 primary code section | [`P500-NPROG-primary.bin`](../firmware/extracted/P500/sections/P500-NPROG-primary.bin) | Recorded SHA-256 `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`; 32-bit little-endian ARM is strongly supported for this P500 section only |
| P520 updater package | [`F-P520-V11W.exe`](../firmware/reference/P520/F-P520-V11W.exe) | Recorded SHA-256 `CFDE64DD155C6DFA6FF6BD74AD807D7A3F615938DCA2190D72A075C8519E6DB2` |
| P520 extracted payload | [`firmware.bin`](../firmware/extracted/P520/P520Update/firmware/firmware.bin) | Recorded SHA-256 `631A4C6AB34E3BE5C7EE1153AD1A7D93986DA2853C79F572B63A3E23129B979C`; the payload remains opaque/high-entropy in the existing analysis |

These are previously recorded hashes; Phase 5A did not recalculate them or modify any package/payload.

## P500 reference evidence

### Confirmed observations

- The P500 primary code section is classified as probable code, with 32-bit little-endian ARM strongly supported. This does not identify the P510 processor or platform.
- The P500 primary-section inventory contains explicit strings `RAW_MODE=`, `-RAW DATA INFO- ACQUSITION SIZE(No.%d) (H,V) = (%5d,%5d)`, `NRW (RAW) processing`, `NRW (RAW) + Basic`, `NRW (RAW) + Fine`, and `NRW (RAW) + Normal`.
- Nearby text includes `Create a JPEG copy at these` and `create JPEG copies.`
- `ERROR 3 : RAW READ ERROR!!` appears among error messages that also mention buffer size, status, folder, and file reads. The P500 string-reference analysis found a coherent conditional code path loading that message and calling `0x537BB0`; the callee's purpose remains unknown.
- JPEG-related reference strings include `Photo - JPEG` and a diagnostic containing `JpegBuffer_TopAddrW()`. These identify text references, not a fully mapped JPEG encoder or buffer.
- P500 resource data contains JPEG SOI-like patterns and JPEG-table-like text. The existing analysis did not validate or carve those sequences into complete JPEG files.

### Bounded interpretation

The P500 evidence is stronger than a single isolated `RAW` substring: multiple explicit NRW/RAW labels and diagnostics coexist with a code-linked RAW-read error path. It therefore supports the classification **possible RAW/NRW data/processing path** for the P500 reference.

It does **not** establish:

- that every RAW/NRW string is reachable or used by the P500 retail configuration;
- that the P500 acquires sensor-native raw data through the named path;
- the identity, address, size, or layout of a RAW/pre-JPEG buffer;
- the RAW-processing algorithm or its input/output data;
- the JPEG encoder implementation or whether it consumes that data;
- the format/file-writing path that produces an NRW/NEF file; or
- any corresponding P510 implementation.

The existing offset-mapped Ghidra inventory reports no Ghidra-generated code xrefs to its matched-string set. The separate string-reference report provides selected bounded manual code links, including the RAW-read error path, but not a full pipeline trace. File offsets are not asserted runtime addresses.

## P520 reference evidence

The P520 payload begins with a short `P520` / `Ver.1.1` prefix followed by a near-maximum-entropy region. The existing scan found JPEG-like SOI sequences but did not validate them as complete files. It found no useful readable RAW/NEF pipeline strings, code references, architecture, or component boundaries. The P520 package comparison establishes some similarities in the **host installer/archive wrapper** to P500, not similarity of camera image-processing architecture.

No P520 RAW/NEF path was identified. The P520 data does not strengthen the P500 RAW interpretation or imply a P510 design.

## P500/P520 similarity boundary

Both installer packages are PE32 Windows executables with a RAR4 marker at the PE overlay and the same first 170 bytes at the corresponding RAR4 lead-in. Their embedded path strings are model-specific (`P500Update\firmware\firmware.bin` and `P520Update\firmware\firmware.bin`). These are package-level similarities only.

The packages differ substantially in size and internal payload form. P500 has readable model/firmware strings and sections analyzed as probable code/resources; P520's payload remains opaque/high-entropy. No shared image pipeline, RAW buffer, encoder, or P510 relationship has been established.

## Requirement answers

| Question | Phase 5A result |
|---|---|
| Strongest RAW-related reference-model finding | P500's cluster of `RAW_MODE`, `NRW (RAW)` processing/quality, raw acquisition-size, and JPEG-copy strings, plus a bounded code-linked `RAW READ ERROR!!` path |
| Was a raw/pre-JPEG buffer identified? | **No.** A raw-size diagnostic and JPEG-buffer diagnostic string exist; no RAW buffer structure/address/layout was identified |
| Was a JPEG encoder path identified? | **No.** JPEG labels and a JPEG-buffer diagnostic exist, but no encoder routine or end-to-end call chain was traced |
| Was NEF creation capability identified? | **No.** The reference strings say NRW/RAW, not NEF; no output-file creation path was established |
| Does file-format selection exist beyond JPEG quality? | **P500 string-level lead only:** `NRW (RAW) + Basic/Fine/Normal` and JPEG-copy labels suggest more than JPEG quality labels, but no active user-selection-to-output path was traced. No P510 conclusion follows |
| P520 RAW/NEF evidence? | No readable or validated RAW/NEF evidence in the existing P520 payload analysis |
| P510 RAW feasibility? | **Not established.** No authentic P510 firmware was analyzed |

## Classification

**REFERENCE ARCHITECTURE SHOWS POSSIBLE RAW DATA PATH**

This classification reflects P500 reference strings and one code-linked RAW-read error path. It is not a classification of P510 RAW capture and must not be reported as P510 feasibility.

## References

- [P500 string-reference analysis](P500-string-reference-analysis.md)
- [P500 section map](P500-section-map.md)
- [P500 expanded Ghidra analysis](P500-ghidra-expanded-analysis.md)
- [P500 payload analysis](P500-payload-analysis.md)
- [P500/P520 package comparison](P500-P520-comparison.md)
- [P520 payload analysis](P520-payload-analysis.md)
- [P510 Phase 3C DeviceInfo analysis](P510-Phase3C6-DeviceInfo-analysis.md)
- [P510 Phase 4 final status](P510-Phase4-final-status.md)
