# Nikon COOLPIX P510 — Known Facts

**Status date:** 2026-11-20  
**Scope:** P510 facts only, with P500/P520 kept explicitly separate as reference material. This document records research status; it does not authorize camera communication or hardware work.

## CONFIRMED

- **Camera model:** Nikon COOLPIX P510. The physical camera is owner-held.
- **Installed camera firmware:** Version **1.0**, directly observed by the owner in the camera's Firmware version menu. This confirms only the displayed version; it does not identify a build ID or binary image.
- **PTP DeviceInfo response:** A controlled, single `GetDeviceInfo (0x1001)` request (transaction ID 1) returned `PTP_OK (0x2001)`. The camera-reported fields were Manufacturer `Nikon Corporation`, Model `P510`, DeviceVersion `V1.00`, StandardVersion `0x0064`, VendorExtensionID `0x00000006`, VendorExtensionVersion `0x0064`, VendorExtensionDesc `microsoft.com: 1.0; Nikon PTP Extensions`, and FunctionalMode `0x0000`.
- **Physical USB identity/interface:** The P510 was observed as VID/PID `04B0:0223` with a standard Still Image/PTP interface (`06/01/01`) and product string `NIKON DSC COOLPIX P510-PTP`. This establishes device identity/transport, not firmware-memory access. See [P510-Phase3C1-PnP-identification.md](P510-Phase3C1-PnP-identification.md) and [P510-Phase3C5C-USB-descriptor-analysis.md](P510-Phase3C5C-USB-descriptor-analysis.md).
- **Official historical Nikon download entry:** Archived Nikon Download Center captures for product `55` (2015-06-14 through 2023-04-07) list an **A-GPS Update File** dated 2012-03-12 as the only item in the P510 Firmware section. The archived detail page identifies `NML_28A.ee` as GPS assistance data for the location-data unit, not camera-body firmware. This confirms a P510-supported GPS-data publication, not a P510 body-firmware release. See [P510-Phase4B-historical-Nikon-firmware-research.md](P510-Phase4B-historical-Nikon-firmware-research.md).
- **PTP capability advertisement:** The same response advertised 26 operation codes, 11 event codes, six device-property codes, an empty CaptureFormats list, and seven ImageFormats codes. The complete raw arrays and hashes are recorded in [P510-Phase3C5B-physical-GetDeviceInfo.md](P510-Phase3C5B-physical-GetDeviceInfo.md); the unchanged raw 293-byte payload is [P510-GetDeviceInfo.raw.bin](P510-GetDeviceInfo.raw.bin).
- **PTP operation boundary:** The only PTP operation transmitted for this capture was `0x1001 GetDeviceInfo`; no PTP session was opened, and no additional advertised operation was executed. This is confirmed by the transport log and physical interrogation report, not inferred from the capability arrays.
- **Local firmware-acquisition inventory (Phase 4A):** No authentic P510 updater/package, payload extracted from an authenticated P510 updater, or validated on-device firmware dump is present in the workspace. `firmware/original/P510` remains empty; the available P500/P520 firmware files are reference-only. See [P510-Phase4A-firmware-acquisition-consolidation.md](P510-Phase4A-firmware-acquisition-consolidation.md).
- **Offline hardware/service-document inventory (Phase 4C):** At that phase's inventory point, the project had no P510-specific service/repair manual, schematic, boardview, PCB photograph, identified board revision, or service/adjustment utility. The available P510 manual/ISO were user documentation. Phase 4D later added public teardown imagery and a strongly supported DRAM marking interpretation, but still did not identify the SoC, firmware-storage device, EEPROM, or debug/test interface. This bounded inventory is not evidence that additional information or parts do not exist elsewhere. See [P510-Phase4C-firmware-acquisition-path-analysis.md](P510-Phase4C-firmware-acquisition-path-analysis.md) and [P510-Phase4D-source-images.md](P510-Phase4D-source-images.md).
- **Public teardown imagery (Phase 4D):** The iFixit P510 motherboard-replacement guide shows the populated side of a P510 motherboard. The visible board sticker reads `280414`; its meaning and relationship to board revision are unknown. A large Micron-marked package visibly reads `21C22` / `D9MTD`; third-party code lookup strongly supports a Micron MT47H128M16RT-25E:C DDR2 SDRAM identification, but the complete part-number mapping is not confirmed by an accessible primary datasheet. A central large IC is obscured by a thermal pad. See [P510-Phase4D-board-identification.md](P510-Phase4D-board-identification.md) and [P510-Phase4D-component-map.md](P510-Phase4D-component-map.md).
- **Board identification limits (Phase 4D):** No P510 SoC, firmware-storage device, PCB assembly number/revision, or debug/service interface was identified. A seller-claimed standalone P510 board visually strongly matches the iFixit board, but the seller's model/authenticity claims are not independent proof. No donor was purchased. See [P510-Phase4D-donor-candidates.md](P510-Phase4D-donor-candidates.md).
- **Phase 4E reverse-face image (strong seller-claimed lead):** A 1024x768 eBay image paired with the component-side photo that strongly matches the iFixit board shows a partially shielded opposite face. A PCB silkscreen appears to read `CMKY-PB2`, and the shield has an apparent `2231` mark; neither transcription/meaning is independently corroborated, and neither establishes a board part number or revision. The reverse face remains mostly obscured, and no new component identity was established. See [P510-Phase4E-new-source-images.md](P510-Phase4E-new-source-images.md) and [P510-Phase4E-component-evidence.md](P510-Phase4E-component-evidence.md).
- **PTP research status:** Phase 3C PTP capability discovery is **PAUSED/COMPLETE FOR NOW**. Unknown codes remain documented; Phase 3C-8's P500 `0xD280`/`0xD303` property-like evidence does not establish P510 behavior.
- **Original P510 documentation ISO:** The inventoried contents are documentation only: `INDEX.pdf` and localized PDF manuals. No firmware package, updater, executable, library, or driver was found in the inventory. See [P510-disc-manual-analysis.md](P510-disc-manual-analysis.md).
- **Original P510 manual:** Documents MTP/PTP data-transfer protocols and Hi-Speed USB 2.0. It does not disclose USB VID/PID or a firmware-memory dump method. See [P510-disc-manual-analysis.md](P510-disc-manual-analysis.md).
- **Camera state constraints:** Keep the P510 on Firmware Version 1.0. Do not update, dump, open, disassemble, connect to, or communicate with it during the current research phase.

