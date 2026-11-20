# Nikon COOLPIX P510 Project Manifest

**Inventory date:** 2026-11-20  
**Intended repository:** `nikon-p510-research` (private; not initialized or pushed)  
**Purpose:** Preserve project-authored research, first-party P510 captures, source, and integrity records while excluding third-party material that should not be republished.

## Inventory summary

The pre-migration workspace inventory found **334 files**. Categories overlap where an artifact has multiple roles.

| Category | Inventory and preservation decision |
|---|---|
| Project documentation | Phase 1-5 reports, P510 known-facts/status reports, P500/P520 analysis notes, PTP/firmware research, tool records, `README.md`, and project rules. Intended for Git. |
| Source code | `scripts/P510PTPGetDeviceInfo.c`, `scripts/P500Phase5BTrace.java`, and `scripts/Validate-P510PTPGetDeviceInfo.ps1`. Intended for Git; hardware access remains separately gated. |
| Scripts | The PowerShell validator and Java analysis script are project scripts under `scripts/`. No third-party source tree is vendored. |
| P510 captured data | The 293-byte `analysis/P510-GetDeviceInfo.raw.bin`, decoded DeviceInfo, and related transport/stdout/stderr records. First-party research capture; intended for Git. The raw PTP payload contains the camera's device serial field, so keep repository access private and do not reproduce the identifier in reports. |
| Hash/manifest files | Eight existing records under `checksums/`, plus this migration hash file. Existing hash values are preserved verbatim; new hash records do not rewrite historical manifests. Intended for Git. |
| Reference firmware | 11 P500/P520 updater and extracted firmware files. Reference-only and proprietary; excluded from Git. Keep local copies unchanged and preserve existing hashes/provenance. |
| Third-party source | No third-party source-code checkout or vendored library was found. Third-party code/tooling evaluations are project-authored notes; external source snapshots are not included. |
| Downloaded research images | 51 JPG research images: iFixit P510/P500 guide photographs and one seller-provided P510 board image. Excluded because reuse/redistribution rights are not established or are license-restricted. Existing image manifests and source records are retained. |
| Ghidra artifacts | 12 project database files and 99 runtime/cache/state files. Excluded as machine-specific generated state. The separate text logs in `analysis/ghidra-logs/` and the analysis reports remain available for research context. |
| Temporary/generated files | 68 `.tmp` files, two compiled PTP executables in `build/`, extracted NX Studio PE content, and other local cache/build artifacts. Excluded; not deleted. |
| Secrets/sensitive data | The enhanced privacy audit replaced local WSL account-name and Windows profile-path username occurrences with `<LOCAL_USER>`. No password, token, API key, private-key block, authorization header, cookie/session credential, private email address, or Windows credential command was found in the repository-bound files. The raw DeviceInfo serial is a device identifier, not an authentication credential; the raw capture is retained as first-party data. |
| Other | Empty `backups/`, `docs/`, and `tools/` directories; root `.gitignore`; existing `README.md`; `.github/copilot-instructions.md`; ignored `build/` outputs. |

The audit scanned text files for credential patterns without printing matched values. The named WSL/USB setup reports were included. The audit did not treat project guidance mentioning passwords or credentials as evidence of a stored secret.

## Research areas to preserve

### Phase 3 - PTP and physical capture

Phase 3 documents the USB identity/interface, PTP capability research, bounded client design/validation, and the single successful standard `GetDeviceInfo (0x1001)` exchange. The raw capture is 293 bytes, returned `PTP_OK (0x2001)`, transaction ID 1, and is accompanied by decoded and transport records. Only the documented operation was sent; unknown advertised values remain unresolved. Start with [P510-known-facts.md](analysis/P510-known-facts.md), [Phase 3C DeviceInfo analysis](analysis/P510-Phase3C6-DeviceInfo-analysis.md), and the [physical capture report](analysis/P510-Phase3C5B-physical-GetDeviceInfo.md).

