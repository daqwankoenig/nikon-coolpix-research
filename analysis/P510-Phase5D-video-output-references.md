# Phase 5D - Video-Output References

**Boundary:** P500 data below is reference-only. P510 manual/PTP facts are identified separately.

## P500 strings and descriptors

| Offset | Reference | What it supports | What it does not support |
|---|---|---|---|
| `0x6E80C8` | `HDMI device control` | HDMI-related resource/UI vocabulary exists | No HDMI-CEC implementation, connection detection, playback route, or OSD behavior is established |
| `0x6F25A0` | `HDMI`; nearby `480p`, `720p`, `Auto` | HDMI output-mode/resource labels exist | No signal-generation or output-path code |
| `0x6ECA7C`, `0x6ECAA0` | `Video mode`, `NTSC` | Analog/video-mode resource labels exist | No NTSC/PAL encoder or analog-output implementation |
| `0x61F664` | `CamVideoSignalMode` | Descriptor-like setting name; offset-word entries at `0x61D88C`, `0x61E4EC`, `0x61EE7C` | Exact semantic mapping, possible values, handler, and relationship to HDMI |
| `0x61F8A0` | `CamTakePreviewOp` | Preview-operation-like descriptor name | Live-view streaming or HDMI routing |
| `0x61F8C8`, `0x61F8E4` | `CamControlLcdOp`, `CamLcdDispOp` | LCD-operation-like descriptor names | LCD/EVF/HDMI source selection or compositor implementation |
| `0x6E7380`, `0x6E7758`, `0x6F2DE8` | `Playback`, `Preview`, `Playback mode` | Playback/preview terms exist in resource data | Which modes are routed to an HDMI connector |

The selective ARM literal-pool scan found references to descriptor strings in data tables, but no code references to the HDMI, NTSC, or video-mode resource strings. The larger P500 Ghidra inventory also warns that its offset mapping yielded no code xrefs for the matched-string set. These are bounded analysis limitations, not proof of dead code.

## P510-specific evidence

- The P510 manual documents video output selection NTSC/PAL and HDMI output modes Auto, 480p, 720p, and 1080i.
- The P510 manual identifies a Mini HDMI Type C connector.
- The reviewed P510 DeviceInfo response advertises no identified HDMI-specific property and no standard live-view operation. The opaque values remain unresolved; none is confirmed as a display control.

These are documentation and advertisement facts. They do not establish a P510 HDMI source path, live-view output, CEC handling, or clean HDMI.

## Status

- HDMI-specific implementation: **not identified**.
- Analog-video implementation: **not identified**.
- HDMI hot-plug/connection handling: **not identified**.
- `CamVideoSignalMode`: **P500 descriptor-like label; exact meaning and implementation unknown**.
- Playback-only HDMI behavior: **not established**.
- P510 clean-HDMI feasibility: **UNKNOWN**.
