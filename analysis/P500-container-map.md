# P500 Firmware Container Map — Phase 1C

## CONFIRMED — Scope and integrity

- The requested top-level path `firmware\extracted\P500\firmware.bin` does not exist. The package member extracted in Phase 1B is at `firmware\extracted\P500\P500Update\firmware\firmware.bin`; that file was analyzed without modification.
- Payload size: 14,614,648 bytes (`0xDF0078`).
- Payload SHA-256 before and after this analysis: `80A297C8B4B77731EB2B3B5DC23D905D557A0052049402364B11A1F7849779B4`.
- P500 source EXE remains unchanged and matches SHA-256 `CA83DDCCD4B3E4CEBAA5C72BD65959F70C1138E3E6E2A273E14DF142C31C99CD`.
- No P520 payload was analyzed in this phase. No firmware was written, carved, disassembled, patched, or executed. No camera was accessed.

## CONFIRMED — Initial 96-byte header

The initial 96 bytes contain an ASCII record followed by padding. The first payload bytes begin at `0x60`.

| Field | Exact offset | Observed value |
|---|---:|---|
| `LENGTH=` | `0x00000000` | `7471104` |
| `SG583` | `0x0000000F` | `SG583` |
| `VER=` | `0x00000015` | `v583-80` |
| `DVR=` | `0x00000021` | `1.10` |
| `SUM=` | `0x0000002A` | `765951917` |
| record-type list | `0x00000038` | `NPROG NDATA NLIPI SFIRM` |
| CR/LF | `0x0000004F` | `0D 0A` |
| payload begins | `0x00000060` | first aligned code-like words |

The visible header text is:

```text
LENGTH=7471104 SG583 VER=v583-80 DVR=1.10 SUM=765951917 NPROG NDATA NLIPI SFIRM
```

`LENGTH`/`SUM` values are ASCII decimal numbers. No numerical load-address field appears in this initial header.

## CONFIRMED — Record map

Each record header occupies 96 bytes (`0x60`). For each row, `LENGTH` equals the bytes after that record's header, and the resulting end lands exactly on the next record header or EOF. Each `SUM` equals the simple sum of those payload bytes.

| Header offset | Identifier / observed fields | Payload offset | Declared length | End boundary (exclusive) | `SUM` field | Payload byte sum | Entropy (bits/byte) | Possible load address / likely purpose |
|---:|---|---:|---:|---:|---:|---:|---:|---|
| `0x00000000` | Initial header; type list includes `NPROG`; `SG583`, `VER=v583-80`, `DVR=1.10` | `0x00000060` | 7,471,104 (`0x720000`) | `0x00720060` | 765,951,917 | 765,951,917 (exact) | No load address recorded. **LIKELY** primary program section; its start contains a branch-vector-like table. |
| `0x00720060` | `NPROG`; `SG583`, `VER=v583-80`, `DVR=1.10` | `0x007200C0` | 2,184,192 (`0x215400`) | `0x009354C0` | 67,364,592 | 67,364,592 (exact) | No load address identified. **LIKELY** second program record. |
| `0x009354C0` | `NDATA`; `SG583`, `VER=v583-80`, `DVR=1.10` | `0x00935520` | 3,188,736 (`0x30A800`) | `0x00C3FD20` | 287,766,792 | 287,766,792 (exact) | No load address identified. **LIKELY** data record. |
| `0x00C3FD20` | `NLIPI`; `SG583`, `VER=v583-80` | `0x00C3FD80` | 12 (`0xC`) | `0x00C3FD8C` | 427 | 427 (exact) | No load address identified. **LIKELY** short trailer/metadata record; its 12 bytes are opaque here. |
| `0x00C3FD8C` | `SFIRM`; `SG583`, `VER=v583-80`, `DVR=1.10` | `0x00C3FDEC` | 1,770,124 (`0x1B028C`) | `0x00DF0078` (EOF) | 177,731,721 | 177,731,721 (exact) | No load address identified. **LIKELY** enclosing slave-firmware record; payload contains the nested record and terminal `NLIPI`. |
| `0x00C3FDEC` | Nested header: `LENGTH=1769920 SG583SLAVE VER=v583-80 DVR=1.10` | `0x00C3FE4C` | 1,769,920 (`0x1B0220`) | `0x00DF000C` | 177,721,714 | 177,721,714 (exact) | No load address identified. **LIKELY** slave-program image. |
| `0x00DF000C` | `NLIPI`; `SG583SLAVE`, `VER=v583-80` | `0x00DF006C` | 12 (`0xC`) | `0x00DF0078` (EOF) | 427 | 427 (exact) | No load address identified. **LIKELY** terminal trailer/metadata record. |

