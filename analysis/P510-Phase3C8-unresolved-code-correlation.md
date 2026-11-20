# P510 Phase 3C-8 — Offline Unresolved-Code Correlation

**Status: COMPLETE — OFFLINE ONLY**

No P510 connection, USB attachment, PTP session, command, property query/write, event subscription, camera test, or firmware modification occurred. The raw P510 DeviceInfo capture and all reference firmware artifacts remained unchanged. P500/P520 findings below are reference-only and do not establish P510 compatibility or behavior.

## Scope and evidence labels

This phase investigated the exact meanings, implementation clues, and cross-model relationships of:

- Operations: `0x90A1`, `0x90A2`, `0x90A3`
- Device properties: `0xD280`, `0xD303`
- Image format: `0xB111`

Evidence labels:

- **CONFIRMED BY PHYSICAL P510** — returned by the one successful, previously captured P510 `GetDeviceInfo`.
- **CONFIRMED BY PROJECT SOURCE** — an exact local source or binary contains the stated code or name. Model provenance is retained.
- **INFERENCE** — a bounded interpretation of source/binary structure, not proof of P510 behavior.
- **UNKNOWN** — meaning or behavior is not established by the available evidence.

“Final status” in the code matrix describes how well the code’s meaning/cross-reference was resolved. Physical advertisement is separately confirmed and does not resolve semantics.

## 1. Capture integrity and authoritative P510 categories

The three hashes below were recomputed before finalizing this report and match the successful Phase 3C-5B record:

| Artifact | SHA-256 | Result |
|---|---|---|
| [P510-GetDeviceInfo.raw.bin](P510-GetDeviceInfo.raw.bin), 293 bytes | `E867C4FEE60CE314FC6DFF9D9A3300FA950136A279484DB13EADFE2E7C17EF96` | MATCH |
| [P510-GetDeviceInfo-decoded.txt](P510-GetDeviceInfo-decoded.txt) | `599FECA3CAA14F4BB4369CEE88791FE8ABCAC28FFDD979E3A1FCF49D332622FB` | MATCH |
| [P510-GetDeviceInfo-transport.log](P510-GetDeviceInfo-transport.log) | `149A647852B5E5A2D9B10B2292FEE603D76093FF130F3DFDB68D47C065AB4A7F` | MATCH |

The raw 293-byte payload was independently reparsed; all bytes were accounted for and the target codes agree with the decoded text:

| Code | Exact P510 DeviceInfo category | P510 advertisement |
|---|---|---|
| `0x90A1` | `OperationsSupported` | Yes |
| `0x90A2` | `OperationsSupported` | Yes |
| `0x90A3` | `OperationsSupported` | Yes |
| `0xD280` | `DevicePropertiesSupported` | Yes |
| `0xD303` | `DevicePropertiesSupported` | Yes |
| `0xB111` | `ImageFormats` | Yes |

`0xB111` occurs in `ImageFormats`, not in `CaptureFormats`, `OperationsSupported`, `EventsSupported`, or `DevicePropertiesSupported`. `CaptureFormats` is empty. The camera advertised 26 operations, 11 events, six properties, and seven image formats. These are capability declarations only; no target code was exercised.

## 2. Sources, search method, and integrity of reference binaries

Reviewed local evidence included:

1. [Phase 3C-5B physical report](P510-Phase3C5B-physical-GetDeviceInfo.md), raw and decoded DeviceInfo, [known facts](P510-known-facts.md), and the [Phase 3C-6 analysis](P510-Phase3C6-DeviceInfo-analysis.md) and [Phase 3C-7 reconciliation](P510-Phase3C7-offline-source-reconciliation.md).
2. The local Nikon Wireshark PTP patch and D7000/D5100 IDA helpers already identified in Phase 3C-7; the source audit and client/transport research were also consulted.
3. [P500 string-reference analysis](P500-string-reference-analysis.md), [P500 section map](P500-section-map.md), [P500 container map](P500-container-map.md), [P500/P520 payload comparison](P500-P520-payload-comparison.md), and [P520 payload analysis](P520-payload-analysis.md).
4. All locally available P500/P520 extracted `.bin` files and the two local Nikon updater `.exe` packages. The `.exe` files were treated as data only and not executed.

