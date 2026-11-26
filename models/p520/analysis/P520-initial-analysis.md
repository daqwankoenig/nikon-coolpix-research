# P520 Reference Package: Initial Read-Only Analysis

This package is P520 reference material only. It is not P510 firmware and no compatibility is implied. Analysis was limited to reading bytes and metadata; the executable was not run, and its payload was not extracted or decompressed.

## CONFIRMED — File identity and hashes

- Exact filename: `F-P520-V11W.exe`
- Relative path: `firmware\reference\P520\F-P520-V11W.exe`
- Size: 74,551,288 bytes
- SHA-256: `CFDE64DD155C6DFA6FF6BD74AD807D7A3F615938DCA2190D72A075C8519E6DB2`
- SHA-1: `BC705FB5E8B385AC4B309B6CBC6BF3D716FE774E`
- MD5 (identification/comparison only): `C3CCFB11851216743C935984C97EE07F`
- The hashes are also recorded in `checksums/P520-reference-hashes.txt`.

## CONFIRMED — First 256 bytes

```text
0000: 4D 5A 90 00 03 00 00 00 04 00 00 00 FF FF 00 00
0010: B8 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00
0020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0030: 00 00 00 00 00 00 00 00 00 00 00 00 E8 00 00 00
0040: 0E 1F BA 0E 00 B4 09 CD 21 B8 01 4C CD 21 54 68
0050: 69 73 20 70 72 6F 67 72 61 6D 20 63 61 6E 6E 6F
0060: 74 20 62 65 20 72 75 6E 20 69 6E 20 44 4F 53 20
0070: 6D 6F 64 65 2E 0D 0D 0A 24 00 00 00 00 00 00 00
0080: 7D C6 81 DE 39 A7 EF 8D 39 A7 EF 8D 39 A7 EF 8D
0090: 1E 61 82 8D 31 A7 EF 8D 1E 61 94 8D 2A A7 EF 8D
00A0: 39 A7 EE 8D 92 A7 EF 8D 27 F5 7A 8D 3C A7 EF 8D
00B0: 30 DF 6C 8D 38 A7 EF 8D 30 DF 6B 8D 15 A7 EF 8D
00C0: 30 DF 7D 8D 38 A7 EF 8D 27 F5 7B 8D 38 A7 EF 8D
00D0: 30 DF 7E 8D 38 A7 EF 8D 52 69 63 68 39 A7 EF 8D
00E0: 00 00 00 00 00 00 00 00 50 45 00 00 4C 01 05 00
00F0: 66 D3 9D 4B 00 00 00 00 00 00 00 00 E0 00 03 01
```

## CONFIRMED — Outer executable and PE structure

- The file begins with `MZ`; the PE signature `PE\0\0` is at offset `0xE8`, matching the DOS header's `e_lfanew`.
- PE machine is `0x014C` (Intel 386/x86); optional-header magic is `0x010B` (PE32); subsystem is `2` (Windows GUI).
- This describes the Windows package/installer executable, not the camera firmware's processor.
- PE timestamp field: raw value `0x4B9DD366`.
- Sections: `.text` (raw size `0x10800`, entropy 6.57502), `.rdata` (`0x1A00`, 5.32677), `.data` (`0x200`, 3.54580), `.CRT` (`0x200`, 0.21310), `.rsrc` (`0x4000`, 4.66319).
- The last PE section's raw data ends at `0x16A00`. The file has 74,458,616 bytes after that point; this overlay begins with the RAR signature described below.
- PE OptionalHeader checksum field: `0x04720C1B`. This field was read, not independently validated as a payload checksum.
- PE certificate-table directory points to file offset `0x47176B8`, size `0x1940`, ending at EOF. Its `WIN_CERTIFICATE` header reports length `0x1940`, revision `0x0200`, type `0x0002`. The signature/certificate was not validated.

## CONFIRMED — Archive and other signature observations

- RAR4 signature bytes `52 61 72 21 1A 07 00` occur at `0x16A00`, exactly at the start of the PE overlay. They are followed by bytes shaped like a RAR4 main archive header.
- Signature-like sequences were observed at: gzip `0x2A4F4C6`, `0x2D7C5A2`; bzip2 `0x16580A1`, `0x1F7ED93`, `0x2C20B0C`, `0x35E340F`; Zstandard `0x3B2E1E8`; JPEG `0x1D6B54F`, `0x29813DB`; and LHA-like `-lh` markers `0x4E4E03`, `0x186EF2F`, `0x343A7D7`, `0x3D06B45`, `0x3EAC447`.
- Additional `MZ` sequences were observed at offsets `0x83B5F`, `0x8F3BD`, `0x8F873`, `0x932E3`, `0xAF3FA`, `0xB8A8A`, `0xBFB0D`, `0xE0D5D`, and `0xFB372`. These are the first ten scan results including the outer `MZ` at offset zero; they have not been validated as embedded executables.
- The signature scan did not identify ZIP, 7-Zip, RAR5, XZ, LZ4, CAB, ELF, SQLite, PDF, PNG, GIF, or TIFF signatures in this file.

## LIKELY — Package/container interpretation

- The PE executable appears to be a Windows installer/self-extracting package with a RAR4 archive at its overlay. The RAR header CRC and full archive structure have not been checked.
- High whole-file entropy (7.999882 bits/byte) and 1 MiB window entropies (72 windows, min 7.964002, max 7.999820, mean 7.998985) are consistent with a large compressed or otherwise high-entropy payload; entropy alone cannot distinguish compression from encryption.
- Printable strings include `Setup`, `Presetup`, `Install`, `Extracting from %s`, CRC-error messages, and `NIKON CORPORATION` strings. They support an installer/package interpretation but do not establish the identity or validity of a signing entity.
- The additional compression/image signature-like byte sequences occur within high-entropy data and may be coincidental or embedded members. They were not validated as independent streams or images.

## CONFIRMED — Nikon/model and firmware-related strings

- Printable strings include `P520Update`, `P520Update\firmware`, and `P520Update\firmware\firmware.bin`.
- The filename contains `V11W`; its exact version semantics are not established by this inspection.
- These are strings embedded in the package. The presence and contents of a corresponding archived `firmware.bin` member were not verified.
- ASCII `ARM`/`ROM`-like fragments also appear in high-entropy data; they are not reliable architecture evidence.

## UNKNOWN — Not determined in this phase

- The actual firmware payload's format, contents, compression/encryption, checksums, processor architecture, and components.
- Whether the RAR structure is complete and valid, whether the additional signature-like sequences begin real streams or embedded files, and whether the PE certificate/signature is valid.
- Any compatibility with P510 firmware or hardware. Nothing in this analysis establishes such compatibility.

## UNKNOWN — Additional tooling needed for further static package inspection

- Validating archive members or identifying payload internals would require an appropriate archive/format parser. No additional tools were installed, and no extraction or decompression was performed.