The `SFIRM` length is measured from `0xC3FDEC` through EOF. Its payload therefore encloses the 96-byte `SG583SLAVE` header, its 1,769,920-byte payload, and the final 108-byte `NLIPI` record. The nested slave payload ends exactly where that final `NLIPI` header begins.

## CONFIRMED — Meaning and offsets of the requested identifiers

- `NPROG`, `NDATA`, `NLIPI`, and `SFIRM` occur in the initial type list and at record headers. Their placement and length/checksum behavior support treating them as record/component identifiers, not merely arbitrary strings.
- `SG583` occurs in record metadata and in static string tables. `SG583SLAVE` marks the nested record. These are identifiers/tags; their vendor-specific meaning is not established.
- The same identifiers also occur in executable string tables at `0x620278`–`0x620290`, and `SG583` occurs in diagnostic/product strings. Those occurrences are not record boundaries.
- Occurrence search was case-sensitive ASCII; the context window below is up to four bytes before and three bytes after the identifier. For `SG583`, matches within `SG583SLAVE` are included.

| Identifier | Exact offset | Surrounding bytes (hex) |
|---|---:|---|
| `SG583` | `0x0000000F` | `31 30 34 20 53 47 35 38 33 20 56 45 52` |
| `SG583` | `0x0062024C` | `00 00 00 00 53 47 35 38 33 53 4C 41 56` |
| `SG583` | `0x0062036C` | `54 48 3D 00 53 47 35 38 33 00 00 00 53` |
| `SG583` | `0x006203A8` | `00 00 00 00 53 47 35 38 33 53 4C 41 56` |
| `SG583` | `0x00620675` | `52 44 59 00 53 47 35 38 33 00 00 00 43` |
| `SG583` | `0x006206ED` | `52 55 4E 00 53 47 35 38 33 00 00 00 41` |
| `SG583` | `0x00620849` | `41 44 4A 00 53 47 35 38 33 00 00 00 49` |
| `SG583` | `0x006208F5` | `41 44 4A 00 53 47 35 38 33 00 00 00 25` |
| `SG583` | `0x006461C8` | `80 DE 28 00 53 47 35 38 33 00 00 00 53` |
| `SG583` | `0x006494E0` | `00 00 00 00 53 47 35 38 33 00 00 00 4E` |
| `SG583` | `0x00720075` | `31 39 32 20 53 47 35 38 33 20 56 45 52` |
| `SG583` | `0x007200C0` | `20 20 20 20 53 47 35 38 33 20 20 20 FF` |
| `SG583` | `0x009354D5` | `37 33 36 20 53 47 35 38 33 20 56 45 52` |
| `SG583` | `0x00C3FD31` | `31 32 20 20 53 47 35 38 33 20 56 45 52` |
| `SG583` | `0x00C3FDA1` | `31 32 34 20 53 47 35 38 33 20 56 45` |
| `SG583` | `0x00C3FDFB` | `39 32 30 20 53 47 35 38 33 53 4C 41 56` |
| `SG583` | `0x00DF001D` | `31 32 20 20 53 47 35 38 33 53 4C 41 56` |
| `NPROG` | `0x00000038` | `39 31 37 20 4E 50 52 4F 47 20 4E 44 41` |
| `NPROG` | `0x00620278` | `04 00 00 00 4E 50 52 4F 47 00 00 00 4E` |
| `NPROG` | `0x00720060` | `00 00 00 00 4E 50 52 4F 47 20 4C 45 4E` |
| `NDATA` | `0x0000003E` | `52 4F 47 20 4E 44 41 54 41 20 4E 4C 49` |
| `NDATA` | `0x00620280` | `47 00 00 00 4E 44 41 54 41 00 00 00 4E` |
| `NDATA` | `0x009354C0` | `FF FF FF FF 4E 44 41 54 41 20 4C 45 4E` |
| `NLIPI` | `0x00000044` | `41 54 41 20 4E 4C 49 50 49 20 53 46 49` |
| `NLIPI` | `0x00620288` | `41 00 00 00 4E 4C 49 50 49 00 00 00 53` |
| `NLIPI` | `0x00C3FD20` | `00 00 00 00 4E 4C 49 50 49 20 4C 45 4E` |
| `NLIPI` | `0x00C3FE29` | `37 31 34 20 4E 4C 49 50 49 0D 0A 20 20` |
| `NLIPI` | `0x00DF000C` | `B5 98 03 97 4E 4C 49 50 49 20 4C 45 4E` |
| `SFIRM` | `0x0000004A` | `49 50 49 20 53 46 49 52 4D 0D 0A 20 20` |
| `SFIRM` | `0x00620290` | `49 00 00 00 53 46 49 52 4D 00 00 00 25` |
| `SFIRM` | `0x00C3FD8C` | `0C 00 80 00 53 46 49 52 4D 20 4C 45 4E` |

