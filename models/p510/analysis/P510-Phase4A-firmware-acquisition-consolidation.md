# P510 Phase 4A — Offline Firmware-Acquisition Evidence Consolidation

**Status: COMPLETE — OFFLINE CONSOLIDATION ONLY**  
**Research date:** 2026-11-20

No P510 communication, USB attachment, PTP operation, property query, firmware retrieval, update/service-mode entry, or camera disassembly occurred. No P500/P520 binary or original media file was modified. No external page was fetched and no software/tool was downloaded or installed in this phase.

## Executive conclusion

No authentic P510 firmware artifact is currently present in the project. Specifically, there is:

- no verified official P510 updater/package;
- no payload extracted from an authenticated official P510 updater;
- no exact on-device P510 firmware image obtained by a validated read-only method.

`firmware/original/P510` is empty. The only firmware packages and extracted firmware payloads in the workspace are the P500 and P520 references; they are not P510 firmware. The locally held Nikon NX Studio installer is desktop software, not an identified firmware updater. The P510 original ISO contains manuals only.

The strongest next route is targeted archival recovery of the already-recorded official Nikon P510 Download Center URL, product identifier `55`, and its historical Nikon-domain download links. If that produces no verified package or release history, request confirmation from Nikon or an authorized Nikon service channel. This phase did not perform that external research.

## 1. Repository audit and acquisition timeline

### Materials reviewed

The audit covered the existing P510 acquisition report and known-facts file; P510 manual/ISO analysis and checksum records; Nikon firmware-tools source audit; all Phase 3C reports; P500/P520 package, payload, section, and string-reference reports; local Nikon desktop-software analysis and installer records; local firmware/media inventories; and existing scripts, logs, URLs, and metadata.

Relevant records include:

- [P510 firmware-acquisition research](P510-firmware-acquisition-research.md)
- [P510 known facts](P510-known-facts.md) and [physical-camera observations](P510-physical-camera-observations.md)
- [P510 disc/manual analysis](P510-disc-manual-analysis.md) and [reference-media hashes](../checksums/P510-reference-media-hashes.txt)
- [Nikon firmware-tools source audit](../../../common/tools/nikon-firmware-tools-source-audit.md)
- [P500/P520 package comparison](../../../comparisons/P500-P520-comparison.md), [payload comparison](../../../comparisons/P500-P520-payload-comparison.md), and [payload analyses](../../p500/analysis/P500-payload-analysis.md) and [P520-payload-analysis.md](../../p520/analysis/P520-payload-analysis.md)
- [Phase 3C-5B physical GetDeviceInfo report](P510-Phase3C5B-physical-GetDeviceInfo.md), [Phase 3C-6](P510-Phase3C6-DeviceInfo-analysis.md), [Phase 3C-7](P510-Phase3C7-offline-source-reconciliation.md), and [Phase 3C-8](P510-Phase3C8-unresolved-code-correlation.md)
- [NX Studio P510 findings](NX-Studio-P510-findings.md), [NX Studio static analysis](../../../common/reference-media/NX-Studio-static-analysis.md), and [installer hashes](../../../common/checksums/NX-Studio-installer-hashes.txt)

The project inventory contains no saved archived Nikon HTML, P510 firmware URL list, P510 updater, P510 firmware payload, or third-party P510 firmware binary. The existing scripts are a constrained `GetDeviceInfo` client and its offline validator; neither implements storage, memory, or firmware retrieval. The local tools directory and backups directory are empty. No separate ViewNX 2 installer is present.

### Timeline and route state

