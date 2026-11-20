# Phase 5D - OSD Suppression and Overlay Analysis

**Scope:** Existing P500/P520 reference evidence plus direct P510 documentation/DeviceInfo records; no physical test.

## P500/P520 findings

- No HDMI OSD enable/disable property, hot-key, service setting, menu entry, or code path was identified in the reviewed P500 reference material.
- `CamLcdDispOp` and `CamControlLcdOp` are P500 descriptor-like names without a verified consumer or overlay parameter.
- P500 resource text describing an “overlay” of differently exposed shots concerns image compositing for an exposure feature, not a separately controlled on-screen or HDMI graphics layer.
- Histogram and AF-area labels are UI/resource text only; no overlay compositor or drawing function was mapped.
- P500 `ADDRESS_THUMBYUV2`, JPEG-buffer, and YUV-dimension diagnostics do not identify a framebuffer before or after OSD composition.
- P520 remains opaque in the reviewed local analysis; no OSD/output architecture was recovered from it.

## Separate HDMI overlay and pre-OSD-buffer questions

| Question | Result |
|---|---|
| Independent HDMI overlay plane? | **Not identified** |
| OSD suppression/bypass control? | **Not identified** |
| HDMI signal with OSD disabled? | **Not established** |
| Image buffer known to precede OSD composition? | **No** |
| YUV/JPEG diagnostic proves a pre-OSD HDMI source? | **No**; no HDMI relationship or composition boundary is known |

## P510 relevance

The P510 manual lists HDMI resolutions/modes but no confirmed clean-output or OSD-suppression setting in the reviewed project evidence. The P510 DeviceInfo analysis identifies no HDMI-specific property. Neither source proves that a clean path exists or that overlays are inseparable.

**P510 CLEAN HDMI FEASIBILITY: UNKNOWN.** No experiment or camera operation was performed.
