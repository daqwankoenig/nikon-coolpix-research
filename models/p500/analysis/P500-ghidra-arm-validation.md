# P500 NPROG ARM Decoding Validation

## Scope and setup

This was a bounded, read-only decoding check of `P500-NPROG-primary.bin`. The source was not modified.

| Item | Result |
|---|---|
| Source size | 7,471,104 bytes |
| SHA-256 before and after | `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29` — matches |
| Ghidra program | Separate `/ARM-Validation/P500-NPROG-primary.bin` program in the existing project |
| Temporary mapping | `0x00000000`; this is only an offset mapping, not a runtime address |
| Decoder profile | ARM, little-endian, 32-bit (`ARM:LE:32:v7`); selecting the Ghidra language profile does not establish the camera's ARM version |
| ARM/Thumb context | `TMode=0` for each tested region |
| Automatic analysis | Off; no analyzer, emulation, or debugging was run |

The test covered 26 unique starting offsets/windows: eight individual vector words and 18 additional bounded regions. Several windows overlap, so their instruction counts are not independent. Existing manually decoded code units were reused by later passes; no full-file disassembly was performed.

## Tested vector entries

Together, the eight consecutive ARM branch encodings form a strong vector-table-shaped structure. Each branch destination is within the file-relative section.

| File offset | Length | ARM decoding and control flow | Pointer/literal observations | ARM/Thumb evidence | Classification | Confidence |
|---:|---:|---|---|---|---|---|
| `0x00000000` | 4 | `B 0x20` | Target is an internal tested startup region | ARM branch; no Thumb evidence | LIKELY CODE | High as part of the vector sequence |
| `0x00000004` | 4 | `B 0x248` | Target is an internal tested handler region | ARM branch; no Thumb evidence | LIKELY CODE | High as part of the vector sequence |
| `0x00000008` | 4 | `B 0x260` | Target is within the tested `0x248` handler window | ARM branch; no Thumb evidence | LIKELY CODE | High as part of the vector sequence |
| `0x0000000C` | 4 | `B 0x278` | Target is within the tested `0x248` handler window | ARM branch; no Thumb evidence | LIKELY CODE | High as part of the vector sequence |
| `0x00000010` | 4 | `B 0x290` | Target is an internal tested handler region | ARM branch; no Thumb evidence | LIKELY CODE | High as part of the vector sequence |
| `0x00000014` | 4 | Branches to itself | Plausible reserved/unused-vector loop | ARM branch; no Thumb evidence | LIKELY CODE | Medium |
| `0x00000018` | 4 | `B 0x11C` | Target is an internal tested exception-entry region | ARM branch; no Thumb evidence | LIKELY CODE | High as part of the vector sequence |
| `0x0000001C` | 4 | `B 0x244` | Target is an internal self-branch | ARM branch; no Thumb evidence | LIKELY CODE | High as part of the vector sequence |

## Tested code and data regions

