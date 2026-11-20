# P510 Phase 4E - Hidden-Component Identification

**Status:** COMPLETE - public/local research only  
**Research date:** 2026-11-20  
**Physical-camera interaction:** None. No purchase, seller contact, probing, programming, or firmware work occurred.

## Result

The Phase 4D evidence review identified an important gap: iFixit's P510 guide documents the populated/component face of the board, but not a clean view of its reverse face. A seller-claimed P510 main-board listing has a second, 1024x768 image of that reverse face. Its outline and port arrangement are consistent with the board in the listing's component-side image, which in turn is a **STRONG VISUAL MATCH** to the iFixit board. The reverse-face photograph therefore adds a useful, but low-resolution and seller-provenance-limited, view.

The reverse face is not bare: a large metal shield covers most of it. A small adjacent region is visible, but no processor marking, nonvolatile-memory part number, PCB assembly number, or service-interface label is established. The processor remains **UNKNOWN**, firmware storage remains **UNKNOWN**, and donor acquisition remains **NOT JUSTIFIED**.

## Phase 4D missing-view matrix, updated

| Category | Region/evidence | Phase 4E assessment |
|---|---|---|
| ADEQUATELY DOCUMENTED | Populated/component face shown in iFixit steps 16-18, including board outline, Micron-marked package, thermal-pad-covered large IC, flex connectors, exposed pads, and the `280414` sticker | Adequately documented for visible layout and the legible `21C22` / `D9MTD` top marking only. It is not a complete component inventory. iFixit source photographs are 4000x3000 for step 16 and step 18. |
| VISIBLE BUT MARKING UNREADABLE | Small ICs and fine details in the iFixit and marketplace photographs | Multiple top marks remain too small, blurred, or angled to transcribe. No unreadable character has been guessed. |
| OBSCURED BY THERMAL MATERIAL | Large central IC on the populated face (U1 candidate) | Still completely unidentified. The seller's component-side image does not expose a readable top marking either. |
| OBSCURED BY SHIELD | Large metal cover on the reverse-face image | Components beneath the cover cannot be observed. The image does not establish the cover's electrical or mechanical function. |
| BOARD SIDE NOT DOCUMENTED | Reverse/connector face in the Phase 4D iFixit set | Partially documented by the seller-claimed eBay image, not by iFixit. The new image shows the broad shielded area and nearby PCB edge, but not a full bare-board view. |
| INSUFFICIENT RESOLUTION | Seller-claimed board photos (1024x768); AliExpress result (800x800) | Useful for outline and gross layout only. Small IC markings, package dimensions, traces, and pad functions cannot be reliably read. |

## Region-by-region observations

### Populated/component face

- The iFixit P510 motherboard-replacement guide remains the highest-resolution model-specific board evidence.
- The large central square package remains covered by thermal interface material. Its marking, manufacturer, and precise function are **UNKNOWN**.
- The Micron logo and `21C22` / `D9MTD` marking remain visible on the DRAM candidate. The MT47H128M16RT-25E:C mapping is strongly supported by prior code lookup but is not newly confirmed by a primary datasheet in this phase.
- The `280414` sticker remains a transcription only; its meaning is **UNKNOWN**.
- The visible small ICs and exposed pad groups do not provide supported flash or debug-interface identities.

### Reverse/connector face

- The seller listing's reverse-face image shows a broad metal shield, several nearby small components, PCB edge features, and two external connector openings.
- A dark mark on the shield appears to read `2231`; it is not established as a part number, date code, or revision.
- A vertical PCB silkscreen appears to read `CMKY-PB2`. This is a provisional visual transcription only; exact characters and meaning are unconfirmed, and an exact-string web search produced no corroborating P510 board record.
- No exposed IC on this face has a confidently readable full part number.
- No pad/header pattern can be assigned UART, JTAG, SWD, programming, or other service function from this photograph.

## Targeted public research performed

