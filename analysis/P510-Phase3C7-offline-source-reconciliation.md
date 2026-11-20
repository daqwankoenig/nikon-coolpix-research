# P510 Phase 3C-7 — Offline Source Reconciliation

**Status: COMPLETE — OFFLINE ONLY**

No P510 connection, USB attachment, hardware-client execution, PTP session, command, property query/write, event subscription, capture, or physical validation occurred. No source or firmware binary was modified. P500/P520 findings remain reference-only.

The Phase 3C-6 report specified the Phase 3C-7 objective and source topics, but did not name an output file. This report uses the project naming pattern and a filename descriptive of the prescribed offline work.

## Objective and evidence boundary

The exact Phase 3C-6 recommendation was to **continue offline source/documentation reconciliation first and not create a physical PTP test plan yet**. The requested unknowns were operations `0x90A1`–`0x90A3`, properties `0xD280` and `0xD303`, and image-format code `0xB111`; the P510 manual, existing P500 focus/video/RAW strings, and P520 reference material were to be reviewed without transferring meanings between models.

The authoritative physical-camera dataset remains the independently decoded 293-byte P510 DeviceInfo payload:

| Artifact | SHA-256 | Result |
|---|---|---|
| [P510-GetDeviceInfo.raw.bin](P510-GetDeviceInfo.raw.bin) | `E867C4FEE60CE314FC6DFF9D9A3300FA950136A279484DB13EADFE2E7C17EF96` | MATCH |
| [P510-GetDeviceInfo-decoded.txt](P510-GetDeviceInfo-decoded.txt) | `599FECA3CAA14F4BB4369CEE88791FE8ABCAC28FFDD979E3A1FCF49D332622FB` | MATCH |

It advertised operations `0x90A1`, `0x90A2`, `0x90A3`; properties `0xD280`, `0xD303`; and image format `0xB111`. `CaptureFormats` was empty. Advertised events were `0x4001`–`0x400A` and `0x400C`; none was in the Nikon `0xC101`–`0xC104` range. These are **CONFIRMED BY PHYSICAL P510** capability declarations only. The capture did not establish the unknown codes' meanings or usable behavior.

Evidence labels in this report:

- **CONFIRMED BY PHYSICAL P510** — returned by the successful GetDeviceInfo capture.
- **CONFIRMED BY PROJECT SOURCE** — an exact local source table or report contains the stated name/relationship. Model provenance is retained.
- **INFERENCE** — bounded interpretation from confirmed evidence; not a new P510 behavior fact.
- **UNKNOWN** — not established by the capture or the specifically reviewed local sources.

## Sources examined

1. P510 evidence: [Phase 3C-6 analysis](P510-Phase3C6-DeviceInfo-analysis.md), [known facts](P510-known-facts.md), [Phase 3C-5B physical report](P510-Phase3C5B-physical-GetDeviceInfo.md), [decoded DeviceInfo](P510-GetDeviceInfo-decoded.txt), and the unchanged raw payload.
2. Nikon firmware-tools source audit at commit `89ad7354b6d721260b3e999061fefc51f3580ee0`, especially the local Wireshark PTP patch at `C:\GitHub\Tools\nikon-firmware-tools\USB\wireshark\release\wireshark_usb_ptp_20130305.patch`, and D7000 code-name helper at `C:\GitHub\Tools\nikon-firmware-tools\IDA_files\D7000\105\ptp_code_names.idc`. Exact-code search covered the audited local repository text. The duplicate `wireshark_usb_ptp_20130302.patch` has the same event mappings.
3. D5100 menu-name source at `C:\GitHub\Tools\nikon-firmware-tools\IDA_files\D5100\D5100_menu_name.idc` and `D5100_menu_fix.idc`, checked to distinguish an address suffix from a PTP code.
4. [Nikon firmware-tools source audit](nikon-firmware-tools-source-audit.md), [Phase 3C-5A client design](P510-Phase3C5A-client-design.md), [Phase 3C-4 PTP transport research](P510-Phase3C4-PTP-transport-research.md), and [firmware-acquisition research](P510-firmware-acquisition-research.md).
5. [P500 string-reference analysis](P500-string-reference-analysis.md), [P520 payload analysis](P520-payload-analysis.md), and [P500/P520 comparison](P500-P520-comparison.md).
6. [P510 manual analysis](P510-disc-manual-analysis.md) and its local source PDF, `C:\GitHub\Nikon P510\reference-media\original\P510_EN.pdf`. The manual-analysis report records the pages and static findings used here.