| Research record / period | Route investigated | Result relevant to acquisition |
|---|---|---|
| P510 manual and original-media analysis | Camera documentation and supplied ISO | The ISO is a documentation disc with `INDEX.pdf` and 25 localized manuals. It contains no executable, driver, updater, firmware, or other non-PDF payload. The separate English manual documents a firmware-version display, but not a camera-firmware update or dump procedure. |
| Earlier P500/P520 reference-package work | Updater/container comparison and payload analysis | P500 and P520 have different model identifiers, package sizes, headers, payload sizes, and internal visibility. Their package paths are useful only as reference conventions. |
| 2026-11-18 | Owner observation and NX Studio static analysis | The P510 menu displays Version 1.0. NX Studio 1.11.0.30000 is a Nikon-signed desktop-software installer, but only its outer InstallShield launcher was inspectable; its main application payload remains opaque. |
| 2026-11-19, recorded in the acquisition report | Official page, archives, Nikon tooling, standard PTP, SD-card, and hardware-method review | The current Nikon Download Center page for product `55` listed a reference manual and no body-firmware package. No historical package or direct firmware-read method was verified. The report recommended official Nikon/authorized-service inquiry and offline archive research. |
| Phase 3C-1 through 3C-5E | PnP/USB identification, transport safety, and one narrowly authorized DeviceInfo capture | Physical VID/PID `04B0:0223` and the standard Still Image/PTP interface were confirmed. The only PTP operation transmitted was standard `GetDeviceInfo (0x1001)`, which returned `PTP_OK (0x2001)` at transaction ID 1 without opening a PTP session. No storage, property, memory, or firmware operation occurred. |
| Phase 3C-6 through 3C-8 | Offline DeviceInfo and code correlation | The raw capability dataset was independently decoded; unknown vendor codes remain unresolved. Phase 3C-8 found P500-only property-like registration evidence for `0xD280`/`0xD303`, not P510 behavior. |
| Phase 4A, 2026-11-20 | Offline evidence consolidation and local-media rescan | No new P510 package or acquisition mechanism was found. PTP capability discovery is recorded as paused/complete for now; direct extraction remains blocked. |

### Current local file inventory

- **P510 originals:** `reference-media/original/Nikon Coolpix P510.iso` and `reference-media/original/P510_EN.pdf`; both match [their recorded checksums](../checksums/P510-reference-media-hashes.txt).
- **Nikon desktop software:** `reference-media/software/NX-Studio/S-NXSTDO-011100WF-ALLIN-ALL___.exe`; installer SHA-256 `3E50B4CD3CE0CBD467F2E59D864DCF6A34C1A4CE28DD381348D4BA29B55D0075`.
- **Firmware reference packages only:** `firmware/reference/P500/F-P500-V11W.exe` and `firmware/reference/P520/F-P520-V11W.exe`, with extracted P500/P520 payloads under `firmware/extracted`.
- **No P510 firmware:** no file exists under `firmware/original/P510`, `firmware/extracted/P510`, or `firmware/modified/P510`.
- **No unverified P510 firmware binary:** prior generic third-party search results did not produce a downloaded or locally stored package.

The P510 ISO SHA-256 is `0C9D5D047FD29789BA51698FFDF9BAED94FA11522806636C0C621D0A690AA6E9`; `P510_EN.pdf` SHA-256 is `0CF36A5602EE572C8AB258E7AE33A45F9AFB5A1B046AE1022DF7C21089AC61A2`. Both were rechecked after this phase's read-only audit and match the checksum record. The NX Studio installer also matches its recorded SHA-256. P500/P520 source and extracted hashes remain in their model-specific checksum records.

## 2. Authenticity classes and current holdings

Only categories A–C can ultimately qualify as authentic P510 firmware.

| Class | Definition | Current project evidence | Authentic P510 firmware now? |
|---|---|---|---|
| **A** | Official Nikon P510 firmware updater/package | No P510 updater filename, download identifier, or package has been verified or found locally. | **No** |
| **B** | Firmware payload extracted from an authenticated official Nikon P510 updater | No qualifying P510 updater exists locally; therefore no authenticated P510 payload has been extracted. | **No** |
| **C** | Exact on-device P510 firmware obtained through a separately validated read-only method | No such method is validated and no firmware dump exists. `GetDeviceInfo` did not read firmware memory. | **No** |
| **D** | Firmware/package from another Nikon model | P500 and P520 packages and extracted payloads are present under their reference-only directories. | **No — reference only** |
| **E** | Unverified third-party binary claimed to be P510 firmware | Generic third-party search-result claims were not verified or downloaded; no such binary is present locally. | **No — untrusted lead only** |

