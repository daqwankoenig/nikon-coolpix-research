# Phase 5C - Live-View Buffer Analysis

**Evidence model:** P500 reference firmware; file-offset-oriented addresses  
**P510 conclusion:** No corresponding P510 buffer evidence

## Buffer-related observations

| File offset | Evidence | Code/data relationship |
|---|---|---|
| `0x646216` | `ADDRESS_THUMBYUV2`; followed by `JpegBuffer_TopAddrW()` at `0x64622B` and `Buffer = %d byte` at `0x646244` | Literal load at `0x396658` uses a pool entry at `0x396998`. Nearby code passes the text to formatting/logging helpers. This is a diagnostic path, not a recovered buffer object or live-view call chain. |
| `0x6494D8` | `YUV H*V=%d*%d` | Literal load at `0x4AA9A8` uses pool entry `0x4AB7E0`; the following code calls formatting helper `0x537BB0`. The text is consistent with a logged horizontal/vertical size, but does not establish actual values or layout. |
| `0x61F8A0` | `CamTakePreviewOp` | P500 descriptor-like operation name. No verified live-view start, frame-fetch, or streaming implementation was linked to it. |
| `0x61F8C8`, `0x61F8E4` | `CamControlLcdOp`, `CamLcdDispOp` | P500 LCD-operation descriptor names; no verified preview-buffer consumer or display route was traced. |

The thumbnail diagnostic appears near P500 movie-size labels such as `MVSZ_FULLHD_HI`, `MVSZ_FULLHD_LOW`, and `MVSZ_HD`. The nearby context supports an image/video diagnostic interpretation, but does not identify whether the named memory is a still thumbnail, movie frame, preview, or another object.

## Format and dimensions

- `YUV` and `THUMBYUV2` appear in labels only. No confirmed pixel format, chroma order, bit depth, plane count, stride, packing, or color space was established.
- `H*V` appears in a formatted diagnostic string. No numeric dimensions or buffer-size calculation tied to a known live-view frame was identified.
- `JpegBuffer_TopAddrW()` and the byte-count label identify a diagnostic mention of a JPEG buffer. The buffer address, allocator, owner, lifetime, and relation to preview frames remain unknown.

**Result:** no live-view buffer was identified. P500 contains YUV/thumbnail/JPEG diagnostic leads, but format and dimensions are **unknown**. These references do not provide a focus-peaking insertion point or a P510 inference.

See the [P500 RAW buffer analysis](P510-Phase5B-P500-RAW-buffer-analysis.md) for a separate, unrelated P500 `10/8` size-calculation lead.
