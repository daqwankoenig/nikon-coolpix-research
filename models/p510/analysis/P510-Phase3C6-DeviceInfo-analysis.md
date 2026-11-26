# P510 Phase 3C-6: Offline DeviceInfo Analysis

**Status: COMPLETE — OFFLINE ANALYSIS ONLY**

No P510 connection, USB attachment, hardware-client execution, PTP operation, PTP session, event subscription, or camera test was performed during this phase. Advertised operations below are capability declarations only; none was executed.

## Evidence classes

- **CONFIRMED BY PHYSICAL P510** means directly returned by the P510's successful Phase 3C-5B `GetDeviceInfo` response, or recorded physical transport identity from that same controlled run.
- **CONFIRMED BY PROJECT SOURCE** means code names or relationships are present in already-reviewed local source/research. A mapping from a different camera does not establish P510 support or semantics.
- **INFERENCE** means a constrained interpretation of confirmed fields; it is not a new camera fact.
- **UNKNOWN** means the capture and existing reviewed sources do not establish the claim.

## 1. Capture integrity

The capture artifacts match the final SHA-256 values recorded in [P510-Phase3C5B-physical-GetDeviceInfo.md](P510-Phase3C5B-physical-GetDeviceInfo.md). The raw payload hash matched, so analysis continued.

| Artifact | SHA-256 | Check |
|---|---|---|
| [P510-GetDeviceInfo.raw.bin](P510-GetDeviceInfo.raw.bin) | `E867C4FEE60CE314FC6DFF9D9A3300FA950136A279484DB13EADFE2E7C17EF96` | MATCH |
| [P510-GetDeviceInfo-decoded.txt](P510-GetDeviceInfo-decoded.txt) | `599FECA3CAA14F4BB4369CEE88791FE8ABCAC28FFDD979E3A1FCF49D332622FB` | MATCH |
| [P510-GetDeviceInfo-transport.log](P510-GetDeviceInfo-transport.log) | `149A647852B5E5A2D9B10B2292FEE603D76093FF130F3DFDB68D47C065AB4A7F` | MATCH |

## 2. Independent raw decode

The raw bytes were parsed independently from the existing decoded text using the PTP DeviceInfo field order and little-endian integer/string decoding. The 293-byte payload was consumed through offset 293, with **zero trailing bytes**.

| Field | Independent decode |
|---|---|
| `StandardVersion` | `0x0064` |
| `VendorExtensionID` | `0x00000006` |
| `VendorExtensionVersion` | `0x0064` |
| `VendorExtensionDesc` | `microsoft.com: 1.0; Nikon PTP Extensions` |
| `FunctionalMode` | `0x0000` |
| `OperationsSupported` (26, device order) | `0x1001 0x1002 0x1003 0x1004 0x1005 0x1006 0x1007 0x1008 0x1009 0x100A 0x100C 0x100D 0x101B 0x100B 0x100F 0x1023 0x1014 0x1015 0x1016 0x9801 0x9802 0x9803 0x9805 0x90A1 0x90A2 0x90A3` |
| `EventsSupported` (11, device order) | `0x4001 0x4002 0x4003 0x4004 0x4005 0x4006 0x4007 0x4008 0x4009 0x400A 0x400C` |
| `DevicePropertiesSupported` (6, device order) | `0x5001 0x5011 0xD280 0xD303 0xD406 0xD407` |
| `CaptureFormats` | Empty |
| `ImageFormats` (7, device order) | `0x3801 0x3001 0x3006 0x3008 0x300D 0xB111 0x3000` |
| `Manufacturer` | `Nikon Corporation` |
| `Model` | `P510` |
| `DeviceVersion` | `V1.00` |
| `SerialNumber` | Present; redacted from this report and decoded-text artifact |