The user-provided P500/P520 packages remain model-specific reference material. Their contents must never be treated as compatible P510 firmware or used to synthesize a P510 image.

## 3. P510 update history: confirmed versus unknown

| Field | Existing evidence | Status |
|---|---|---|
| Installed version | Owner directly observed **Firmware Version 1.0** in the P510 menu. | **CONFIRMED installed version only** |
| PTP `DeviceVersion` | Physical P510 returned the text `V1.00` in DeviceInfo. | **CONFIRMED reported text; equivalence to the menu field is UNKNOWN** |
| Factory/original version | No factory image, release history, or first-sale firmware record was found. The current 1.0 observation does not show whether the camera was ever updated. | **UNKNOWN** |
| Later P510 firmware versions | No later version has been verified in the project. The current product page has no body-firmware entry, but historical completeness is unknown. | **No later version confirmed; UNKNOWN whether any existed** |
| Official P510 updater/package filename | No filename was verified. `F-P510...` is only a search prefix, not a discovered Nikon filename. | **UNKNOWN** |
| Official P510 download/support identifier | Current page path is `/en/products/55/COOLPIX_P510.html`; `55` is the observed product-page identifier, not a firmware-download ID. | **Current product page identified; download ID UNKNOWN** |
| Historical Nikon download URL / redirect / CDN path | No historical updater URL, redirect, or CDN path is preserved in the project. | **UNKNOWN** |
| Release notes, publication date, supported OS | No P510 firmware release notes, updater metadata, or OS requirements were found. The manual's February 2012 PDF dates are not firmware-release dates. | **UNKNOWN** |
| Firmware payload filename / header / version string | No P510 payload exists locally. `P510Update\firmware\firmware.bin` is an unverified naming hypothesis based only on P500/P520. | **UNKNOWN** |
| Firmware checksum/signature | No P510 package or payload exists to hash or authenticate. | **UNKNOWN** |

The P510 manual's `Firmware version` menu displays a version but documents no camera-firmware update procedure in the passages/index reviewed. Its `Update failed` message and SD-card instructions refer to A-GPS data, not camera firmware. The manual mentions a `ViewNX 2 Installer CD` in the camera package illustration, but the local P510 ISO is a manual disc; whether a separate software disc was supplied is unknown.

### Exact Nikon URL currently preserved

The only exact P510 Nikon support/download URL recorded by prior research is:

`https://downloadcenter.nikonimglib.com/en/products/55/COOLPIX_P510.html`

The 2026-11-19 page retrieval found the P510 product page and English Reference Manual but no body-firmware updater, firmware release note, updater filename, or firmware download ID. No archived snapshot of this page or historical direct-download URL was found in the local project. No external archival search was performed in Phase 4A.

## 4. Historical download artifacts and local identifier search

The local record contains no P510-specific `.exe`, `.zip`, `.dmg`, `.bin`, `.dat`, updater URL, redirect, CDN link, archived HTML, or temporary extraction name. Exact strings preserved for nearby-model comparison are **not** P510 artifacts:

- P500 package: `F-P500-V11W.exe`; embedded path `P500Update\firmware\firmware.bin`.
- P520 package: `F-P520-V11W.exe`; embedded path `P520Update\firmware\firmware.bin`.
- P500 payload header: `LENGTH=7471104 SG583 VER=v583-80 DVR=1.10 SUM=765951917 NPROG NDATA NLIPI SFIRM`.
- P520 payload prefix: `P520`; version text `Ver.1.1`.
- NX Studio desktop-software installer: `S-NXSTDO-011100WF-ALLIN-ALL___.exe`; launcher version `1.11.0.30000`.