## CONFIRMED — Other record fields, apparent addresses, and checksums

- Additional `LENGTH=` field offsets are `0x720066`, `0x9354C6`, `0xC3FD26`, `0xC3FD92`, `0xC3FDEC`, and `0xDF0012`. The first header has `LENGTH=` at `0x0`.
- Record `VER=` offsets are `0x15`, `0x72007B`, `0x9354DB`, `0xC3FD37`, `0xC3FDA7`, `0xC3FE06`, and `0xDF0028`. `DVR=` offsets are `0x21`, `0x720087`, `0x9354E7`, `0xC3FDB3`, and `0xC3FE12`.
- Record `SUM=` offsets are `0x2A`, `0x720090`, `0x9354F0`, `0xC3FD43`, `0xC3FDBC`, `0xC3FE1B`, and `0xDF0034`.
- The `SUM` values exactly equal the byte sum of the payload ranges in the record map. This confirms an additive byte-sum check for these records; it is not a cryptographic integrity mechanism.
- `LOADADDRESS=` occurs at `0x6202AC` and `0x6202C4` in a NUL-separated format-string table alongside `LENGTH=`, `SUM=`, `VER=`, and `DVR=` templates. These are not populated load-address fields.
- The secondary NPROG data starts with `SG583` and includes `FF FF FF FF 1A 00 AA 10`; the little-endian value `0x10AA001A` has no validated meaning and is not assigned as a load address.
- Aligned little-endian words at file offsets `0x15C`–`0x178` include `0x57FCA000`, `0x57FCB000`, `0x57FCC000`, `0x57FCD000`, `0x57FCE000`, `0x57FCF000`, `0x57EA0000`, and `0x57F14028`. **LIKELY:** these are address/pointer-like values, possibly a memory-map table. No external address map was used, so they are not identified as section load addresses.

## CONFIRMED — Entropy by 256 KiB windows

Shannon entropy uses base-2 bits per byte. Blocks are aligned from file offset zero; block 55 is the 196,728-byte tail. The transitions are summarized below the complete table.