The exact-code search covered case and prefix variants (`0x90A1`/`90A1`/`0x90a1`/`90a1`, and equivalent forms for the other five codes), raw little- and big-endian 16-bit byte pairs, exact 32-bit forms in both byte orders, ASCII strings, and UTF-16LE strings. Raw-byte scans used no-Unicode mode so high-byte escapes were not transformed into UTF-8. A byte match by itself was not treated as semantic evidence.

### SHA-256 of scanned firmware/package inputs

| Model/context | Artifact | SHA-256 |
|---|---|---|
| P500 | `firmware/extracted/P500/P500Update/firmware/firmware.bin` | `80A297C8B4B77731EB2B3B5DC23D905D557A0052049402364B11A1F7849779B4` |
| P500 | `sections/P500-NPROG-primary.bin` | `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29` |
| P500 | `sections/P500-NDATA.bin` | `20656DFDF01560188DED6063BCB5CE29BDEC7FC6D127A5B20B3A38280A41CBD2` |
| P500 | `sections/P500-NPROG-secondary.bin` | `B661EF6464B58ABCD14876A9E0E2C7C6C74521ADEB200810C32214B74A959203` |
| P500 | `sections/P500-SFIRM-composite-payload.bin` | `8840083A1CBD3024E8D02FFCF6AF04773F37D30A21E26A16B07EB0D3D762E5FE` |
| P500 | `sections/P500-SG583SLAVE-payload.bin` | `6E7D0AA03908549C1FDDAA9637297EBB4BFBE626C14A0E7BEB76ACD902773100` |
| P500 | Both 12-byte `NLIPI` section files (identical) | `3C499749966CB76F69831BF06ED8DA33C0A47130E4D6D08EA0DD4B616C2B8CF3` |
| P520 | `firmware/extracted/P520/P520Update/firmware/firmware.bin` | `631A4C6AB34E3BE5C7EE1153AD1A7D93986DA2853C79F572B63A3E23129B979C` |
| P500 | `firmware/reference/P500/F-P500-V11W.exe` | `CA83DDCCD4B3E4CEBAA5C72BD65959F70C1138E3E6E2A273E14DF142C31C99CD` |
| P520 | `firmware/reference/P520/F-P520-V11W.exe` | `CFDE64DD155C6DFA6FF6BD74AD807D7A3F615938DCA2190D72A075C8519E6DB2` |

These are read-only identity records; scanning did not alter any source or extracted artifact. The P500 complete `firmware.bin` contains mapped sections, so its hits are not independent corroboration of hits in the extracted sections.

## 3. Exact-code search results

### Local source cross-references

- **`0x90A1`–`0x90A3`:** no exact semantic definition in the available Wireshark/Nikon firmware-tools text, D7000/D5100 helpers, or reviewed project notes. Other named Nikon operations such as `0x90C0`, `0x90C1`, and `0x90CA` are distinct values and do not define these codes.
- **`0xD303`:** the D7000 helper at `IDA_files/D7000/105/ptp_code_names.idc` returns the literal label `NIKON_D303`. It supplies no semantic name, parameter schema, value type, or behavior. The adjacent helper entries for `0xD200` and `0xD201` have descriptive Picture Control names; that adjacency does not transfer their meaning to `0xD303`.
- **`0xD280`:** no exact PTP-property name was found. A D5100 script contains a memory/menu-name address ending in `0xD280`; it is not a PTP code reference.
- **`0xB111`:** no exact format name was found in the reviewed local source tables. The Wireshark format table names other image formats but has no entry for `0xB111`.
- The prior source audit found no locally available libgphoto2 source checkout, so no direct libgphoto2-source mapping can be claimed. No exact semantic mapping was found in the other locally available Nikon/PTP source material or NikonDump-related project material.

### Raw 16-bit byte-pattern counts

Counts are little-endian (`LE`) and big-endian (`BE`) raw 16-bit occurrences, not counts of PTP table entries. Repeated, unaligned, instruction, compressed, and high-entropy matches are included. They are not semantic matches. `—` means no occurrence in the 12-byte NLIPI records.

