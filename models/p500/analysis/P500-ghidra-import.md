# P500 NPROG Ghidra Import — Phase 2D

## Import record

- **CONFIRMED** — Ghidra 12.2 imported `firmware/extracted/P500/sections/P500-NPROG-primary.bin` into the project `analysis/ghidra-projects/P500-NPROG-primary-offsets`.
- **CONFIRMED** — Input size: 7,471,104 bytes. SHA-256 before and after import: `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`, matching [P500-section-hashes.txt](../checksums/P500-section-hashes.txt).
- **CONFIRMED** — Ghidra used the Raw Binary loader and created the memory block `P500_NPROG_file_offsets` at address `0x0`.
- **IMPORTANT LIMIT** — Address `0x0` is used only as a file-offset coordinate system for this import. It is not asserted or proposed as the firmware's runtime image base.
- **CONFIRMED** — The selected language/compiler is `DATA:LE:64:default:pointer32`. This generic little-endian data language preserves the bytes and a 32-bit pointer-size convention; it does not assert an instruction set or CPU architecture.
- **CONFIRMED** — The import used `-noanalysis`. Automatic analysis, disassembly, emulation, and debugging were not run.
- **CONFIRMED** — Project databases, runtime state, and the import log are under `analysis/ghidra-projects/` or `analysis/ghidra-logs/`, both covered by `.gitignore`.
- **CONFIRMED** — The source firmware remained unchanged. No camera was accessed.

## Interpretation and limits

The Phase 2C analysis strongly supported 32-bit little-endian ARM code, but the exact image base remained **UNKNOWN**: several nearby candidates resolved nearly the same number of pointer-like values, and none reached SUPPORTED confidence. A raw, offset-oriented import therefore preserves the file for Ghidra without forcing a candidate runtime address or an ARM variant.

This project is a data-only import baseline, not a disassembly or analysis result. Any later ARM-language import, image-base selection, or automatic analysis should be a separate, explicitly documented step using additional evidence.

**CONFIRMED — P510 physical-camera observation:** The camera owner directly observed Firmware Version 1.0 in the camera's Firmware version menu. This does not establish an internal build identifier, processor architecture, compatibility with P500/P520 firmware, or the existence of a newer P510 release. The P500 findings remain reference-only and do not establish P510 compatibility. See [P510-physical-camera-observations.md](../../p510/analysis/P510-physical-camera-observations.md).