- Re-reviewed the Phase 4D board map, source-image inventory, 50-entry image manifest, and local iFixit images. No Phase 4D image was copied or re-downloaded.
- Checked Google and Bing image/web results for P510 main-board, motherboard, PCB, system-board, bare-board, and `280414` queries. Results converged on the known iFixit guide, the previously observed eBay board listing, and seller-claimed marketplace listings; no independently identified bare-board source with readable chip markings was found.
- Recovered the direct eBay CDN URLs and native dimensions for both images in item [115640102604](https://www.ebay.com/itm/115640102604). Only the materially new reverse-face image is saved locally; the component-side eBay image duplicates the already documented iFixit face at lower resolution and was not copied.
- Checked the AliExpress P510 board listing and its 800x800 image. It did not provide an accepted new board side or an independently corroborated model/revision.
- Exact-string searches for `280414` and the provisional `CMKY-PB2` transcription did not establish a Nikon part number, assembly number, date code, lot code, or revision.
- The [SpareParts.plus P510 page](https://www.spareparts.plus/Electronics/Camera/Nikon/P510/spareparts/) is an affiliate/search landing page that directs users to an eBay search, not a Nikon parts catalog or board-specific parts diagram.
- A [Partmaster P510 catalog result](https://www.partmaster.co.uk/camera/p510/catalogue.pl?shop=nikon&path=137941&model_ref=2440195) returned HTTP 403 to the research fetcher; no board entry or part number could be verified from it.
- Nikon's [Self Service Repair page](https://www.nikonusa.com/content/self-service) describes service-manual availability for some products, but no P510-specific service manual or board part number was located in the reviewed results.
- A Bing Images result for a Russian P510 lens-repair post exposed a 1600x900 image URL, but the source timed out when opened. It was not used for component identification.

## Evidence boundary and conclusions

### Supported

- The iFixit guide documents a P510 board's populated face.
- A seller-claimed board image pair includes a reverse-face view that is visually consistent with the component-side board in the same listing.
- The component-side seller image is a **STRONG VISUAL MATCH** to the iFixit board; this makes the paired reverse-face image a useful, but not independently confirmed, P510 board view.
- The reverse-face view is mostly shielded and insufficient for identifying hidden components.

### Not established

- Main processor identity, manufacturer, architecture, debug capabilities, or internal flash.
- Any external NOR, NAND, EEPROM, eMMC, or other nonvolatile-memory device.
- Board assembly/part number or revision; the meaning of `280414`, `CMKY-PB2`, and `2231`.
- Any signal or function for exposed pads, connectors, or the reverse-face shield.
- A shared P500/P510/P520 processor, memory, or board family. No P500/P520 comparison was repeated because Phase 4E established no confirmed processor, memory part, or board-family identifier.
- In-circuit or chip-off read feasibility.

## Donor gate and recommended Phase 4F

**Decision: MORE DOCUMENTATION REQUIRED.** This new image closes part of the missing-view gap, but the shield still conceals most of the reverse face and the processor remains thermally covered. No firmware-storage target or acquisition interface is identified. A donor purchase would still not expose a known read-only acquisition path, so neither a standalone board nor a broken complete camera is justified now.

Recommended Phase 4F: continue public documentation research for a P510-specific Nikon parts diagram/service document or a sharp, full-board image with both faces and readable board identifiers. Keep any seller claims separate from visual matching. Reassess donor feasibility only if that work identifies a specific component or documented interface. Do not execute hardware work, purchase a donor, contact the working camera, or attempt readout in Phase 4F without a separate approval.

## Sources

- [iFixit P510 motherboard-replacement guide](https://www.ifixit.com/Guide/Nikon+Coolpix+P510+Motherboard+Replacement/40287)
- [eBay seller-claimed P510 board, item 115640102604](https://www.ebay.com/itm/115640102604)
- [SpareParts.plus P510 listing page](https://www.spareparts.plus/Electronics/Camera/Nikon/P510/spareparts/)
- [Partmaster P510 catalog result](https://www.partmaster.co.uk/camera/p510/catalogue.pl?shop=nikon&path=137941&model_ref=2440195)
- [Nikon USA Self Service Repair](https://www.nikonusa.com/content/self-service)
- [P510 Phase 4D source image inventory](P510-Phase4D-source-images.md)
- [P510 Phase 4D component map](P510-Phase4D-component-map.md)
