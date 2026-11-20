# P500 / P520 Extracted Payload Comparison

These are extracted reference payloads for neighboring camera models only. They are not P510 firmware, and the comparison does not imply compatibility. Both payloads were analyzed read-only; neither was executed or disassembled.

## CONFIRMED — Identity and extraction results

| Finding | P500 reference | P520 reference |
|---|---|---|
| Extracted path | `firmware\extracted\P500\P500Update\firmware\firmware.bin` | `firmware\extracted\P520\P520Update\firmware\firmware.bin` |
| Size | 14,614,648 bytes | 81,264,928 bytes |
| SHA-256 | `80A297C8B4B77731EB2B3B5DC23D905D557A0052049402364B11A1F7849779B4` | `631A4C6AB34E3BE5C7EE1153AD1A7D93986DA2853C79F572B63A3E23129B979C` |
| RAR member CRC-32 | `D5CC5508` | `1DFDC34C` |
| Archive encryption flag | None | None |
| Package archive method string | `m3:22` | `m3:22` |

- Both archive listings exposed the same relative member path, `P<Model>Update\firmware\firmware.bin`, and two directory entries.
- 7-Zip 25.01 reported successful extraction and CRC checks. Both source EXE packages still match their recorded SHA-256 hashes.
- P520's payload is 66,650,280 bytes larger than P500's.

## CONFIRMED — First-level structure and headers

- P500 begins with a readable multi-field header: `LENGTH=7471104 SG583 VER=v583-80 DVR=1.10 SUM=765951917 NPROG NDATA NLIPI SFIRM`. Further `NPROG`, `NDATA`, `NLIPI`, and `SFIRM` records appear at offsets documented in `analysis/P500-payload-analysis.md`.
- P520 begins with `P520`, zero padding, and ` Ver.1.1` at offset `0x10`; bytes from `0x20` onward are high-entropy.
- The payloads have no common initial byte: the first byte is `L` in P500 and `P` in P520. Their first 512 bytes differ.
- P500's visible records and code-like region provide evidence for multiple internal sections. P520 has no verified internal component boundaries from this read-only scan.

## LIKELY — Architecture, format, and component comparison

- P500's instruction-like bytes beginning around `0x60` are consistent with 32-bit little-endian ARM code. This is stronger evidence than its lack of architecture-name strings, but it remains an inference without disassembly or independent metadata.
- P500 is likely a structured multi-section firmware container with program/data/other component records identified by `NPROG`, `NDATA`, `NLIPI`, and `SFIRM`. The exact length-field semantics and component boundaries remain unverified.
- P520 is likely an opaque, model/version-prefixed data container. Its near-maximum entropy is consistent with compression, encryption, or both; entropy alone does not determine which.
- P500 contains readable P500/Nikon/COOLPIX strings, version/build fields, filesystem names, and third-party copyright strings. P520 exposes only its model and `Ver.1.1` reliably; other apparent architecture/OS/compiler matches are noisy fragments.
- P500 has JPEG/TIFF-like signature candidates and numerous MZ/PE byte patterns, but no valid nested PE or complete image was confirmed. P520 has gzip-, bzip2-, and JPEG-like candidates within its high-entropy region; none was validated as an embedded component.

## CONFIRMED — Entropy comparison

| Payload | Whole-file entropy | 1 MiB windows (count; min / max / mean) |
|---|---:|---|
| P500 | 5.985927 bits/byte | 14; 2.450703 / 7.014606 / 5.495707 bits/byte |
| P520 | 7.999998 bits/byte | 78; 7.999732 / 7.999969 / 7.999840 bits/byte |

## UNKNOWN — Limits and P510 relevance

- P500's component record semantics, checksums, and exact boundaries have not been independently validated.
- P520's internal format, architecture, component boundaries, and the meaning of its high-entropy region remain unknown.
- Apparent embedded JPEG/TIFF/compression signatures were not validated using format-specific parsers.
- Neither payload provides confirmed evidence about P510. Any inference about the P510 based on P500/P520 must remain a hypothesis until checked against actual P510 firmware or P510 hardware.
- Further decompression, format-specific parsing, or disassembly is outside this phase. No additional tools were installed; deeper format validation may require approved tooling.