**libgphoto2 source availability:** The existing project research pins libgphoto2 to commit `31a2f4089f19aec6caca7920b03e3eb7a251c5b6` and cites `ptp.h`, `ptp.c`, `ptp-pack.c`, and `usb.c`. No local `camlibs\ptp2\ptp.h` or libgphoto2 source checkout was present under the project or `C:\GitHub\Tools`; no source was downloaded during this phase. The local client-design and transport-research reports were consulted, but they do not supply exact mappings for the unknown codes below. Accordingly, no direct libgphoto2-source name is claimed.

## Exact-code results

Each row distinguishes P510 advertisement from source mappings and functional behavior. A source hit from a different model is not a P510 mapping.

### Vendor-range operations

| Code | Category / P510 advertisement | Exact local source cross-reference and meaning | Evidence level | P500 relationship | P520 relationship | RAW capture relevance | Focus-peaking relevance | Clean-HDMI relevance | Remaining unknowns |
|---|---|---|---|---|---|---|---|---|---|
| `0x90A1` | Operation; **advertised** | No exact token match in the audited Nikon firmware-tools source tree, including its Wireshark tables. The Wireshark table separately names Nikon `0x90C0 Capture`, `0x90C1 AfDrive`, and `0x90CA GetVendorPropCodes` (patch lines 1713–1723); these are different codes. | **CONFIRMED BY PHYSICAL P510** as advertised; meaning **UNKNOWN**. Nearby Nikon mappings are **CONFIRMED BY PROJECT SOURCE** only for those other codes. | P500 report contains MTP/PTP strings, but no operation table or `0x90A1` mapping. | P520 analysis has no PTP operation mapping. | No direct relationship established; could only be relevant if its meaning were independently identified. | No direct relationship established; `AfDrive` at `0x90C1` is not this code. | No direct relationship established. | Vendor namespace, name, parameters, effects, model scope, and P510 functional behavior. |
| `0x90A2` | Operation; **advertised** | Same exact-code search result: no match. Other Nikon `0x90xx` names in Wireshark do not identify this value. | **CONFIRMED BY PHYSICAL P510** as advertised; meaning **UNKNOWN**. | No P500 code mapping; only unrelated P500 PTP/MTP landmarks. | No P520 PTP mapping. | No direct relationship established. | No direct relationship established. | No direct relationship established. | Vendor namespace, name, parameters, effects, model scope, and P510 functional behavior. |
| `0x90A3` | Operation; **advertised** | Same exact-code search result: no match. No name is assigned by numeric proximity to other Nikon operations. | **CONFIRMED BY PHYSICAL P510** as advertised; meaning **UNKNOWN**. | No P500 code mapping; only unrelated P500 PTP/MTP landmarks. | No P520 PTP mapping. | No direct relationship established. | No direct relationship established. | No direct relationship established. | Vendor namespace, name, parameters, effects, model scope, and P510 functional behavior. |

The P510-reported vendor-extension description contains “Nikon PTP Extensions”, but that description alone does not map any of `0x90A1`–`0x90A3` to a Nikon operation. The source's named Nikon operations are useful comparison points only; they are not aliases or evidence of equivalent behavior.

### Device properties

