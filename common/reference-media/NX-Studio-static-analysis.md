# NX Studio Installer Static Analysis

Analysis date: 2026-11-18

## Status update

- **CONFIRMED** — The NX Studio investigation is paused at the user's direction. Do not spend additional time attempting to unpack or execute the installer at this stage.
- **CONFIRMED** — Preserve the original installer and its recorded hashes for possible future investigation.
- **IMPORTANT LIMIT** — The accessible launcher did not expose a P510 model database, USB VID/PID, PTP definitions, firmware binaries, or camera communication libraries. The main application payload was not accessible through the current read-only 7-Zip inspection. Absence of P510 strings or files in the launcher must **not** be interpreted as evidence that NX Studio itself lacks P510 or other Nikon camera definitions.
- **CONFIRMED by direct owner observation** — The physical P510 displays Firmware Version 1.0 in its Firmware version menu. This does not establish an internal build identifier, processor architecture, compatibility with P500/P520 firmware, or whether a newer P510 release exists. The camera remains on Version 1.0; see [P510-physical-camera-observations.md](../../../analysis/P510-physical-camera-observations.md).

## Scope and handling

- **CONFIRMED** — The reference installer is `reference-media/software/NX-Studio/S-NXSTDO-011100WF-ALLIN-ALL___.exe`.
- **CONFIRMED** — The original installer was not modified or executed. No NX Studio software was installed, no camera was connected, and no Ghidra analysis was performed.
- **CONFIRMED** — SHA-256, SHA-1, and MD5 are recorded in [NX-Studio-installer-hashes.txt](../../../checksums/NX-Studio-installer-hashes.txt). SHA-256 matched before and after 7-Zip inspection and extraction.
- **CONFIRMED** — The requested output and first-level extracted PE data are under `reference-media/analysis/NX-Studio/`.

## Installer identity and signature

| Property | Result |
|---|---|
| Exact filename | `S-NXSTDO-011100WF-ALLIN-ALL___.exe` |
| Size | 263,118,416 bytes |
| PE type | PE32, x86 (I386), Windows GUI |
| File version | 1.11.0.30000 |
| Product version | 1.11.0.30000 |
| Company / product | Nikon Corporation / NX Studio |
| File description | Setup Launcher NX Studio |
| Additional launcher metadata | InstallShield Setup Suite Launcher Unicode, internal version 29.0.111 |
| Signature | **CONFIRMED — Valid** using Windows `Get-AuthenticodeSignature`; signature verified |
| Signer | NIKON CORPORATION; issued by DigiCert Trusted G4 Code Signing RSA4096 SHA384 2021 CA1 |
| Timestamp certificate | Present; DigiCert SHA256 RSA4096 Timestamp Responder 2025 1 |

The signing certificate's `NotAfter` date is 2026-10-10, before the analysis date. Windows nevertheless reported the Authenticode signature as **Valid**, and a timestamp certificate was present. The precise signing timestamp was not independently recovered.

The x86 architecture applies to the setup launcher only; it does not establish the architecture of the NX Studio application payload.

## 7-Zip container inspection

- **CONFIRMED** — Existing 7-Zip 25.01 can parse and extract the launcher's PE sections without executing it.
- **CONFIRMED** — 7-Zip identifies the file as `Type = PE`, not as a directly browseable ZIP/CAB/MSI or other ordinary archive.
- **CONFIRMED** — The PE contains a 261,273,768-byte overlay at file offset `0x1BFC00`. Its first bytes are `49 53 53 65 74 75 70 53 74 72 65 61 6D 00 02 01`, ASCII `ISSetupStream` followed by binary version/header bytes.
- **LIKELY** — This overlay is an InstallShield Setup Suite stream. A direct 7-Zip listing attempt on the extracted overlay failed with “Cannot open the file as archive”; 7-Zip could not list its inner files.
- **CONFIRMED** — 7-Zip extracted 21 PE section/resource entries, totaling 263,117,155 bytes, to `reference-media/analysis/NX-Studio/extracted/`. This is a structural extraction of the PE, **not** extraction of the InstallShield application payload.
- **UNKNOWN** — The inner contents of the InstallShield stream, including any NX Studio application files or databases, remain unavailable with the existing 7-Zip extraction capability. No additional tools were installed or downloaded.

### Complete inventory of extracted entries