**Comparison:** Every independently decoded value, array length, array order, and code listed above matches [P510-GetDeviceInfo-decoded.txt](P510-GetDeviceInfo-decoded.txt). No discrepancy was found. The serial string is present in the raw payload; its content is intentionally not repeated here.

## 3. OperationsSupported

The P510 advertised 26 operation codes. Names below are taken from the project’s pinned libgphoto2 research and/or the audited Nikon Wireshark operation table. Code classification does not establish that an operation is safe, usable in the current camera mode, or appropriate to execute.

**Status legend:** `CONFIRMED STANDARD`, `CONFIRMED NIKON`, `LIKELY NIKON`, `UNKNOWN`. MTP-defined operations are marked as standard MTP extensions. “Nikon-specific name” is shown only when the reviewed sources provide an exact mapping.

| Code | Protocol classification / authoritative name | Nikon-specific name | Relevance to P510 research | Status / evidence |
|---|---|---|---|---|
| `0x1001` | Standard PTP — `GetDeviceInfo` | None | Direct identification and capability advertisement; this was the sole transmitted operation in Phase 3C-5B. | **CONFIRMED STANDARD** — capture; PTP definitions in Phase 3C-5A client-design research. |
| `0x1002` | Standard PTP — `OpenSession` | None | Session lifecycle only; advertised but not sent in Phase 3C-5B. | **CONFIRMED STANDARD** — PTP definitions in Phase 3C-5A client-design research. |
| `0x1003` | Standard PTP — `CloseSession` | None | Session lifecycle only; no PTP session was opened. | **CONFIRMED STANDARD** — PTP definitions in Phase 3C-5A client-design research. |
| `0x1004` | Standard PTP — `GetStorageIDs` | None | Lists exposed media stores; does not identify internal firmware memory. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x1005` | Standard PTP — `GetStorageInfo` | None | Describes exposed media storage, not internal firmware. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x1006` | Standard PTP — `GetNumObjects` | None | Counts exposed objects; not firmware-memory access. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x1007` | Standard PTP — `GetObjectHandles` | None | Enumerates exposed media objects; could describe files, not a firmware dump mechanism. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x1008` | Standard PTP — `GetObjectInfo` | None | Describes an exposed object; no direct capture-control meaning. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x1009` | Standard PTP — `GetObject` | None | Retrieves an exposed object; does not by itself cause capture or establish that a RAW object exists. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x100A` | Standard PTP — `GetThumb` | None | Retrieves a thumbnail for an exposed object; not RAW capture. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x100C` | Standard PTP — `SendObjectInfo` | None | Host-to-camera object-transfer operation; not read-only. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x100D` | Standard PTP — `SendObject` | None | Host-to-camera object transfer; not read-only. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x101B` | Standard PTP — `GetPartialObject` | None | Reads a range of an exposed object only; not arbitrary firmware-address access. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x100B` | Standard PTP — `DeleteObject` | None | Destructive media-object operation; advertisement is not authorization or evidence of safe use. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x100F` | Standard PTP — `FormatStore` | None | Potentially destructive storage operation; advertisement is not authorization or evidence of safe use. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x1023` | Standard PTP — `GetFilesystemManifest` | None | Filesystem metadata, if implemented; no evidence it exposes internal firmware. | **CONFIRMED STANDARD** — audited Wireshark PTP table. |
| `0x1014` | Standard PTP — `GetDevicePropDesc` | None | Relevant to determining a reported property's type/range/enumeration; not executed. | **CONFIRMED STANDARD** — Wireshark and Phase 3C-4 research. |
| `0x1015` | Standard PTP — `GetDevicePropValue` | None | Relevant to reading a reported property value; not executed. | **CONFIRMED STANDARD** — Wireshark and Phase 3C-4 research. |
| `0x1016` | Standard PTP — `SetDevicePropValue` | None | Property write operation; its advertisement does not prove any listed property is writable. Not executed. | **CONFIRMED STANDARD** — Wireshark PTP table. |
| `0x9801` | MTP extension — `GetObjectPropsSupported` | None | Object-property metadata, not Nikon camera-control properties. | **CONFIRMED STANDARD (MTP)** — Wireshark MTP operation table. |
| `0x9802` | MTP extension — `GetObjectPropDesc` | None | Describes an object property; not a Nikon-specific P510 name. | **CONFIRMED STANDARD (MTP)** — Wireshark MTP operation table. |
| `0x9803` | MTP extension — `GetObjectPropValue` | None | Reads an object property; not itself capture configuration. | **CONFIRMED STANDARD (MTP)** — Wireshark MTP operation table. |
| `0x9805` | MTP extension — `GetObjPropList` | None | Reads a list of object properties; object metadata, not proof of device-control capability. | **CONFIRMED STANDARD (MTP)** — Wireshark MTP operation table. |
| `0x90A1` | Vendor-extension code range; exact vendor/name not mapped | None supported | Potentially relevant only as an unresolved vendor operation. | **UNKNOWN** — no exact code mapping found in the reviewed Wireshark table, pinned libgphoto2 research summary, Nikon source audit, or P500/P520 reports. |
| `0x90A2` | Vendor-extension code range; exact vendor/name not mapped | None supported | Potentially relevant only as an unresolved vendor operation. | **UNKNOWN** — same evidence boundary as `0x90A1`. |
| `0x90A3` | Vendor-extension code range; exact vendor/name not mapped | None supported | Potentially relevant only as an unresolved vendor operation. | **UNKNOWN** — same evidence boundary as `0x90A1`. |

