# P500 Firmware Payload: Phase 1B Read-Only Analysis

The source is reference firmware for the P500 only, not P510 firmware. The Nikon EXE was not executed. The embedded RAR archive was listed and extracted with the already-installed 7-Zip 25.01; the payload was read as data only. No payload was run, disassembled, patched, or modified.

## CONFIRMED — Extracted tree and payload identity

```text
firmware\extracted\P500\
└── P500Update\
    └── firmware\
        └── firmware.bin
```

- Exact filename: `firmware.bin`
- Relative path: `firmware\extracted\P500\P500Update\firmware\firmware.bin`
- Size: 14,614,648 bytes
- SHA-256: `80A297C8B4B77731EB2B3B5DC23D905D557A0052049402364B11A1F7849779B4`
- The archive listing reported CRC-32 `D5CC5508`, no encryption, and successful extraction/CRC check.
- The package member's recorded uncompressed size is 14,614,648 bytes; packed size is 4,781,788 bytes.
- The source package still matches its recorded SHA-256: `CA83DDCCD4B3E4CEBAA5C72BD65959F70C1138E3E6E2A273E14DF142C31C99CD`.

## CONFIRMED — First 512 bytes

```text
0000: 4C 45 4E 47 54 48 3D 37 34 37 31 31 30 34 20 53
0010: 47 35 38 33 20 56 45 52 3D 76 35 38 33 2D 38 30
0020: 20 44 56 52 3D 31 2E 31 30 20 53 55 4D 3D 37 36
0030: 35 39 35 31 39 31 37 20 4E 50 52 4F 47 20 4E 44
0040: 41 54 41 20 4E 4C 49 50 49 20 53 46 49 52 4D 0D
0050: 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20
0060: 06 00 00 EA 8F 00 00 EA 94 00 00 EA 99 00 00 EA
0070: 9E 00 00 EA FE FF FF EA 3F 00 00 EA 88 00 00 EA
0080: D1 F0 21 E3 D0 D0 9F E5 D2 F0 21 E3 CC D0 9F E5
0090: D3 F0 21 E3 C8 D0 9F E5 D7 F0 21 E3 C4 D0 9F E5
00A0: DB F0 21 E3 C0 D0 9F E5 DF F0 21 E3 BC D0 9F E5
00B0: E6 00 00 EB 01 00 00 EB DC 00 00 EA 00 00 A0 E1
00C0: F0 43 2D E9 A8 00 9F E5 A8 10 9F E5 00 20 41 E0
00D0: 00 40 A0 E3 00 50 A0 E3 00 60 A0 E3 00 70 A0 E3
00E0: 00 80 A0 E3 00 90 A0 E3 00 C0 A0 E3 00 E0 A0 E3
00F0: 07 00 00 EA F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8
0100: F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8
0110: F0 53 A0 E8 40 2F 52 E2 F5 FF FF 2A FF 20 12 E2
0120: F0 83 BD 08 20 20 52 E2 F0 53 A0 28 FC FF FF 2A
0130: 20 20 92 E2 F0 83 BD 08 04 20 52 E2 10 00 A0 28
0140: FC FF FF 2A 04 20 92 E2 F0 83 BD 08 01 20 52 E2
0150: 01 40 C0 24 FC FF FF 2A F0 83 BD E8 00 A0 FC 57
0160: 00 B0 FC 57 00 C0 FC 57 00 D0 FC 57 00 E0 FC 57
0170: 00 F0 FC 57 00 00 EA 57 28 40 F1 57 84 D1 9F E5
0180: 00 E0 8D E5 00 E0 4F E1 04 E0 8D E5 78 D1 9F E5
0190: DF F0 21 E3 0F 58 2D E9 68 01 9F E5 00 10 90 E5
01A0: 04 20 90 E5 06 00 2D E9 60 01 9F E5 00 10 90 E5
01B0: 01 10 81 E2 00 10 80 E5 54 01 9F E5 00 10 90 E5
01C0: 01 10 81 E2 00 10 80 E5 01 10 51 E2 06 00 00 1A
01D0: 0D 10 A0 E1 3C 01 9F E5 00 D0 90 E5 02 00 2D E9
01E0: 01 00 00 EA 00 00 A0 E1 00 00 A0 E1 00 10 0F E1
01F0: 40 20 81 E3 C0 30 01 E2 02 F0 21 E1 78 07 A0 E3
```