The capture should be reviewed for device-identifier exposure before adding collaborators. The raw file is preserved unchanged; its SHA-256 is recorded in the existing research record and in `GITHUB-MIGRATION-MANIFEST.sha256`.

### Phase 4 - Firmware acquisition and board documentation

Phase 4 records public firmware/archive searches, Nikon-page evidence, board-image research, and acquisition blockers. No authentic P510 firmware is available; `firmware/original/P510/` remains empty. Public firmware and board-documentation paths are exhausted for now. Read [P510-Phase4-final-status.md](analysis/P510-Phase4-final-status.md) and the related Phase 4 reports in `analysis/`.

### Phase 5 - Enhancement feasibility

- **RAW:** P500-only evidence supports a possible RAW/NRW-related path; P510 feasibility remains unknown.
- **Focus peaking:** reference evidence is insufficient; P510 feasibility remains unknown.
- **Clean HDMI:** reference evidence is insufficient; playback-only behavior is unestablished; P510 feasibility remains unknown.

Read [P510-Phase5-final-status.md](analysis/P510-Phase5-final-status.md) and [P510-enhancement-research-checkpoint.md](analysis/P510-enhancement-research-checkpoint.md). P500/P520 conclusions are never P510 facts without independent evidence.

### Source, validation, hashes, and manifests

- Project source and scripts are under `scripts/`.
- Existing SHA-256 records are under `checksums/`; do not change recorded values as part of migration.
- `GITHUB-MIGRATION-MANIFEST.sha256` records current hashes for intended repository-bound files before the first commit. It excludes itself because a file cannot contain its own stable hash.
- Two locally compiled PTP executables are in ignored `build/`; they are reproducible outputs, not source-of-truth artifacts.
- Ghidra project/runtime state is ignored; project-authored analysis notes, scripts, and text evidence remain.

## Excluded third-party artifacts

Excluded files remain on the local workstation. The existing project hash manifests and source-image reports are authoritative for complete per-file records; hashes below are copied from those records, not recalculated for this inventory.