### Operation-level conclusions

- `InitiateCapture (0x100E)` is **not** in the P510's advertised operation list. This means it was not advertised in this DeviceInfo response; it does not prove the camera can never capture through another path.
- `GetDevicePropDesc`, `GetDevicePropValue`, and `SetDevicePropValue` are advertised. This does not reveal the values/descriptors of any property, establish that a particular property is writable, or prove that a control is usable.
- The list includes potentially state-changing/destructive standard operations (`SendObjectInfo`, `SendObject`, `DeleteObject`, `FormatStore`, `SetDevicePropValue`). They were not sent. The one authorized `0x1001` transaction completed; no further command is authorized by this report.
- The Nikon Wireshark table names other Nikon operations, including `0x90C0 Capture`, `0x90C1 AfDrive`, and `0x90CA GetVendorPropCodes`. These are **not** among the P510-advertised values. Their existence does not identify `0x90A1`–`0x90A3` or establish P510 support.

## 4. DevicePropertiesSupported

DeviceInfo advertises property identifiers, not their current values, descriptions, ranges, or whether the camera allows setting them. No property query or write occurred.

| Code | Source mapping / classification | Status | Enhancement relevance and limits |
|---|---|---|---|
| `0x5001` | Standard PTP `BatteryLevel` | **CONFIRMED STANDARD** — Wireshark standard device-property table. | No direct relevance to RAW capture, focus peaking, or HDMI. |
| `0x5011` | Standard PTP `DateTime` | **CONFIRMED STANDARD** — Wireshark standard device-property table. | No direct relevance to the three enhancement goals. |
| `0xD280` | No exact mapping found in reviewed local sources | **UNKNOWN** | Could only be evaluated as an opaque advertised property. No feature or control meaning can be inferred from its value. |
| `0xD303` | Nikon D7000 IDA helper labels this code `NIKON_D303`, without a semantic name | **LIKELY NIKON** for the neighboring D7000 source only; P510 meaning remains **UNKNOWN**. | A cross-model code identity clue, not evidence it represents focus, capture, HDMI, or any P510 feature. |
| `0xD406` | MTP `SessionInitiatorInfo` | **CONFIRMED STANDARD (MTP)** — Wireshark MTP property table. | Session metadata; no direct image, exposure, focus, live-view, or display control implication. |
| `0xD407` | MTP `PerceivedDeviceType` | **CONFIRMED STANDARD (MTP)** — Wireshark MTP property table. | Device classification metadata; no direct enhancement-goal implication. |

