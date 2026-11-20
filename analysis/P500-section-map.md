# P500 Firmware Section Map — Phase 1D

## Scope and integrity

- Source: `firmware/extracted/P500/P500Update/firmware/firmware.bin` (14,614,648 bytes).
- Source SHA-256 before extraction and after extraction: `80A297C8B4B77731EB2B3B5DC23D905D557A0052049402364B11A1F7849779B4` (unchanged).
- All copies are literal byte ranges from the mapped payload offsets. The source was opened read-only; no firmware was patched, executed, decompressed, or disassembled, and no camera was accessed.
- The SFIRM payload includes its nested SG583SLAVE record header and terminal NLIPI record. The separately extracted slave payload and terminal NLIPI payload therefore overlap this outer payload by design.
- Additive SUM is a simple byte sum, not a cryptographic integrity mechanism. Each extracted file also has a SHA-256 record.

## Section map

| Record | Source Offset (payload) | Length | Extracted Filename | SHA-256 | Checksum Verification | Entropy (bits/byte) | Classification | Architecture Evidence | Possible Load Address | Notes |
|---|---:|---:|---|---|---|---:|---|---|---|---|
| NPROG (primary) | `0x00000060` | 7471104 (`0x720000`) | `P500-NPROG-primary.bin` | `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29` | PASS: 765951917 = 765951917 | 6.0204 | PROBABLE CODE | 32-bit little-endian ARM strongly supported: eight branch-vector-like words at relative 0x00-0x1C target offsets 0x20, 0x248, 0x260, 0x278, 0x290, 0x14, 0x11C, and 0x244, all within this section; many aligned ARM-like instruction patterns and BX patterns also occur. Thumb use is not independently established. | UNKNOWN; none established by the record | Contains the primary code-like region. First eight words are branch-vector-shaped. Address-like words include 0x57FCA000-0x57FCF000 near relative 0xFC; these do not establish an image base. Long zero-filled regions occur, including a 130,040-byte same-byte run. |
| NPROG (secondary) | `0x007200C0` | 2184192 (`0x215400`) | `P500-NPROG-secondary.bin` | `B661EF6464B58ABCD14876A9E0E2C7C6C74521ADEB200810C32214B74A959203` | PASS: 67364592 = 67364592 | 2.9306 | PROBABLE RESOURCES | No credible leading vector table; sparse instruction-like patterns are insufficient to classify as code. No architecture assignment. | UNKNOWN; none established by the record | Begins with SG583/version-like text and structured values; extensive zero/FF fill, camera menu/localization strings, firmware-update and MTP/PTP text. GZIP/BMP/JPEG-like markers are only candidate signatures, not validated embedded files. |
| NDATA | `0x00935520` | 3188736 (`0x30A800`) | `P500-NDATA.bin` | `20656DFDF01560188DED6063BCB5CE29BDEC7FC6D127A5B20B3A38280A41CBD2` | PASS: 287766792 = 287766792 | 6.5133 | PROBABLE RESOURCES | No credible leading vector table; instruction-like pattern counts are not treated as code evidence. No architecture assignment. | UNKNOWN; none established by the record | Contains binary tables and repeated JPEG SOI-like signatures (first matches at relative 0xC00, 0x7E00, 0xF200, 0x16400, 0x1DC00, 0x24C00); visible JPEG-table-like strings. Treat as resource/data content; no carving or decompression performed. No audio/filesystem image confirmed. |
| NLIPI (before SFIRM) | `0x00C3FD80` | 12 (`0xC`) | `P500-NLIPI-pre-SFIRM.bin` | `3C499749966CB76F69831BF06ED8DA33C0A47130E4D6D08EA0DD4B616C2B8CF3` | PASS: 427 = 427 | 2.4508 | PROBABLE METADATA | Not applicable; 12-byte metadata-like record. | UNKNOWN; none established by the record | Opaque 12-byte record body: 30 49 4C 4E 0C 00 00 00 0C 00 80 00. The two 32-bit values are recorded, not assigned semantics. |
| SFIRM (composite payload) | `0x00C3FDEC` | 1770124 (`0x1B028C`) | `P500-SFIRM-composite-payload.bin` | `8840083A1CBD3024E8D02FFCF6AF04773F37D30A21E26A16B07EB0D3D762E5FE` | PASS: 177731721 = 177731721 | 5.9031 | PROBABLE METADATA | Contains a nested SG583SLAVE header, ARM-like program payload beginning at relative 0x60, and a terminal NLIPI record; the outer copy is a wrapper, not a clean code image. | UNKNOWN; none established by the record | Payload is composite: nested 96-byte SG583SLAVE header, 1,769,920-byte slave payload, and 108-byte terminal NLIPI record. It overlaps the separately extracted slave and terminal payload copies by design; no source bytes were changed. |
| SG583SLAVE payload | `0x00C3FE4C` | 1769920 (`0x1B01C0`) | `P500-SG583SLAVE-payload.bin` | `6E7D0AA03908549C1FDDAA9637297EBB4BFBE626C14A0E7BEB76ACD902773100` | PASS: 177721714 = 177721714 | 5.9028 | PROBABLE CODE | 32-bit little-endian ARM strongly supported: eight branch-vector-like words at relative 0x00-0x1C target offsets 0x20, 0x244, 0x32C, 0x290, 0x2DC, 0x14, 0x11C, and 0x328, all within this section; repeated ARM-like instruction patterns and BX patterns also occur. Thumb use is not independently established. | UNKNOWN; none established by the record | Slave program region closely resembles primary NPROG code structure and contains the same address-like sequence near relative 0xFC. FAT/EXFAT and storage-related strings occur; they do not prove an embedded filesystem. |
| NLIPI (terminal) | `0x00DF006C` | 12 (`0xC`) | `P500-NLIPI-terminal.bin` | `3C499749966CB76F69831BF06ED8DA33C0A47130E4D6D08EA0DD4B616C2B8CF3` | PASS: 427 = 427 | 2.4508 | PROBABLE METADATA | Not applicable; 12-byte metadata-like record. | UNKNOWN; none established by the record | Byte-identical to the earlier 12-byte NLIPI payload. Opaque record body: 30 49 4C 4E 0C 00 00 00 0C 00 80 00. |

