# Phase 5B - P500 RAW/NRW Callgraph Evidence

**Scope:** P500 reference primary code section only; file-offset-oriented addresses  
**Source hash:** `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`

## Supported edges

| Source offset | Target offset | Evidence and interpretation |
|---|---|---|
| `0x1CF190` | `0x1CF8B8` | ARM `BL` target calculation; enters a bounded status/error formatter |
| `0x1CF860` | `0x1CF8B8` | ARM `BL` target calculation; second entry to that formatter |
| `0x1CFBC0` | `0x1CFA38` | ARM `BL` target calculation; target is a RAW-named candidate routine, semantics unresolved |
| `0x1CFBD8` | `0x1CFAF0` | ARM `BL` target calculation; enters a routine with dimension-helper calls and size arithmetic |
| `0x1CF984` | `0x614818` via pool `0x1CFC10` | ARM `LDR` literal; loads `ERROR 3 : RAW READ ERROR!!` on a conditional status path |
| `0x1CFAAC`, `0x1CFB00`, `0x1CFB10` | RAW/DATA string pool | ARM literal references to `RAW` and `DATA%d` tokens |

The direct-call findings are raw ARM branch-word calculations against the offset-mapped P500 section. They identify candidate edges but do not establish runtime addresses or higher-level API semantics.

## Partial data-operation path

The bounded routine entered at `0x1CFAF0` has these observed operations:

1. Calls `0x86314` using indices 0 and 1; the values are multiplied.
2. Computes the product multiplied by 10 and divided by 8.
3. Passes `44` and a stack pointer to `0x2DF08C`.
4. Calls `0x2DF0E0` with the computed size and an argument formed from an index and `0x40000000`.
5. Releases through `0x2DF0B0`.

The relevant wrapper calls appear in the raw call scan at `0x1CFAC4`, `0x1CFB78`, `0x1CFB9C`, `0x1CFAE4`, and `0x1CFBA4`. These wrapper and callee roles are not identified. Do not label them as file-open/read/write, sensor-buffer, or allocator APIs without additional evidence.

## Status/error path

At `0x1CF8B8`, conditional status tests select among error labels for status read, buffer size, RAW read, folder read, file read, and RGB read. The selected text is passed with an output-buffer pointer to `0x537BB0`; the helper's exact behavior is unknown. This is a diagnostic path, not a proven RAW data-flow edge.

## NRW/NEF type-table references

Separate ARM literal loads refer to a type-name sequence:

| Load site | Entry |
|---|---|
| `0x4A24F8` | `RAW` |
| `0x4A2520` | `NEF` |
| `0x4A2534` | `NRW` |

These are references into a file-type/name table. No verified edge connects this table to the RAW-named routine, a capture handler, or a file writer.

## Unproven edges

No evidence completes a chain from sensor readout through a confirmed RAW buffer, processing, JPEG encoding, and NRW/NEF/JPEG file creation. The following remain unknown:

- The meaning of the two values returned by `0x86314`.
- The functions behind wrappers `0x2DF08C`, `0x2DF0B0`, and `0x2DF0E0`.
- Whether `0x40000000 + 4 × index` denotes a buffer, file/resource handle, address, or another identifier.
- Whether the size calculation is consumed as a transfer length, buffer capacity, or another quantity.
- Any connection from these operations to sensor output or a user-selectable format.

No corresponding P510 callgraph exists; P500 edges must not be transferred to the P510.
