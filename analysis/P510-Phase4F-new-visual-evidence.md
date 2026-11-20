# P510 Phase 4F - New Visual Evidence

**Status:** COMPLETE - public/local research only  
**Novelty rule:** Preserve only images that reveal materially new evidence. No new image met that threshold in Phase 4F.

## Result

**New P510 board images accepted: 0.** No image showed the processor marking, removed thermal material, removed shield, readable nonvolatile-memory marking, useful new board identifier, or a materially higher-resolution view than the existing evidence.

No image files were added and the SHA-256 manifest was not changed. The existing Phase 4E image and hash remain in [P510-Phase4E-research-image-hashes.txt](../checksums/P510-Phase4E-research-image-hashes.txt).

## Candidate review

| Candidate | Source and resolution | Novelty/evidence assessment | Disposition |
|---|---|---|---|
| iFixit P510 board images, steps 16-18 | 4000x3000 for the main board views; already locally preserved and hash-verified in Phase 4D | Component face only; central IC remains under thermal material. No new iFixit asset or unobscured view was found. | Reused for comparison only; not copied or re-hashed |
| eBay item 115640102604, component face | 1024x768 direct CDN image; documented in Phase 4E | Duplicates the iFixit populated face at lower resolution; processor remains obscured. | Not saved again |
| eBay item 115640102604, reverse face | 1024x768 direct CDN image; already saved and hashed in Phase 4E | Shows a shielded reverse face, but the shield is still present. No new copy or higher-resolution variant was found. | No Phase 4F change |
| AliExpress item 3256812077468437 | 800x800 seller image | No new board face, readable marking, or independent identity evidence. | Not saved |
| Pikabu P510 lens-repair image results | Two image URLs reported as 1600x900 in Bing Images | Source image requests timed out; a Bing CDN preview attempt returned a blank page. Image content and board identity could not be verified. | **UNKNOWN**; not saved or used |

## Historical listing and image recovery

- Wayback CDX returned two 2025-12-15 records associated with eBay item `115640102604`, both HTTP 307 responses.
- Replaying a simplified archived listing URL returned HTTP 404; no archived gallery content could be recovered.
- The Wayback CDX query for the known eBay reverse-face image returned no archived image captures.
- Current eBay and AliExpress image assets remain as described in [P510-Phase4E-new-source-images.md](P510-Phase4E-new-source-images.md); no additional original marketplace image was found.

The failed archive replay and inaccessible repair-post images are research limitations, not evidence that no other copies exist anywhere.

## Image integrity and storage

- No Phase 4F image was downloaded or modified.
- The Phase 4E image SHA-256 manifest remains unchanged.
- No AI enhancement, upscaling, or image processing was used.
- No P500/P520 image was used as P510 evidence.

## Conclusion

There is no new visual evidence to update the component map or [P510-known-facts.md](P510-known-facts.md). The only useful next view would need to show the central IC without thermal material or the reverse-face components without the shield, from a board with independently supported P510 identity.

## Sources

- [iFixit P510 motherboard-replacement guide](https://www.ifixit.com/Guide/Nikon+Coolpix+P510+Motherboard+Replacement/40287)
- [eBay seller-claimed P510 board, item 115640102604](https://www.ebay.com/itm/115640102604)
- [AliExpress seller-claimed P510 board, item 3256812077468437](https://www.aliexpress.us/item/3256812077468437.html?gatewayAdapt=glo2usa4itemAdapt)
- [P510 Phase 4E source-image inventory](P510-Phase4E-new-source-images.md)
- [Wayback CDX query for eBay item 115640102604](https://web.archive.org/cdx/search/cdx?url=ebay.com/itm/115640102604*&output=json&fl=timestamp,original,statuscode)
- [Bing `2231` P510 image/search context](https://www.bing.com/search?q=%222231%22+Nikon+P510+PCB+board)
