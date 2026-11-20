# Phase 5C - Display and Overlay Analysis

**Scope:** P500 reference labels and bounded literal references; no P510 firmware examined.

## LCD, preview, and video-control labels

P500 primary-code strings include:

| File offset | String | Evidence limit |
|---|---|---|
| `0x61F4AC` | `CamLcdMode` | Descriptor-like setting name; no consumer path identified |
| `0x61F5E0` | `CamLcdBrightness` | Descriptor-like setting name |
| `0x61F5F4` | `CamLcdDirection` | Descriptor-like setting name |
| `0x61F664` | `CamVideoSignalMode` | Descriptor-like video-signal setting name; no output-routing or OSD behavior established |
| `0x61F6B0` | `CamLcdType` | Descriptor-like setting name |
| `0x61F8A0` | `CamTakePreviewOp` | Operation-like descriptor name; not proof of live-view streaming |
| `0x61F8C8` | `CamControlLcdOp` | Operation-like descriptor name; implementation not mapped |
| `0x61F8E4` | `CamLcdDispOp` | Operation-like descriptor name; implementation not mapped |

These names occur in structured descriptor-like records. The existing P500 string-reference report does not establish direct code consumers for the focus/video setting descriptors. The selective scan found no LCD/EVF/HDMI route, preview compositor, or overlay-disable function.

## Histogram and AF-area graphics

P500 resource strings include `View/hide histograms` (`0x6EB7A0`), `Histogram BSS` (`0x6EC03C`), `AF area mode` (`0x6EE9F4`), and `Spot AF area` (`0x6EF0B4`). They indicate UI vocabulary only. No histogram renderer, AF-area box renderer, compositing layer, or connection to a display buffer was identified.

The reference string about overlaying differently exposed shots near `0x6F80CC` describes image compositing for an exposure-related feature. It is not evidence of an on-screen overlay plane or OSD pipeline.

## Clean HDMI

No P500 clean-HDMI hook was identified. `CamVideoSignalMode` is a video-signal label, not a clean-output control. No path was found for suppressing OSD, switching LCD/EVF/HDMI display routes, or composing overlays before external video output.

The P510 manual separately documents HDMI output modes Auto, 480p, 720p, and 1080i. That establishes documented output modes only; it does not establish P510 firmware routing or an overlay-free mode.

## Determination

- LCD/EVF display routing: **not identified**.
- OSD/overlay compositor: **not identified**.
- Histogram and AF-area rendering: **not identified** beyond UI/resource labels.
- Clean-HDMI control hook: **not identified** for either reference firmware or P510.

P500/P520 labels are reference-only and do not establish P510 implementation or compatibility.