## CONFIRMED — Readable strings and component-like records

- The initial header text is `LENGTH=7471104 SG583 VER=v583-80 DVR=1.10 SUM=765951917 NPROG NDATA NLIPI SFIRM`.
- Additional component-like header strings and offsets:

| Offset | Readable record |
|---:|---|
| `0x720060` | `NPROG LENGTH=2184192 SG583 VER=v583-80 DVR=1.10 SUM=67364592` |
| `0x9354C0` | `NDATA LENGTH=3188736 SG583 VER=v583-80 DVR=1.10 SUM=287766792` |
| `0xC3FD20` | `NLIPI LENGTH=12 SG583 VER=v583-80 SUM=427` |
| `0xC3FD8C` | `SFIRM LENGTH=1770124 SG583 VER=v583-80 DVR=1.10 SUM=177731721` |
| `0xC3FDCB` | `LENGTH=1769920 SG583SLAVE VER=v583-80 DVR=1.10 SUM=177721714 NLIPI` |
| `0xDF000C` | `NLIPI LENGTH=12 SG583SLAVE VER=v583-80 SUM=427` |

- Model/product strings include `P500`, `COOLPIX P500`, `COOLPIX P500V1.1`, `NIKON DIGITAL CAMERA`, `NIKON DSC COOLPIX P500`, and `NIKON DSC COOLPIX P500-PTP`.
- Version/build strings include `Ver.1.10`, `VER=v583-80`, and `DVR=1.10`.
- Filesystem-related strings include `EXFAT`, `FAT12`, `FAT16`, and `FAT32`. Their presence does not establish which filesystem is used for a particular firmware partition.
- Copyright strings include `Copyright (c) 2009-2010 Tokyo Electron Device Ltd.`, `Copyright (c) 2000-2008 by FotoNation. All rights reserved.`, and `Copyright (C) 2010, Arcsoft Inc.`.
- No reliable operating-system or compiler-identification string was found. Other short architecture/toolchain-like matches were noisy fragments and are not treated as findings.

## LIKELY — Architecture and payload structure

- The instruction-like words beginning around offset `0x60` are consistent with 32-bit little-endian ARM code. This is a static byte-pattern inference, not a disassembly or independent processor identification.
- The repeated `NPROG`, `NDATA`, `NLIPI`, and `SFIRM` records, with differing lengths and `SG583`/`SG583SLAVE` identifiers, strongly suggest an internal multi-section or multi-component firmware container rather than a single flat code image.
- `COOLPIX P500V1.1` and `Ver.1.10` are consistent with a P500 firmware release labeled 1.1; the precise relationship among these version fields is not established.

## CONFIRMED — Entropy and recognizable signatures

- Whole-file Shannon entropy: 5.985927 bits/byte.
- Across 1 MiB windows (last window partial): 14 windows, min 2.450703, max 7.014606, mean 5.495707 bits/byte.
- No valid nested PE executable was found by checking `MZ` candidates and their PE-header offsets. `MZ`-like sequences occur at `0x2DE998`, `0x416388`, `0x476AB0`, `0x5AD2BB`, `0x5DA56D`, `0x5E28A0`, `0x6CD724`, `0x6E0F9D`, `0x95131D`, and `0x96436A`; PE-signature byte sequences also occur at `0x809CE0`, `0x80D87C`, and `0x8B187C`.
- JPEG SOI-like sequences occur at multiple offsets, including `0x2AC1E0`, `0x5D3705`, `0x5F0A07`, `0x5F2BA7`, `0x5F361B`, and `0x5F3627`. TIFF little-endian magic-like sequences occur at `0xA3233E` and other offsets. These signatures were not validated as complete image files.
- The scan found no RAR4, ZIP, 7-Zip, gzip, bzip2, XZ, Zstandard, LZ4, SquashFS, cramfs, U-Boot, ELF, or ROMFS magic in the payload.

## UNKNOWN — Remaining questions and scope

- The exact boundaries, checksums, and semantics of the component-like records have not been independently parsed or validated; the declared lengths are recorded as strings, not assumed to be standalone member sizes.
- The JPEG/TIFF-like sequences may be embedded assets or coincidental byte patterns; no image parser was used.
- No P510 conclusion follows from this P500-only payload. No P510 firmware was examined.
- No disassembly, patching, or modification was performed.