| Code | Category / P510 advertisement | Exact local source cross-reference and meaning | Evidence level | P500 relationship | P520 relationship | RAW capture relevance | Focus-peaking relevance | Clean-HDMI relevance | Remaining unknowns |
|---|---|---|---|---|---|---|---|---|---|
| `0xD280` | Device property; **advertised** | No exact PTP property definition was found in the audited source tree or reviewed project reports. A D5100 menu script contains address `0x8F9CD280` associated with `MN_Perspectivecontrol_1`; that is a D5100 memory/menu-name address, **not** a PTP property-code mapping. | **CONFIRMED BY PHYSICAL P510** as advertised; P510 meaning **UNKNOWN**. The D5100 address is **CONFIRMED BY PROJECT SOURCE** but unrelated. | No P500 property-code mapping. Focus/video strings in the P500 report do not name this property. | No P520 PTP property mapping. | Unknown; no evidence links it to image format or RAW. | Unknown; no evidence links it to focus state or peaking. | Unknown; no evidence links it to display or HDMI. | Name, type, value/range, writeability, model scope, and functional effect. |
| `0xD303` | Device property; **advertised** | The D7000 helper `IDA_files\D7000\105\ptp_code_names.idc`, line 421, maps the numeric code to the literal label `NIKON_D303`. It supplies no semantic name or behavior. No exact P510/P500/P520 mapping was found. | **CONFIRMED BY PROJECT SOURCE** as a D7000 helper label; **LIKELY NIKON** as a code-family clue only. P510 property meaning and functionality remain **UNKNOWN**. | P500 focus and video descriptor strings do not map `0xD303`. | No P520 PTP property mapping. | Unknown; no RAW relationship established. | A possible research lead only; no focus meaning established. | No HDMI/display meaning established. | Semantic meaning, whether the D7000 label corresponds to this P510 property, property descriptor/value, writeability, and behavior. |

An advertised property is not evidence that it is readable, writable, or effective in any camera mode. Standard `FocusMode (0x500A)` is not in the captured P510 property list; that absence does not prove the camera has no focus controls by other means.

### Image format

| Code | Category / P510 advertisement | Exact local source cross-reference and meaning | Evidence level | P500 relationship | P520 relationship | RAW capture relevance | Focus-peaking relevance | Clean-HDMI relevance | Remaining unknowns |
|---|---|---|---|---|---|---|---|---|---|
| `0xB111` | Image-format code; **advertised** | No exact token match in the audited Wireshark source tree or reviewed project research. The same Wireshark format table explicitly names `0x3801 EXIF_JPEG`, `0x3008 WAV`, and `0x300D MOV` (patch lines 1867–1874), but has no `0xB111` entry. No direct local libgphoto2 source mapping was available. | **CONFIRMED BY PHYSICAL P510** as an ImageFormats entry; format/vendor meaning **UNKNOWN**. | `P500-string-reference-analysis.md` records `ERROR 3 : RAW READ ERROR!!` and P500 `CamMemoryFormat`/image-related strings. They are P500 firmware evidence, not a PTP mapping for `0xB111` and not proof of P510 RAW capture. | P520 payload analysis found no PTP format mapping; its opaque payload does not resolve `0xB111`. | Directly relevant as an unresolved advertised image format, but not confirmed as RAW/NEF. Empty `CaptureFormats` and absence of a recognized NEF code do not prove the imaging pipeline cannot produce RAW. | No direct relation established. | No direct relation established. | Actual format, vendor assignment, whether any object can use it, and whether the stock camera can capture or emit it. |

The remaining captured image formats have project-table names: `0x3801 EXIF_JPEG`, `0x3001 Association`, `0x3006 DPOF`, `0x3008 WAV`, `0x300D MOV`, and `0x3000 Undefined`. `CaptureFormats` is empty. These declarations do not prove the camera actually creates objects in each format.

### Events: Nikon cross-references that are not P510-advertised

The Wireshark patch's Nikon-flavor event rows (lines 1520–1526) give exact names for these codes. All are **not advertised** in the P510 DeviceInfo event array, so these rows are negative cross-references, not P510 capabilities.