The standard identifiers commonly associated with image size (`0x5003`), compression (`0x5004`), white balance (`0x5005`), aperture (`0x5007`), focus distance/mode (`0x5009`/`0x500A`), exposure time/index/bias (`0x500D`/`0x500F`/`0x5010`), and still-capture mode (`0x5013`) are **not present** in this advertised list. Their absence is a fact about this response's list, not proof those functions are absent from camera firmware or inaccessible through all interfaces.

### Advertised versus proven usable

**Advertised:** six property IDs in DeviceInfo, plus the standard operations needed to request descriptions/values and set a device property.

**Proven usable:** no property query, descriptor retrieval, value read, or set operation was performed in this phase. Therefore no listed property is proven readable or settable by this analysis; no enhancement capability is established.

## 5. EventsSupported

All eleven advertised events map to standard PTP events in the project's Wireshark table. No Nikon vendor event was advertised in this list.

| Code | Event name | Status | Possible relevance (advertisement only) |
|---|---|---|---|
| `0x4001` | `CancelTransaction` | **CONFIRMED STANDARD** | Transaction control; no enhancement-specific inference. |
| `0x4002` | `ObjectAdded` | **CONFIRMED STANDARD** | Could notify about a newly exposed object; does not establish capture support or RAW content. |
| `0x4003` | `ObjectRemoved` | **CONFIRMED STANDARD** | Object-state notification only. |
| `0x4004` | `StoreAdded` | **CONFIRMED STANDARD** | Storage-state notification only. |
| `0x4005` | `StoreRemoved` | **CONFIRMED STANDARD** | Storage-state notification only. |
| `0x4006` | `DevicePropChanged` | **CONFIRMED STANDARD** | Generic property-change notification; not focus-, exposure-, or HDMI-specific. |
| `0x4007` | `ObjectInfoChanged` | **CONFIRMED STANDARD** | Generic object metadata notification. |
| `0x4008` | `DeviceInfoChanged` | **CONFIRMED STANDARD** | Generic DeviceInfo-change notification. |
| `0x4009` | `RequestObjectTransfer` | **CONFIRMED STANDARD** | Object-transfer request; not an image-capture command. |
| `0x400A` | `StoreFull` | **CONFIRMED STANDARD** | Storage-state notification. |
| `0x400C` | `StorageInfoChanged` | **CONFIRMED STANDARD** | Storage-state notification. |

`CaptureComplete (0x400D)` is not advertised. Nikon event examples in the Wireshark table (`0xC101`–`0xC104`) are also absent. No event was subscribed to, awaited, or executed. The event list does not prove that these notifications are actually emitted in a particular mode.

## 6. Format analysis

### CaptureFormats

`CaptureFormats` is **empty** in the captured DeviceInfo dataset. Thus the response advertises no capture-format codes in that field.

### ImageFormats

| Code | Existing source mapping | Interpretation |
|---|---|---|
| `0x3801` | Standard PTP `EXIF_JPEG` | JPEG is advertised in `ImageFormats`; this alone does not prove stock capture behavior or a particular quality setting. |
| `0x3001` | Standard PTP `Association` | A container/directory-style object format, not a RAW image format. |
| `0x3006` | Standard PTP `DPOF` | Print-order format, not a RAW image format. |
| `0x3008` | Standard PTP `WAV` | Audio format; no camera capture conclusion. |
| `0x300D` | Standard PTP `MOV` | QuickTime/MOV object format; advertisement alone does not prove a specific video mode. |
| `0xB111` | No exact mapping in the reviewed Wireshark table or project research | **UNKNOWN**; do not label it NEF, RAW, or Nikon-specific without further evidence. |
| `0x3000` | Standard PTP `Undefined` | Undefined format; it cannot be identified as RAW from this code alone. |