The `V11W` package-name suffix is not interpreted as a P510 release version. Neither the P500 `DVR=1.10` header nor P520 `Ver.1.1` is evidence about P510. No P510-specific archive filename or version string was recovered.

### Offline search of present local media

| Local material | Identifier/search result | Acquisition significance |
|---|---|---|
| P510 ISO | ISO volume labels are `COOLPIX_P510` and `COOLPIX P510`; Joliet inventory contains `INDEX.pdf` and 25 localized `P510RM_EU(...)01.pdf` files. Every inventoried file begins `%PDF-1.4`. | Complete directory/sector inventory found no executable, updater, driver, firmware, or non-PDF payload. Raw token hits in a disc/manual are not firmware evidence. |
| Separate P510 English manual | `P510_EN.pdf`, 260 pages; includes P510 model text and the `Firmware version` menu documentation. | The manual does not give a firmware package name, download URL, firmware version, dump method, or camera-firmware update procedure. |
| NX Studio installer and extracted launcher sections | Exact local installer name/version are above. Existing ASCII/UTF-16LE string scans found no intact `P510`, `COOLPIX`, `firmware`, `firmware.bin`, `updater`, `VID_`, `PID_`, or P510 model-table string in the inspectable launcher layer. | Its inaccessible InstallShield application payload remains **UNKNOWN**; the launcher findings do not establish that the full NX Studio application lacks camera support. |
| P500/P520 updater and extracted payload files | No P510 model string or P510 updater path was found in the local reference binaries by the Phase 4A identifier scan. Their known paths and headers identify P500/P520. | Useful only as a packaging recognition profile; not a P510 candidate. |
| Nikon firmware-tools source tree | Two duplicate Wireshark patches identify packed ID `0x04b00223` as “Nikon Coolpix P510”; source has no P510 camera-model profile. Generic Nikon utilities select by VID and include nontrivial service/memory/write paths. | USB identity is not firmware support or an acquisition method. Do not execute NikonDump/NikonFlags or their service/memory routines. |
| Scripts, logs, checksums, and project notes | The local client is limited to the single standard `GetDeviceInfo`; logs record the already completed transaction. No URL list, firmware dump, or updater extraction is present. | No acquisition route is implemented by the local PTP client. |

The identifier rescan used `04B0`, `0223`, `04B0:0223`, packed `04b00223`, `P510`, `COOLPIX P510`, and `NIKON DSC COOLPIX P510` against local text and media. A separate broad-string sweep included `firmware`, `update`, `firm`, `bin`, and `dat`. The confirmed hardware ID is `04B0:0223`; `P5100` is a different model and must remain excluded. Generic `bin`/`dat` byte-string hits in the ISO, PDFs, or opaque package data are not treated as firmware/package evidence. The parsed ISO directory inventory and actual model-specific filenames are controlling; any identifier occurrence in PDF/ISO/package data must be interpreted in its file/structure context.

## 5. P500/P520 updater-family recognition profile — reference only