## STRONGLY SUPPORTED — P500 ONLY; NOT P510 FACTS

The following is the current P500 stopping point, recorded for reference and explicitly **not transferred to the P510**:

- ARM32 little-endian is **STRONGLY SUPPORTED** for `P500-NPROG-primary.bin`.
- Phase 2D-4 examined 25 high-value strings; 21 had file-offset-valued matches and 15 were connected to coherent ARM code. PTP/MTP, firmware-related, and lens-task landmarks were identified.
- No tested runtime image base produced exact string-pointer resolution. `0x57E70000` remains only **PLAUSIBLE**. `0x57EA0000` is associated with writable zero-fill memory and is not supported as the firmware image base.
- Rebase is **NOT justified**. Broad P500 firmware reverse engineering is **PAUSED** at Phase 2D-4.
- Phase 3C-8's SHA-256-verified, read-only scan found a P500 code/pointer sequence at `P500-NPROG-primary.bin` file offset `0x006AD594`: `0xD303` is paired with an initializer at `0x00132F50`, and `0xD280` with one at `0x0013355C`. Both routines write their code IDs at structure offset `+0xB0` and literal `2` at `+0xB2`. This is P500-only evidence suggestive of property/descriptor registration; it does not establish either semantic meaning, a confirmed data type, or P510 behavior. See [Phase 3C-8 unresolved-code correlation](P510-Phase3C8-unresolved-code-correlation.md).
- The complete record is [P500-string-reference-analysis.md](P500-string-reference-analysis.md).

## HYPOTHESIS