The returned list contains no recognized TIFF (`0x3802`/`0x380D`), DNG (`0x3811`), or named Nikon NEF code in the reviewed local format table. `0xB111` remains unresolved. It may be a vendor-specific code, but the vendor and format meaning are not established here.

**RAW/NEF boundary:** absence of a known RAW/NEF code from this advertised list does **not** prove the imaging pipeline cannot produce RAW data. Conversely, if a future mapping identified `0xB111` as RAW/NEF, that would still not prove the stock P510 can capture that format in its current configuration. Capability advertisement, object-format support, capture initiation, and actual usable RAW capture are separate questions.

## 7. Vendor extension

| Field | P510-reported value | What existing source establishes |
|---|---|---|
| `VendorExtensionID` | `0x00000006` | The audited Wireshark table identifies ID `0x00000006` as MTP/Microsoft. |
| `VendorExtensionVersion` | `0x0064` | Raw reported value; no separate semantic mapping is asserted here. |
| `VendorExtensionDesc` | `microsoft.com: 1.0; Nikon PTP Extensions` | Exact P510-reported description string. It explicitly contains both the Microsoft MTP label and Nikon PTP Extensions text. |

**CONFIRMED BY PHYSICAL P510:** the fields above were returned in the successful DeviceInfo data container.

**CONFIRMED BY PROJECT SOURCE:** the local Wireshark table treats `0x00000006` as the MTP/Microsoft extension ID; the existing Phase 3C-4 research records Nikon's libgphoto2 vendor ID as `0x0000000A` for other Nikon PTP definitions.

**Interpretation boundary:** the P510's returned ID is `0x00000006`, not `0x0000000A`. The description text indicates a Nikon extension label within the reported MTP/Microsoft extension context, but does not establish that every Nikon operation/property in another Nikon model applies to P510. The exact meanings of `0x90A1`–`0x90A3` remain unknown.

## 8. DeviceVersion versus firmware and USB revision

Three distinct observations must remain separate:

1. **PTP `DeviceVersion`:** `V1.00`, directly returned by the P510.
2. **Camera Firmware version menu:** `1.0`, directly observed by the owner and recorded in [P510-physical-camera-observations.md](P510-physical-camera-observations.md).
3. **USB `bcdDevice` / Windows `REV_0100`:** `0x0100`, observed in the USB descriptor/PnP records.

The text `V1.00` is numerically consistent with the menu's `1.0`, but no evidence establishes that this PTP string is the camera's installed firmware version field. USB `bcdDevice` is a USB descriptor revision value and is not, without further evidence, the firmware version. These are separate fields; semantic equivalence is **UNKNOWN**.

## 9. Reverse-engineering priorities by enhancement goal

The ordering below ranks evidence/research relevance only. It does **not** rank feasibility, safety of untested commands, or likelihood of success.

### Goal 1 — RAW capture

1. **Highest direct relevance: format and capture advertisement.** `ImageFormats` includes EXIF/JPEG (`0x3801`) and unknown `0xB111`; `CaptureFormats` is empty. Standard `InitiateCapture (0x100E)` is absent from `OperationsSupported`.
2. **Related but limited: object and property operations.** `GetObject` (`0x1009`), `GetPartialObject` (`0x101B`), and property description/value operations (`0x1014`/`0x1015`) are advertised. Object reads could concern already exposed media objects; they are not capture initiation or arbitrary firmware access. No RAW-specific property is identified.
3. **Events:** `ObjectAdded` (`0x4002`) and `DevicePropChanged` (`0x4006`) are generic; `CaptureComplete` (`0x400D`) is absent. No event was used.
4. **Neighbor-model context:** P500 static analysis found a `RAW READ ERROR` string; that is P500-only firmware evidence and does not establish P510 RAW capture. P520 payload analysis is opaque and supplies no P510 PTP/RAW mapping.
5. **Missing evidence:** meaning of `0xB111`; P510 image pipeline/output formats; whether a usable RAW object is ever produced; whether the empty `CaptureFormats` field reflects mode or implementation.
6. **Safest next offline work:** inspect only existing P510 documentation for still-image/RAW support; compare the exact `0xB111` value against already-held PTP format tables and provenance; keep P500/P520 observations explicitly separate.

