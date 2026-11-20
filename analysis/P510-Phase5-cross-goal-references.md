# P510 Phase 5 - Cross-Goal References

**Purpose:** Record evidence-qualified leads for RAW, focus peaking, and clean HDMI. Phases 5B–5D used neighboring-model firmware only; none establishes P510 implementation.

## FOCUS PEAKING

Cross-reference terms:

- live-view buffers
- framebuffer
- edge/detail processing
- focus metrics
- overlays
- display composition

Existing evidence pointers only:

- The P510's advertised PTP properties `0xD280` and `0xD303` remain unresolved; none is identified as a focus metric or display control.
- Existing P500 reference strings include `CamFocusMode`, `CamManualFocus`, `Focus Drive cre_sem`, and lens-task diagnostics. They are P500-only strings and do not establish focus peaking on either the P500 or P510.
- Phase 5C found P500 `CamAfArea`, AF-area and histogram UI labels, plus `ADDRESS_THUMBYUV2`/JPEG-buffer and `YUV H*V` diagnostics. It did not identify an AF contrast metric, live-view buffer, edge map, display compositor, or focus-peaking hook.
- **Reference classification:** INSUFFICIENT EVIDENCE. **P510 focus-peaking feasibility:** UNKNOWN.

See [Phase 5C focus and edge references](P510-Phase5C-focus-and-edge-references.md), [live-view buffer analysis](P510-Phase5C-liveview-buffer-analysis.md), [display/overlay analysis](P510-Phase5C-display-overlay-analysis.md), the [P510 Phase 3C DeviceInfo analysis](P510-Phase3C6-DeviceInfo-analysis.md), and [P500 string-reference analysis](P500-string-reference-analysis.md).

## CLEAN HDMI

Cross-reference terms:

- HDMI
- video output
- OSD
- overlay
- display routing
- monitor output
- live-view output

Existing evidence pointers only:

- The P510 user documentation and Phase 3C analysis record HDMI output modes, but no P510 firmware path for overlays, OSD suppression, routing, or clean output is established.
- Existing P500 reference strings include `CamVideoSignalMode`; this is not a P510 mapping and does not establish clean HDMI behavior.
- Phase 5C also found P500 `CamControlLcdOp` and `CamLcdDispOp` descriptor names, but no output-routing, OSD-suppression, or overlay-composition implementation. No clean-HDMI hook was identified.
- Phase 5D found P500 HDMI/menu resource strings (`HDMI device control`, `HDMI`, resolution labels, `NTSC`) and descriptor names, but no HDMI/analog output code, hot-plug handling, display routing, or OSD suppression path. Playback-only behavior was not established.
- **Reference classification:** INSUFFICIENT EVIDENCE. **P510 clean-HDMI feasibility:** UNKNOWN.

See [Phase 5D clean-HDMI architecture](P510-Phase5D-clean-HDMI-architecture.md), [video-output references](P510-Phase5D-video-output-references.md), [display-routing analysis](P510-Phase5D-display-routing-analysis.md), and [OSD-suppression analysis](P510-Phase5D-OSD-suppression-analysis.md), along with [Phase 5C display/overlay analysis](P510-Phase5C-display-overlay-analysis.md), the [P510 Phase 3C DeviceInfo analysis](P510-Phase3C6-DeviceInfo-analysis.md), [P510 manual analysis](P510-disc-manual-analysis.md), and [P500 string-reference analysis](P500-string-reference-analysis.md).

## Scope boundary

This file is a cross-reference checklist, not evidence that any listed feature exists. P500/P520 data remains model-specific reference material. Phases 5C and 5D establish neither focus-peaking nor clean-HDMI implementation on the P510. Revisit these goals only in a separately scoped phase, using direct P510 evidence where available and labeling neighboring-model observations as hypotheses.
