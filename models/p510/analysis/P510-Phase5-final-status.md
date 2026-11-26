# Nikon COOLPIX P510 - Phase 5 Final Status

**Status date:** 2026-11-20  
**Phase:** 5 - Enhancement feasibility research, Phases 5A-5D closed  
**Next phase:** None started; do not begin Phase 5E  
**Evidence boundary:** P500/P520 firmware is reference-only. It is not interchangeable with P510 firmware and does not establish P510 implementation.

## Executive summary

Of the three enhancement goals, RAW capture has the strongest existing reference-model lead: P500 evidence supports a possible RAW/NRW-related data path. It does not establish a complete pipeline or P510 capability. Focus peaking and clean HDMI remain insufficiently supported even in the reviewed reference architecture. All three P510 feasibility assessments remain **UNKNOWN**.

The principal implementation-level blocker is the absence of authentic P510 firmware. `firmware/original/P510/` remains empty. No P500/P520 result may be substituted for evidence about P510 code, architecture, or behavior.

## RAW capture

### Reference-model evidence - P500 only

- P500 contains NRW/RAW-related mode and processing strings, including RAW-mode, NRW processing, and NRW quality labels.
- Acquisition-size and JPEG-copy/reference strings are present.
- A `RAW READ ERROR!!` label is linked to a bounded P500 status/error-reporting code path.
- Phase 5B examined a RAW-named routine and size arithmetic, but the helper inputs and wrapper semantics remain unknown.
- No raw/pre-JPEG buffer was established.
- No JPEG encoder boundary or encoder call path was established.
- No NRW/NEF file-creation path was established.
- An active RAW/NRW selection-to-output path was not verified.
- P500/P520 package similarities are installer/container observations; they do not establish shared image-processing architecture.

**Reference classification: REFERENCE ARCHITECTURE SHOWS POSSIBLE RAW DATA PATH**

This is **not** a P510 RAW-capability finding.

**P510 status: RAW CAPTURE FEASIBILITY: UNKNOWN**

P510-specific metadata does not resolve this question. The captured DeviceInfo advertises an empty `CaptureFormats` list, includes `ImageFormats` codes `0x3801` and unresolved `0xB111`, and does not advertise standard `InitiateCapture (0x100E)`. These observations do not prove that the imaging pipeline cannot produce RAW data, and they do not demonstrate RAW capture.

See the [Phase 5A architecture analysis](P510-Phase5A-RAW-architecture-analysis.md), [Phase 5B deep trace](P510-Phase5B-P500-RAW-deep-trace.md), [buffer analysis](P510-Phase5B-P500-RAW-buffer-analysis.md), and [NRW/NEF file-path analysis](P510-Phase5B-P500-NRW-file-path.md).

## Focus peaking

### Reference-model evidence - P500 only

- Partial manual-focus control and lens-task evidence exists.
- `CamManualFocus` is a possible mode-gating reference, not a confirmed peaking hook.
- No AF/contrast focus metric was traced.
- No per-pixel focus/edge-processing path was established.
- No live-view framebuffer, LCD/EVF routing, or OSD compositor was established.
- `THUMBYUV2`, JPEG-buffer, and YUV diagnostics remain weak leads only; their buffer semantics and relation to live view are unknown.
- Histogram and AF-area evidence is primarily UI/descriptor-level.

**Reference classification: INSUFFICIENT EVIDENCE**

**P510 status: FOCUS PEAKING FEASIBILITY: UNKNOWN**

See the [Phase 5C architecture report](P510-Phase5C-focus-peaking-architecture.md), [focus and edge references](P510-Phase5C-focus-and-edge-references.md), [live-view buffer analysis](P510-Phase5C-liveview-buffer-analysis.md), and [display/overlay analysis](P510-Phase5C-display-overlay-analysis.md).

## Clean HDMI output

### Reference-model evidence - P500 only

- `CamVideoSignalMode` exists as a P500 descriptor-like label; its exact meaning, values, and consumers are unknown.
- P500 contains HDMI, resolution, NTSC/video-mode, and HDMI-device-control resource strings.
- No HDMI-specific implementation path or analog-versus-HDMI routing implementation was established.
- No HDMI hot-plug handling or live-view-to-HDMI routing was established.
- No OSD suppression path, separate HDMI overlay, or pre-OSD framebuffer was established.
- Playback-only HDMI behavior was **not** established.

**Working architecture classification: Model E - unresolved**  
**Reference classification: INSUFFICIENT EVIDENCE**  
**P510 status: CLEAN HDMI FEASIBILITY: UNKNOWN**

The P510 manual documents output modes, but those user-facing settings do not establish internal routing or clean-output capability. See the [Phase 5D architecture report](P510-Phase5D-clean-HDMI-architecture.md), [video-output references](P510-Phase5D-video-output-references.md), [display-routing analysis](P510-Phase5D-display-routing-analysis.md), and [OSD-suppression analysis](P510-Phase5D-OSD-suppression-analysis.md).

## Comparison of the three goals