### Goal 2 — Focus peaking

1. **Highest direct relevance: unknown property IDs.** `0xD280` and `0xD303` are unresolved for P510. Standard `FocusMode (0x500A)` is not in the advertised property list.
2. **Related operations/events:** generic `GetDevicePropDesc`/`GetDevicePropValue` operations are advertised, as is `DevicePropChanged (0x4006)`; none establishes a focus metric, focus-state stream, or peaking overlay.
3. **Neighbor-model context:** P500 static analysis found `CamFocusMode`, `CamManualFocus`, and coherent lens/focus-task diagnostics. These are P500-only references. P520 analysis did not reveal a focus/PTP table.
4. **Missing evidence:** P510 focus metric/state access, video-frame path, display overlay hooks, and meanings of D280/D303.
5. **Safest next offline work:** map the P500 focus-related references already documented and compare naming/structure only as a hypothesis; examine existing P510 manual material for focus and display features. Do not query or set any property.

### Goal 3 — Clean HDMI output

1. **Highest direct relevance in existing P510 material:** the P510 manual documents HDMI output modes Auto, 480p, 720p, and 1080i. DeviceInfo advertises no identified HDMI/display property.
2. **Related PTP evidence:** `DevicePropChanged` (`0x4006`) is generic. The only opaque P510 property codes are D280/D303 plus MTP session/device metadata D406/D407; none is identified as HDMI control. `InitiateCapture (0x100E)` and standard live-view controls are not advertised.
3. **Neighbor-model context:** P500 static analysis found the descriptor string `CamVideoSignalMode`; it is not a P510 mapping and does not establish clean HDMI behavior.
4. **Missing evidence:** P510's HDMI processing path, overlay generation, mode selection implementation, and any P510 firmware/settings representation.
5. **Safest next offline work:** review the already inventoried P510 manual sections describing HDMI output and on-screen display behavior; treat P500 `CamVideoSignalMode` only as a research lead. No PTP operation is justified by this advertisement alone.

## 10. High-value unknown-code shortlist

No code in this list is to be tested. “Cross-reference” means only a lead in existing source; it does not establish P510 meaning.

| Code(s) | Dataset type | Existing cross-reference | Current status | Offline work that could reduce uncertainty |
|---|---|---|---|---|
| `0x90A1`, `0x90A2`, `0x90A3` | Operations | The Wireshark table names other Nikon operations in the `0x90xx` area, e.g. `0x90C0 Capture`, `0x90C1 AfDrive`, and `0x90CA GetVendorPropCodes`; the Nikon source audit documents distinct Nikon operations on other bodies. No exact mapping for these three codes was found. | **UNKNOWN** | Search only the already pinned/local Nikon operation tables, existing P500/P520 research, and audited source snapshots for exact values; inspect any exact hit's model provenance before considering semantics. |
| `0xD303` | Device property | The Nikon D7000 IDA naming helper labels the code `NIKON_D303`, but gives no semantic name. The source is D7000-specific and no P510 match was found. | **LIKELY NIKON** as a code-family clue; P510 meaning **UNKNOWN** | Review surrounding D7000 code-name/property-table context already in the source snapshot; compare exact code provenance against any existing P500 tables. Do not transfer a D7000 meaning to P510. |
| `0xD280` | Device property | No exact mapping was found in the reviewed Wireshark, Nikon-tooling, P500, or P520 material. It is included because it is an opaque property advertised by the P510 and could be relevant to an enhancement only after its meaning is established. | **UNKNOWN** | Recheck exact-code occurrence in existing project-held text/source inventories and record a bounded no-hit if none exists. Avoid semantic guesses based on the numeric value. |
| `0xB111` | Image format | Wireshark's format table lists standard image formats and several vendor formats but has no `0xB111` mapping. P500 firmware research has RAW-related strings, but no PTP `0xB111` mapping; P520 provides no PTP mapping. | **UNKNOWN** | Compare only existing PTP format-code tables and local source snapshots for the exact value; keep the RAW/NEF interpretation unknown unless an exact, provenance-qualified mapping is found. |
| Nikon event codes `0xC101`–`0xC104` | Events (not advertised) | Wireshark maps these to Nikon event names for Nikon PTP implementations; none appears in the P510 `EventsSupported` array. | Not a P510-advertised unknown; included as a **negative cross-reference** only. | Offline compare code provenance and other Nikon model scopes if needed; do not infer P510 event support or subscribe to any event. |

