# Nikon COOLPIX P510 - Phase 4 Final Status

**Status date:** 2026-11-20  
**Phase:** 4 - Firmware acquisition research  
**Disposition:** CLOSED for current evidence. No additional acquisition phase is authorized or recommended.

## Executive status

Phase 4 did not obtain an authentic P510 camera-body firmware image or establish a safe, supported way to read one from the camera. Public Nikon/archive firmware searching and the targeted public motherboard/service-documentation search have reached diminishing returns and are **EXHAUSTED FOR NOW**. The project is paused at an evidence-preservation and research-direction decision point.

The P510's physical firmware menu reports Version 1.0, but that is not a firmware binary or build identifier. The successful Phase 3C PTP exchange establishes limited device identity and capability declarations only; it does not establish access to firmware storage.

**No P500/P520 firmware, board, or architecture finding is treated as a P510 fact.** Those models remain reference-only.

## Confirmed acquisition findings

- No authentic P510 firmware image is currently available locally.
- [`firmware/original/P510/`](../firmware/original/P510/) remains empty. No original firmware image was moved, overwritten, or modified.
- No public P510 camera-body firmware updater/package was recovered or downloaded.
- Archived Nikon P510 Download Center pages examined showed A-GPS material but no camera-body firmware package. The examined history includes 16 official product-page captures between 2015-06-14 and 2023-04-07; those entries list A-GPS material, not a P510 body-firmware release.
- `NML_28A.ee` is Nikon A-GPS assistance data for the location-data unit, **not** P510 camera-body firmware.
- Public/archive firmware searching reached diminishing returns. This means the bounded public search is exhausted for now; it does not prove that no historical, regional, private, or service-only package exists.
- Targeted public motherboard/service-documentation research is **EXHAUSTED FOR NOW**. No P510 service manual, schematic, boardview, component-level service utility, useful OEM mainboard part number, or materially new unobscured board view was established.
- P510 processor identity and architecture remain unknown.
- P510 nonvolatile firmware-storage device remains unknown; no firmware-storage candidate was identified.
- No P510 mainboard part number or board revision was established.
- Board markings `280414`, provisional `CMKY-PB2`, and apparent shield mark `2231` remain unexplained.
- No P500/P520 architectural relationship to the P510 has been established.
- No firmware-read mechanism or readout feasibility has been established.

These are findings about the evidence recovered, not claims that missing materials or capabilities can never exist.

## Physical P510 facts to preserve

### Camera and USB identity

- The owner-held physical camera is a Nikon COOLPIX P510.
- The owner observed **Firmware Version 1.0** in the camera's menu. This does not identify a build ID or binary image.
- USB VID/PID: **`04B0:0223`**.
- The camera presents a standard Still Image/PTP interface (`06/01/01`) and product string `NIKON DSC COOLPIX P510-PTP`.
- This identity/interface evidence establishes transport and model metadata, not internal firmware-memory access.

### Successful, bounded PTP `GetDeviceInfo`

Phase 3C-5B successfully sent exactly one standard `GetDeviceInfo (0x1001)` operation with transaction ID `1`. It did not open a PTP session, send `OpenSession`, retry, or execute another advertised operation. The camera returned a 293-byte DeviceInfo payload in a 305-byte data container and `PTP_OK (0x2001)` in a 12-byte response container. Phase 3C-6 independently decoded the payload with no trailing bytes or decode discrepancy.

The decoded fields were:

| Field | Camera-reported value |
|---|---|
| StandardVersion | `0x0064` |
| VendorExtensionID | `0x00000006` |
| VendorExtensionVersion | `0x0064` |
| VendorExtensionDesc | `microsoft.com: 1.0; Nikon PTP Extensions` |
| FunctionalMode | `0x0000` |
| Manufacturer | `Nikon Corporation` |
| Model | `P510` |
| DeviceVersion | `V1.00` |
| CaptureFormats | Empty |
| ImageFormats | `0x3801 0x3001 0x3006 0x3008 0x300D 0xB111 0x3000` |

`DeviceVersion=V1.00` is recorded as reported; it is not assumed to be the camera's full firmware identity or equated with the menu's Version 1.0. The serial number exists in the raw payload and is redacted from human-readable evidence; it is not reproduced here.

The camera advertised these arrays, in device-reported order:

- **OperationsSupported (26):** `0x1001 0x1002 0x1003 0x1004 0x1005 0x1006 0x1007 0x1008 0x1009 0x100A 0x100C 0x100D 0x101B 0x100B 0x100F 0x1023 0x1014 0x1015 0x1016 0x9801 0x9802 0x9803 0x9805 0x90A1 0x90A2 0x90A3`
- **EventsSupported (11):** `0x4001 0x4002 0x4003 0x4004 0x4005 0x4006 0x4007 0x4008 0x4009 0x400A 0x400C`
- **DevicePropertiesSupported (6):** `0x5001 0x5011 0xD280 0xD303 0xD406 0xD407`
- **CaptureFormats:** empty
- **ImageFormats (7):** `0x3801 0x3001 0x3006 0x3008 0x300D 0xB111 0x3000`

These are device-advertised values, not proof that any untested operation works or is safe. Meanings of P510 vendor operations `0x90A1`-`0x90A3`, properties `0xD280` and `0xD303` (and the other unmapped property values), and image-format code `0xB111` remain unresolved. In particular, `0xB111` is **not** established as RAW/NEF. The PTP discovery status is **PAUSED / COMPLETE FOR CURRENT EVIDENCE**.

The early Phase 3C-3 document is a planning/stopped-attempt record; the later Phase 3C-5B report documents the one successful, bounded physical `GetDeviceInfo` operation and is authoritative for the result.

### Physical motherboard evidence

- Public P510 teardown imagery shows the populated side of a P510 motherboard. The central large IC is obscured by thermal material; its identity remains unknown.
- A large Micron-marked package reads `21C22` / `D9MTD`. Third-party code lookup strongly supports Micron `MT47H128M16RT-25E:C` DDR2 SDRAM, but a complete primary-datasheet confirmation is unavailable. This is RAM evidence, **not** firmware-storage evidence.
- The reverse-face seller image is only a strong visual match, not independent proof of seller/model identity. It shows a shielded area; component identities remain unknown.
- No distinct PCB revisions/variants are established.
- No debug/test-pad signal assignment, service interface, or firmware-storage device is established.
- The P510 disc contains user documentation only, not a firmware package, updater, service utility, or driver.

## Donor and working-camera status

### Donor

- **DONOR ACQUISITION: DEFERRED.**
- A donor P510 is technically justified **only if the goal is component identification**—for example, to inspect the specific IC obscured by thermal material or components hidden by the reverse-face shield.
- A donor is **NOT currently justified specifically for firmware extraction** because:
  - firmware storage has not been identified;
  - processor architecture remains unknown;
  - debug interfaces remain unknown; and
  - readout feasibility remains unknown.
- Preferred hypothetical donor characteristics: an intact mainboard; a documented non-board failure such as lens, LCD, or mechanical damage; no corrosion/water damage; and no evidence of prior board harvesting.
- No donor or standalone motherboard was purchased. This report does not authorize a purchase or physical inspection.

### Working camera

**WORKING P510 PHYSICAL INVESTIGATION: NOT JUSTIFIED**

Do not:

- open the camera;
- remove thermal material or shielding;
- probe test pads;
- attempt JTAG/UART;
- attach programmers;
- invoke unknown PTP commands;
- enter undocumented service modes; or
- attempt firmware writes.

The working camera remains off-limits to physical investigation and any additional communication.

## Concrete resume conditions

Reopen firmware acquisition research only when a specific new evidence trigger appears:

1. A genuine P510 firmware/updater package appears.
2. A P510 service manual or schematic appears.
3. An unobscured P510 motherboard image reveals processor markings.
4. An image identifies a P510 nonvolatile-memory device.
5. A verified Nikon P510 mainboard part number is discovered.
6. Credible P510-specific service software is discovered.
7. Technical documentation identifies a P510 firmware-read mechanism.
8. A suitable donor becomes available **and** there is a defined hardware question worth answering.

A generic motherboard image or marketplace listing alone is not a trigger. Do not start another broad acquisition-search phase absent one of these concrete conditions.

## Artifact integrity and evidence inventory

The hashes below are existing records from the Phase 3C/Phase 4 reports and manifests. They were **not recalculated for this final checkpoint**. No project-wide rehash was performed.

### Phase 3C primary capture and transport

| Artifact | Existing SHA-256 / inventory |
|---|---|
| [`P510-GetDeviceInfo.raw.bin`](P510-GetDeviceInfo.raw.bin), 293 bytes | `E867C4FEE60CE314FC6DFF9D9A3300FA950136A279484DB13EADFE2E7C17EF96` |
| [`P510-GetDeviceInfo-decoded.txt`](P510-GetDeviceInfo-decoded.txt) | `599FECA3CAA14F4BB4369CEE88791FE8ABCAC28FFDD979E3A1FCF49D332622FB` |
| [`P510-GetDeviceInfo-transport.log`](P510-GetDeviceInfo-transport.log) | `149A647852B5E5A2D9B10B2292FEE603D76093FF130F3DFDB68D47C065AB4A7F` |
| [`P510-USB-descriptors.txt`](P510-USB-descriptors.txt) | `D966A78CF419CF1428189ADBD9CAC7BBC035DB3A4EE8367869D1F5B46662CC42` |