| File offset | Length | ARM decoding quality and control flow | Pointer/literal observations | ARM/Thumb evidence | Classification | Confidence |
|---:|---:|---|---|---|---|---|
| `0x00000020` | `0x40` | 15 instructions / 60 bytes; mode changes, stack setup, two calls, then branch to `0x3D0` | Loads six values from literals at `0xFC–0x110` into mode-specific SP registers; values are `0x57FCA000–0x57FCF000` | Coherent ARM startup sequence; no BX/BLX here | STRONG CODE CANDIDATE | High |
| `0x00000060` | `0x80` | Coherent ARM setup leading to the fill routine; control transfers to `0xB4`; later listing includes overlapping decoded code | Loads `0x57EA0000` and `0x57F14028`, subtracts them to obtain `0x74028`, and prepares zero-valued registers | LDR, SUB, MOV, STM/LDM and conditional-loop code elsewhere in the routine; ARM state | STRONG CODE CANDIDATE | High |
| `0x0000011C` | `0x40` | 16 instructions / 64 bytes; coherent exception-entry operations, stack switching, register saves, loads/stores | Literals include `0x506ABA00`, `0x57FCB000`, `0x57EEFA84`, and `0x57EEFA94` | MRS/MSR, STM and LDR/STR; no Thumb transition observed | STRONG CODE CANDIDATE | High |
| `0x00000244` | 4 | One self-branch; plausible unhandled-vector loop but no surrounding function body tested | None | ARM branch; no Thumb evidence | AMBIGUOUS | Low |
| `0x00000248` | `0x40` | 16 instructions / 64 bytes; repeated exception wrappers adjust LR, store it, set a reason value, and call a common target | Loads `0x506ABA08`; calls at `0x25C` and `0x274` target file-relative `0x2D1C3C`, outside this section | Coherent ARM control flow and data operations; no BX/BLX | STRONG CODE CANDIDATE | High |
| `0x00000290` | `0x40` | Nine instructions / 36 bytes decoded; the initial wrapper sequence is coherent, followed by literal-looking words | Calls `0x2D1C3C`; words at `0x2A8` onward include `0x506ABA00`, `0x57FCB000`, and `0x57EEFA84` | ARM wrapper pattern; do not treat the later literal words as code | LIKELY CODE | Medium |
| `0x000003D0` | `0x40` | Four instructions form a small callable routine: save LR, call `0x700C`, set `r0=0`, return through `LDR PC,[SP],#4` | Internal call target `0x700C` | Plausible ARM prologue/call/return | STRONG CODE CANDIDATE | High |
| `0x000003F0` | `0x40` | 16 instructions / 64 bytes; coherent initialization sequence with an internal call | CP15 operations and constants including `0x40000037`, `0x50000037`, and `0x60000000`; their memory-map meaning is not established | MRC/MCR to coprocessor 15 is strong ARM-system-code evidence | STRONG CODE CANDIDATE | High |
| `0x000000B4` | `0x80` | Conditional fill-tail logic, word/byte remainder handling, and return; this window overlaps the separate `0x11C` test | Uses the start/length prepared at `0x60` | Coherent ARM conditional branches, stores, and LDM return | STRONG CODE CANDIDATE | High |
| `0x00000094` | `0x20` | Eight consecutive `STMIA r0!` instructions each store 32 bytes; `r4–r9`, `r12`, and `lr` were zeroed before this loop | Writes through the pointer in `r0` | Strong ARM block-store loop evidence | STRONG CODE CANDIDATE | High |
| `0x00006AEC` | `0x60` | Five-instruction routine reads CPSR, sets a control bit, writes CPSR, then returns with `BX LR` | Direct call from `0x3F4` | `BX LR` is a conventional ARM return here; no evidence its target is odd or Thumb | STRONG CODE CANDIDATE | High |
| `0x0000700C` | `0x60` | 24 instructions / 96 bytes; stack-frame prologue and 13 calls to internal offsets | Literal `0x57EEFA80`; its mapped candidates are examined below | Coherent ARM calls and stack operations | STRONG CODE CANDIDATE | High |
| `0x00050280` | `0x40` | 16 instructions / 64 bytes; coherent data operations, compare, and conditional branch | This is where `0x57EF0280` maps under base `0x57EA0000` | Coherent ARM sequence; supports ARM decoding, not the base uniquely | LIKELY CODE | Medium-high |
| `0x00080280` | `0x40` | 12 instructions / 48 bytes; conditional branch, memory operations, and internal branch | This is where `0x57EF0280` maps under base `0x57E70000` | Coherent ARM sequence; supports ARM decoding, not the base uniquely | LIKELY CODE | Medium |
| `0x0004FA84` | `0x40` | 16 consecutive load/store and bit-clear instructions, without a tested function boundary or branch | Mapping of `0x57EEFA84` under base `0x57EA0000` | ARM-like sequence, but insufficient control-flow context | AMBIGUOUS | Low-medium |
| `0x0007FA84` | `0x40` | 15 instructions / 60 bytes; coherent load/store, call, compare, conditional branch, and branch | Mapping of `0x57EEFA84` under base `0x57E70000` | Coherent ARM sequence; does not uniquely establish the mapping | LIKELY CODE | Medium |
| `0x000A4028` | `0x40` | 16 instructions / 64 bytes; coherent load, compare, conditional branch, and data manipulation | Mapping of `0x57F14028` under base `0x57E70000` | Coherent ARM sequence; address is also the zero-fill endpoint described below | LIKELY CODE | Medium |
| `0x00074028` | `0x60` | Only four words decoded as instruction-like operations; the raw words form an aligned address table rather than coherent flow | Initial values include `0x57EF0280`, `0x57EF0288`, `0x57EF0284`, `0x57EF028C`, and further nearby entries | The words point to coherent code under either tested base; no Thumb evidence | LIKELY DATA | High |

The exception wrappers at `0x248–0x2A4` repeatedly call `0x2D1C3C`, which is outside the 7,471,104-byte file-relative extent. It may belong to code outside this extracted section; this test does not identify it. The temporary zero mapping must not be interpreted as the runtime address.

## Address interpretation and base hypotheses

### Strongly supported memory behavior

- **CONFIRMED from the decoded instructions:** The startup code loads `r0=0x57EA0000` and `r1=0x57F14028`, computes `r2=r1-r0=0x74028`, and branches into a routine that fills the pointed-to range with zero-valued register contents. The range is `[0x57EA0000, 0x57F14028)`; this is evidence for an initialized memory/work area, not an image-base reference.
- **CONFIRMED from the decoded instructions:** Startup changes ARM modes and loads SP from `0x57FCA000`, `0x57FCB000`, `0x57FCC000`, `0x57FCD000`, `0x57FCE000`, and `0x57FCF000`. These are mode-specific stack-pointer values spaced by `0x1000`; a likely RAM stack region is `0x57FCA000–0x57FD0000`, but its actual allocation boundaries are not established.
- `0x506ABA00` and `0x506ABA08` are also used as absolute stack/data references and fall outside both tested image-sized spans. Their exact memory type is unknown.