| Feature | P500 reference | P520 reference | What it can establish for P510 |
|---|---|---|---|
| Outer package | `F-P500-V11W.exe`, 4,892,776 bytes, PE32 x86; SHA-256 `CA83DDCCD4B3E4CEBAA5C72BD65959F70C1138E3E6E2A273E14DF142C31C99CD`. | `F-P520-V11W.exe`, 74,551,288 bytes, PE32 x86; SHA-256 `CFDE64DD155C6DFA6FF6BD74AD807D7A3F615938DCA2190D72A075C8519E6DB2`. | These are Windows-host package properties, not camera architecture or P510 identity. |
| Wrapper/container observations | RAR4-shaped overlay begins at `0x19400`; embedded path string `P500Update\firmware\firmware.bin`. | RAR4-shaped overlay begins at `0x16A00`; embedded path string `P520Update\firmware\firmware.bin`. | The similar path format is a naming convention only. It does not prove a P510 package or internal format. |
| Extracted payload | 14,614,648 bytes; SHA-256 `80A297C8B4B77731EB2B3B5DC23D905D557A0052049402364B11A1F7849779B4`; archive CRC-32 `D5CC5508`; visible `SG583` multi-record header and P500-specific sections. | 81,264,928 bytes; SHA-256 `631A4C6AB34E3BE5C7EE1153AD1A7D93986DA2853C79F572B63A3E23129B979C`; archive CRC-32 `1DFDC34C`; `P520` / `Ver.1.1` prefix followed by an opaque, near-maximum-entropy region. | No P510 header, key, component boundary, architecture, or checksum pattern has been established. |
| Integrity/authentication | Existing extraction passed the reported RAR CRC check. The PE contains a certificate-table directory, but signature validity was not checked. | Existing extraction passed the reported RAR CRC check. The PE contains a certificate-table directory, but signature validity was not checked. | CRC is not source authentication. No P510 signature/authentication profile can be inferred. |

The common RAR lead-in and shared installer strings support a similar P500/P520 Windows package pattern, but the internals differ substantially. The packages are user-provided references and are not treated as P510 firmware. Do not copy, combine, rename, or flash their contents as P510 firmware.

### Minimum recognition criteria for a future P510 candidate

1. Establish an official Nikon source chain or authenticated archived Nikon page naming **COOLPIX P510**, not P5100, P500, P520, D5100, or D5200.
2. Preserve the exact source URL, redirect chain, package filename, retrieval date, size, and cryptographic hash before inspection.
3. Confirm that package metadata/content is P510-specific; filename resemblance or a `P510` string by itself is insufficient.
4. If extracting a payload, preserve the original updater, record hashes, and establish that the payload came from that authenticated P510 updater. Do not infer the installed camera image is byte-identical to an update payload.
5. Treat any P500/P520-shaped `P510Update\firmware\firmware.bin` hypothesis as unverified until supported by a real P510 source.

## 6–8. Nikon software, NX Studio, and P510 disc value

### NX Studio

The local installer is a validly signed Nikon NX Studio 1.11.0.30000 x86 InstallShield launcher. Existing read-only extraction exposed PE sections/resources and an opaque `ISSetupStream`, but not the main application files. The launcher scan found no P510 model table, VID/PID, firmware URL, updater package name, or camera-firmware component. Generic InstallShield “suite update” strings concern desktop software installation.

**Assessment:** NX Studio is not presently a demonstrated P510 firmware-acquisition route and is low priority. Whether its inaccessible application payload contains camera-model tables or other Nikon infrastructure remains **UNKNOWN**. Do not resume payload extraction or execute/install NX Studio as part of this phase; revisit only if a verified Nikon source or later approved static-analysis tool makes the inner payload available.

### P510 disc

The original ISO was read-only and parsed directly by sector; it was not mounted, extracted, or executed. Its 26-file inventory contains only `INDEX.pdf` and localized P510 reference manuals. The separate P510 manual records that the package illustration names a `ViewNX 2 Installer CD`, but the locally held ISO itself is not that installer. The manual’s `Update failed`/SD-card update instructions concern A-GPS data, not firmware. The disc therefore has documentation value, but no current firmware-acquisition value.

### Nikon source/tooling and other software

The local Nikon firmware-tools source audit found no P510 `CameraModels` profile, firmware key/container definition, or P510 dump procedure. Its USB/PTP table lists the P510 product identity only. `NikonDump` includes model-specific DSLR EEPROM/service/address-space routines (including FE31/FE34 memory reads and write-capable paths); it is not P510-specific and is not a validated read-only P510 firmware method. It must not be used on the P510.

The local source records for libgphoto2 describe standard PTP behavior and selected other Nikon models; they do not establish P510 firmware access. No separate Nikon Transfer/ViewNX installer or P510-specific firmware utility was found in the project inventory.