## Per-section read-only observations

### NPROG (primary) — P500-NPROG-primary.bin

- Source payload offset: ``0x00000060``; length: 7471104 bytes (``0x720000``); additive sum: 765951917 (verified); SHA-256: ``42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29``.
- Entropy: 6.0204 bits/byte. Padding observations: zero=1529064 (20.47%), ff=131053 (1.75%), longest_same_byte_run=130040 of 0x00.
- Classification: **PROBABLE CODE**. Contains the primary code-like region. First eight words are branch-vector-shaped. Address-like words include 0x57FCA000-0x57FCF000 near relative 0xFC; these do not establish an image base. Long zero-filled regions occur, including a 130,040-byte same-byte run.
- Architecture observations: 32-bit little-endian ARM strongly supported: eight branch-vector-like words at relative 0x00-0x1C target offsets 0x20, 0x248, 0x260, 0x278, 0x290, 0x14, 0x11C, and 0x244, all within this section; many aligned ARM-like instruction patterns and BX patterns also occur. Thumb use is not independently established.
- Readable ASCII runs (section-relative offsets; representative scan results): 0xF44A: )))))))))); 0xF459: )))))))))); 0x23696: %%%%%%%%%%%%; 0x26FB4: )5AAAAAAAAAAA; 0x2D062: (5DTfz; 0x869A7: HH%HH3:; 0x8DCBB: *5@Kalw; 0x8E187: #.9DOZ; 0xAC6F9:  #88&88),/25; 0xB7082: #&2:^mpy; 0xD863E:  "&$&&-; 0xDAB23: ?3333h; 0xDC686:  '.7@GP\; 0xEB625: 8888888888888; 0xEB636: 8888 /88#888888)88&8588852; 0xEF213: "+.17:=CORUX[^djps; 0xEF226: v4a@my|; 0xEF52A:  $&(*24KK68:>@K; 0xEF53A: B"KKKKKKKKKK; 0xEF547: <DFHJKK,.0; 0x10122E: %6HYk|; 0x10845F: #.9DOZ; 0x11CEFE: #&),/2T5TJ8;>A; 0x11D0A0: d17=@C.g%FI+g(U; 0x26CDF0: ExifJFIFJFXX; 0x26F0B6: kPJFIF; 0x2809E8: Photo - JPEG; 0x281BE4: NIKON DIGITAL CAMERA; 0x29BA5C: NIKON CO.,LTD.; 0x2A3EA0: Photo - JPEG; 0x2A5170: NIKON DIGITAL CAMERA; 0x2C4430: =DKRY`gnu|; 0x335F4D: RY`gnu|; 0x51F15C: APVC_UpdateSelectFrameEngine error.; 0x5F0B2C: EXFAT   ; 0x5F0B54: FAT12   ; 0x5F0B60: FAT32   ; 0x5F0B6C: FAT16   ; 0x5F0BD4: Copyright (c) 2009-2010 Tokyo Electron Device Ltd.; 0x6010F6: [BIF:ERR]  BBM_UpdatePIExt is failed(nVol=%d, nID=%x); 0x602A00: Slave not boot; 0x6041D8: [SM :ERR] _UpdateCache : pBuf cannot be NULL in write operation; 0x60446A: [BBM:ERR]  Writing(Pbn:%d,SecOff:%d) confirm is failed; 0x604E0E: [BBM:   ]   _UpdateLPCA is failed; 0x604E32: [BBM:   ]   _UpdateUPCA is failed; 0x605226: [BBM:ERR] _UpdateUPCA is failed; 0x60524A: [BBM:ERR] _UpdateLPCA is failed; 0x618B3C: FAT16   ; 0x618B48: FAT12   ; 0x618B67: EXFAT   ; 0x61AF24: NIKON DIGITAL CAMERA; 0x61F368: CamThumbnailSize; 0x61F390: CamThumbHandle; 0x61F53C: CamDownloadFirmwareHandle; 0x61F654: CamUsbInitMode; 0x61FB28: CamDebugUsbMode; 0x61FC10: NIKON CO.,LTD.; 0x6201EC: SG583SLAVE; 0x6202F8: FIRMWAREBIN; 0x620324: FIRMWAREBIN; 0x620330: FIRMWARE   ; 0x620348: SG583SLAVE; 0x620354: SUB_FIRMHEX; 0x62055C: RTOS TCB
- Candidate byte signatures (section-relative; not validated or carved): JPEG: 0x2AC180, 0x5D36A5, 0x5F09A7, 0x5F2B47, 0x5F35BB, 0x5F35C7; GZIP: 0x37BF4, 0xDA8C1, 0x198790, 0x2923A5, 0x579D8C, 0x5F0249; PE: 0x2DE938, 0x416328, 0x476A50, 0x5AD25B, 0x5DA50D, 0x5E2840; RIFF: 0x2786DC, 0x2B452C, 0x615B74, 0x61B9A4, 0x61BF64, 0x635A90; BMP: 0xB7828, 0x2DA848, 0x41278C, 0x5A9AC4, 0x5FD7D2, 0x5FD81A

First 256 bytes (section-relative offset 0x00000000):

```text
06 00 00 EA 8F 00 00 EA 94 00 00 EA 99 00 00 EA 9E 00 00 EA FE FF FF EA 3F 00 00 EA 88 00 00 EA D1 F0 21 E3 D0 D0 9F E5 D2 F0 21 E3 CC D0 9F E5 D3 F0 21 E3 C8 D0 9F E5 D7 F0 21 E3 C4 D0 9F E5 DB F0 21 E3 C0 D0 9F E5 DF F0 21 E3 BC D0 9F E5 E6 00 00 EB 01 00 00 EB DC 00 00 EA 00 00 A0 E1 F0 43 2D E9 A8 00 9F E5 A8 10 9F E5 00 20 41 E0 00 40 A0 E3 00 50 A0 E3 00 60 A0 E3 00 70 A0 E3 00 80 A0 E3 00 90 A0 E3 00 C0 A0 E3 00 E0 A0 E3 07 00 00 EA F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 40 2F 52 E2 F5 FF FF 2A FF 20 12 E2 F0 83 BD 08 20 20 52 E2 F0 53 A0 28 FC FF FF 2A 20 20 92 E2 F0 83 BD 08 04 20 52 E2 10 00 A0 28 FC FF FF 2A 04 20 92 E2 F0 83 BD 08 01 20 52 E2 01 40 C0 24 FC FF FF 2A F0 83 BD E8 00 A0 FC 57
```

Last 256 bytes (section-relative offset 0x0071FF00):

```text
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```

### NPROG (secondary) — P500-NPROG-secondary.bin

- Source payload offset: ``0x007200C0``; length: 2184192 bytes (``0x215400``); additive sum: 67364592 (verified); SHA-256: ``B661EF6464B58ABCD14876A9E0E2C7C6C74521ADEB200810C32214B74A959203``.
- Entropy: 2.9306 bits/byte. Padding observations: zero=1481757 (67.84%), ff=10707 (0.49%), longest_same_byte_run=3604 of 0x00.
- Classification: **PROBABLE RESOURCES**. Begins with SG583/version-like text and structured values; extensive zero/FF fill, camera menu/localization strings, firmware-update and MTP/PTP text. GZIP/BMP/JPEG-like markers are only candidate signatures, not validated embedded files.
- Architecture observations: No credible leading vector table; sparse instruction-like patterns are insufficient to classify as code. No architecture assignment.
- Readable ASCII runs (section-relative offsets; representative scan results): 0x0: SG583   ; 0x10: v583-80                         ; 0x458: English; 0x67C: Portrait left; 0x69C: High(3072; 0x6BC: Max. rec. time; 0x6EC: File will be deleted. OK?; 0x724: Copy sound files; 0x754: Camera to card; 0x78C: Selected files; 0x7B4: Select sound files; 0x7E4: Select; 0x824: Card to camera; 0x85C: TV movie 640; 0x884: HD 720p; 0x894: Shooting menu; 0x8BC: White balance; 0x8E4: Daylight; 0x92C: Stop-motion movie; 0x954: Shadow BSS; 0x974: Vivid color; 0x994: dates?; 0x9C4: Frame intvl; 0x9EC: Erase XXX images?; 0xB44: COOLPIX; 0xCAC: MTP/PTP; 0xD84: Update firmware to newer; 0xDC4: during update!; 0x1BCC: Select a USB option, or choose; 0x244C: Update to new firmware?; 0x2A34: Update GPS data; 0x2A64: Failed to update GPS data; 0x2F2C: Confirm password; 0x2FC4: to server.; 0x38EC: Adjust USB and video settings.; 0x4CF0: complete update.; 0x4DE0: Confirm; 0x5014: Update error; 0x663C: Update GPS data?; 0x8B3C: Firmware version; 0xC498: Update complete; 0xC5B0: Update current position.; 0xCB90: Create a JPEG copy at these; 0xCBC8: create JPEG copies.; 0xCCB8: Confirm address and alias; 0xDA1C: COOLPIX SXXX; 0xDA29: ~pj ver.1.0; 0xDA8C: select "Projector" for USB.; 0xECD8: COOLPIX (Ni-MH); 0xF118: Update sbm-firm to; 0xF168: IN USB MENU.; 0x10D88: Display the camera firmware version.; 0x13F94: computer via USB.; 0x15344: COOLPIX; 0x154AC: MTP/PTP; 0x2221C: COOLPIX SXXX; 0x22229: ~pj Ver.1.0; 0x234D8: COOLPIX (Ni-MH); 0x23918: SBM-FIRMWARE; 0x29B44: COOLPIX; 0x29CAC: MTP/PTP; 0x2ABCE: finit une option USB ou un; 0x2BDFC: copie JPEG avec ces r; 0x2BF2C: Confirmer le mot passe
- Candidate byte signatures (section-relative; not validated or carved): GZIP: 0x98093; BMP: 0x23919, 0x85B4A

First 256 bytes (section-relative offset 0x00000000):

```text
53 47 35 38 33 20 20 20 FF FF FF FF 1A 00 AA 10 76 35 38 33 2D 38 30 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 02 00 00 00 00 44 6E 50 80 46 01 00 A4 00 00 00 A6 00 00 00 00 44 6E 50 80 46 01 00 A4 00 00 00 4A 01 00 00 00 44 6E 50 80 46 01 00 A4 00 00 00 EE 01 00 00 00 44 6E 50 80 46 01 00 A4 00 00 00 92 02 00 00 00 44 6E 50 80 46 01 00 A4 00 00 00 36 03 00 00 00 44 6E 50 80 46 01 00 A4 00 00 00 DA 03 00 00 00 44 6E 50 80 46 01 00 A4 00 00 00 7E 04 00 00 00 44 6E 50 80 46 01 00 A4 00 00 00
```

Last 256 bytes (section-relative offset 0x00215300):

```text
FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
```

### NDATA — P500-NDATA.bin

- Source payload offset: ``0x00935520``; length: 3188736 bytes (``0x30A800``); additive sum: 287766792 (verified); SHA-256: ``20656DFDF01560188DED6063BCB5CE29BDEC7FC6D127A5B20B3A38280A41CBD2``.
- Entropy: 6.5133 bits/byte. Padding observations: zero=591788 (18.56%), ff=56583 (1.77%), longest_same_byte_run=6262 of 0x00.
- Classification: **PROBABLE RESOURCES**. Contains binary tables and repeated JPEG SOI-like signatures (first matches at relative 0xC00, 0x7E00, 0xF200, 0x16400, 0x1DC00, 0x24C00); visible JPEG-table-like strings. Treat as resource/data content; no carving or decompression performed. No audio/filesystem image confirmed.
- Architecture observations: No credible leading vector table; instruction-like pattern counts are not treated as code evidence. No architecture assignment.
- Readable ASCII runs (section-relative offsets; representative scan results): 0xC3B:  $.' ",#; 0xC45: (7),01444; 0xC4F: '9=82<.342; 0xC6B: !22222222222222222222222222222222222222222222222222; 0xD13: %&'()*456789:CDEFGHIJSTUVWXYZcdefghijstuvwxyz; 0xDEE: &'()*56789:CDEFGHIJSTUVWXYZcdefghijstuvwxyz; 0x2560: byQspG; 0x2570: V9"IDg*[; 0x2765: t<Uj@O; 0x2FBE: pGol!\; 0x3119: \0:Oos; 0x3235: IaEz@jxk; 0x354A: |9gom%; 0x369F: < # w<; 0x3856: o,*P3e@; 0x3926: +t_or{; 0x3A41: kKY'Qi; 0x423C: xWlQ\H; 0x44A6: I*9ynd; 0x450A: zm^+6]; 0x47B0: ROALDo; 0x4AB2: Ri#GDr; 0x4DAE: >$V?gl; 0x4E76: zTmqhH; 0xC17A1: KpGNu2I; 0x2BE231: P<POP\PtPuP
- Candidate byte signatures (section-relative; not validated or carved): JPEG: 0xC00, 0x7E00, 0xF200, 0x16400, 0x1DC00, 0x24C00; GZIP: 0x787AF, 0xC0351, 0xC6C5F, 0xCED00, 0xFC464, 0x11A55D; PE: 0x1BDFD, 0x2EE4A, 0x3AC28, 0x3D45A, 0x4654C, 0x91F5F; BMP: 0x6FE2D, 0xB547F, 0xF0701

First 256 bytes (section-relative offset 0x00000000):

```text
31 30 83 05 05 40 2A 0B C9 05 00 00 00 00 00 00 18 02 00 00 C9 05 00 00 2E 03 00 00 E1 07 00 00 1B 00 00 00 0F 0B 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```

Last 256 bytes (section-relative offset 0x0030A700):

```text
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```

### NLIPI (before SFIRM) — P500-NLIPI-pre-SFIRM.bin

- Source payload offset: ``0x00C3FD80``; length: 12 bytes (``0xC``); additive sum: 427 (verified); SHA-256: ``3C499749966CB76F69831BF06ED8DA33C0A47130E4D6D08EA0DD4B616C2B8CF3``.
- Entropy: 2.4508 bits/byte. Padding observations: zero=5 (41.67%), ff=0 (0.00%), longest_same_byte_run=3 of 0x00.
- Classification: **PROBABLE METADATA**. Opaque 12-byte record body: 30 49 4C 4E 0C 00 00 00 0C 00 80 00. The two 32-bit values are recorded, not assigned semantics.
- Architecture observations: Not applicable; 12-byte metadata-like record.
- No qualifying readable ASCII runs (6+ printable bytes) found by the scan.
- No scanned candidate image/archive/executable signatures found.

First 12 bytes (section-relative offset 0x00000000):

```text
30 49 4C 4E 0C 00 00 00 0C 00 80 00
```

Last 12 bytes (section-relative offset 0x00000000):

```text
30 49 4C 4E 0C 00 00 00 0C 00 80 00
```

### SFIRM (composite payload) — P500-SFIRM-composite-payload.bin

- Source payload offset: ``0x00C3FDEC``; length: 1770124 bytes (``0x1B028C``); additive sum: 177731721 (verified); SHA-256: ``8840083A1CBD3024E8D02FFCF6AF04773F37D30A21E26A16B07EB0D3D762E5FE``.
- Entropy: 5.9031 bits/byte. Padding observations: zero=361069 (20.40%), ff=26052 (1.47%), longest_same_byte_run=10490 of 0x00.
- Classification: **PROBABLE METADATA**. Payload is composite: nested 96-byte SG583SLAVE header, 1,769,920-byte slave payload, and 108-byte terminal NLIPI record. It overlaps the separately extracted slave and terminal payload copies by design; no source bytes were changed.
- Architecture observations: Contains a nested SG583SLAVE header, ARM-like program payload beginning at relative 0x60, and a terminal NLIPI record; the outer copy is a wrapper, not a clean code image.
- Readable ASCII runs (section-relative offsets; representative scan results): 0x0: LENGTH=1769920 SG583SLAVE VER=v583-80 DVR=1.10 SUM=177721714 NLIPI; 0x44:                             ; 0x98E0: !%)-159=YAEIMYQU; 0x23975: NRU`kx&24@Bv; 0x23BA5: -15:?D; 0x3AE95: qqqqR#; 0x3AE9C: qqaq#qq#"; 0x3B0A0: (float); 0x3BCCC: =;;;;;;;; 0x3C997: WRPLY0; 0x3CA70: SENDRPLYRDY; 0x498B6: (5DTfz; 0x5F079:  #88&88),/25; 0x7619A: #&2:^mpy; 0x85836: =.Jl]y; 0x8AF5F: *8ES`n{; 0xC15EC: "+29@J{; 0xC198F: '4@MYfr; 0xD2186: %%%%%%%%%%%%; 0xD5A78: )5AAAAAAAAAAA; 0xD9D7B: HH%HH3:; 0xDA737: "+.17:=CORUX[^djps; 0xDA74A: v4a@my|; 0xDAA4E:  $&(*24KK68:>@K; 0x15F5E0: FAT16   ; 0x15F5EC: FAT12   ; 0x15F60B: EXFAT   ; 0x185114: EXFAT   ; 0x18513C: FAT12   ; 0x185148: FAT32   ; 0x185154: FAT16   ; 0x1851BC: Copyright (c) 2009-2010 Tokyo Electron Device Ltd.; 0x1A1212: [BIF:ERR]  BBM_UpdatePIExt is failed(nVol=%d, nID=%x); 0x1A5AA4: [SM :ERR] _UpdateCache : pBuf cannot be NULL in write operation; 0x1A5D36: [BBM:ERR]  Writing(Pbn:%d,SecOff:%d) confirm is failed; 0x1A66DA: [BBM:   ]   _UpdateLPCA is failed; 0x1A66FE: [BBM:   ]   _UpdateUPCA is failed; 0x1A6AF2: [BBM:ERR] _UpdateUPCA is failed; 0x1A6B16: [BBM:ERR] _UpdateLPCA is failed; 0x1B0220: NLIPI LENGTH=12  SG583SLAVE VER=v583-80 SUM=427
- Candidate byte signatures (section-relative; not validated or carved): JPEG: 0x184F8F, 0x187143, 0x187BB7, 0x187BC3; GZIP: 0x184831, 0x184841; PE: 0x1614E7; BMP: 0x76940, 0x1816B0, 0x19D8EE, 0x19D936, 0x19DBFA, 0x19DCA3

First 256 bytes (section-relative offset 0x00000000):

```text
4C 45 4E 47 54 48 3D 31 37 36 39 39 32 30 20 53 47 35 38 33 53 4C 41 56 45 20 56 45 52 3D 76 35 38 33 2D 38 30 20 44 56 52 3D 31 2E 31 30 20 53 55 4D 3D 31 37 37 37 32 31 37 31 34 20 4E 4C 49 50 49 0D 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 06 00 00 EA 8E 00 00 EA C7 00 00 EA 9F 00 00 EA B1 00 00 EA FE FF FF EA 3F 00 00 EA C1 00 00 EA D1 F0 21 E3 D0 D0 9F E5 D2 F0 21 E3 CC D0 9F E5 D3 F0 21 E3 C8 D0 9F E5 D7 F0 21 E3 C4 D0 9F E5 DB F0 21 E3 C0 D0 9F E5 DF F0 21 E3 BC D0 9F E5 19 01 00 EB 01 00 00 EB 0F 01 00 EA 00 00 A0 E1 F0 43 2D E9 A8 00 9F E5 A8 10 9F E5 00 20 41 E0 00 40 A0 E3 00 50 A0 E3 00 60 A0 E3 00 70 A0 E3 00 80 A0 E3 00 90 A0 E3 00 C0 A0 E3 00 E0 A0 E3 07 00 00 EA F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8
```

Last 256 bytes (section-relative offset 0x001B018C):

```text
00 03 19 F0 04 03 19 F0 10 03 19 F0 14 03 19 F0 20 03 19 F0 24 03 19 F0 30 03 19 F0 34 03 19 F0 40 03 19 F0 44 03 19 F0 50 03 19 F0 54 03 19 F0 74 01 1B 50 7C 01 1B 50 84 01 1B 50 8C 01 1B 50 94 01 1B 50 9C 01 1B 50 00 03 19 F0 04 03 19 F0 10 03 19 F0 14 03 19 F0 20 03 19 F0 24 03 19 F0 30 03 19 F0 34 03 19 F0 40 03 19 F0 44 03 19 F0 50 03 19 F0 54 03 19 F0 98 05 10 F0 9C 05 10 F0 A0 05 10 F0 00 05 10 F0 30 05 10 F0 50 05 10 F0 B5 98 03 97 4E 4C 49 50 49 20 4C 45 4E 47 54 48 3D 31 32 20 20 53 47 35 38 33 53 4C 41 56 45 20 56 45 52 3D 76 35 38 33 2D 38 30 20 53 55 4D 3D 34 32 37 0D 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 30 49 4C 4E 0C 00 00 00 0C 00 80 00
```

### SG583SLAVE payload — P500-SG583SLAVE-payload.bin

- Source payload offset: ``0x00C3FE4C``; length: 1769920 bytes (``0x1B01C0``); additive sum: 177721714 (verified); SHA-256: ``6E7D0AA03908549C1FDDAA9637297EBB4BFBE626C14A0E7BEB76ACD902773100``.
- Entropy: 5.9028 bits/byte. Padding observations: zero=361064 (20.40%), ff=26052 (1.47%), longest_same_byte_run=10490 of 0x00.
- Classification: **PROBABLE CODE**. Slave program region closely resembles primary NPROG code structure and contains the same address-like sequence near relative 0xFC. FAT/EXFAT and storage-related strings occur; they do not prove an embedded filesystem.
- Architecture observations: 32-bit little-endian ARM strongly supported: eight branch-vector-like words at relative 0x00-0x1C target offsets 0x20, 0x244, 0x32C, 0x290, 0x2DC, 0x14, 0x11C, and 0x328, all within this section; repeated ARM-like instruction patterns and BX patterns also occur. Thumb use is not independently established.
- Readable ASCII runs (section-relative offsets; representative scan results): 0x9880: !%)-159=YAEIMYQU; 0x23915: NRU`kx&24@Bv; 0x23B45: -15:?D; 0x3AE35: qqqqR#; 0x3AE3C: qqaq#qq#"; 0x3B040: (float); 0x3BC6C: =;;;;;;;; 0x3C937: WRPLY0; 0x3CA10: SENDRPLYRDY; 0x49856: (5DTfz; 0x5F019:  #88&88),/25; 0x7613A: #&2:^mpy; 0x857D6: =.Jl]y; 0x8AEFF: *8ES`n{; 0xC158C: "+29@J{; 0xC192F: '4@MYfr; 0xD2126: %%%%%%%%%%%%; 0xD5A18: )5AAAAAAAAAAA; 0xD9D1B: HH%HH3:; 0xDA6D7: "+.17:=CORUX[^djps; 0xDA6EA: v4a@my|; 0xDA9EE:  $&(*24KK68:>@K; 0xDA9FE: B"KKKKKKKKKK; 0xDAA0B: <DFHJKK,.0; 0x15F580: FAT16   ; 0x15F58C: FAT12   ; 0x15F5AB: EXFAT   ; 0x1850B4: EXFAT   ; 0x1850DC: FAT12   ; 0x1850E8: FAT32   ; 0x1850F4: FAT16   ; 0x18515C: Copyright (c) 2009-2010 Tokyo Electron Device Ltd.; 0x1A11B2: [BIF:ERR]  BBM_UpdatePIExt is failed(nVol=%d, nID=%x); 0x1A5A44: [SM :ERR] _UpdateCache : pBuf cannot be NULL in write operation; 0x1A5CD6: [BBM:ERR]  Writing(Pbn:%d,SecOff:%d) confirm is failed; 0x1A667A: [BBM:   ]   _UpdateLPCA is failed; 0x1A669E: [BBM:   ]   _UpdateUPCA is failed; 0x1A6A92: [BBM:ERR] _UpdateUPCA is failed; 0x1A6AB6: [BBM:ERR] _UpdateLPCA is failed
- Candidate byte signatures (section-relative; not validated or carved): JPEG: 0x184F2F, 0x1870E3, 0x187B57, 0x187B63; GZIP: 0x1847D1, 0x1847E1; PE: 0x161487; BMP: 0x768E0, 0x181650, 0x19D88E, 0x19D8D6, 0x19DB9A, 0x19DC43

First 256 bytes (section-relative offset 0x00000000):

```text
06 00 00 EA 8E 00 00 EA C7 00 00 EA 9F 00 00 EA B1 00 00 EA FE FF FF EA 3F 00 00 EA C1 00 00 EA D1 F0 21 E3 D0 D0 9F E5 D2 F0 21 E3 CC D0 9F E5 D3 F0 21 E3 C8 D0 9F E5 D7 F0 21 E3 C4 D0 9F E5 DB F0 21 E3 C0 D0 9F E5 DF F0 21 E3 BC D0 9F E5 19 01 00 EB 01 00 00 EB 0F 01 00 EA 00 00 A0 E1 F0 43 2D E9 A8 00 9F E5 A8 10 9F E5 00 20 41 E0 00 40 A0 E3 00 50 A0 E3 00 60 A0 E3 00 70 A0 E3 00 80 A0 E3 00 90 A0 E3 00 C0 A0 E3 00 E0 A0 E3 07 00 00 EA F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 F0 53 A0 E8 40 2F 52 E2 F5 FF FF 2A FF 20 12 E2 F0 83 BD 08 20 20 52 E2 F0 53 A0 28 FC FF FF 2A 20 20 92 E2 F0 83 BD 08 04 20 52 E2 10 00 A0 28 FC FF FF 2A 04 20 92 E2 F0 83 BD 08 01 20 52 E2 01 40 C0 24 FC FF FF 2A F0 83 BD E8 00 A0 FC 57
```

Last 256 bytes (section-relative offset 0x001B00C0):

```text
32 00 00 00 04 00 00 00 01 00 00 00 FC 00 1B 50 04 01 1B 50 0C 01 1B 50 14 01 1B 50 1C 01 1B 50 24 01 1B 50 2C 01 1B 50 34 01 1B 50 3C 01 1B 50 44 01 1B 50 4C 01 1B 50 54 01 1B 50 08 03 19 F0 0C 03 19 F0 18 03 19 F0 1C 03 19 F0 28 03 19 F0 2C 03 19 F0 38 03 19 F0 3C 03 19 F0 48 03 19 F0 4C 03 19 F0 58 03 19 F0 5C 03 19 F0 00 03 19 F0 04 03 19 F0 10 03 19 F0 14 03 19 F0 20 03 19 F0 24 03 19 F0 30 03 19 F0 34 03 19 F0 40 03 19 F0 44 03 19 F0 50 03 19 F0 54 03 19 F0 74 01 1B 50 7C 01 1B 50 84 01 1B 50 8C 01 1B 50 94 01 1B 50 9C 01 1B 50 00 03 19 F0 04 03 19 F0 10 03 19 F0 14 03 19 F0 20 03 19 F0 24 03 19 F0 30 03 19 F0 34 03 19 F0 40 03 19 F0 44 03 19 F0 50 03 19 F0 54 03 19 F0 98 05 10 F0 9C 05 10 F0 A0 05 10 F0 00 05 10 F0 30 05 10 F0 50 05 10 F0 B5 98 03 97
```

### NLIPI (terminal) — P500-NLIPI-terminal.bin

- Source payload offset: ``0x00DF006C``; length: 12 bytes (``0xC``); additive sum: 427 (verified); SHA-256: ``3C499749966CB76F69831BF06ED8DA33C0A47130E4D6D08EA0DD4B616C2B8CF3``.
- Entropy: 2.4508 bits/byte. Padding observations: zero=5 (41.67%), ff=0 (0.00%), longest_same_byte_run=3 of 0x00.
- Classification: **PROBABLE METADATA**. Byte-identical to the earlier 12-byte NLIPI payload. Opaque record body: 30 49 4C 4E 0C 00 00 00 0C 00 80 00.
- Architecture observations: Not applicable; 12-byte metadata-like record.
- No qualifying readable ASCII runs (6+ printable bytes) found by the scan.
- No scanned candidate image/archive/executable signatures found.

First 12 bytes (section-relative offset 0x00000000):

```text
30 49 4C 4E 0C 00 00 00 0C 00 80 00
```

Last 12 bytes (section-relative offset 0x00000000):

```text
30 49 4C 4E 0C 00 00 00 0C 00 80 00
```

## Cross-section content scan

- **Nikon identifiers:** the primary NPROG contains `NIKON DIGITAL CAMERA`, `NIKON CO.,LTD.`, firmware-update, USB/PTP, and camera-function strings. The secondary NPROG contains COOLPIX menu/localization text, MTP/PTP, and update prompts. These are P500-reference findings only.
- **Filesystem strings:** FAT12/FAT16/FAT32 and EXFAT labels occur in the primary and slave code payloads. These strings do not establish an embedded filesystem image.
- **RTOS/compiler clues:** `RTOS TCB` occurs in the primary code region, but no specific RTOS or compiler/toolchain can be identified from it. No reliable GCC/GNU, ARM compiler, or operating-system identification string was found.
- **Image/resource clues:** NDATA has repeated JPEG SOI-like byte patterns and JPEG-table-like printable fragments; the secondary NPROG has BMP- and GZIP-like signatures. Other sections also contain JPEG/GZIP/RIFF/BMP/MZ-like matches. These are signature occurrences only; none were validated as complete embedded files. No audio format/container was confirmed.
- **Padding and entropy:** the measured entropy and zero/`FF` counts are recorded per section above. Long repeated zero/`FF` regions are consistent with padding or sparse structured regions, but do not alone determine purpose or compression.
- **Possible tables and addresses:** the primary and slave code payloads contain repeated address-like values, including `0x57FCA000` through `0x57FCF000`. These may be pointer or memory-map references; neither they nor the opaque `NLIPI` fields establish section load addresses.
- No section was decompressed, carved, or disassembled.

## Findings and Ghidra recommendation

- **First target: `P500-NPROG-primary.bin`.** It has the clearest leading ARM branch-vector-like structure and extensive corroborating ARM-like instruction patterns. Configure a raw image as ARM, little-endian, 32-bit. ARM state is the best-supported initial mode; `BX` patterns may indicate interworking, but no Thumb region has been verified.
- **Second target: `P500-SG583SLAVE-payload.bin`.** It has a similarly strong vector-like start and corroborating patterns. Use ARM, little-endian, 32-bit as the initial configuration; investigate possible interworking rather than presuming mixed code.
- Do not start with the whole SFIRM composite payload: its first 96 bytes are the nested record header and it ends with a metadata record. Use the clean slave payload copy for code analysis.
- **Image base is UNKNOWN.** The container provides no populated load-address field. The repeated 0x57FCxxxx-like values are address-like references, not sufficient evidence for a base. Do not assign a physical load address from these observations. If Ghidra requires a base, 0 is only a provisional relative-analysis convention, not a claimed load address.
- No Ghidra installation or launch occurred. No full disassembly, decompression, or embedded-file carving was performed.

## Interpretation limits

- Signature scans report byte-pattern occurrences only. They do not prove that every match is a complete image, archive, compressed stream, executable, or filesystem.
- Instruction-pattern counts can include coincidental data matches. Classification combines vectors, repeated aligned patterns, string/resource evidence, and record structure; it is not a disassembly.
- P500 observations do not establish P510 architecture or compatibility.
