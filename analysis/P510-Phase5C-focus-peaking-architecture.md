# Phase 5C - Focus-Peaking Architecture

**Status:** COMPLETE - bounded offline reference analysis  
**Reference evidence:** Nikon COOLPIX P500 firmware only; P520 remains opaque  
**P510 firmware/hardware:** Not examined or contacted  
**Firmware modification or patching:** None

## Executive result

The P500 reference contains manual-focus, autofocus-area, LCD-control, preview-operation, histogram, YUV-thumbnail, and JPEG-buffer **labels or diagnostics**. A separate P500 code-linked diagnostic sequence mentions focus-drive synchronization and the lens-motor task. These observations identify camera controls and diagnostic leads, but do not reveal a live-view frame pipeline, a contrast/edge focus metric, a focus-dependent display compositor, or a call site where focus-peaking pixels could be drawn.

> **REFERENCE ARCHITECTURE FOCUS-PEAKING CLASSIFICATION: INSUFFICIENT EVIDENCE**
>
> This classification is for the reviewed P500 reference evidence only. P510 focus-peaking feasibility remains **UNKNOWN**; no authentic P510 firmware or P510-specific implementation evidence was analyzed.

## Input and evidence limits

The P500 primary-code input was `firmware/extracted/P500/sections/P500-NPROG-primary.bin`, SHA-256:

`42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`

The hash matches the existing record. Addresses are file-offset-oriented and are not runtime addresses. Findings combine the existing bounded P500 string/code inventory with a read-only scan of literal-pool references. The P500 inventory warns that its offset-mapped Ghidra program produced no code xrefs for the matched-string set; absence of such xrefs is not proof that a string is unused.

P520 contributes no focus/display architecture evidence in the reviewed local analysis: its payload remains opaque/high-entropy. P500/P520 package-level similarities do not establish shared camera firmware architecture.

## Required determinations

| Question | Result |
|---|---|
| Manual-focus path identified? | **Partial P500 control/task evidence.** `CamManualFocus` and `CamFocusMode` occur in descriptor-like records; P500 UI text names manual-focus mode; separate lens-task diagnostics identify focus-drive synchronization. No setting-to-motor end-to-end path was traced. |
| AF/contrast focus metric identified? | **No.** AF mode/area labels exist, but no contrast score, sharpness metric, focus-evaluation loop, or AF metric-to-display path was identified. |
| Edge/detail processing identified? | **No focus-edge path.** P500 has `Image sharpening` UI text, `Lumin Detail Level`/mask/face diagnostics, and `cam_edge=` diagnostic fields. Their code semantics do not establish a live-view edge detector or focus metric. |
| Live-view buffer identified? | **No.** `ADDRESS_THUMBYUV2` and JPEG-buffer diagnostics are leads, not a confirmed live-view buffer or stream. |
| Buffer format/dimensions supported? | **No confirmed format or dimensions.** The text `YUV H*V=%d*%d` and `THUMBYUV2` names are diagnostic labels; actual layout, size values, planes, stride, and relationship to live view are unknown. |
| LCD/EVF display routing identified? | **No.** LCD and video-signal descriptor names are present, but no source-to-LCD/EVF/HDMI routing code was established. |
| OSD/overlay compositor identified? | **No.** No on-screen overlay compositor, layer buffer, drawing call, or overlay-disable path was identified. |
| Histogram implementation useful? | **UI/resource evidence only.** `View/hide histograms` and `Histogram BSS` strings exist; no histogram calculation or rendering implementation was traced. |
| AF-area graphics useful? | **UI/descriptor evidence only.** `CamAfArea`, `AF area mode`, and `Spot AF area` exist; no AF-box drawing or graphics pipeline was identified. |
| Strongest eventual focus-peaking hook? | **No code hook can be named.** `CamManualFocus` is the strongest possible mode-gating lead, while the YUV/JPEG diagnostic is a weak buffer-inspection lead. Neither is a verified pixel-processing or rendering hook. |
| Clean-HDMI hooks discovered? | **No.** `CamVideoSignalMode`, `CamControlLcdOp`, and `CamLcdDispOp` are P500 descriptor labels only; no clean-output, OSD suppression, or output-routing path was traced. |

## P510 relevance

No P500/P520 discovery is a P510 fact. P510 has no authentic firmware image available in the project, and this phase did not contact or operate the camera. The existing P510 manual analysis documents HDMI output selections, but that is not evidence of firmware routing or clean HDMI. P510 focus-peaking feasibility therefore remains **UNKNOWN**; `P510-known-facts.md` was not changed.

## Major missing evidence

- P510 firmware or another direct P510 implementation source.
- A confirmed live-view frame buffer, its format/dimensions, and its producer/consumer chain.
- A focus/edge metric computed on live-view image data.
- A relationship between manual-focus state and a preview/display update path.
- LCD/EVF/HDMI routing and the display-composition function.
- An OSD/overlay layer or safe insertion point in the P500 reference, let alone the P510.

## Recommended Phase 5D

If selected, keep Phase 5D a separate, bounded, offline analysis of **P500 reference** video-output and display-routing evidence, beginning with the `CamVideoSignalMode`, `CamControlLcdOp`, and `CamLcdDispOp` descriptor families and looking for verified output/OSD consumers. Do not treat those names as proof of clean HDMI or P510 behavior. Phase 5D was **not executed**.

See the [focus and edge references](P510-Phase5C-focus-and-edge-references.md), [live-view buffer analysis](P510-Phase5C-liveview-buffer-analysis.md), [display/overlay analysis](P510-Phase5C-display-overlay-analysis.md), and [Phase 5 cross-goal list](P510-Phase5-cross-goal-references.md).