| Scanned artifact | `90A1` LE/BE | `90A2` LE/BE | `90A3` LE/BE | `D280` LE/BE | `D303` LE/BE | `B111` LE/BE |
|---|---:|---:|---:|---:|---:|---:|
| P500 complete `firmware.bin` | 31/31 | 84/48 | 32/28 | 131/356 | 65/77 | 41/43 |
| P500 NPROG primary | 9/9 | 7/36 | 11/5 | 111/25 | 33/35 | 18/14 |
| P500 NDATA | 19/19 | 75/11 | 18/18 | 15/326 | 31/40 | 15/20 |
| P500 NPROG secondary | 3/0 | 1/0 | 0/2 | 0/0 | 0/0 | 0/0 |
| P500 SFIRM composite | 0/3 | 1/1 | 3/3 | 5/5 | 1/2 | 8/9 |
| P500 SG583SLAVE | 0/3 | 1/1 | 3/3 | 5/5 | 1/2 | 8/9 |
| P500 NLIPI records | — | — | — | — | — | — |
| P520 opaque payload | 1092/1114 | 1386/1315 | 1257/1255 | 1280/1234 | 1623/1609 | 1392/1330 |
| P500 updater executable | 63/56 | 63/57 | 75/69 | 75/67 | 90/94 | 63/99 |
| P520 updater executable | 1100/1139 | 1085/1163 | 1105/1176 | 1140/1164 | 1130/1190 | 1125/1175 |

No ASCII or UTF-16LE textual rendering of the six codes supplied a firmware semantic name. The many P520 payload matches are expected to be non-semantic in context: its 81,264,928-byte payload was previously measured at 7.999998 bits/byte overall, with 1 MiB-window mean 7.999840. For example, the aligned P520 `0x90A2` little-endian 32-bit byte sequence at `0x041C51E0` is surrounded by high-entropy bytes, not a structured code table.

Representative P500 contexts likewise do not establish an operation family:

- P500 primary `0x90A1` LE hit at `0x000DD11D` is unaligned relative to the ARM word at `0x000DD11C`; the matched bytes are part of an instruction word, not a PTP identifier record.
- P500 primary `0x90A2` LE hit at `0x00017198` falls within an ARM branch instruction encoding.
- P500 primary `0x90A3` LE hit at `0x00515107` is unaligned in instruction bytes. A BE 32-bit occurrence at `0x005F2256` lies in an unlabelled numeric sequence; the same sequence also occurs in the SFIRM composite.
- A P500 updater `0xB111` BE hit at `0x0000D939` is in the PE installer code before its archive overlay, not in camera firmware. A P520 updater `0xD303` LE hit at `0x0357BCC1` is in the package's compressed archive region.

The exact 32-bit scan did find **structured P500-only evidence for `0xD303` and `0xD280`**, detailed below. Other aligned/unaligned 32-bit hits in P500/P520/package bytes lacked comparable table/handler context and remain unresolved binary matches.

## 4. Code-by-code investigation

### `0x90A1`, `0x90A2`, `0x90A3` — possible operation cluster

**CONFIRMED BY PHYSICAL P510:** all three occur in `OperationsSupported`.

No local text source contains a shared definition, and no P500/P520 structure contains a table or switch with all three. A bounded scan for the three exact codes together in contiguous or fixed-stride layouts (including 2-, 4-, 8-, 12-, 16-, 24-, and 32-byte strides) found no common record. No shared handler, dispatch sequence, parameter block, or response parser was identified. Individual 16-bit hits in P500 and P520 do not form a command-family reference; examples above include ARM instruction bytes and unrelated numeric data.

**Conclusion:** contiguity is the only evidence that might suggest a family, and that is insufficient. Treat each operation as **UNKNOWN**. No Nikon name, parameter count/type, data direction, or behavior is assigned. P500/P520 association: none established.

### `0xD303` — trace of `NIKON_D303`

