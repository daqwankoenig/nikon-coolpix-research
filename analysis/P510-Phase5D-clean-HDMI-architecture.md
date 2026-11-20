# Phase 5D - Clean HDMI Architecture

**Status:** COMPLETE - bounded offline review of existing evidence  
**Reference firmware:** P500 only; P520 provides no readable display architecture in the reviewed analysis  
**P510 hardware:** Not contacted or operated  
**Firmware modification/testing:** None

## Executive determination

The P500 reference contains an `HDMI device control` resource string, an `HDMI` resolution/menu label, NTSC video-mode text, and a `CamVideoSignalMode` descriptor. These are configuration/resource leads, not an HDMI signal-processing or output-routing implementation. No HDMI-specific code, analog-video implementation, cable/hot-plug handling, display route, independent overlay plane, or OSD suppression function was identified.

The P500 strings do not establish that HDMI is playback-only. Playback and preview labels exist, but no code or data path connects them to HDMI output. Therefore:

**CLEAN-HDMI REFERENCE CLASSIFICATION: INSUFFICIENT EVIDENCE**  
**P510 CLEAN HDMI FEASIBILITY: UNKNOWN**

## P500 reference evidence

The P500 primary-code input hash was verified as `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`.

- `HDMI device control` occurs at file offset `0x6E80C8`.
- `HDMI` occurs at `0x6F25A0`; nearby resource entries include `480p`, `720p`, and `Auto`.
- `Video mode` and `NTSC` occur at `0x6ECA7C` and `0x6ECAA0`.
- `CamVideoSignalMode` occurs at `0x61F664` and is referenced by descriptor-like offset records at `0x61D88C`, `0x61E4EC`, and `0x61EE7C`.
- `CamControlLcdOp` and `CamLcdDispOp` are descriptor-like strings at `0x61F8C8` and `0x61F8E4`; `CamTakePreviewOp` is at `0x61F8A0`.
- A selective ARM literal-pool scan found descriptor-table entries but no code references to the HDMI/resource labels above. This bounded negative result does not prove that no implementation exists elsewhere.

The P500 resource data also contains `Playback`, `Preview`, and movie-size labels. No HDMI output routine, playback routine, or preview operation was traced into a common or separate signal path. “Playback-focused” is therefore **not confirmed**.

## Output questions

| Question | Result |
|---|---|
| `CamVideoSignalMode` meaning/status | P500 descriptor-like setting name; likely video-signal configuration, but exact semantics, values, and consumers are unknown. It is not an HDMI routing or clean-output control by itself. |
| HDMI-specific code identified? | **No.** HDMI/menu strings are present, but no HDMI-specific code path or function was identified. |
| Analog-video code identified? | **No.** P500 has `Video mode`/`NTSC` resource text and the `CamVideoSignalMode` descriptor; no analog output implementation was traced. |
| HDMI connection/hot-plug handling? | **Not identified.** No cable-detect, connection-state, hot-plug, or HDMI event path was established. |
| Live-view versus playback evidence? | **Undetermined.** Playback and preview labels occur in P500 data but are not connected to HDMI. No playback-only conclusion is supported. |
| Display routing? | **Not identified.** No LCD/EVF/HDMI source selection or route-switching code was established. |
| OSD/overlay control? | **Not identified.** No HDMI OSD enable/disable, layer control, or suppressible overlay path was found. |
| Separate HDMI overlay evidence? | **None identified.** The P500 exposure-compositing “overlay” text describes combining differently exposed images, not an HDMI graphics plane. |
| Possible pre-OSD framebuffer? | **No.** P500 YUV/thumbnail/JPEG diagnostics are not tied to an HDMI source, an OSD boundary, or a pre-composited frame. |

## Reference architecture models

The project has no prior A–E model definitions. For this report, the following are working topology labels, not claims about Nikon hardware:

| Model | Hypothetical topology | Evidence status |
|---|---|---|
| A | HDMI mirrors a final LCD/EVF framebuffer with graphics already composed | Not established |
| B | HDMI shares image data but uses a separately composited OSD plane | Not established |
| C | HDMI can route a clean pre-OSD image or bypass the OSD compositor | Not established |
| D | HDMI is limited to playback/movie output, without live-view output | Not established |
| E | Output topology cannot be determined from available evidence | **Selected: INSUFFICIENT EVIDENCE** |

## P510 relevance

The P510 manual documents HDMI modes Auto, 480p, 720p, and 1080i, plus NTSC/PAL video-mode selection. These are direct P510 documentation facts, but they do not reveal internal routing, OSD behavior, playback/live-view scope, or a clean-output mode. Existing P510 DeviceInfo analysis identifies no HDMI-specific property or standard live-view operation; that absence does not prove the hardware cannot output live view.

No P500/P520 result is transferred to the P510. **P510 CLEAN HDMI FEASIBILITY: UNKNOWN.** `P510-known-facts.md` was not changed.

## Major missing evidence

- P510 firmware or authoritative P510 service documentation describing video output.
- HDMI/analog transmitter and source-routing code.
- Cable-detect/hot-plug state and event handling.
- A confirmed live-view or playback framebuffer and its display consumers.
- The boundary between image pixels and OSD composition.
- Evidence of a separately controllable HDMI overlay plane or pre-OSD path.

## Phase 5 overall assessment

| Goal | Strongest evidence | Strongest blocker | Value of more reference-model analysis | P510 firmware dependency | Could a safe P510 documentation-only review materially answer implementation feasibility? |
|---|---|---|---|---|---|
| RAW | P500 RAW/NRW labels, a code-linked RAW-read diagnostic, and a candidate `×10/8` size calculation | No confirmed sensor-to-buffer-to-encoder-to-file chain; no P510 firmware | Low to moderate: opaque P500 wrappers may be mapped, but that cannot establish P510 support | **High** | No. Manuals may clarify advertised file modes, not an undocumented capture pipeline. |
| Focus peaking | P500 manual-focus/lens-task leads and YUV/JPEG diagnostic labels | No AF metric, live-view buffer, or display compositor | Low to moderate: further P500 mapping would remain model-specific | **High** | No. A manual can establish user-visible focus features, not an image-processing/render hook. |
| Clean HDMI | P510 manual output modes; P500 `CamVideoSignalMode` and HDMI resource labels | No HDMI routing, hot-plug, pre-OSD, or overlay-control path | Low: current neighboring-model evidence is descriptor/resource-level | **High** | No. Documentation may clarify user-visible output behavior but not whether P510 can suppress overlays. |

## Recommended next project direction

Pause further neighboring-model architecture expansion unless a concrete, relevant P510 source appears (for example, authentic P510 firmware or an authoritative service document). Preserve and cross-reference the current evidence. No physical experiment, camera connection, firmware change, or next phase is authorized or executed here.

See the [video-output references](P510-Phase5D-video-output-references.md), [display-routing analysis](P510-Phase5D-display-routing-analysis.md), [OSD-suppression analysis](P510-Phase5D-OSD-suppression-analysis.md), and [Phase 5 cross-goal references](P510-Phase5-cross-goal-references.md).
