# P500 Reference Package: Initial Read-Only Analysis

This package is P500 reference material only. It is not P510 firmware and no compatibility is implied. Analysis was limited to reading bytes and metadata; the executable was not run, and its payload was not extracted or decompressed.

## CONFIRMED — File identity and hashes

- Exact filename: `F-P500-V11W.exe`
- Relative path: `firmware\reference\P500\F-P500-V11W.exe`
- Size: 4,892,776 bytes
- SHA-256: `CA83DDCCD4B3E4CEBAA5C72BD65959F70C1138E3E6E2A273E14DF142C31C99CD`
- SHA-1: `AED92F1D9D7F1C7DB7C8809B6D59B2AC5B828E0A`
- MD5 (identification/comparison only): `DFD458DF65A53F2D38DEA2FD9F2C8A2F`
- The hashes are also recorded in `checksums/P500-reference-hashes.txt`.

## CONFIRMED — First 256 bytes

```text
0000: 4D 5A 50 00 02 00 00 00 04 00 0F 00 FF FF 00 00
0010: B8 00 00 00 00 00 00 00 40 00 1A 00 00 00 00 00
0020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0030: 00 00 00 00 00 00 00 00 00 00 00 00 00 02 00 00
0040: BA 10 00 0E 1F B4 09 CD 21 B8 01 4C CD 21 90 90
0050: 54 68 69 73 20 70 72 6F 67 72 61 6D 20 6D 75 73
0060: 74 20 62 65 20 72 75 6E 20 75 6E 64 65 72 20 57
0070: 69 6E 33 32 0D 0A 24 37 00 00 00 00 00 00 00 00
0080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0090: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00A0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00B0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00C0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00D0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00E0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00F0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```

## CONFIRMED — Outer executable and PE structure

- The file begins with `MZ`; the PE signature `PE\0\0` is at offset `0x200`, matching the DOS header's `e_lfanew`.
- PE machine is `0x014C` (Intel 386/x86); optional-header magic is `0x010B` (PE32); subsystem is `2` (Windows GUI).
- This describes the Windows package/installer executable, not the camera firmware's processor.
- PE timestamp field: raw value `0x46F268E6`.
- Sections: `.text` (raw size `0x13800`, entropy 6.46548), `.data` (`0xA00`, 4.90968), `.idata` (`0x1000`, 5.12446), `.rsrc` (`0x3C00`, 4.71166).
- The last PE section's raw data ends at `0x19400`. The file has 4,789,352 bytes after that point; this overlay begins with the RAR signature described below.
- PE OptionalHeader checksum field: `0x004ABB66`. This field was read, not independently validated as a payload checksum.
- PE certificate-table directory points to file offset `0x4A8C38`, size `0x1C30`, ending at EOF. Its `WIN_CERTIFICATE` header reports length `0x1C30`, revision `0x0200`, type `0x0002`. The signature/certificate was not validated.

## CONFIRMED — Archive and other signature observations

- RAR4 signature bytes `52 61 72 21 1A 07 00` occur at `0x19400`, exactly at the start of the PE overlay. They are followed by bytes shaped like a RAR4 main archive header.
- A `BZh` bzip2 signature-like sequence occurs at `0x384327`.
- Additional `MZ` sequences were observed at offsets `0x2826C`, `0x31099`, `0x348BB`, `0x40E48`, `0x5F270`, `0x77B58`, `0x7EC8A`, `0xAC382`, and `0xAF681`. These have not been validated as embedded executables.
- The signature scan did not identify ZIP, 7-Zip, gzip, XZ, Zstandard, CAB, ELF, SQLite, PDF, PNG, JPEG, GIF, or TIFF signatures in this file.

## LIKELY — Package/container interpretation

- The PE executable appears to be a Windows installer/self-extracting package with a RAR4 archive at its overlay. The RAR header CRC and full archive structure have not been checked.
- High whole-file entropy (7.996450 bits/byte) and 1 MiB window entropies (5 windows, min 7.954648, max 7.999218, mean 7.990187) are consistent with a large compressed or otherwise high-entropy payload; entropy alone cannot distinguish compression from encryption.
- Printable strings include `Setup`, `Presetup`, `Install`, `Extracting from %s`, CRC-error messages, and `NIKON CORPORATION` strings. They support an installer/package interpretation but do not establish the identity or validity of a signing entity.

## CONFIRMED — Nikon/model and firmware-related strings

- Printable strings include `P500Update`, `P500Update\firmware`, and `P500Update\firmware\firmware.bin`.
- The filename contains `V11W`; its exact version semantics are not established by this inspection.
- These are strings embedded in the package. The presence and contents of a corresponding archived `firmware.bin` member were not verified.
- ASCII `ARM`/`ROM`-like fragments also appear in high-entropy data; they are not reliable architecture evidence.

## UNKNOWN — Not determined in this phase

- The actual firmware payload's format, contents, compression/encryption, checksums, processor architecture, and components.
- Whether the RAR structure is complete and valid, whether the signature-like bzip2 sequence begins a real stream, and whether the PE certificate/signature is valid.
- Any compatibility with P510 firmware or hardware. Nothing in this analysis establishes such compatibility.

## UNKNOWN — Additional tooling needed for further static package inspection

- Validating archive members or identifying payload internals would require an appropriate archive/format parser. No additional tools were installed, and no extraction or decompression was performed.