## 9. Acquisition-route matrix

| Acquisition route | Evidence already collected | Authenticity potential | Technical feasibility | Risk to physical camera | Missing information | Next research action | Status |
|---|---|---|---|---|---|---|---|
| Current Nikon support/archive | Current product URL `/en/products/55/COOLPIX_P510.html`; page retrieval listed a manual, no body-firmware entry. | **A/B** if an official P510 package is found. | High for further source/history research. | None for offline research. | Historical listings, package IDs, old direct-download links. | Search archived versions of the exact official URL and product `55`; record exact Nikon-domain links. | Current page checked; historical status unknown. |
| Historical Nikon URLs | No historical updater URL, redirect, or CDN path is preserved. | **A/B** only with an official Nikon source chain or authenticated Nikon archive capture. | Unknown until a URL is recovered. | None for URL research. | Any old support page, redirect, CDN filename, or release ID. | Use the preserved product URL as the archive lookup key; do not infer download paths. | No historical URL found locally. |
| Web/archive recovery | No archive snapshot or archived HTML is present locally; third-party search snippets were not verified. | Potentially **A/B** if an archived Nikon page/package is authenticated. | Moderate; archive completeness and download preservation unknown. | None if page/metadata inspection only. | Snapshot dates, exact filenames, redirect target, source authenticity, package bytes. | Target the exact current product URL and Nikon-hosted links in Phase 4B. | Not performed in Phase 4A. |
| Official updater filename recovery | No `F-P510...` filename or P510 updater ID found. | **A** if confirmed by Nikon or an authenticated Nikon page. | High if official archive/index metadata is accessible. | None. | Filename, release ID/date, OS, package hash. | Search exact P510 model/product ID `55` in official historical catalogs. | No filename verified. |
| P510 original software disc | Local ISO is manual-only; separate manual names `ViewNX 2 Installer CD`. | The ISO is authentic documentation, but contains no firmware (**not A/B/C**). A separate Nikon software disc could provide leads, not firmware by itself. | High to inspect the existing manual; no further disc extraction needed. | None. | Whether a separate software disc exists and its contents. | Ask owner only if another original disc/media is known; do not infer one exists. | Existing ISO fully inventoried; no updater. |
| Nikon desktop software / NX Studio | Local signed NX Studio 1.11.0.30000 launcher; inner InstallShield payload opaque. No other Nikon transfer installer found. | Low as a firmware source; possibly useful metadata only if verified application files are later exposed. | Low with current static artifacts. | None if kept offline; camera communication/update must remain disabled. | Inner payload model tables, services, URLs, updater names. | Keep paused; reconsider only with an approved static-analysis path or a concrete Nikon-source lead. | Low priority; no acquisition route established. |
| Updater-family correlation | P500/P520 PE32/RAR4 patterns, model-specific payload paths and distinct headers are documented. | **D only** for P500/P520; no authenticity as P510. | High for identifying differences in a future verified candidate. | None while static/offline. | Any P510 package to compare against. | Apply recognition criteria only to a P510-authenticated candidate. | Reference baseline complete; no P510 inference. |
| Third-party archived updater | Generic third-party “P510 firmware” claims were seen, but no verified URL/package/hash was preserved or downloaded. | **E** until independently linked to an official Nikon source; could become A/B only after authentication. | Unknown. | High if executed/installed or used to update; none for passive metadata review. | Provenance, model identity, exact bytes, malware/signature status. | Do not use unless a Nikon source chain and independent package identity are established. | No local binary; not recommended as first route. |
| Direct physical-camera extraction | P510 PnP/PTP identity and GetDeviceInfo are confirmed. No documented firmware-read operation or validated read-only dump method exists. | **C** only after a separately validated, exact on-device read-only acquisition. | Unknown/very low; no known mechanism. | Unknown/high; firmware/memory/service operations could alter state or damage camera. | Specific documented read-only mechanism, address/layout, completeness and integrity method. | Keep blocked. Do not design or test a dump procedure from GetDeviceInfo success alone. | **BLOCKED** |
| P500/P520 reference analysis | Packages and extracted payloads exist with model-specific hashes, headers, and paths. | **D only**; never authentic P510 firmware. | Useful for packaging recognition only. | None if analysis stays offline; flashing is prohibited. | P510-specific confirmation. | Retain reference-only labels; do not construct a P510 image. | Available and analyzed; not an acquisition route. |
| Standard PTP / DeviceInfo | One physical `GetDeviceInfo (0x1001)` returned `PTP_OK (0x2001)`, transaction 1, without opening a session. | Not firmware (no A/B/C output). | Proven only for that one standard operation and dataset. | The recorded command succeeded; no firmware access was tested or implied. | Any safe, documented firmware-read mechanism (none known). | Close Phase 3C capability discovery; do not query or probe unknown codes. | **PAUSED/COMPLETE FOR NOW; no firmware acquisition** |

