# Phase 5D - Display-Routing Analysis

**Model:** P500 reference firmware; P510 conclusions remain unknown  
**Purpose:** Determine whether existing evidence maps an image source to LCD, EVF, analog video, or HDMI.

## Evidence inventory

The P500 primary code section contains these descriptor-like names:

- `CamVideoSignalMode` (`0x61F664`), present in offset-word tables at `0x61D88C`, `0x61E4EC`, and `0x61EE7C`.
- `CamLcdMode` (`0x61F4AC`), `CamLcdBrightness` (`0x61F5E0`), `CamLcdDirection` (`0x61F5F4`), and `CamLcdType` (`0x61F6B0`).
- `CamTakePreviewOp` (`0x61F8A0`), `CamControlLcdOp` (`0x61F8C8`), and `CamLcdDispOp` (`0x61F8E4`).

P500 resource strings include `HDMI device control`, HDMI resolution labels, `Video mode`, and `NTSC`. The `ADDRESS_THUMBYUV2`, `JpegBuffer_TopAddrW()`, and `YUV H*V` diagnostics are described in the [live-view buffer analysis](P510-Phase5C-liveview-buffer-analysis.md).

## Routing result

No reviewed code/data relationship identifies:

- a camera-image source feeding LCD or EVF;
- a separate analog-video or HDMI source;
- whether the HDMI signal duplicates LCD output or uses an independent framebuffer;
- a route switch between playback, live view, and movie preview;
- an HDMI or analog-video connection-state handler; or
- a pre-OSD image path.

The operation/setting names and video-mode labels do not establish these behaviors. The P500 YUV/JPEG diagnostic labels do not identify their buffer consumers or output destination.

## P510 boundary

The P510 manual confirms selectable video and HDMI output modes, but not the internal route. Existing P510 DeviceInfo contains no identified HDMI/display property. P510 firmware is unavailable, so no P510 routing path can be analyzed.

**Determination:** display routing is **not identified** for the P500 reference or P510. The “HDMI appears playback-focused” hypothesis remains **unproven**; current evidence is insufficient to distinguish playback-only, live-view, mirrored-display, or independent-output topologies.
