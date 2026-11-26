# Phase 5B - P500 RAW Buffer Analysis

**Model:** Nikon COOLPIX P500 reference firmware  
**Input:** `P500-NPROG-primary.bin`, SHA-256 `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`  
**P510 applicability:** None established

## Size calculation

A routine around file offset `0x1CFAF0` calls helper `0x86314` for indices 0 and 1, multiplies the returned values, and calculates:

`value0 × value1 × 10 / 8`

If the helper returns width and height, the arithmetic is compatible with a packed 10-bit-per-sample byte count. The helper's return semantics are not confirmed, however. Consequently this is **a packed-size hypothesis**, not a confirmed width, height, RAW bit depth, frame size, or buffer allocation.

The routine also passes a 44-byte size and stack pointer to wrapper `0x2DF08C`; later it calls `0x2DF0E0` with the calculated size and an indexed argument derived from `0x40000000`, then calls `0x2DF0B0`. The wrappers' exact roles are unknown. The evidence does not establish that the calculated size is used to allocate or read a RAW image buffer.

## Buffer evidence inventory

| Candidate | Evidence | Status |
|---|---|---|
| RAW/pre-JPEG image buffer | No confirmed address, structure, allocator, dimensions, stride, or ownership relationship | **Not identified** |
| `10 bits × value0 × value1 / 8` | Arithmetic in a RAW-named routine; inputs from an unidentified helper | **Possible packed-size calculation; semantics unknown** |
| `0x40000000 + 4 × index` | Argument supplied to an opaque wrapper alongside the computed size | **Identifier/address semantics unknown** |
| JPEG buffer | P500 diagnostic text `JpegBuffer_TopAddrW()` at `0x646216` | **Text-only lead; buffer not mapped** |
| Sensor/CFA/Bayer layout | No confirmed CFA pattern, sensor interface, raw pixel ordering, or sensor-to-buffer edge | **Not identified** |

## Interpretation limits

The arithmetic is compatible with one possible packed-data size calculation but is not sufficient to classify a buffer as RAW. The nearby RAW tokens and the separate `RAW READ ERROR!!` message do not establish that the routine accesses sensor-native samples. Its wrappers could refer to a file, a memory/resource object, an internal device interface, or another service.

No JPEG encoder entry point or data handoff from the candidate routine to JPEG processing was identified. No corresponding buffer evidence exists for the P510.

**Result:** a raw/pre-JPEG buffer was **not identified** in the P500 reference. The P510 buffer status remains **unknown**.
