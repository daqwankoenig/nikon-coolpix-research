# Phase 5B - P500 RAW/NRW Deep Trace

**Status:** COMPLETE - bounded offline static analysis  
**Evidence model:** Nikon COOLPIX P500 reference firmware only  
**P510 firmware or hardware:** Not examined or contacted  
**Firmware modifications:** None

## Input and method

The analyzed input was `firmware/extracted/P500/sections/P500-NPROG-primary.bin`, SHA-256:

`42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`

The hash matches the existing project record. Addresses below are file-offset-oriented addresses in the P500 Ghidra program mapped at `0x00000000`; they are not asserted runtime addresses. The trace used literal-pool/reference scans and ARM `BL`-word target calculations, with selected code notes from the isolated Phase 5B analysis copy. No firmware image was changed.

## Findings

### RAW-read diagnostic

The P500 text `ERROR 3 : RAW READ ERROR!!` is at file offset `0x614818`. An ARM literal load at `0x1CF984` obtains its pointer from `0x1CFC10`. It appears among status, buffer-size, folder-read, file-read, and RGB-read error messages.

The surrounding bounded path checks bits in a status word and appends the corresponding text through a helper at `0x537BB0`. The helper's exact role and the meaning of the status bits are unknown. This is code-linked **error/reporting evidence**, not proof of sensor acquisition, a particular file read, or RAW output.

### RAW-named routine and size arithmetic

The P500 section contains `RAW` filename tokens and a `DATA%d` format string at `0x6148A8–0x6148B0`. Literal-load sites include `0x1CFAAC`, `0x1CFB00`, and `0x1CFB10`.

A bounded routine around `0x1CFAF0` calls helper `0x86314` with indices 0 and 1, multiplies the returned values, then calculates `product × 10 / 8`. This is consistent with a 10-bit-per-sample packed-size formula **only if** the helper returns image dimensions; that meaning is not established. The arithmetic alone does not identify a RAW buffer or pixel format.

The routine also passes a 44-byte size and a stack pointer to wrapper `0x2DF08C`, invokes wrapper `0x2DF0E0` with the computed size and an indexed argument based on `0x40000000`, and later releases through `0x2DF0B0`. These wrappers reach opaque internal routines. No path or API name establishes whether the data is a file, memory object, device buffer, or another internal resource.

### Call-site and configuration context

The raw ARM branch-word scan found these direct-call candidates:

| Caller offset | Target offset | Observation |
|---|---|---|
| `0x1CF190`, `0x1CF860` | `0x1CF8B8` | Calls into the status/error formatting path |
| `0x1CFBC0` | `0x1CFA38` | Calls a RAW-named candidate routine |
| `0x1CFBD8` | `0x1CFAF0` | Calls the size-computation / generic-wrapper routine |

`RAW_MODE=` and the acquisition-size diagnostic are loaded in a separate diagnostic/configuration area near `0x565334` and `0x565748`. Nearby strings include monitor-size and even/odd diagnostic labels. This context is not evidence of a retail user setting or a sensor-capture path.

The `NRW (RAW) processing`, `NRW (RAW) + Basic/Fine/Normal`, and JPEG-copy text remains resource/string evidence. No setting-to-capture transition or output-writing chain was established.

## Determination

The P500 has a stronger RAW/NRW lead than isolated strings alone: a RAW-named routine includes size arithmetic and generic data-operation wrappers, and a separate RAW-read error label is conditionally formatted. However, the data source, buffer semantics, image dimensions, processing operation, and destination remain unresolved.

**P500 reference conclusion:** a possible RAW/NRW-related data or processing path exists.  
**P510 conclusion:** unknown; no P510 firmware evidence supports a RAW path or capture capability.

See the [callgraph](P510-Phase5B-P500-RAW-callgraph.md), [buffer analysis](P510-Phase5B-P500-RAW-buffer-analysis.md), [NRW file-path analysis](P510-Phase5B-P500-NRW-file-path.md), [Phase 5A baseline](P510-Phase5A-RAW-architecture-analysis.md), and the [targeted Ghidra trace log](ghidra-logs/P500-Phase5B-extended-trace.log).