### Comparison of the two image-base hypotheses

The prior broad aligned-pointer scan tied `0x57E70000` and `0x57EA0000` at 10,492/15,971 values (65.69%). Those totals are not independent code references and cannot select a base.

| Candidate base | Evidence for | Evidence against | Pointers resolved | Confidence | Notes |
|---:|---|---|---:|---|---|
| `0x57E70000` | The broad pointer scan ties for the highest count. Under this mapping, values such as `0x57EF0280` and `0x57EEFA84` map to regions that decode coherently as ARM code. | No direct reference to `0x57E70000` was found in the tested startup code. The same pointer values also map to coherent ARM sequences under `0x57EA0000`. | 10,492 / 15,971 (65.69%) in the prior scan | PLAUSIBLE | Statistical candidate only; not a selected or verified image base. |
| `0x57EA0000` | Ties the broad pointer scan. It appears as an exact startup literal; related address references map into the file-sized span. | The literal is used as the start of a zero-fill range, not identified as the binary load address. Mapping the section contiguously here would overlap that range with the section's beginning; the alternative mapping also explains the tested pointer targets. | 10,492 / 15,971 (65.69%) in the prior scan | WEAK | Better interpreted as the start of the zero-fill/work area. Relocation or aliases are not ruled out, so this is not a formal rejection. |
| `0x57E80000–0x57E90000` | Adjacent points on the prior 64-KiB grid had 10,491/15,971 resolutions, nearly tied with the maximum. | No independently validated references or code/data relationships select either value. | 10,491 / 15,971 (65.68%) each in the prior scan | WEAK | Part of the same broad statistical plateau. |

Address-table values at `0x74028` map to `0x50280` under `0x57EA0000` and `0x80280` under `0x57E70000`; both destinations decode as plausible ARM code. Likewise, `0x57EEFA84` maps to `0x4FA84` or `0x7FA84`, both containing ARM-like sequences. These checks do not distinguish the bases. The stack pointers fall inside both candidate file-sized spans when subtracted, but they are stack values, not evidence that they point into the file.

The prior statement that `0x57FCxxxx` fell outside the two candidate spans was incorrect. With the 7,471,104-byte (`0x720000`) section, those values are in both spans: offsets `0x12A000–0x12F000` under `0x57EA0000`, and `0x15A000–0x15F000` under `0x57E70000`. Their decoded use as stack pointers makes them poor image-base discriminators.

**Image-base conclusion: UNKNOWN.** No candidate reaches SUPPORTED or STRONGLY SUPPORTED. Do not rebase the Ghidra program based on these results.

## Architecture and memory-range assessment

- **ARM32 little-endian: STRONGLY SUPPORTED, not hardware-confirmed.** The branch-vector-shaped startup, mode-specific SP setup, coherent prologues/calls/returns, conditional loops, LDR/STR and STM/LDM sequences, and CP15 instructions decode consistently in ARM state.
- **Thumb or ARM/Thumb interworking: NOT ESTABLISHED.** The only BX found in these samples is `BX LR` at `0x6AFC`, a normal ARM return. No BLX or odd-valued function pointer was observed in the tested regions. Earlier low-bit-set values alone do not prove Thumb code.
- **Probable RAM/work area:** `[0x57EA0000, 0x57F14028)` is explicitly zero-filled at startup and is likely RAM or another writable work area. The six mode-specific stack-pointer values cluster at `0x57FCA000–0x57FCF000`; likely RAM, with exact allocation bounds unknown.
- **Probable ROM:** No ROM address range is established. The candidate image spans under `0x57E70000` or `0x57EA0000` remain hypotheses and cannot be labeled ROM.
- **Data alongside code:** Confirmed by the address table at file offset `0x74028` and by literal pools interleaved with startup instructions.

## Recommendation and stop point

The evidence is sufficient to justify a **limited set of ARM analyzers** on the separate offset-zero analysis program, but none were enabled or run in this phase. Keep the mapping at `0x00000000`; do not rebase to `0x57EA0000` or `0x57E70000`. Full automatic analysis, SG583SLAVE analysis, firmware modification, export, emulation, and camera interaction remain out of scope.

## Operational note

Ghidra's headless startup output indicated it consulted its default per-user preferences/log location under `%APPDATA%\ghidra\ghidra_12.2_PUBLIC` and invoked cache maintenance under `%LOCALAPPDATA%\ghidra\fscache2`, both outside the authorized project/tool roots. No firmware or project database was intentionally placed there. I did not attempt to move or clean up those user-profile locations. No global `PATH`, `JAVA_HOME`, or Windows system configuration was changed.
