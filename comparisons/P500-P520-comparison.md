# P500 / P520 Reference Package Comparison

Both files are neighboring-model reference packages only. Neither is P510 firmware, and the observations below do not establish P510 compatibility. The files were only read as bytes: neither executable was run, nor was any payload extracted or decompressed.

## CONFIRMED — Package inventory and hashes

| Model reference | Exact filename and relative path | Size (bytes) | SHA-256 |
|---|---|---:|---|
| P500 | `F-P500-V11W.exe` — `firmware\reference\P500\F-P500-V11W.exe` | 4,892,776 | `CA83DDCCD4B3E4CEBAA5C72BD65959F70C1138E3E6E2A273E14DF142C31C99CD` |
| P520 | `F-P520-V11W.exe` — `firmware\reference\P520\F-P520-V11W.exe` | 74,551,288 | `CFDE64DD155C6DFA6FF6BD74AD807D7A3F615938DCA2190D72A075C8519E6DB2` |

- P500 SHA-1: `AED92F1D9D7F1C7DB7C8809B6D59B2AC5B828E0A`; MD5: `DFD458DF65A53F2D38DEA2FD9F2C8A2F` (identification/comparison only).
- P520 SHA-1: `BC705FB5E8B385AC4B309B6CBC6BF3D716FE774E`; MD5: `C3CCFB11851216743C935984C97EE07F` (identification/comparison only).
- Full hash records are in `checksums/P500-reference-hashes.txt` and `checksums/P520-reference-hashes.txt`.

## CONFIRMED — Container/header similarities and differences

- Both files are PE32 Windows GUI executables for machine `0x014C` (Intel 386/x86). These are host-side package executables; this does not identify either camera's processor.
- P500 PE signature is at `0x200`, with four sections; P520 PE signature is at `0xE8`, with five sections. The section names and sizes differ.
- Both have a PE certificate-table directory ending exactly at file EOF. Each table begins with `WIN_CERTIFICATE` revision `0x0200`, type `0x0002`; certificate/signature validity was not checked.
- Their first two bytes are `MZ`; their longest identical prefix is only 2 bytes. The first 64 bytes, and the first 4,096 bytes, otherwise differ.
- A 64-byte all-zero block at absolute offset `0x3C0` is identical in both files; this is low-information padding.

## CONFIRMED — Update packaging and common byte sequences

- A RAR4 signature and RAR4-main-header-shaped bytes occur at each PE overlay start: P500 offset `0x19400`; P520 offset `0x16A00`.
- The first 170 bytes starting at those respective RAR markers are identical. The common initial 32 bytes are:

  ```text
  52 61 72 21 1A 07 00 CF 90 73 00 00 0D 00 00 00 00 00 00 00
  F2 8B 7A 00 80 23 00 73 00 00 00 71
  ```

- Both packages contain common printable strings including `Setup`, `Presetup`, `Install`, `Software\Microsoft\Windows\CurrentVersion`, and `NIKON CORPORATION`.
- Model-specific strings identify `P500Update\firmware\firmware.bin` and `P520Update\firmware\firmware.bin`, respectively. These are embedded path strings; the existence and contents of corresponding archive members were not verified.

## CONFIRMED — Size and structural differences

| Observation | P500 | P520 |
|---|---:|---:|
| PE overlay start | `0x19400` | `0x16A00` |
| Bytes after last PE section (overlay length) | 4,789,352 | 74,458,616 |
| PE sections | `.text`, `.data`, `.idata`, `.rsrc` | `.text`, `.rdata`, `.data`, `.CRT`, `.rsrc` |
| PE OptionalHeader checksum field | `0x004ABB66` | `0x04720C1B` |

- P520 is 69,658,512 bytes larger than P500. The difference in size does not establish a difference in firmware feature set or compatibility.
- The two embedded RAR lead-ins match for 170 bytes, but archive contents and full structural similarity remain unexamined.

## CONFIRMED — Entropy and signature observations

- Whole-file Shannon entropy is 7.996450 bits/byte for P500 and 7.999882 bits/byte for P520.
- Across 1 MiB windows, P500 has 5 windows (min 7.954648, max 7.999218, mean 7.990187); P520 has 72 windows (min 7.964002, max 7.999820, mean 7.998985).
- Both contain RAR4 markers at the PE overlay. P500 also contains a `BZh` sequence at `0x384327`.
- P520 has gzip-, bzip2-, Zstandard-, JPEG-, and LHA-like signature sequences at offsets listed in `analysis/P520-initial-analysis.md`; they have not been validated as separate streams or files.
- The PE OptionalHeader checksum values are fields in the Windows wrappers, not verified checksums for the contained firmware. Installer strings mention CRC errors, but no archive-member CRC was checked.

## LIKELY — Interpretation

- Both appear to use a similar Windows installer plus RAR4-based overlay packaging pattern. The matching 170-byte archive lead-in and shared installer strings support similar packaging, but do not prove identical tools, archive contents, or update mechanisms.
- The very high entropy across most 1 MiB windows is consistent with compressed or otherwise high-entropy package data; it cannot distinguish compression from encryption.
- The P520's additional signature-like occurrences may indicate embedded compressed/image data, or may be coincidental byte patterns. No embedded component was validated beyond the outer PE and RAR4 lead-in.

## UNKNOWN — Firmware, architecture, and Nikon-specific conclusions

- Actual firmware member names, payload bytes, component layout, compression/encryption, and firmware-level checksums.
- Processor architecture or instruction set used by either camera. The x86 PE headers describe only Windows executables; noisy `ARM`/`ROM` strings are not sufficient evidence.
- Whether either PE certificate is valid, who signed it, or whether the RAR archives are complete and valid.
- The meaning of the `V11W` filename suffix and whether it encodes a release/version.
- Any binary compatibility or transferability among P500, P510, and P520. No conclusion about P510 is confirmed by these reference packages; any neighboring-model-based P510 conclusion must remain a hypothesis until checked against actual P510 firmware or hardware.

## UNKNOWN — Next analysis requirements

- Archive validation, member inventory, decompression, and payload-specific analysis require suitable parsing tools. None were installed or used in this phase. No payload was extracted or decompressed.
