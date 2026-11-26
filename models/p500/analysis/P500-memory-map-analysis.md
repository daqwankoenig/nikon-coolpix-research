# P500 Primary-Code Memory Map Analysis — Phase 2C

## Scope and integrity

- **CONFIRMED** — Target: `firmware/extracted/P500/sections/P500-NPROG-primary.bin`, 7,471,104 bytes (`0x720000`).
- **CONFIRMED** — SHA-256: `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`; it matches the expected value in [P500-section-hashes.txt](../checksums/P500-section-hashes.txt).
- **CONFIRMED** — Analysis was read-only. The payload was not modified, disassembled, imported into Ghidra, or used to create a project. No camera was accessed.
- **CONFIRMED** — The P520 was not analyzed. The P500 slave payload was not used to infer this image's address space.

## Executive result

- **STRONGLY SUPPORTED** — The primary section contains 32-bit little-endian ARM code, including a branch-vector-shaped startup table and many ARM-like instruction patterns.
- **UPDATED BY PHASE 2D-1** — The broad pointer scan ties `0x57EA0000` and `0x57E70000`, but ARM decoding shows `0x57EA0000` is used as the start of a zero-fill range. Treat it as a likely work-area address, not as the strongest image-base candidate.
- **UNKNOWN** — The exact image base is not established. `0x57E70000` remains only a statistical candidate; nearby 64-KiB-aligned values resolve nearly the same number of pointers, and no candidate has independent string-address or external memory-map corroboration.
- **UPDATED BY PHASE 2D-1** — The `0x57FCxxxx` values are loaded into mode-specific stack-pointer registers; they are likely stack addresses, although the backing RAM extent is not independently confirmed. Other address-looking ranges remain unclassified.
- **Recommendation** — The evidence is not strong enough to import this binary into Ghidra with an asserted image base. Do not choose a base merely to satisfy the importer.

## Startup words and branch targets

The first 4 KiB were scanned as 1,024 aligned 32-bit little-endian words. The first eight words have the encoding pattern of ARM unconditional branches. Applying the ARM PC-relative branch-target calculation gives:

| File offset | Word | Calculated file-relative target |
|---:|---:|---:|
| `0x00` | `0xEA000006` | `0x20` |
| `0x04` | `0xEA00008F` | `0x248` |
| `0x08` | `0xEA000094` | `0x260` |
| `0x0C` | `0xEA000099` | `0x278` |
| `0x10` | `0xEA00009E` | `0x290` |
| `0x14` | `0xEAFFFFFE` | `0x14` (self-branch) |
| `0x18` | `0xEA00003F` | `0x11C` |
| `0x1C` | `0xEA000088` | `0x244` |

- **LIKELY** — This is an ARM exception-vector/startup table: the eight entries have the expected regular spacing and branch form, and every calculated target lies within the file.
- **CONFIRMED** — The first 4 KiB contains 121 words matching the tested ARM branch/branch-link pattern; all 121 calculated targets remain inside the 7,471,104-byte section.
- **UNKNOWN** — No initial stack pointer can be read from these eight entries; they are branches, not a vector table containing an initial-SP word. Startup code may set stacks elsewhere, but that was not decoded here.
- **IMPORTANT LIMIT** — These branches are PC-relative. Their in-file targets support the startup/code interpretation but do not determine an absolute load address.

## Address-like word scan

Aligned 32-bit words were grouped by broad numeric range. These are raw counts, not counts of confirmed pointers; zero values, instruction encodings, immediates, and data are included.

| Word-value range | Raw aligned-word count |
|---|---:|
| `0x00000000–0x0FFFFFFF` | 297,470 |
| `0x10000000–0x1FFFFFFF` | 62,949 |
| `0x20000000–0x2FFFFFFF` | 13,527 |
| `0x40000000–0x4FFFFFFF` | 9,937 |
| `0x50000000–0x5FFFFFFF` | 24,907 |
| `0x80000000–0x8FFFFFFF` | 14,416 |
| `0xE0000000–0xEFFFFFFF` | 1,308,670 |