| Goal | Strongest reference evidence | Strongest P510 evidence | Primary blocker | Value of more P500 analysis | Dependency on P510 firmware | Current status |
|---|---|---|---|---|---|---|
| RAW capture | P500 NRW/RAW strings, acquisition-size/JPEG-copy references, and a code-linked `RAW READ ERROR!!` path | Firmware version 1.0; verified DeviceInfo with empty `CaptureFormats`, `0x3801`, and unresolved `0xB111`; no capture-initiate operation advertised in that response | No confirmed pre-JPEG buffer, encoder boundary, or NRW/NEF writer; no P510 pipeline evidence | Limited to low-to-moderate: opaque P500 wrappers may yield more P500 detail, but cannot establish P510 support | High | Strongest existing reference lead only; **P510 feasibility UNKNOWN** |
| Focus peaking | P500 manual-focus/lens-task evidence and weak YUV/JPEG diagnostic leads | P510 DeviceInfo is preserved; no direct focus metric, live-view buffer, or overlay implementation evidence | No focus metric, frame buffer, display route, or compositor established | Low-to-moderate: any further P500 mapping remains model-specific | High | **Reference INSUFFICIENT EVIDENCE; P510 feasibility UNKNOWN** |
| Clean HDMI | P500 `CamVideoSignalMode` descriptor-like label and HDMI/resolution/video-mode resource strings | P510 manual documents HDMI/video output modes; no P510 implementation path is established | No routing, hot-plug, live-view source, OSD control, or pre-OSD path | Low: current neighboring-model evidence is predominantly labels/descriptors | High | **Reference INSUFFICIENT EVIDENCE; P510 feasibility UNKNOWN** |

RAW has the strongest current reference-model lead, but it is not evidence that RAW capture is feasible on the P510. P500/P520 findings must remain separately attributed and must not be used as substitutes for P510 firmware.

## Dominant project blocker

`firmware/original/P510/` remains empty; no authentic P510 firmware image is available in the project. Without authentic P510 firmware, the project cannot reliably determine:

- actual P510 processor code paths or executable architecture;
- the P510 image pipeline or whether P500 RAW architecture exists in P510;
- actual P510 live-view buffers or display compositor;
- actual P510 HDMI routing;
- whether hidden P510 functionality exists;
- P510-specific safe patch locations; or
- the P510 checksums, signatures, and update format relevant to any future modification research.

Do not attempt to overcome this blocker by treating P500 or P520 firmware as compatible with P510.

## High-value leads to preserve

These are pointers into existing model-specific evidence, not proof of P510 features.

### RAW - P500 reference

- NRW/RAW mode and processing references.
- Code-linked `RAW READ ERROR!!` region.
- Acquisition-size references and candidate size arithmetic.
- JPEG-copy references.
- Start with the [Phase 5B deep trace](P510-Phase5B-P500-RAW-deep-trace.md) and its [callgraph evidence](P510-Phase5B-P500-RAW-callgraph.md).

### Focus peaking - P500 reference

- `CamManualFocus` and partial manual-focus/lens-task paths.
- `THUMBYUV2` and YUV/JPEG diagnostic references.
- No buffer, focus-metric, edge-processing, or compositor meaning is established for these leads.
- Start with the [Phase 5C focus and edge references](P510-Phase5C-focus-and-edge-references.md).

### Clean HDMI - P500 reference

- `CamVideoSignalMode`.
- HDMI and resolution-related resource strings.
- HDMI-device-control strings.
- These are not verified output implementation or routing paths.
- Start with the [Phase 5D video-output references](P510-Phase5D-video-output-references.md).

### P510 - direct evidence to preserve

- Owner-observed physical firmware version **1.0**.
- USB VID/PID **04B0:0223** and Still Image/PTP interface.
- Verified 293-byte `GetDeviceInfo` payload, obtained from one `GetDeviceInfo (0x1001)` request with transaction ID 1 and response `PTP_OK (0x2001)`.
- `ImageFormats` includes **0x3801** and unresolved **0xB111**; do not assign a new meaning to `0xB111`.
- Vendor-extension operations **0x90A1-0x90A3** remain unresolved.
- Device properties **0xD280** and **0xD303** remain unresolved; do not assign new meanings.

The raw capture, decoded record, and transport evidence are linked from [P510-known-facts.md](P510-known-facts.md) and the [Phase 3C DeviceInfo analysis](P510-Phase3C6-DeviceInfo-analysis.md). The known-facts file was not changed for this closeout.

## Conditions for resuming enhancement analysis

Resume detailed implementation research only when one or more concrete triggers occur:

1. Authentic P510 firmware is acquired.
2. A verified official/service P510 firmware image appears.
3. P510 firmware storage is positively identified and a safe, read-only acquisition method is supported.
4. P510 processor/SoC architecture becomes established.
5. P510 service documentation exposes image, display, or HDMI architecture.
6. P510-specific source or tooling reveals relevant internal behavior.

A new generic P500/P520 string match alone is not sufficient reason to restart deep analysis.

## Project safety state

- **WORKING P510 HARDWARE INVESTIGATION:** NOT JUSTIFIED
- **UNKNOWN PTP COMMAND EXECUTION:** NOT JUSTIFIED
- **FIRMWARE MODIFICATION:** BLOCKED
- **FIRMWARE FLASHING:** BLOCKED
- **DONOR PURCHASE:** DEFERRED
- **PUBLIC P510 FIRMWARE SEARCH:** EXHAUSTED FOR NOW
- **PUBLIC P510 BOARD DOCUMENTATION SEARCH:** EXHAUSTED FOR NOW
- **P510 original firmware directory:** remains empty

Phase 5 is closed for the current evidence. No Phase 5E or other next phase was started.