| Artifact | Size | Recorded SHA-256 | Source/provenance and decision |
|---|---:|---|---|
| `firmware/reference/P500/F-P500-V11W.exe` | 4,892,776 bytes | `CA83DDCCD4B3E4CEBAA5C72BD65959F70C1138E3E6E2A273E14DF142C31C99CD` | Nikon P500 updater reference sample; direct download URL is not preserved in the local record. Excluded; see `checksums/P500-reference-hashes.txt`. |
| `firmware/reference/P520/F-P520-V11W.exe` | 74,551,288 bytes | `CFDE64DD155C6DFA6FF6BD74AD807D7A3F615938DCA2190D72A075C8519E6DB2` | Nikon P520 updater reference sample; direct download URL is not preserved in the local record. Excluded; see `checksums/P520-reference-hashes.txt`. |
| P500 extracted payload and sections | 14,614,648-byte payload; 7 section files | Payload SHA-256 `80A297C8B4B77731EB2B3B5DC23D905D557A0052049402364B11A1F7849779B4`; section hashes in manifest | Derived from proprietary P500 updater; all firmware binaries excluded. See `checksums/P500-section-hashes.txt`. |
| P520 extracted payload | 81,264,928 bytes | `631A4C6AB34E3BE5C7EE1153AD1A7D93986DA2853C79F572B63A3E23129B979C` | Derived from proprietary P520 updater; excluded. See `checksums/P520-reference-hashes.txt` and Phase 1/2 analysis. |
| `reference-media/original/Nikon Coolpix P510.iso` | 464,158,720 bytes | `0C9D5D047FD29789BA51698FFDF9BAED94FA11522806636C0C621D0A690AA6E9` | Nikon P510 documentation disc; local source URL is not recorded. Excluded as a copyrighted disc image. See `checksums/P510-reference-media-hashes.txt`. |
| `reference-media/original/P510_EN.pdf` | 16,879,484 bytes | `0CF36A5602EE572C8AB258E7AE33A45F9AFB5A1B046AE1022DF7C21089AC61A2` | Nikon user/reference manual supplied locally; direct source URL is not recorded. Excluded. See `checksums/P510-reference-media-hashes.txt`. |
| NX Studio installer | 263,118,416 bytes | `3E50B4CD3CE0CBD467F2E59D864DCF6A34C1A4CE28DD381348D4BA29B55D0075` | Nikon-published installer `S-NXSTDO-011100WF-ALLIN-ALL___.exe`; exact retrieval URL is not in the local record. Excluded, not executed; see `checksums/NX-Studio-installer-hashes.txt`. |
| NX Studio PE-section/stream extraction | 21 extracted entries; largest opaque stream 261,273,768 bytes | No separate complete extraction hash manifest | Derived proprietary installer content; excluded under `reference-media/analysis/NX-Studio/extracted/`. Source installer identity/hash and extraction scope are documented in the NX Studio analysis notes. |
| iFixit P510/P500 board-guide photographs | 50 JPG files | Per-image hashes in `checksums/P510-Phase4D-research-image-hashes.txt` | P510 guide: [iFixit Nikon Coolpix P510 Motherboard Replacement](https://www.ifixit.com/Guide/Nikon+Coolpix+P510+Motherboard+Replacement/40287); P500 reference guide: [iFixit Nikon COOLPIX P500 Front Case Replacement](https://www.ifixit.com/Guide/Nikon+COOLPIX+P500+Front+Case+Replacement/37637). P510 guide content is marked CC BY-NC-SA 3.0; excluded rather than republished. Image URLs, dimensions, and descriptions are in `analysis/P510-Phase4D-source-images.md`. |
| Seller-provided P510 board photograph | 1 JPG; 1024x768 | `13395DB7D23BE42F4BC05720932A18AAAD642B1F0BD102D085BA497FF213BA5A` | eBay item [115640102604](https://www.ebay.com/itm/115640102604); original image URL and provenance are in `analysis/P510-Phase4E-new-source-images.md`. No reuse license was established; excluded. |
| Archived Nikon/Wayback HTML page captures | 6 HTML files | Per-file hashes in `checksums/P510-Phase4B-web-capture-hashes.txt` | Official page: [Nikon P510 Download Center](https://downloadcenter.nikonimglib.com/en/products/55/COOLPIX_P510.html); historical snapshots and dates are recorded in Phase 4B notes. Raw page bodies excluded; notes and hashes retained. |

Source URLs absent from local provenance records are explicitly marked as not recorded; no URLs are guessed. Existing notes and hashes are retained so locally held files can be verified without committing them.

## Large-file review

The full local inventory contained:

- **7 files larger than 10 MB**
- **5 files larger than 50 MB**
- **3 files larger than 100 MB**

All files above 10 MB are third-party installers/media or P500/P520 firmware and are excluded by `.gitignore`. No Git LFS configuration is warranted for the planned repository contents. Do not enable Git LFS automatically.

Largest excluded items:

| Local artifact | Approx. size | Git decision |
|---|---:|---|
| Nikon P510 ISO | 442.66 MiB | Exclude |
| NX Studio installer | 250.93 MiB | Exclude |
| Extracted NX Studio opaque stream | 249.17 MiB | Exclude |
| P520 extracted firmware payload | 77.50 MiB | Exclude |
| P520 updater installer | 71.10 MiB | Exclude |
| P510 manual PDF | 16.10 MiB | Exclude |
| P500 extracted firmware payload | 13.94 MiB | Exclude |

## Git migration boundary

The intended Git contents are project-authored research, source/scripts, existing hash records, selected first-party P510 capture data, and minimal repository metadata. `.gitignore` excludes firmware binaries, proprietary/downloaded manuals and installers, third-party images and archived HTML bodies, build outputs, Ghidra databases/cache, temporary files, and credential material.

The repository is **not initialized or pushed**. Review the migration manifest and private-repository access scope before any future commit or publication.