- **CONFIRMED** — Of the 24,907 words in the `0x5` range, 15,971 are 4-byte-aligned values. The large `0xE` count is dominated by instruction-like values and is not treated as an address-space candidate.
- **LIKELY** — The aligned `0x5` values are the most useful address candidates in this scan because a substantial subset forms coherent in-file references under nearby candidate bases. Their interpretation as pointers is not individually confirmed.
- **UNKNOWN** — The other broad-range counts do not independently identify ROM, RAM, or a hardware register region.

### Base-resolution comparison

For each tested candidate, aligned values in `0x50000000–0x5FFFFFFF` were counted as resolved when `candidate_base <= value < candidate_base + 0x720000`. Bases were tested on a 64-KiB grid; this is a heuristic scan, not proof that the actual base must be 64-KiB-aligned.

| Candidate base | Aligned `0x5` values resolving inside image | Resolution rate | Confidence | Evidence and limitations |
|---:|---:|---:|---|---|
| `0x57E70000` | 10,492 / 15,971 | 65.69% | **PLAUSIBLE** | Tied for the maximum grid count. No exact references to this base or independent address-map corroboration were found. |
| `0x57E80000` | 10,491 / 15,971 | 65.68% | **PLAUSIBLE** | One fewer resolution than the maximum; otherwise part of the same near-tied plateau. |
| `0x57E90000` | 10,491 / 15,971 | 65.68% | **PLAUSIBLE** | One fewer resolution than the maximum; otherwise part of the same near-tied plateau. |
| `0x57EA0000` | 10,492 / 15,971 | 65.69% | **PLAUSIBLE** | Tied for the maximum. The exact value occurs at file offsets `0x114`, `0x2B8`, and `0x8778`, including among address-like constants near startup. This is useful supporting evidence, but does not distinguish it decisively from the other top grid candidate. |
| `0x57E00000` | 10,470 / 15,971 | 65.57% | **PLAUSIBLE** | Only 22 fewer aligned values resolve than at the maximum; this small difference does not reject it. |
| `0xE5740000`-like candidates | Not meaningful | — | **REJECTED** | A broad numeric scan can favor instruction-encoding-dominated `0xE...` values. Those results are not credible load-base evidence. |

- **CONFIRMED** — The best result on the tested grid is 10,492/15,971 (65.69%), tied at `0x57E70000` and `0x57EA0000`; adjacent grid points differ by at most one resolution in this plateau.
- **LIKELY** — The values support a candidate-base grid from `0x57E70000` through `0x57EA0000` at 64-KiB increments, with a `0x720000`-byte image-sized span. The grid scan does not establish an exact base, nor does it test every possible unaligned base.
- **UNKNOWN** — No exact candidate reaches **SUPPORTED** confidence. The image base therefore remains unknown.

### Candidate pointer-table runs at `0x57EA0000`

These are runs of consecutive aligned words whose values fall inside the candidate image interval when based at `0x57EA0000`. They are coherent supporting evidence for an address mapping, but their semantics have not been decoded; they are called candidate pointer tables, not confirmed function tables.

| Source file offset | Entries | Observed target-address range | Resolved inside image | Candidate base |
|---:|---:|---:|---:|---:|
| `0x004AB800` | 56 | `0x57EC03A0–0x57EEE994` | 56/56 (100%) | `0x57EA0000` |
| `0x004AD0F0` | 43 | `0x57EE6C60–0x57F0EA3C` | 43/43 (100%) | `0x57EA0000` |
| `0x0037DF60` | 37 | `0x57EC76E0–0x57EC7780` | 37/37 (100%) | `0x57EA0000` |
| `0x001BE194` | 31 | `0x57EAF448–0x57EB4954` | 31/31 (100%) | `0x57EA0000` |

- **LIKELY** — These runs are structured address tables or similar data: each is a consecutive series of aligned values and every entry maps into the candidate image.
- **UNKNOWN** — The runs do not independently choose `0x57EA0000`; a nearby base shifts the file offsets while retaining many in-range entries.

## Startup address constants and strings