**Exact source:** `C:\GitHub\Tools\nikon-firmware-tools\IDA_files\D7000\105\ptp_code_names.idc`, line 421. This is a D7000-context IDA code-name helper. Its mapping is the code-shaped string `NIKON_D303`, not a semantic name. It is a lookup/label only; it does not transmit a PTP command or read/write a device property. The helper supplies no type, length, parameter/value table, UI control, or property get/set implementation. `NIKON_D303` is therefore semantically opaque; calling it a placeholder is an inference about its naming role, not an author-confirmed fact.

**New P500-only binary evidence:** the SHA-256-verified P500 `P500-NPROG-primary.bin` contains a code/pointer sequence at file offset `0x006AD594`:

| File offset | 16-bit code | Paired 32-bit target (offset-oriented Ghidra mapping) |
|---:|---:|---:|
| `0x006AD594` | `0xD407` | `0x00132F20` |
| `0x006AD59C` | `0xD303` | `0x00132F50` |
| `0x006AD5B4` | `0xD005` | `0x0013352C` |
| `0x006AD5BC` | `0xD280` | `0x0013355C` |

The D303 stub at `0x00132F50` loads literal `0xD303` from `0x001330B4`, stores it as a halfword at structure offset `+0xB0`, writes literal `2` at `+0xB2`, clears byte fields at `+0x04` and `+0x05`, clears a word at `+0x10`, then returns. The P500 D280 stub at `0x0013355C` does the analogous writes using literal `0xD280` at `0x001335A0`. These are writes to a caller-provided structure; they are **not** evidence that the actual camera property value is queried or set.

**Bounded interpretation:** paired code IDs and initializer targets, plus a nearby `0xD407` entry that local source identifies as MTP `PerceivedDeviceType`, strongly suggest a P500 property/descriptor registration structure. The table has no recovered symbolic name or proven dispatch call site, so the exact structure and whether/when it executes remain unconfirmed. The adjacent field value `2` could be a descriptor data-type selector; if it is the standard PTP DataType field, it would correspond to UINT8 and a one-byte value. That field interpretation, value length, allowed values/enumeration, current value, and read/write behavior are **not confirmed**.

**Model boundary:** P510 advertises `0xD303`; a D7000 helper labels the same number; and P500 has this property-like initializer. These establish a cross-model numeric association only. They do not establish the P510 property's meaning or behavior. No corresponding P520 structure/name was found.

### `0xD280` — P500 relationship

P510 advertises `0xD280` as a device property. The P500 table and initializer at `0x006AD5BC` / `0x0013355C` provide the same property-like registration evidence described above. No semantic name is associated with the P500 entry, and no `0xD280` source mapping was found in the D7000 helper. The D5100 address ending in `0xD280` remains unrelated.

The P500 initializer writes the code at `+0xB0` and the literal `2` at `+0xB2`; this does not establish a property meaning, P510 datatype, actual value size, enum, UI control, or read/write operation. P520 matches occur only in opaque binary material with no corresponding structure.

### `0xB111` — category and binary correlation

The independently parsed physical P510 structure places `0xB111` only in `ImageFormats`. It is not an operation, property, event, or advertised capture format. No exact local format-name entry or P500/P520 code table gives it a semantic identity. Raw byte occurrences in P500/P520 binaries and installer packages lack reliable structure and remain **UNRESOLVED BINARY MATCHES**.

It is therefore a real, directly advertised P510 image-format identifier with an **UNKNOWN** format name. It is not confirmed as JPEG, TIFF, RAW, NEF, or another Nikon format. Conversely, its absence from `CaptureFormats` or from recognized NEF tables does not prove that the imaging pipeline cannot produce RAW data; advertisement alone would not prove the stock camera can capture that format either.

## 5. Code neighborhoods and evidence matrix

The P500 table groups `0xD303` with `0xD407`, and `0xD280` with `0xD005`; the helper separately names D7000 `0xD200` and `0xD201`. These neighborhoods support inspecting the surrounding P500 descriptor-like structures, but do not imply shared feature semantics. No meaningful `0x90A1`–`0x90A3` code-family neighborhood was found. P520 high-entropy halfword matches are not a functional neighborhood.

