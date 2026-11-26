# Nikon COOLPIX P510 - Phase 5 Overview

**Status date:** 2026-11-20  
**Phase:** 5 - Static architecture research  
**Current work:** Phase 5D - clean-HDMI reference architecture review complete  
**Physical P510 operations:** None authorized or performed

## Purpose and evidence boundary

Phase 5 uses already-held documentation, P510 observations, and P500/P520 reference firmware to identify research leads for image-format, focus-overlay, and HDMI/output questions. P500 and P520 are **reference samples only**. Their code, strings, architecture, and package structures must not be transferred to the P510 as facts or treated as binary compatibility evidence.

The P510 has no authentic firmware image available locally. Its firmware-storage device, processor, and read mechanism remain unknown. Consequently, Phase 5 can assess neighboring-model evidence and P510-reported metadata, but cannot establish P510 firmware implementation or RAW capture feasibility.

## Phase 5A result - RAW architecture

The strongest reference-model RAW evidence is in the P500 reference firmware: strings include `RAW_MODE=`, `NRW (RAW) processing`, `NRW (RAW) + Basic/Fine/Normal`, raw acquisition-size diagnostics, and JPEG-copy labels. A separate `RAW READ ERROR!!` string is linked to a bounded P500 code path. This supports a **possible P500 RAW/NRW-related data/processing path**, but no sensor-to-buffer-to-encoder-to-file path was traced.

**RAW feasibility classification:** **REFERENCE ARCHITECTURE SHOWS POSSIBLE RAW DATA PATH**

This classification applies to the **P500 reference architecture only**. It does **not** classify RAW capture as feasible on the P510. P520 reference payload evidence does not provide a usable RAW/NEF pipeline mapping.

Phase 5A did not identify:

- a RAW/pre-JPEG buffer or its layout;
- a JPEG encoder function/call path;
- an end-to-end NRW/NEF file-creation path; or
- a P510 file-format selection or RAW capture capability. Phase 5B did not establish these either.

P500 string labels suggest a RAW/NRW-plus-JPEG-quality selection vocabulary beyond JPEG quality alone, but no setting-to-capture/file-output flow was verified. The exact `NRW` labels are not evidence of NEF creation.

See [P510-Phase5A-RAW-architecture-analysis.md](P510-Phase5A-RAW-architecture-analysis.md), [P510-Phase5A-RAW-string-and-code-references.md](P510-Phase5A-RAW-string-and-code-references.md), and [P510-Phase5A-capture-pipeline.md](P510-Phase5A-capture-pipeline.md).

## Phase 5B result - P500-only trace

Phase 5B traced selected P500 RAW-read diagnostics, a RAW-named routine with `value0 × value1 × 10 / 8` size arithmetic, and generic wrapper calls. The inputs and wrappers remain unidentified; no RAW/pre-JPEG buffer, JPEG encoder path, or NRW/NEF output writer was established. P500 file-type tables contain RAW/NEF/NRW names, but they are not proof of output support.

**Reference-model classification remains:** **REFERENCE ARCHITECTURE SHOWS POSSIBLE RAW DATA PATH** (P500 only).  
**P510 RAW capture:** not established.

See the [Phase 5B deep trace](P510-Phase5B-P500-RAW-deep-trace.md), [callgraph](P510-Phase5B-P500-RAW-callgraph.md), [buffer analysis](P510-Phase5B-P500-RAW-buffer-analysis.md), and [NRW file-path analysis](P510-Phase5B-P500-NRW-file-path.md).

## Cross-goal references

Phase 5C performed a bounded P500-reference focus/display review. It found focus controls and diagnostic labels but no focus metric, live-view buffer, compositor, or peaking hook. The reference-model focus-peaking classification is **INSUFFICIENT EVIDENCE**; P510 feasibility remains **UNKNOWN**. No clean-HDMI hook was established.

- [P510-Phase5-cross-goal-references.md](P510-Phase5-cross-goal-references.md) records the current evidence and the remaining cross-goal terms.
- See the [Phase 5C architecture report](P510-Phase5C-focus-peaking-architecture.md), [focus/edge references](P510-Phase5C-focus-and-edge-references.md), [live-view buffer analysis](P510-Phase5C-liveview-buffer-analysis.md), and [display/overlay analysis](P510-Phase5C-display-overlay-analysis.md).

## Phase 5D result - clean HDMI

P500 contains HDMI/video-mode resource labels and `CamVideoSignalMode`/LCD-operation descriptor names, but no HDMI/analog output code, hot-plug path, display routing, OSD suppression, or pre-OSD HDMI buffer was identified. Available evidence does not establish playback-only HDMI behavior.

**Reference-model clean-HDMI classification:** **INSUFFICIENT EVIDENCE**.  
**P510 CLEAN HDMI FEASIBILITY:** **UNKNOWN**.

See the [Phase 5D architecture report](P510-Phase5D-clean-HDMI-architecture.md), [video-output references](P510-Phase5D-video-output-references.md), [display-routing analysis](P510-Phase5D-display-routing-analysis.md), and [OSD-suppression analysis](P510-Phase5D-OSD-suppression-analysis.md).

## P510 evidence remains separate

The P510-specific facts remain those in [P510-known-facts.md](P510-known-facts.md), including the owner-observed firmware version 1.0 and the single successful `GetDeviceInfo` response. That response advertises an empty `CaptureFormats` array and `ImageFormats` codes including unresolved `0xB111`; it does not identify RAW/NEF or establish capture behavior. No new P510-supported fact was uncovered in Phase 5A, 5B, 5C, or 5D, so `P510-known-facts.md` was not changed.

## Next-step boundary

Phase 5A–5D are complete for current evidence. Additional neighboring-model static analysis has diminishing value for P510 implementation questions. Preserve the evidence base and resume only if concrete P510-specific firmware or authoritative service documentation becomes available.

Do not communicate with the P510, issue PTP commands, remove hardware material, install/download tools, or modify any firmware as part of this recommendation. No next phase was executed.