- **CONFIRMED** — Address-like constants at offsets `0xFC–0x118` include `0x57FCA000`, `0x57FCB000`, `0x57FCC000`, `0x57FCD000`, `0x57FCE000`, `0x57FCF000`, `0x57EA0000`, and `0x57F14028`.
- **CORRECTED BY PHASE 2D-1** — Under the `0x57EA0000` candidate, `0x57EA0000` maps to file offset `0x0` and `0x57F14028` maps to `0x74028`. ARM decoding shows these two values are used as the start and exclusive end of a zero-fill range of `0x74028` bytes; this is memory-initialization evidence, not independent evidence for the image base.
- **CORRECTED BY PHASE 2D-1** — The `0x57FCxxxx` mode-stack values are inside both candidate spans: offsets `0x12A000–0x12F000` for base `0x57EA0000`, and `0x15A000–0x15F000` for base `0x57E70000`. Their use as stack pointers means these offsets do not validate either image-base hypothesis.
- **CONFIRMED** — Readable P500/Nikon strings exist in this section, including `NIKON DIGITAL CAMERA` at `0x281BE4`, `0x2A5170`, `0x61AF24`, `0x620AF8`, and `0x649488`; and `COOLPIX P500` at `0x620C90`, `0x6461E0`, `0x64668C`, `0x64837E`, `0x649470`, `0x6497BE`, `0x6497D6`, and `0x6BA7AD`.
- **CONFIRMED** — Exact aligned references to the tested string starts were not found for `0x57E00000`, `0x57E70000`, or `0x57EA0000`. This is a lack of corroboration, not proof that strings are never referenced indirectly or by interior addresses.
- **UNKNOWN** — No error-message, filename, device-name, or other string-address relationship independently validates a candidate base in these checks.

## ARM, Thumb, and data assessment

- **STRONGLY SUPPORTED — ARM** — The startup words match ARM branch encodings, their PC-relative destinations are coherent, and the earlier section analysis found repeated ARM-style prologue/epilogue and `BX` instruction patterns in this payload. These are structural/pattern indicators, not a complete disassembly or processor identification.
- **CONFIRMED** — Low-bit-set address-like values were also checked as possible Thumb-tagged pointers using `0x57EA0000`. There were 2,480 in-image occurrences (612 distinct targets after clearing bit 0), but target halfwords did not show a convincing distribution of Thumb entry patterns: none began with the tested push, pop, or BX forms; only 3 targets had a push-like halfword within the next 16 halfwords, and 1 had a pop/BX-like halfword there.
- **UNKNOWN** — Thumb code is not established. The low-bit-set values may have another meaning or may point into ARM instructions/data; their presence alone does not demonstrate ARM/Thumb interworking.
- **LIKELY** — The section contains data alongside code. The address-table runs and readable product, filesystem, update, and diagnostic strings are evidence of non-instruction data within the same section.
- **UPDATED BY PHASE 2D-1** — Startup loads `0x57FCA000`, `0x57FCB000`, `0x57FCC000`, `0x57FCD000`, `0x57FCE000`, and `0x57FCF000` into mode-specific SP registers. These are likely stack tops spaced by `0x1000`; exact stack allocation boundaries remain unknown.

## ROM/RAM interpretation and Ghidra decision

- **HYPOTHESIS** — If the section is mapped contiguously at one of the leading candidates, its file-backed range would be:
  - base `0x57E70000` → exclusive end `0x58490000`;
  - base `0x57EA0000` → exclusive end `0x58520000`.
- **UNKNOWN** — The file does not establish a ROM range or a contiguous firmware image base. Phase 2D-1 identifies a likely writable zero-fill/work area at `[0x57EA0000, 0x57F14028)` and likely mode stacks around `0x57FCA000–0x57FD0000`, but their physical memory type and exact bounds are not independently confirmed.
- **UNKNOWN** — No hardware documentation or independent load-address field was used to corroborate these candidate values.
- **Decision** — **Not strong enough to import with an explicit image base.** The exact base remains unknown; further independent evidence is needed before selecting one. No Ghidra project was created and no binary was imported.

## Method limits

- Pointer resolution means only that a candidate value falls within the file-size interval after subtracting the candidate base. It does not prove that the value is a pointer or that the image is loaded there.
- The candidate-base scan used aligned words and a 64-KiB grid. Instruction immediates and data can resemble addresses, and unaligned bases were not exhaustively tested.
- No section was carved, no code was disassembled, and no emulation or execution was performed.
- No P510 conclusion follows from this P500-only analysis.
