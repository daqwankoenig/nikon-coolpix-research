# P510 Phase 4E - Component Evidence

**Status:** COMPLETE - public/local research only  
**Evidence standard:** A component identity requires a readable marking plus corroboration. A seller's model description alone is not sufficient.

## Candidate inventory

| ID / region | Visible marking or evidence | Package / location | Possible role | Classification | Conclusion |
|---|---|---|---|---|---|
| U1 | No legible top marking; covered by gray thermal-interface material in iFixit and seller component-side images | Large central square package on the populated face | Main processor / image processor candidate based on size and location only | **UNKNOWN** | Manufacturer, exact part, architecture, flash capability, and debug features remain unidentified. |
| U2 | Micron logo; `21C22` and `D9MTD` | Large memory package adjacent to U1 on the populated face | DRAM | **STRONGLY SUPPORTED** | Prior code lookup associates D9MTD with Micron MT47H128M16RT-25E:C DDR2 SDRAM. A full P510 part number is not confirmed from an accessible primary datasheet. It is not evidence of firmware storage. |
| U3+ | Small device markings are blurred, too small, or angled | Distributed around the populated face and the exposed region beside the reverse-face shield | Unknown | **UNKNOWN** | No exact manufacturer/part number can be transcribed safely. Do not promote any of these devices to flash or EEPROM candidates. |
| Reverse-face shield | An apparent dark `2231` mark on the metal shield | Large metal cover on the seller-claimed reverse-face image | Unknown marking on a shield | **UNKNOWN** | Not established as a device marking, board identifier, date/lot code, or revision. |
| PCB silkscreen candidate | Appears to read `CMKY-PB2` in the reverse-face image | Vertical text on the exposed PCB region beside the shield | Possible board/supplier marking | **POSSIBLE transcription; meaning UNKNOWN** | Exact characters are not independently corroborated; exact-string search did not identify a P510 part or revision. Do not treat as a board-family identifier. |
| Sticker | `280414` | White sticker on the populated face in the iFixit images | Unknown | **CONFIRMED transcription; meaning UNKNOWN** | No evidence establishes it as a part number, assembly code, date, lot, or revision. |
| TESTPAD-GROUP-A / B | Exposed round pads; no signal names or numbering established | Populated face near board edges and connectors | Test, power, ground, or other functions are possible | **UNKNOWN** | No pad is assigned UART, JTAG, SWD, boot-mode, or programming function. |
| Large reverse-face shielded region | No internal markings visible | Reverse/connector face in the 1024x768 eBay image | Unknown covered circuitry | **UNKNOWN** | Components are not visible; no storage type or function can be inferred from the shield. |

## Nonvolatile-memory assessment

**PRIMARY FIRMWARE STORAGE CANDIDATE: none identified.**  
**SECONDARY CANDIDATE: none identified.**

No P510-specific NOR, NAND, EEPROM, eMMC, or other nonvolatile-memory device has a readable part number in the reviewed sources. The Micron `D9MTD` device is strongly supported as volatile DDR2 SDRAM and must not be targeted as firmware storage. The reverse-face photograph adds no exposed memory candidate.

| Property | Finding |
|---|---|
| Candidate part number / manufacturer | None identified |
| Capacity / bus / package / voltage | Unknown |
| Read protocol / write protection | Unknown |
| Common programmer compatibility | Not assessable without an identified part |
| In-circuit byte-exact read feasibility | Unknown |
| Chip-off read feasibility | Unknown; no chip has been identified as firmware storage |

No physical readout procedure is proposed.

## Processor and debug-interface assessment

- U1 remains covered by thermal material. No exact or partial chip marking can be transcribed from the current images.
- No exact-part research, architecture research, datasheet capability comparison, or P500/P520 processor comparison is justified without a credible processor identification.
- Visible pad groups remain neutral TESTPAD groups. Their spacing or location alone is not evidence of UART, JTAG, SWD, factory programming, or a specific signal.
- The reverse-face photograph does not expose a labeled header or documented service interface.

## Board markings and parts-catalog correlation

| Mark | Source / surface | Current reading | Meaning |
|---|---|---|---|
| `280414` | iFixit P510 guide, sticker on populated face | Legible | Unknown; no board revision or part-number meaning established |
| `CMKY-PB2` | Seller-claimed matching board, reverse-face PCB silkscreen | Provisional transcription | Unknown; exact-string searches yielded no corroboration |
| `2231` | Seller-claimed matching board, metal shield | Apparent transcription | Unknown; not proven to identify the PCB or an IC |

Public search results did not reveal a P510-specific main-board/service part number. The SpareParts.plus page is an affiliate eBay-search page, the Partmaster page could not be retrieved (HTTP 403), and Nikon's general Self Service Repair page did not identify a P510 manual or board item. No part number or revision is inferred from these results.

## Final component-level finding

The only strongly supported semiconductor identity remains the Micron DRAM candidate documented in Phase 4D. The processor, firmware storage, shielded components, board assembly number, and debug/test interfaces remain **UNKNOWN**. No new P510 component identity was established in Phase 4E.

## Sources

- [iFixit P510 motherboard-replacement guide](https://www.ifixit.com/Guide/Nikon+Coolpix+P510+Motherboard+Replacement/40287)
- [P510 Phase 4D component map](P510-Phase4D-component-map.md)
- [P510 Phase 4E new source images](P510-Phase4E-new-source-images.md)
- [P510 Phase 4E hidden-component identification](P510-Phase4E-hidden-component-identification.md)
