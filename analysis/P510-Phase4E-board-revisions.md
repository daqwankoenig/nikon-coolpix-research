# P510 Phase 4E - Board-Revisions Assessment

**Status:** COMPLETE - public/local research only  
**Research date:** 2026-11-20

## Conclusion

**Distinct P510 board variants/revisions supported by evidence: 0.** One P510 board layout is documented by the model-specific iFixit teardown; one seller-claimed board has a **STRONG VISUAL MATCH** to that layout and provides a paired reverse-face view. This is evidence for one observed layout, not proof that only one P510 board revision exists.

No PCB assembly number, Nikon board part number, explicit revision code, or revision-qualified component change was established. The meaning of the `280414` sticker remains unknown.

## Candidate comparison

| Candidate | Source and visual evidence | Identity classification | Revision evidence | Use |
|---|---|---|---|---|
| Reference board A | iFixit [P510 motherboard-replacement guide](https://www.ifixit.com/Guide/Nikon+Coolpix+P510+Motherboard+Replacement/40287), steps 16-18. The board is shown in the P510 teardown sequence; populated-face board outline, connectors, Micron package, thermal-covered IC, and `280414` sticker are visible. | **CONFIRMED VISUAL MATCH** to the model-specific guide's P510 board | No assembly number or revision printed/readable in the guide images | Primary P510 visual reference |
| Candidate board B | eBay [item 115640102604](https://www.ebay.com/itm/115640102604), seller title claims “GENUINE NIKON COOLPIX P510 SYSTEM MAIN BOARD PART FOR REPAIR.” The component-side photo has a strong layout match to iFixit; the paired 1024x768 image shows the opposite, shielded face. | **STRONG VISUAL MATCH**, not independently confirmed P510 | No verified revision mark. The apparent PCB text `CMKY-PB2`, shield mark `2231`, and the `280414` sticker do not establish revision identity. | Reverse-face geometry only; no new component identity |
| Candidate board C | AliExpress listing 3256812077468437 claims to show a P510 main board; one 800x800 image | **UNKNOWN** | No readable revision or board identifier; no independent visual match established | Excluded from revision count |

## Marking analysis

- `280414` is the only clearly documented sticker transcription on the confirmed iFixit board. No corroborating source assigns its meaning.
- `CMKY-PB2` is a provisional reading of small reverse-face silkscreen on the seller-claimed matching board. Exact text and purpose are not established; it is not treated as a confirmed board-family identifier.
- `2231` appears on the seller image's metal shield. It is not established as a PCB identifier, IC marking, revision, or date code.
- Searches for these strings did not produce a P510-specific board assembly catalog entry or corroborated revision record.

## Variant-count limits

- **One** layout is documented in the P510 guide and strongly corroborated by the eBay component-side image.
- **Zero** distinct alternative layouts/revisions are supported by the reviewed material.
- This count describes the evidence collected, not the total number of revisions manufactured.
- Differences in sticker, shielding, or component placement cannot be asserted because no independently identified second P510 board was found.

No P500/P520 board comparison was repeated. Phase 4E did not establish a processor, memory device beyond the prior DRAM candidate, or confirmed board-family identifier that would justify such a comparison. No architectural link is inferred.

## Decision

**MORE DOCUMENTATION REQUIRED.** A seller image of the reverse face improves visual coverage but does not resolve board revision or expose the shielded components. A donor or standalone board is not technically justified until a specific storage device or documented acquisition interface is identified and the candidate hardware can be revision-validated.

## Sources

- [iFixit P510 motherboard-replacement guide](https://www.ifixit.com/Guide/Nikon+Coolpix+P510+Motherboard+Replacement/40287)
- [eBay seller-claimed P510 board](https://www.ebay.com/itm/115640102604)
- [AliExpress seller-claimed P510 board](https://www.aliexpress.us/item/3256812077468437.html?gatewayAdapt=glo2usa4itemAdapt)
- [P510 Phase 4D board-identification report](P510-Phase4D-board-identification.md)
- [P510 Phase 4E component evidence](P510-Phase4E-component-evidence.md)
