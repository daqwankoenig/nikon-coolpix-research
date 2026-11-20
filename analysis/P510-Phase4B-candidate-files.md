# P510 Phase 4B - Candidate File Inventory

**Research date:** 2026-11-20  
**Result:** No P510 camera-body firmware candidate file was recovered or downloaded.

| File/name | Source and evidence | Classification | Handling/authenticity |
|---|---|---|---|
| No P510 body-firmware updater/package | No official or archived Nikon page inspected lists a body-firmware updater; no verified third-party package was found | No candidate | No file downloaded; no authenticity claim possible |
| `NML_28A.ee` | Nikon archived A-GPS detail page `https://downloadcenter.nikonimglib.com/en/download/fw/111.html` identifies this as the A-GPS Update File for P510/P520/P330 and D5300 | **NOT P510 FIRMWARE** | Only the page metadata was reviewed. The file itself was not downloaded, hashed, executed, or installed. It updates GPS assistance data, not camera-body firmware |
| `F-P500-V11W.exe`, `F-P520-V11W.exe` and extracted payloads | Existing local P500/P520 reference samples | **NOT P510 FIRMWARE** | Reference-only; not modified or used as P510 candidates |

## Candidate authenticity classes

| Class | Phase 4B result |
|---|---|
| AUTHENTIC OFFICIAL P510 PACKAGE | None found |
| PROBABLY AUTHENTIC | None |
| UNVERIFIED | No candidate body-firmware binary retained |
| NOT P510 FIRMWARE | `NML_28A.ee` by its official Nikon description; all P500/P520 reference packages |
| SUSPICIOUS | No candidate file to assess |

No candidate package was downloaded, so there is no candidate-file manifest, signature report, or candidate SHA-256/SHA-1/MD5 record. Saved Nikon/Wayback HTML research captures and their SHA-256 values are documented in [P510-Phase4B-historical-Nikon-firmware-research.md](P510-Phase4B-historical-Nikon-firmware-research.md) and [P510-Phase4B-web-capture-hashes.txt](../checksums/P510-Phase4B-web-capture-hashes.txt).