| Relative path under `extracted/` | Size (bytes) | Static identification |
|---|---:|---|
| `.text` | 1,137,258 | PE code section |
| `.orpc` | 418 | PE RPC-related section |
| `.rdata` | 377,080 | PE read-only data section |
| `.data` | 22,528 | PE initialized writable data |
| `.didat` | 248 | PE delay-import data |
| `.reloc` | 94,980 | PE relocation data |
| `.rsrc_1` | 372 | Additional PE resource data |
| `.rsrc\0\version.txt` | 1,888 | Nikon launcher version resource |
| `.rsrc\1033\version.txt` | 1,868 | Flexera/InstallShield version resource |
| `.rsrc\1033\string.txt` | 64 | SetupSuite resource strings |
| `.rsrc\1033\TYPELIB\1` | 26,756 | Type library resource |
| `.rsrc\0\ICON\1.ico` | 152,126 | Icon resource |
| `.rsrc\1033\ICON\1.ico` | 1,150 | Icon resource |
| `.rsrc\1033\ICON\2.ico` | 4,286 | Icon resource |
| `.rsrc\1033\ICON\3.ico` | 9,662 | Icon resource |
| `.rsrc\0\GROUP_ICON\100` | 20 | Group-icon resource |
| `.rsrc\1033\GROUP_ICON\100` | 48 | Group-icon resource |
| `.rsrc\0\MANIFEST\1` | 1,331 | PE application manifest |
| `.rsrc\1033\MANIFEST\1` | 640 | PE application manifest |
| `CERTIFICATE` | 10,664 | Authenticode certificate data |
| `[0]` | 261,273,768 | Opaque InstallShield stream; not recognized as an archive by 7-Zip |

The extracted items are PE sections, metadata, icons, manifests, a type library, signature data, and the opaque installer stream. No actual NX Studio DLL, EXE, SYS, INF, DAT, BIN, DB, XML, JSON, INI, CFG, ZIP, CAB, or MSI payload was extracted. This statement describes only the first-level PE extraction; it does not establish that such files are absent from the inaccessible InstallShield stream.

## Static strings and structures

Readable metadata and strings in the launcher/PE resources include:

- `Setup Launcher NX Studio`, `NX Studio`, `Nikon Corporation`, and `Copyright 2020 Nikon Corporation`.
- `InstallShield`, `Setup Suite Launcher Unicode`, `SetupSuite`, internal version `29.0.111`, and build number `210554`.
- Generic InstallShield bootstrap, maintenance, reboot, and suite-update terminology.
- The PE application manifest requests administrator execution for one manifest resource. The installer was not run.

ASCII and UTF-16LE printable-string scans were performed against the installer bytes, including the overlay. No intact readable occurrence of `P510`, `COOLPIX`, `firmware`, `firmware.bin`, `firmware version`, `updater`, `VID_`, `PID_`, `NPROG`, `NDATA`, `NLIPI`, `SFIRM`, `SG583`, `ViewNX 2`, `Nikon Transfer`, or `Nikon Transfer 2` was identified in the launcher-readable strings. Incidental short character fragments in binary data were not treated as strings or protocol evidence.

- **CONFIRMED** — The readable update/maintenance strings concern the InstallShield setup suite; they do not identify a camera firmware updater.
- **UNKNOWN** — String searches cannot establish absence inside compressed or otherwise encoded InstallShield payload data.
- **IMPORTANT LIMIT** — The inspectable layer is the setup launcher, not the main NX Studio application. No conclusion about model support or camera definitions in NX Studio itself follows from the launcher's contents.
- **CONFIRMED** — No installer filenames were exposed by the PE extraction beyond PE sections and resources. No model database, camera capability table, camera communication library, or camera firmware component was exposed.

## Findings by value

| Classification | Findings |
|---|---|
| **HIGH VALUE** | None in the PE launcher extraction for P510 communication or firmware research. |
| **POTENTIALLY USEFUL** | Installer version, Nikon publisher metadata, and signature data provide provenance for this NX Studio reference package. |
| **GENERAL NIKON INFRASTRUCTURE** | Nikon-branded InstallShield setup launcher and generic suite bootstrap/maintenance/reboot strings. No camera-specific infrastructure is exposed. |
| **UNRELATED** | Generic InstallShield suite-update, install-maintenance, and reboot behavior; this is not evidence of camera firmware-update functionality. |
| **UNKNOWN** | Inner NX Studio payload contents, including whether it contains model tables, PTP/MTP implementations, camera libraries, or firmware-related components. |

## Conclusion

The installer is a validly signed Nikon NX Studio 1.11.0.30000 x86 InstallShield launcher. 7-Zip can extract its PE structure but cannot browse the `ISSetupStream` payload. The current extracted files are therefore insufficient to assess NX Studio's camera-model database or camera communication implementation. Further payload inspection would require an InstallShield-stream-capable tool; none was installed or used.

No launcher component is recommended as a P510-focused Ghidra target. The outer launcher is generic InstallShield infrastructure, and no Nikon camera-communication DLL or executable was exposed.