| Block | Range | H | Block | Range | H | Block | Range | H | Block | Range | H |
|---:|---|---:|---:|---|---:|---:|---|---:|---:|---|---:|
| 0 | `0x00000000–0x00040000` | 5.963442 | 1 | `0x00040000–0x00080000` | 5.852423 | 2 | `0x00080000–0x000C0000` | 5.794628 | 3 | `0x000C0000–0x00100000` | 5.919122 |
| 4 | `0x00100000–0x00140000` | 5.813495 | 5 | `0x00140000–0x00180000` | 6.013870 | 6 | `0x00180000–0x001C0000` | 5.825763 | 7 | `0x001C0000–0x00200000` | 5.615631 |
| 8 | `0x00200000–0x00240000` | 5.749876 | 9 | `0x00240000–0x00280000` | 5.757236 | 10 | `0x00280000–0x002C0000` | 6.005166 | 11 | `0x002C0000–0x00300000` | 5.916696 |
| 12 | `0x00300000–0x00340000` | 5.925044 | 13 | `0x00340000–0x00380000` | 5.696627 | 14 | `0x00380000–0x003C0000` | 5.786709 | 15 | `0x003C0000–0x00400000` | 5.818605 |
| 16 | `0x00400000–0x00440000` | 5.798307 | 17 | `0x00440000–0x00480000` | 5.796701 | 18 | `0x00480000–0x004C0000` | 5.877158 | 19 | `0x004C0000–0x00500000` | 6.191747 |
| 20 | `0x00500000–0x00540000` | 6.148622 | 21 | `0x00540000–0x00580000` | 6.001786 | 22 | `0x00580000–0x005C0000` | 5.826071 | 23 | `0x005C0000–0x00600000` | 5.912213 |
| 24 | `0x00600000–0x00640000` | 5.237502 | 25 | `0x00640000–0x00680000` | 5.979180 | 26 | `0x00680000–0x006C0000` | 5.689057 | 27 | `0x006C0000–0x00700000` | 5.599139 |
| 28 | `0x00700000–0x00740000` | 1.533829 | 29 | `0x00740000–0x00780000` | 2.838572 | 30 | `0x00780000–0x007C0000` | 2.536942 | 31 | `0x007C0000–0x00800000` | 2.587697 |
| 32 | `0x00800000–0x00840000` | 2.524580 | 33 | `0x00840000–0x00880000` | 2.867355 | 34 | `0x00880000–0x008C0000` | 3.051303 | 35 | `0x008C0000–0x00900000` | 2.796677 |
| 36 | `0x00900000–0x00940000` | 3.481917 | 37 | `0x00940000–0x00980000` | 7.730577 | 38 | `0x00980000–0x009C0000` | 7.736860 | 39 | `0x009C0000–0x00A00000` | 7.806727 |
| 40 | `0x00A00000–0x00A40000` | 7.884808 | 41 | `0x00A40000–0x00A80000` | 7.311094 | 42 | `0x00A80000–0x00AC0000` | 3.816369 | 43 | `0x00AC0000–0x00B00000` | 1.973632 |
| 44 | `0x00B00000–0x00B40000` | 4.434706 | 45 | `0x00B40000–0x00B80000` | 4.512690 | 46 | `0x00B80000–0x00BC0000` | 5.305720 | 47 | `0x00BC0000–0x00C00000` | 4.909885 |
| 48 | `0x00C00000–0x00C40000` | 4.995627 | 49 | `0x00C40000–0x00C80000` | 5.654382 | 50 | `0x00C80000–0x00CC0000` | 5.757101 | 51 | `0x00CC0000–0x00D00000` | 5.809820 |
| 52 | `0x00D00000–0x00D40000` | 5.926646 | 53 | `0x00D40000–0x00D80000` | 5.970027 | 54 | `0x00D80000–0x00DC0000` | 5.196863 | 55 | `0x00DC0000–0x00DF0078` | 5.783151 |

- Whole-file entropy is 5.985927 bits/byte.
- **CONFIRMED:** entropy drops across the first NPROG boundary at `0x720060` (block 28 straddles the boundary and is 1.533829; following blocks are mostly 2.5–3.5).
- **CONFIRMED:** entropy rises sharply after the NDATA header at `0x9354C0` (block 37 begins just after the boundary at 7.730577; blocks 37–41 are 7.31–7.88).
- **CONFIRMED:** the SFIRM/nested slave region begins at `0xC3FD8C`/`0xC3FDEC`, inside block 48; following blocks are generally around 5.65–5.97.
- **HYPOTHESIS:** these entropy transitions are consistent with the identified records containing different mixtures of code, structured data, and high-entropy regions. Entropy alone does not identify a section's function or compression.

## CONFIRMED — Architecture indicators

- The main NPROG payload begins at `0x60` with eight aligned 32-bit little-endian words: `EA000006 EA00008F EA000094 EA000099 EA00009E EAFFFFFE EA00003F EA000088`.
- The nested `SG583SLAVE` payload begins at `0xC3FE4C` with a second eight-word sequence: `EA000006 EA00008E EA0000C7 EA00009F EA0000B1 EAFFFFFE EA00003F EA0000C1`.
- Both sequences have the encoding pattern of ARM unconditional branch instructions. Their branch destinations, interpreted relative to their respective payload starts, fall within the corresponding program regions. Each table includes a branch-to-self entry.
- Four-byte-aligned scans of the main NPROG payload found 254,604 branch/branch-link-pattern words, 11,554 `STMFD SP!`-pattern words, 11,591 `LDMFD SP!`-pattern words, and 6,901 `BX`-pattern words. The nested slave payload contained 54,272, 2,855, 2,797, and 2,465 of those patterns, respectively. These are opcode-pattern counts, not a disassembly; data can create false matches.
- The main payload contains aligned little-endian values `0x57FCA000` through `0x57FCF000` in a 4 KiB sequence at offsets `0x15C`–`0x170`, plus nearby values `0x57EA0000` and `0x57F14028`. **LIKELY:** these are pointer or memory-map references.
- No reliable `ARM`, GCC/GNU, IAR, Keil, or other compiler-identification string was found. No stack-pointer value was established from the vector-like tables; they are branch-vector-shaped rather than Cortex-M-style initial-SP tables.