| Code | Category / P510 advertisement | Exact local source cross-reference and meaning | Evidence level | P500 relationship | P520 relationship | RAW capture relevance | Focus-peaking relevance | Clean-HDMI relevance | Remaining unknowns |
|---|---|---|---|---|---|---|---|---|---|
| `0xC101` | Nikon event; **not advertised** | Wireshark Nikon flavor: `ObjectAddedInSDRAM` (patch line 1520). | **CONFIRMED BY PROJECT SOURCE** as a Nikon-flavor table label; not a P510 event fact. | No P500 event-code mapping in the string-reference report. | No P520 event mapping. | The label suggests an object-added notification in that source's context; no P510 support or RAW link. | No link established. | No link established. | Exact protocol semantics, model scope, and P510 support/functionality. |
| `0xC102` | Nikon event; **not advertised** | Wireshark Nikon flavor: `CaptureCompleteRecInSdram` (patch line 1522). | **CONFIRMED BY PROJECT SOURCE** as a Nikon-flavor table label; not a P510 event fact. | No P500 event-code mapping. | No P520 event mapping. | Capture-related label in another Nikon source; no P510 support or RAW link. | No link established. | No link established. | Exact semantics, model scope, and P510 support/functionality. |
| `0xC103` | Nikon event; **not advertised** | Wireshark Nikon flavor: `AdvancedTransfer` (patch line 1524). | **CONFIRMED BY PROJECT SOURCE** as a Nikon-flavor table label; not a P510 event fact. | No P500 event-code mapping. | No P520 event mapping. | Transfer label only; no P510/RAW behavior established. | No link established. | No link established. | Exact semantics, model scope, and P510 support/functionality. |
| `0xC104` | Nikon event; **not advertised** | Wireshark Nikon flavor: `PreviewImageAdded` (patch line 1526). | **CONFIRMED BY PROJECT SOURCE** as a Nikon-flavor table label; not a P510 event fact. | No P500 event-code mapping. | No P520 event mapping. | Preview-image label only; no P510/RAW behavior established. | No link established. | No link established. | Exact semantics, model scope, and P510 support/functionality. |

All eleven events actually advertised by the P510 map to standard PTP event names in the reviewed Wireshark table: `0x4001 CancelTransaction`, `0x4002 ObjectAdded`, `0x4003 ObjectRemoved`, `0x4004 StoreAdded`, `0x4005 StoreRemoved`, `0x4006 DevicePropChanged`, `0x4007 ObjectInfoChanged`, `0x4008 DeviceInfoChanged`, `0x4009 RequestObjectTransfer`, `0x400A StoreFull`, and `0x400C StorageInfoChanged`. `0x400D CaptureComplete` is not advertised. No event was subscribed to or awaited. These standard event advertisements do not establish capture, focus, or display behavior.

## P500/P520 context and P510 manual findings

### P500 — reference only

The P500 Phase 2D-4 report confirms exact strings and descriptor-offset entries for `CamFocusMode`, `CamManualFocus`, and `CamVideoSignalMode`. It also records lens/focus-task diagnostics and `ERROR 3 : RAW READ ERROR!!`. The report explicitly says the focus/video setting strings were not connected to coherent ARM code and the RAW-read helper's exact semantics are unknown. No P500 PTP operation/property/event table maps any of the Phase 3C-7 codes. These strings are useful static-analysis leads, not P510 properties or proof of focus peaking, clean HDMI, or RAW capture.

### P520 — reference only

The P520 payload report describes a model/version prefix followed by an opaque, very-high-entropy region. The package-comparison report records packaging similarities and model-specific differences, but neither report contains PTP operation/property/event/format mappings for the codes investigated here. Nothing in that material identifies P510 behavior or establishes compatibility.

### P510 manual

The local manual analysis records supported HDMI output selections of Auto, 480p, 720p, and 1080i, and lists still/movie-related filename extensions including `.JPG`, `.MOV`, `.WAV`, and `.MPO`. It does not establish a clean/overlay-free HDMI mode, a focus-peaking mode, or a RAW/NEF capture mode. These manual findings do not turn an advertised PTP code into a usable control; absence from the examined manual material is not proof a feature is impossible.

