# P520 Firmware Payload: Phase 1B Read-Only Analysis

The source is reference firmware for the P520 only, not P510 firmware. The Nikon EXE was not executed. The embedded RAR archive was listed and extracted with the already-installed 7-Zip 25.01; the payload was read as data only. No payload was run, disassembled, patched, or modified.

## CONFIRMED — Extracted tree and payload identity

```text
firmware\extracted\P520\
└── P520Update\
    └── firmware\
        └── firmware.bin
```

- Exact filename: `firmware.bin`
- Relative path: `firmware\extracted\P520\P520Update\firmware\firmware.bin`
- Size: 81,264,928 bytes
- SHA-256: `631A4C6AB34E3BE5C7EE1153AD1A7D93986DA2853C79F572B63A3E23129B979C`
- The archive listing reported CRC-32 `1DFDC34C`, no encryption, and successful extraction/CRC check.
- The package member's recorded uncompressed size is 81,264,928 bytes; packed size is 74,451,802 bytes.
- The source package still matches its recorded SHA-256: `CFDE64DD155C6DFA6FF6BD74AD807D7A3F615938DCA2190D72A075C8519E6DB2`.

## CONFIRMED — First 512 bytes

```text
0000: 50 35 32 30 00 00 00 00 00 00 00 00 00 00 00 00
0010: 20 56 65 72 2E 31 2E 31 00 00 00 00 00 00 00 00
0020: 9E A1 08 6F 35 77 C1 DE EB 3B 93 0F 51 ED 2E 34
0030: E0 FA 8C CB 3B BD 6E A1 45 10 0E EC CD E4 A3 95
0040: 1F B3 4C B1 B1 6E 64 77 92 81 A8 D0 1D 0B D9 41
0050: 9E 30 19 B6 D3 03 31 43 BF 0A CB C3 3A 6C C2 7B
0060: B9 C5 FA F1 7D 16 54 7E 85 48 D8 55 10 F7 86 D1
0070: 8E 63 15 DB 6A 8D 94 36 C4 BD B4 A4 74 69 A5 9B
0080: 1B 8D 72 85 9F E1 90 98 3B 2C 50 FE E9 FD F0 9D
0090: BE CE 21 78 FE E5 CF E6 5F 39 6B 1B B5 AC 40 64
00A0: 1F FE 87 D5 83 9F 61 04 25 67 5E B7 22 3F FB 45
00B0: DD B2 17 91 86 2D 33 B8 4A 74 AF 6A 29 A9 66 0E
00C0: AD C0 CC 8B 92 C7 EE FB 9B E5 09 A4 F5 D7 62 42
00D0: F2 49 7A 56 E6 EC 7F EF 64 14 75 C9 6D 37 E2 38
00E0: 76 D9 12 85 99 C9 89 2F 97 46 29 B1 2B 39 06 02
00F0: E8 8E 1B FD 76 9B 97 5C 3D 04 1C DA A1 24 58 F3
0100: 82 DE 5D 76 7C CF 02 19 DC 80 FB 2D F3 0C D3 83
0110: E1 E5 CD B0 36 F4 89 FD 9F A4 22 4B E8 21 2A 42
0120: 81 41 D6 09 AA A9 1F 00 91 DB 4D 69 A7 B9 A2 C2
0130: FE 79 37 C0 AC 80 8C 79 36 9C B6 8A 33 3A 7D 4B
0140: 5D 53 92 D7 8F B0 62 AD 98 61 76 B6 A3 2C 7A 9F
0150: 9C 6C C7 D8 0C DD EF 9D 39 56 15 AD E4 B2 1C A5
0160: BB 99 24 9F A3 C8 8A A0 E3 A8 06 33 CE 29 58 0F
0170: 60 83 CB BD C1 52 4A E8 1A 63 6A 7A AA A7 7A 45
0180: F4 6D AC EC AE 81 E3 98 39 70 8E 90 36 93 2C 43
0190: E8 2F FF 1E C4 34 11 38 95 5A B5 CD 5B B2 9E BA
01A0: 61 1F 59 B3 49 4E BA DA 2B 04 80 61 79 E1 26 9B
01B0: 33 57 C9 F7 FD FC ED 66 14 14 71 BC D6 77 B8 D0
01C0: 77 22 12 ED FC 16 30 25 91 85 D7 72 23 09 BC 9C
01D0: 20 AB A4 30 85 3D A1 31 F2 74 AB 1F B4 E0 3C E6
01E0: 60 B9 CC 53 5C 17 57 F1 95 24 F7 67 FC E7 D8 DC
01F0: 72 EE C5 2B 50 44 CC 80 07 66 C2 0C 79 FA 86 2D
```

## CONFIRMED — Readable strings

- At offset `0x0`, the payload begins with `P520`, followed by zero padding.
- At offset `0x10`, the header contains ` Ver.1.1`, followed by zero padding; bytes from `0x20` onward appear high-entropy.
- The string scan found no reliable `Nikon`, `COOLPIX`, operating-system, bootloader, filesystem, or compiler/copyright strings elsewhere in the payload.
- Short matches such as `ARM`, `QNX`, `GCC`, `NEC`, `LZ4`, and `UDF` occurred inside otherwise noisy printable fragments. They are not treated as reliable identification strings.

## LIKELY — Payload structure and entropy

- The 32-byte visible prefix (model/version fields plus padding) followed by high-entropy data is consistent with a short model/version header preceding an opaque data region.
- Whole-file Shannon entropy is 7.999998 bits/byte. Across 1 MiB windows (last window partial): 78 windows, min 7.999732, max 7.999969, mean 7.999840 bits/byte.
- This near-maximum entropy is consistent with encrypted or compressed data, but cannot distinguish those possibilities or prove encryption.
- The uniformly high-entropy region prevents a reliable processor/architecture inference from printable strings or simple byte signatures.

## CONFIRMED — Recognizable signatures and component candidates

- No recognized PE, ELF, RAR, ZIP, 7-Zip, XZ, Zstandard, LZ4, SquashFS, cramfs, U-Boot, or ROMFS signature was identified.
- gzip-like sequences occur at `0xD91273`, `0x25C2327`, `0x2E5DAED`, `0x2F2014E`, `0x35E07A1`, and `0x3D9C4CC`; bzip2-like sequences occur at `0xDF0826`, `0x115C195`, `0x140B565`, `0x1BB453D`, `0x2DA2797`, `0x2F0D55E`, and `0x3D991CC`.
- JPEG SOI-like byte sequences occur at `0x50982C`, `0x7AA24B`, `0xADFFD8`, `0x32FD643`, `0x3B475CC`, `0x405C77F`, `0x419E30C`, and `0x43B9050`. These were not validated as complete JPEG files.
- `MZ`-like sequences occur at multiple offsets, but checking their DOS-header PE offsets found no valid nested PE candidates.

## HYPOTHESIS — Possible interpretation

- The header and opaque region may represent a P520-specific encoded firmware image or container. The signature-like occurrences may be coincidental in high-entropy data, or may indicate internal compressed components; neither explanation was verified.
- No independent subcomponent boundary or header was established beyond the initial model/version prefix.

## UNKNOWN — Remaining questions and scope

- Whether the high-entropy region is compressed, encrypted, or a mixture; its internal framing, checksums, payload components, and architecture.
- Whether any gzip-, bzip2-, or JPEG-like sequence begins a real embedded stream/file.
- The exact semantics of `Ver.1.1` and any relationship to Nikon's release numbering.
- Any compatibility with P510 firmware or hardware. Nothing in this P520-only analysis establishes such compatibility.
- No P510 firmware was examined; no disassembly, patching, or modification was performed.