- The PTP-reported `DeviceVersion` string `V1.00` is textually consistent with the owner's menu observation of Firmware Version 1.0, but the capture does not establish that DeviceVersion is the installed firmware-version field or a full build identifier.
- P500 and P520 packages use model-specific `P<Model>Update\firmware\firmware.bin` paths. A similar P510 path such as `P510Update\firmware\firmware.bin` is only a naming hypothesis; no P510 package or path has been verified.
- P500, P510, and P520 are distinct model names; similarity or numbering does not establish a shared platform, processor, container, keys, or binary compatibility.
- The proposition that Nikon never publicly released a P510 camera-body firmware update is **PARTIALLY SUPPORTED** by the empty current Firmware section and 16 examined official product-page captures from 2015-2023 with no body-firmware entry. It is not proven because no capture of that page was located before 2015-06-14, and some regional archive queries were empty or unavailable. The A-GPS file listed in Nikon's Firmware category is GPS assistance data, not a body-firmware update.

## UNKNOWN

- P510 processor architecture and processor/platform identifier; the central large IC in public teardown photographs is thermally covered and unreadable.
- P510 firmware container format, internal sections, and runtime image base.
- Whether the P510 firmware contains ARM or Thumb code.
- Whether its firmware is signed, encrypted, compressed, or uses another integrity/authentication mechanism.
- A safe, supported firmware-dumping or read-only memory-acquisition mechanism.
- The meaning and applicability to P510 of the advertised vendor-extension operation codes `0x90A1`, `0x90A2`, and `0x90A3`, and property codes `0xD280` and `0xD303`.
- Whether advertised PTP operations, events, properties, or formats work in any particular camera mode beyond the successful `GetDeviceInfo` exchange.
- Whether image-format code `0xB111` represents RAW/NEF or another format. The DeviceInfo list contains an empty CaptureFormats array and no recognized NEF code, but this does not prove that the imaging pipeline cannot produce RAW data.
- Any P510 service/debug interface, service commands, or memory-read operation; visible pad groups have no supported signal/function assignments.
- Meaning of the visible P510 board sticker `280414`; meaning and exact reading of seller-image markings provisionally transcribed as `CMKY-PB2` and `2231`; PCB assembly number/revision; identities of components hidden beneath the reverse-face shield.
- Identity, capacity, interface, voltage, and readout protection of any P510 firmware-storage device. No candidate has been identified from the reviewed photos.
- Whether the PTP `DeviceVersion` string `V1.00` is semantically the installed firmware version 1.0; USB `bcdDevice`/`REV_0100` is a separate USB revision field.
- Whether Nikon ever publicly released a P510 camera-body firmware update before the earliest located product-page capture (2015-06-14) or on a regional/support page not recovered in Phase 4B. The examined current page has an empty Firmware section; the 2015-2023 captures list only A-GPS data, not body firmware.
- Whether the owner-observed installed Version 1.0 is factory/original firmware or was installed as an update; no P510 release history has been verified.
- Whether any P510 firmware image exists in historical official Nikon archives or service records.
- Whether P500 or P520 firmware components have any P510 platform commonality. They must remain reference-only and must never be used to construct P510 firmware.

## Evidence boundary

P510-specific facts in this file come from the physical owner's menu observation, the inventoried P510 documentation, Windows PnP/USB observations, the successful raw PTP DeviceInfo capture, and clearly labeled public iFixit P510 teardown imagery. The teardown photographs document a guide camera and do not establish that its board revision matches the owner's camera. PTP code names and vendor/property/event mappings are confirmed only as project-source definitions unless explicitly returned by the P510; mappings from other models are not P510 behavior evidence. P500 ARM, memory-map, package, and string findings are not evidence of P510 architecture or implementation.

The offline Phase 3C-7 source check confirmed that the D7000 IDA helper labels property code `0xD303` as `NIKON_D303` without defining its meaning. A D5100 script address ending in `0xD280` is a menu-name/memory address, not a PTP property mapping. These are project-source observations only; neither establishes P510 property semantics. See [P510-Phase3C7-offline-source-reconciliation.md](P510-Phase3C7-offline-source-reconciliation.md).