| Code | P510 category | Advertised by P510 | Exact source/binary match | Nikon model association | Symbolic name | Semantic evidence | P500 evidence | P520 evidence | RAW relevance | Focus-peaking relevance | Clean-HDMI relevance | Confidence | Final status |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| `0x90A1` | Operation | Yes | No source definition; scattered raw-byte matches only | P510 advertisement only | None | None | No structured match | Opaque-payload matches only | Unknown | Unknown | Unknown | High for advertisement; none for meaning | **UNKNOWN** |
| `0x90A2` | Operation | Yes | No source definition; scattered raw-byte matches only | P510 advertisement only | None | None | No structured match | Opaque-payload matches only | Unknown | Unknown | Unknown | High for advertisement; none for meaning | **UNKNOWN** |
| `0x90A3` | Operation | Yes | No source definition; scattered raw-byte matches only | P510 advertisement only | None | None | No structured match | Opaque-payload matches only | Unknown | Unknown | Unknown | High for advertisement; none for meaning | **UNKNOWN** |
| `0xD280` | Device property | Yes | P500 code/pointer entry and initializer; no semantic source name | P510 and P500 code identity only | None | P500 property/descriptor-like initializer; meaning unproved | Structured P500-only partial association | No structure/name; opaque hits only | Unknown | Unknown | Unknown | Medium for P500 property-like association; none for meaning | **PARTIALLY SUPPORTED** |
| `0xD303` | Device property | Yes | D7000 code-derived helper label; P500 code/pointer entry and initializer | P510, P500; D7000 helper label | `NIKON_D303` (opaque label) | P500 property/descriptor-like initializer; no semantic meaning | Structured P500-only partial association | No structure/name; opaque hits only | Unknown | Unknown | Unknown | Medium for cross-model property-code association; low/none for meaning | **PARTIALLY SUPPORTED** |
| `0xB111` | Image format | Yes, in `ImageFormats` only | No exact semantic table name; binary matches unstructured | P510 advertisement only | None | Category confirmed; format meaning unknown | No structured format mapping | No structured mapping; opaque hits only | Directly relevant unresolved format ID; not RAW proof | No direct evidence | No direct evidence | High for category; none for meaning | **UNKNOWN** |

**No code became semantically CONFIRMED or STRONGLY SUPPORTED.** The partial statuses for D280/D303 refer only to their P500 property-like registration/cross-model code association.

### Highest-value offline follow-up by code

These are research options only; none was executed beyond the bounded correlations documented above.

| Code | Offline analysis that could discriminate meaning |
|---|---|
| `0x90A1` | Search any subsequently available Nikon PTP operation tables for this exact value; if a structured firmware table is found, trace its dispatcher/handler and parameters. Current raw hits provide no candidate handler to follow. |
| `0x90A2` | Apply the same exact-source and structured-dispatch search independently; do not infer a role from the adjacent `0x90A1`/`0x90A3` values. Current P500 instruction/data hits are not a handler reference. |
| `0x90A3` | Search for a labeled operation table or code path that uses the value as an operation identifier, then inspect its parameters and response parsing. Current numeric-sequence and instruction-byte matches are insufficient. |
| `0xD280` | In P500 only, trace references to the initializer and its table consumer to determine whether `+0xB2` is a PTP DataType field and whether descriptor values, allowed-value lists, or UI labels are linked. Search P520/reference source for a structured property registration, not a byte match. |
| `0xD303` | Separately trace the P500 initializer/table consumer and search for linked descriptor, enum, UI, or get/set handlers; check any future D7000 source beyond the code-name helper for an actual property definition. The existing label alone supplies none of these. |
| `0xB111` | Search authoritative Nikon/vendor image-format enums and structured P500/P520 file-format tables for a format registration linked to this code. Require a table/handler/format-name relationship; isolated byte matches or file extensions are not enough. |

## 6. Enhancement-goal correlation and non-PTP evidence

The classification below distinguishes evidence level from model scope. No P510 firmware image is available, so **no firmware-level implementation is confirmed for the P510**.