The raw capture, redacted decode, transport log, and descriptor evidence remain in `analysis/`. The raw payload contains the camera serial number and must be handled as sensitive data.

### Phase 3C hardware-client source and executable records

| Artifact/version | Existing SHA-256 |
|---|---|
| [`scripts/P510PTPGetDeviceInfo.c`](../scripts/P510PTPGetDeviceInfo.c), initial Phase 3C-5A.1 record | `949D57FAB8799BA56D6E847664A98A877FBBFF845EBDCB9F8FBFC485A4849144` |
| [`scripts/Validate-P510PTPGetDeviceInfo.ps1`](../scripts/Validate-P510PTPGetDeviceInfo.ps1) | `19F59204B53ECFA6522C90220DE77F4FF317CF8C6344AB181512AD947C009B22` |
| C source after the Phase 3C-5A.2 offline portability changes | `DE0B903F0A37E449857E3DFACF6E8F23A7999EE3ABFFE3545BE80E8CDCEAAA74` |
| [`build/P510PTPGetDeviceInfo-offline`](../build/P510PTPGetDeviceInfo-offline) | `E5F6305AF37809330FD294CC27B43BC39085F538086B8281BC7A1E067EEF4BB5` |
| C source after the Phase 3C-5A.3 hardware build changes | `0EDEC20AC13B15776DD1E29358BA1301C843688ECFE6167FC2E53D46782D8D09` |
| Earlier hardware executable, Phase 3C-5A.3 | `1C8B778405C07B241AEA84F63C1B1F38E25C0F8E9E1A98B24C787755B93EDA13` |
| Final recorded C source, Phase 3C-5A.4 / 3C-5B | `31A76A18943D416B24E0DF746DCF9E3E1ACFECC948D76B06E2A3C1A073FF11BE` |
| Final recorded [`build/P510PTPGetDeviceInfo-hardware`](../build/P510PTPGetDeviceInfo-hardware) | `4CDAA7F497010A131419420C42D2A980100D21BBB69914482746C619172E6CAA` |

The source and executable hashes are documented in the linked Phase 3C build and physical-execution reports. The hardware-enabled client was narrowly constrained to one standard `GetDeviceInfo`; its recorded successful execution did not establish a firmware-read path.

### Phase 4 acquisition, archive, and board artifacts

| Artifact | Existing SHA-256 / inventory |
|---|---|
| [`P510-Phase4B-web-capture-hashes.txt`](../checksums/P510-Phase4B-web-capture-hashes.txt) | Manifest for six saved Nikon/Wayback HTML captures; individual values below |
| [`P510-Phase4D-research-image-hashes.txt`](../checksums/P510-Phase4D-research-image-hashes.txt) | Per-image SHA-256 entries for 50 downloaded iFixit research images; images and provenance are in [`phase4d-board-images/`](phase4d-board-images/) |
| [`ebay-115640102604-side-b.jpg`](phase4e-board-images/ebay-115640102604-side-b.jpg) | `13395DB7D23BE42F4BC05720932A18AAAD642B1F0BD102D085BA497FF213BA5A` |
| [`P510-Phase4E-research-image-hashes.txt`](../checksums/P510-Phase4E-research-image-hashes.txt) | Manifest for the single Phase 4E reverse-face seller image above |
| Phase 4F visual evidence | No new image retained; the Phase 4E manifest was not changed |

Existing Phase 4B HTML capture hashes:

| Saved capture | Bytes | SHA-256 |
|---|---:|---|
| [`Nikon-COOLPIX-P510-Download-Center-2026-11-20.html`](phase4b-web-captures/Nikon-COOLPIX-P510-Download-Center-2026-11-20.html) | 15,190 | `BE803EEC37FB26A1A25D07387BB7D44FDA60771EFAA363F94B0EB82A1649B390` |
| [`Wayback-2015-06-14-P510-product.html`](phase4b-web-captures/Wayback-2015-06-14-P510-product.html) | 17,423 | `5FECBF907AEC6401D36EDDAC2BA700844415795BE78D010F3B01FB9C49C22B73` |
| [`Wayback-2016-04-21-P510-product.html`](phase4b-web-captures/Wayback-2016-04-21-P510-product.html) | 17,423 | `AA295678E7D044311F980B17A605F5D17B9306F36852799BB5C140346BBCA668` |
| [`Wayback-2016-03-18-A-GPS-details.html`](phase4b-web-captures/Wayback-2016-03-18-A-GPS-details.html) | 11,712 | `F913B7E2ED7F6EA90A46AA3810259ED6589C41711BAA5B2B296FF06452FF2480` |
| [`Wayback-2018-04-05-P510-product.html`](phase4b-web-captures/Wayback-2018-04-05-P510-product.html) | 17,799 | `3AA415EF3B0FF204462A23848916622F6B3D9AFC9D06355EFC49AC64082483B4` |
| [`Wayback-2022-11-29-P510-product.html`](phase4b-web-captures/Wayback-2022-11-29-P510-product.html) | 16,596 | `6397098FD1E01F4BA808139E5930A04EC33DE756BBBCB12A338196C87FFB95B1` |

The captures are stored under [`phase4b-web-captures/`](phase4b-web-captures/). Phase 4A/4C/4D/4E/4F reports, board maps, source-image records, and known-facts notes are preserved as linked research artifacts; no new hashes were calculated for those documents.

### Key reports and records

- Phase 3C physical capture and analysis: [physical GetDeviceInfo report](P510-Phase3C5B-physical-GetDeviceInfo.md), [DeviceInfo analysis](P510-Phase3C6-DeviceInfo-analysis.md), [offline source reconciliation](P510-Phase3C7-offline-source-reconciliation.md), [unresolved-code correlation](P510-Phase3C8-unresolved-code-correlation.md), and [USB descriptor analysis](P510-Phase3C5C-USB-descriptor-analysis.md).
- Phase 4 firmware acquisition: [Phase 4A local inventory](P510-Phase4A-firmware-acquisition-consolidation.md), [Phase 4B Nikon archive research](P510-Phase4B-historical-Nikon-firmware-research.md), and [Phase 4C acquisition-path analysis](P510-Phase4C-firmware-acquisition-path-analysis.md).
- Phase 4 board evidence: [Phase 4D board identification](P510-Phase4D-board-identification.md), [component map](P510-Phase4D-component-map.md), [source-image inventory](P510-Phase4D-source-images.md), [Phase 4E component evidence](P510-Phase4E-component-evidence.md), and [Phase 4F targeted documentation search](P510-Phase4F-targeted-documentation-search.md).
- Consolidated findings: [P510-known-facts.md](P510-known-facts.md).

## Project status

| Workstream | Status |
|---|---|
| **PTP CAPABILITY DISCOVERY** | **PAUSED / COMPLETE FOR CURRENT EVIDENCE** |
| **P510 PUBLIC FIRMWARE SEARCH** | **EXHAUSTED FOR NOW** |
| **P510 PUBLIC BOARD DOCUMENTATION SEARCH** | **EXHAUSTED FOR NOW** |
| **DIRECT FIRMWARE EXTRACTION** | **BLOCKED - NO SUPPORTED READ MECHANISM** |
| **DONOR ACQUISITION** | **DEFERRED** |
| **WORKING CAMERA HARDWARE INVESTIGATION** | **NOT JUSTIFIED** |

## Evidence-supported non-acquisition directions

These are options only. None is automatically selected or executed by this report.

1. **Preserve and catalog the current P510 evidence base.** Maintain provenance and recorded integrity values for the DeviceInfo capture, transport log, source/build records, Nikon archive captures, board photographs, manifests, component maps, and reports. Do not expose the raw DeviceInfo serial number.
2. **Study the P510 imaging pipeline in relation to RAW.** The P510 reports an empty `CaptureFormats` array and image-format value `0xB111`, whose meaning is unresolved. Existing P500/P520 firmware may be used for clearly labeled reference research only; neither model establishes P510 RAW capability.
3. **Study display/overlay pipelines in relation to focus peaking.** Any P500/P520 analysis remains neighboring-model reference evidence and cannot establish that the P510 has a focus metric or peaking overlay.
4. **Study HDMI/output architecture in relation to clean HDMI.** P510 conclusions must be limited to direct P510 documentation/evidence; neighboring-model behavior remains a hypothesis until confirmed on P510 evidence.
5. **Perform a deeper P500/P520 reference-firmware architecture comparison.** Keep all package, processor, and architecture findings labeled by their source model. No binary compatibility or P510 platform relationship is implied.

No firmware acquisition, donor purchase, hardware investigation, or next project direction is selected here. **Phase 4 is closed.**
