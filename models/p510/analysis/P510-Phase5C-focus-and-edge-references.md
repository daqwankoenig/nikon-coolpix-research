# Phase 5C - Focus and Edge References

**Model boundary:** P500-only firmware evidence; none of these entries establishes P510 behavior.

## Focus controls and lens tasking

| File offset | Evidence | Bounded interpretation |
|---|---|---|
| `0x61F47C` | `CamFocusMode` | P500 setting/descriptor name; offset-word entries at `0x61D5D4`, `0x61E24C`, and `0x61EC3C` |
| `0x61F49C` | `CamManualFocus` | P500 setting/descriptor name; offset-word entries at `0x61D604`, `0x61E27C`, and `0x61EC6C` |
| `0x61F5D0` | `CamFocusTemp` | P500 descriptor name; purpose and values unknown |
| `0x61F934` | `CamAfArea` | P500 operation/property-like descriptor name; entries occur at `0x61DD0C` and `0x61EF24`; consumer semantics unknown |
| `0x602C5C` | `Focus Drive cre_sem` | Loaded from a P500 literal pool at `0x106720`; code near `0x1061D8–0x106840` contains repeated task/synchronization diagnostics |
| `0x602CD8` | `lens_mtr_drv_master_task_start` | Repeated literal loads in the same bounded lens/task diagnostic region; task implementation and focus-position data path were not recovered |
| `0x601930`, `0x601964`, `0x60198C` | `FOCUS`, `FOCUS BACKRUSH`, `FOCUS_DOWN` | Focus/mechanical diagnostic labels; not a focus-confidence or image-edge score |
| `0x6E69B0`, `0x6E8654` | `Select manual focus (MF) mode.`, `Autofocus mode` | User-facing P500 resource text; no code linkage to a peaking/display path |

**Determination:** A P500 manual-focus control and focus-drive tasking context are supported at the descriptor/diagnostic level. A complete user-setting-to-lens-command path is not established.

## AF area, edge, and detail

| File offset | Evidence | Bounded interpretation |
|---|---|---|
| `0x6EE9F4` | `AF area mode` | P500 UI/resource string |
| `0x6EF0B4` | `Spot AF area` | P500 UI/resource string |
| `0x6EF2F8` | `Image sharpening` | P500 image-quality setting label; no processing function or live-view connection identified |
| `0x6F5248` onward | Text about adjusting contrast, sharpening, and saturation | User guidance/resource text; not an edge-detection implementation |
| `0x664C2C` | `Lumin Detail Level: %d`; nearby mask and face-rectangle diagnostics | Image/detail diagnostic context; no AF or focus-peaking relation established |
| `0x6143A4`, `0x614760` | `cam_edge=` diagnostics among acquisition, scene, exposure, white-balance, and flash fields | Meaning of `cam_edge` is unknown; context does not identify a focus-edge metric |

No measured AF contrast score, gradient magnitude, focus-peak threshold, per-pixel edge map, or frame-associated focus statistic was identified. The `CamAfArea` table entry is not evidence of an AF-area graphic renderer.

## Histogram and “overlay” terms

- `View/hide histograms` at `0x6EB7A0` and `Histogram BSS` at `0x6EC03C` are P500 UI/resource strings. No histogram computation or screen-rendering path was traced.
- The P500 help text near `0x6F80CC` describes an image made from normal-exposure and differently exposed shots with an “overlay.” This is exposure-image compositing language, not evidence of an on-screen OSD compositor.
- Strings `Continuous auto overlay L/H` appear in resource data near `0x6E7A90` and `0x6E7F18`; their feature semantics are not established. They are not sufficient evidence for display overlays.

The expanded P500 inventory's offset-mapped analysis reported no code xrefs for its matched-string set. The selective literal-reference scan also did not establish code consumers for the histogram, AF-area, or sharpening labels. These limitations leave use/reachability unknown rather than proving the strings are unused.

## Result

P500 supports **manual-focus and AF-area UI/control leads**, but not a traced AF metric, edge/detail focus signal, or focus-peaking rendering path. P510 focus and edge processing remain unknown.

References: [P500 string-reference analysis](P500-string-reference-analysis.md), [P500 expanded Ghidra analysis](P500-ghidra-expanded-analysis.md), and [P500 expanded inventory](ghidra-logs/P500-expanded-inventory.log).