All P510-advertised event IDs map to standard PTP events in the reviewed table; therefore there is no unknown advertised Nikon event code to shortlist. MTP operation codes `0x9801`, `0x9802`, `0x9803`, and `0x9805`, and MTP properties `0xD406`/`0xD407`, have source mappings and are not treated as unknown Nikon commands.

## 11. Recommended Phase 3C-7

**Recommendation: continue offline source/documentation reconciliation first. Do not create a physical PTP test plan yet.**

1. Reconcile exact unknown codes `0x90A1`–`0x90A3`, `0xD280`, `0xD303`, and `0xB111` against only the already-held Wireshark/libgphoto2/Nikon-tooling source snapshots, recording model provenance and no-hit results.
2. Review the existing P510 manual for what it establishes about HDMI modes, image formats, and focus/display behavior; keep manual claims separate from PTP advertisement.
3. Map P500 focus/video/RAW strings to their precise P500-only evidence and determine whether any offline comparison is informative without asserting P510 compatibility. P520 material remains reference-only.
4. Reassess the missing P510 evidence: no advertised capture-initiate operation, empty `CaptureFormats`, unresolved `0xB111`, and no known focus/HDMI-specific property. Do not issue a property query or any other PTP command as part of this recommendation.
5. Continue official P510 firmware-acquisition research as a separate offline thread; the DeviceInfo response is not a firmware image or memory-read capability.

Phase 3C-7 is **recommended only** and was not executed. No additional physical camera test is proposed or authorized by this report.

## Project references reviewed

- [P510 Phase 3C-5B physical report](P510-Phase3C5B-physical-GetDeviceInfo.md), [transport log](P510-GetDeviceInfo-transport.log), [raw payload](P510-GetDeviceInfo.raw.bin), and [decoded text](P510-GetDeviceInfo-decoded.txt).
- [P510 known facts](P510-known-facts.md), [P510 physical observations](P510-physical-camera-observations.md), [manual analysis](P510-disc-manual-analysis.md), and [firmware-acquisition research](P510-firmware-acquisition-research.md).
- [Phase 3C-4 PTP transport research](P510-Phase3C4-PTP-transport-research.md), [Phase 3C-5A client design](P510-Phase3C5A-client-design.md), [Nikon firmware-tools source audit](../../../common/tools/nikon-firmware-tools-source-audit.md), and [P500 string-reference analysis](../../p500/analysis/P500-string-reference-analysis.md).
- [P520 payload analysis](../../p520/analysis/P520-payload-analysis.md) and [P500/P520 comparison](../../../comparisons/P500-P520-comparison.md); both are reference material only.
- Local audited source: `C:\GitHub\Tools\nikon-firmware-tools\USB\wireshark\release\wireshark_usb_ptp_20130305.patch` and `C:\GitHub\Tools\nikon-firmware-tools\IDA_files\D7000\105\ptp_code_names.idc`. These are source-code references, not P510 behavior evidence.