| Goal | PTP-relevant evidence | Firmware-level evidence | Classification | Limits and missing evidence |
|---|---|---|---|---|
| **RAW capture** | **Exists:** P510 directly advertises `0xB111` in `ImageFormats`; `CaptureFormats` is empty and `InitiateCapture (0x100E)` is absent from the capture. The meaning and usability of `0xB111` remain unknown. | **Exists only as a P500 lead:** P500 has `ERROR 3 : RAW READ ERROR!!` and `CamMemoryFormat`-related material; this is not P510 firmware evidence. | **Both** — PTP evidence is P510-specific; firmware-level lead is P500-only. | No known P510 RAW/NEF identifier, capture path, or P510 pipeline implementation. Neither the empty list nor the P500 string proves or disproves P510 RAW capture. |
| **Focus peaking** | **Not established:** P510 advertises opaque `0xD280`/`0xD303`, but no evidence connects either to focus or peaking. Generic PTP property operations and autofocus-related names are not enough. | **Exists only as P500 leads:** P500 contains focus/manual-focus descriptors and lens-task diagnostics; no focus-peaking overlay is identified. | **Firmware-level evidence exists** (P500-only leads); P510 PTP relevance and P510 firmware support are **not established**. | Need a P510 focus metric/state path and overlay/display implementation evidence. Autofocus controls do not establish focus peaking. |
| **Clean HDMI output** | **Not established:** no identified P510 HDMI, overlay, or output-routing property/operation. Opaque properties do not count as HDMI evidence. | **Exists only as a P500 lead:** P500 has `CamVideoSignalMode`; the P510 manual lists HDMI output modes but no clean/overlay-free setting. | **Firmware-level evidence exists** (P500-only lead); P510 PTP relevance and P510 firmware support are **not established**. | Need P510 output-routing/overlay-generation evidence and proof an overlay-free path exists. Video mode/resolution is not clean HDMI. |

These classifications do not imply that any feature requires a firmware modification, nor that it is impossible through another interface. They identify where evidence currently exists and where model-specific proof is missing.

## 7. Diminishing returns and recommended transition

Phase 3C PTP capability discovery has reached **diminishing returns** for these six codes:

- The P510 capability advertisement is already authoritative.
- Exhaustive local text/source correlation did not yield meanings for the three operations or `0xB111`.
- P500 offers a useful but bounded property-like association for `0xD280` and `0xD303`; it does not resolve either property's semantics.
- P520 raw matches are consistent with its opaque, near-maximum-entropy payload and do not provide useful cross-references.
- No result identifies a specific, safe physical query that would answer the remaining questions. Probing or querying the physical P510 is not recommended.

### Recommended transition out of Phase 3C

Close PTP code discovery for now; do not create a physical PTP test or probe the unknown values. Transition to an **offline P510 firmware-acquisition availability/evidence review** using already-held documentation and source material. The objective should be to identify whether authoritative P510 firmware or a documented read-only acquisition route exists, without downloading firmware/tools, installing software, executing unfamiliar code, or communicating with the camera. Any download or hardware interaction remains subject to separate explicit approval.

If actual P510 firmware is later legitimately obtained, first preserve the original and record/verify SHA-256, then investigate the P510 image-format, focus/display, and HDMI paths directly. Until then, keep all P500/P520 findings labeled as hypotheses/reference-only. This transition is a recommendation only; it was not executed.

## Final status

1. **Newly resolved codes:** none semantically resolved.
2. **Partially supported:** `0xD280` and `0xD303` have structured P500 property/descriptor-like registration evidence; meanings remain unknown. `0xD303` also has only the code-derived D7000 label `NIKON_D303`.
3. **Still UNKNOWN:** meanings of `0x90A1`, `0x90A2`, `0x90A3`, `0xD280`, `0xD303`, and `0xB111`; parameter/data schemas and behavior for all six.
4. **RAW:** P510 has an unresolved ImageFormats code `0xB111`; it is not proven RAW/NEF. No RAW capability is established or ruled out.
5. **Focus peaking:** no P510 evidence establishes a focus metric or peaking overlay. P500 focus findings are reference-only.
6. **Clean HDMI:** no P510 output/overlay control is established. HDMI resolutions and the P500 video-signal descriptor do not establish clean output.
7. **Further PTP work:** not justified at this time; stop capability discovery rather than probing the unresolved codes.
8. **Next direction:** offline review of P510 firmware availability/acquisition evidence; no download or camera action is included.