## Findings by enhancement goal

### RAW capture

- **Confirmed by physical P510:** `0xB111` appears in `ImageFormats`; `CaptureFormats` is empty; the captured operation list omits standard `InitiateCapture (0x100E)`.
- **Confirmed by project source:** the reviewed Wireshark table names the ordinary JPEG/WAV/MOV entries but not `0xB111`; P500 has a RAW-read diagnostic string only in its own firmware.
- **Inference:** the advertised dataset does not identify a P510 RAW/NEF format or PTP capture path.
- **Unknown:** what `0xB111` denotes; whether RAW/NEF is produced through another camera path; whether an image-format advertisement means the format is usable for capture.
- **Implication:** no RAW capability is established, but the absence of a recognized RAW code does not prove that the imaging pipeline cannot produce RAW data.

### Focus peaking

- **Confirmed by physical P510:** `0xD280` and `0xD303` are advertised properties; standard `FocusMode (0x500A)` is absent from the returned property list.
- **Confirmed by project source:** a D7000 helper labels `0xD303` as `NIKON_D303` without semantics; P500 has focus-related strings and diagnostics.
- **Inference:** P510 DeviceInfo alone exposes no identified focus metric, peaking overlay, or direct focus property.
- **Unknown:** meanings/values of the two P510 properties, access to a P510 focus metric, and any image-overlay path.
- **Implication:** no evidence that P510 supports focus peaking or a PTP route to implement it. P500 strings remain model-specific leads.

### Clean HDMI output

- **Confirmed by physical P510:** the capture advertises the same opaque properties and generic events; no HDMI-specific PTP property or live-view operation was identified.
- **Confirmed by project source/manual:** the manual lists HDMI resolutions/modes; P500 has a `CamVideoSignalMode` descriptor string, with no transfer of semantics to P510.
- **Inference:** the current evidence identifies selectable HDMI modes, not whether overlays can be removed or controlled.
- **Unknown:** P510 HDMI pipeline, overlay generation, and any corresponding P510 firmware setting/property.
- **Implication:** neither clean HDMI nor an HDMI-control code is established. The manual's resolution options do not prove a clean output mode.

## Updated evidence classification

- **CONFIRMED BY PHYSICAL P510:** the capture returned the listed code arrays, `CaptureFormats` empty, model `P510`, and the documented DeviceInfo fields. No Phase 3C-7 functional behavior was physically validated.
- **CONFIRMED BY PROJECT SOURCE:** the exact source labels described above, including the Wireshark Nikon event labels, separate `0x90C0`/`0x90C1`/`0x90CA` operation names, D7000 helper label `NIKON_D303`, P500-only firmware strings, and manual-listed HDMI modes.
- **INFERENCE:** unknown advertised values may be relevant research targets only after their meanings are established. Numeric proximity, a model-family label, or a related string does not establish P510 semantics.
- **UNKNOWN:** names/semantics and functionality of `0x90A1`–`0x90A3`, `0xD280`, `0xD303`, and `0xB111`; all corresponding camera behavior; and whether P510 can produce RAW, offer focus peaking, or provide clean HDMI.

## Recommended Phase 3C-8

**Remain offline. No accumulated evidence demonstrates a specific need for another physical-camera query.**

1. Continue searching only already-held or independently authorized offline P510 documentation/source material for model-specific definitions; preserve exact code and model provenance.
2. Keep P500/P520 comparisons separately labelled and do not use their firmware or code tables as P510 behavior evidence.
3. If an authoritative P510 firmware image is later obtained, preserve and hash it before static analysis, then use it to investigate the relevant format, focus/display, and HDMI paths.
4. Reconsider a physical query only if a concrete question cannot be resolved offline and a narrowly scoped, safe query can answer it. Any such interaction would require separate explicit authorization. Do not query or set any property, invoke an unknown operation, or test an event as part of this recommendation.

Phase 3C-8 is recommended only and was not executed.