## CONFIRMED — Requested strings and offsets

| Category | Useful strings and offsets |
|---|---|
| Nikon/model | `NIKON DIGITAL CAMERA` at `0x281C44` and `0x620B58`; `NIKON CO.,LTD.` at `0x29BABC`; `P500` at `0x61AF04`; `COOLPIX P500` at `0x620CF0`; `COOLPIX P500V1.1` at `0x646240`; `Nikon Corporation` at `0x646D10`; `NIKON DSC COOLPIX P500` at `0x649814`; `NIKON DSC COOLPIX P500-PTP` at `0x64982C`. |
| Version/build | `VER=v583-80`, `DVR=1.10`, and `SUM=...` occur in the record headers listed above; `Ver.1.10` at `0x620B91`; `COOLPIX P500V1.1` at `0x646240`. |
| Architecture/compiler | No reliable architecture-name or compiler string. Short `gnu`-like matches were noise, not GCC/GNU identification. |
| OS/RTOS | No reliable RTOS or operating-system name found. |
| Filesystem | `EXFAT` at `0x5F0B8C`; `FAT12` at `0x5F0BB4`; `FAT32` at `0x5F0BC0`; `FAT16` at `0x5F0BCC`. |
| JPEG/USB/PTP | `Photo - JPEG` at `0x280A48`; `jpeg` at `0x2A7584`; `JpegBuffer_TopAddrW()` at `0x64628B`; `CamUsbInitMode` at `0x61F6B4`; `CamDebugUsbMode` at `0x61FB88`; `USB IN` at `0x620785`; `NIKON DSC COOLPIX P500-PTP` at `0x64982C`. |
| Firmware/update/boot/debug | `CamDownloadFirmwareHandle` at `0x61F59C`; `Slave not boot` at `0x602A60`; `FIRMWARE.BIN` at `0x620D10`; `Update firmware to newer` at `0x6E4DE0`; `Update to new firmware?` at `0x6E64A8`; `Firmware version` at `0x6ECB98`; `Update complete` at `0x6F04F4`; `SBM-FIRMWARE` at `0x7439D8`; `CamDebugUsbMode` at `0x61FB88`; `CPU register when exception occured` at `0x620428`. |
| Copyright | `Copyright (c) 2009-2010 Tokyo Electron Device Ltd.` at `0x5F0C34`; `Copyright (c) 2000-2008 by FotoNation. All rights reserved.` at `0x64D7CC`; `Copyright (C) 2010, Arcsoft Inc.` at `0x664540`. |
| Assert | No reliable `assert` string found. |

## STRONGLY SUPPORTED — Processor architecture classification

The P500 code regions are strongly supported as 32-bit little-endian ARM based on multiple independent structural indicators: two separate program-region starts each contain eight aligned ARM-branch-pattern vectors whose destinations remain in-region; the main and slave regions both contain repeated ARM-style prologue/epilogue and `BX` patterns; and the main image contains a coherent sequence of little-endian address-like values. This is not **CONFIRMED** because no processor-identification string or independent hardware documentation was found, and no disassembler or execution was used.

## CONFIRMED — Section extraction readiness

The container is sufficiently mapped to make byte-exact analysis copies of the listed record payload ranges in a later, separately approved step: each header is 96 bytes, each declared length lands on the next header or EOF, and every `SUM` matches the payload byte sum. No internal section was extracted in this phase. This establishes copy boundaries only; it does not establish that a component is independently loadable, executable, or safe to flash.

## UNKNOWN — Remaining interpretation limits

- The vendor-specific meanings of `SG583`, `DVR`, `NPROG`, `NDATA`, `NLIPI`, and `SFIRM` beyond their observed record positions.
- The actual load addresses and the meaning of binary fields such as `0x10AA001A`.
- The exact role of the short `NLIPI` payloads and of the secondary NPROG record.
- Whether image-signature-like byte sequences are complete embedded assets. They were not carved based on magic bytes.
- No conclusion about P510 architecture or compatibility follows from this P500 analysis.