## 10–11. Physical extraction block and Phase 3C preservation

**Direct P510 firmware extraction remains BLOCKED.** A successful standard `GetDeviceInfo` establishes only that the camera returned its PTP DeviceInfo dataset. It does not establish arbitrary memory access, firmware storage visibility, a firmware-read command, or safe behavior for any unknown vendor extension. No physical dump procedure is proposed or executed here.

The NikonDump FE31/FE34 routines found in third-party source target DSLR model maps and coexist with service-mode, state-changing, and write-capable code. The source audit does not establish P510 support or a complete firmware image. These routines are not a reason to test the P510.

**Phase 3C PTP capability discovery is PAUSED/COMPLETE FOR NOW.** Existing Phase 3C reports were preserved and not rewritten. Unresolved codes `0x90A1`–`0x90A3`, `0xD280`, `0xD303`, and image-format code `0xB111` remain documented in the Phase 3C reports. The P500 property-like `0xD280`/`0xD303` evidence remains P500-only; no P510 semantics were added.

## 12. Highest-value next action and Phase 4B recommendation

**Priority 1:** targeted historical/archive research using the exact official Nikon P510 product URL and identifier `55`. Recover snapshots and links from that page, then follow only Nikon-domain updater/download URLs and preserve timestamps, redirects, exact filenames, metadata, and hashes. The present project has the exact product URL but no archived snapshot or historical direct-download URL; this is the highest-value unresolved lead.

**Priority 2:** if archival recovery produces no official record, ask Nikon or an authorized Nikon service channel whether a P510 body-firmware updater ever existed and whether a manufacturer-supported read-only retrieval of the installed Version 1.0 image is available. Do not contact the camera or perform an update/dump.

### Recommended Phase 4B

Conduct the targeted archival research for the exact official Nikon product URL and product ID `55`, then assess any recovered page/package against the recognition criteria in this report. Keep research to page/metadata recovery first; do not download or execute an updater without the required approval. If no authoritative package or read-only service route is confirmed, record the bounded negative result and keep physical extraction blocked.

This recommendation was not executed in Phase 4A.

## Final status

1. **Authentic P510 firmware material currently local:** none. There is no A, B, or C artifact.
2. **Still missing:** any official P510 updater/payload, historical release record, verified download URL/filename, and validated read-only on-device firmware image.
3. **Most promising route:** archival recovery of `https://downloadcenter.nikonimglib.com/en/products/55/COOLPIX_P510.html` and its historical Nikon-domain links; then official Nikon/authorized-service confirmation if needed.
4. **Exact identifiers worth researching next:** listed one per line in [P510-firmware-acquisition-targets.txt](P510-firmware-acquisition-targets.txt). Candidate `F-P510` and `P510Update\firmware\firmware.bin` strings are explicitly unverified patterns, not discovered artifacts.
5. **Another physical-camera operation justified? NO.** Phase 3C is paused/complete for now; DeviceInfo success provides no evidence that a firmware read is possible or necessary.
