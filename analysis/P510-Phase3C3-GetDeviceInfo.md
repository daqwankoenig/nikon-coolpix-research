# P510 Phase 3C-3: Minimal PTP GetDeviceInfo Interrogation

**Status:** STOPPED — standard PTP `GetDeviceInfo` was not issued.  
**Observation date:** 2026-11-19  
**Target:** Nikon COOLPIX P510, physically confirmed Firmware Version 1.0  
**Known PnP identity:** `USB\VID_04B0&PID_0223\31100075`

## Safety result

- PnP node status was confirmed as present and working.
- No PTP/WPD application session was opened.
- PTP `GetDeviceInfo (0x1001)` was **not** issued.
- No Nikon vendor-specific operation was sent.
- No operation in the `0x9000-0xFFFF` range was sent.
- No property was written.
- No camera setting was changed.
- No capture was initiated.
- No object was uploaded or deleted.
- No firmware or memory operation was performed.
- No driver was installed or replaced.

## Exact method considered

The existing Windows PnP and Portable Devices interfaces were reviewed:

```powershell
Get-PnpDevice -PresentOnly -InstanceId 'USB\VID_04B0&PID_0223\31100075'
Get-PnpDeviceProperty -InstanceId 'USB\VID_04B0&PID_0223\31100075' -KeyName ...
```

The PnP checks confirmed the existing Windows MTP/WPD identity:

| Property | Windows result |
|---|---|
| Name | P510 |
| Bus description | NIKON DSC COOLPIX P510-PTP |
| Manufacturer | Nikon Corporation |
| VID/PID | `04B0` / `0223` |
| Hardware ID | `USB\VID_04B0&PID_0223&REV_0100` |
| Instance ID | `USB\VID_04B0&PID_0223\31100075` |
| PnP class | WPD |
| Driver | `WUDFWpdMtp` |
| INF | `wpdmtp.inf` |
| INF section | `MTP` |
| Driver provider/version | Microsoft / `10.0.26100.9750` |
| Status | OK, problem code 0 |

These PnP results do not contain the raw PTP `DeviceInfo` dataset.

## Available WPD interface limitation

Microsoft exposes normal WPD interfaces for opening a device, enumerating content, reading properties, and querying capabilities. However, no ordinary WPD wrapper was found that directly maps to the raw standard PTP `GetDeviceInfo (0x1001)` dataset.

The Microsoft WPD MTP-extension execute command does exist, but Microsoft documents it as:

- command category `WPD_CATEGORY_MTP_EXT_VENDOR_OPERATIONS`
- an MTP **vendor-extended operation code**
- a direct `IPortableDevice::SendCommand` interface
- followed by vendor-extension read/end-transfer calls

Using that route with `0x1001` would require treating a standard PTP opcode through a vendor-operation category and would not establish that Windows sends exactly the standard PTP command with no hidden session or other transaction. It was therefore not used.

## Session/interrogation status

| Item | Result |
|---|---|
| PTP session actually opened | NO |
| PTP `GetDeviceInfo (0x1001)` actually issued | NO |
| Standard PTP response obtained | NO |
| Raw PTP response bytes obtained | NONE |
| Vendor-specific operation sent | NO |

## Requested `DeviceInfo` fields

| Field | Camera-reported value | Source |
|---|---|---|
| StandardVersion | UNKNOWN | Not obtained |
| VendorExtensionID | UNKNOWN | Not obtained |
| VendorExtensionVersion | UNKNOWN | Not obtained |
| VendorExtensionDesc | UNKNOWN | Not obtained |
| FunctionalMode | UNKNOWN | Not obtained |
| OperationsSupported | UNKNOWN | Not obtained |
| EventsSupported | UNKNOWN | Not obtained |
| DevicePropertiesSupported | UNKNOWN | Not obtained |
| CaptureFormats | UNKNOWN | Not obtained |
| ImageFormats | UNKNOWN | Not obtained |
| Manufacturer | Nikon Corporation | Windows PnP metadata, not a PTP `DeviceInfo` response |
| Model | P510 | Windows PnP-friendly name/bus metadata, not a PTP `DeviceInfo` response |
| DeviceVersion | UNKNOWN as camera PTP data | Windows PnP does not provide a verified PTP `DeviceInfo.DeviceVersion` |
| SerialNumber | UNKNOWN | No PTP response; PnP instance suffix `31100075` is not classified as a PTP serial number |

No value above is labeled as camera-reported PTP `DeviceInfo` unless specifically obtained as that dataset. The Manufacturer and Model entries in this table came from Windows PnP metadata.

## Supported operation codes

**UNKNOWN — no supported-operation table was obtained.**

No vendor-specific operations were discovered by this phase.

No numeric code in the `0x9000-0xFFFF` range was sent or interpreted. Vendor-specific values remain unavailable.

## Supported event codes

**UNKNOWN — no supported-event table was obtained.**

## Supported property codes

**UNKNOWN — no supported-device-property table was obtained.**

## Capture and image formats

**UNKNOWN — no PTP `CaptureFormats` or `ImageFormats` arrays were obtained.**

## Raw Windows/WPD information

The following is directly confirmed from Windows PnP/WPD metadata:

- Model/friendly name: P510
- Manufacturer: Nikon Corporation
- Bus description: NIKON DSC COOLPIX P510-PTP
- VID/PID: `04B0` / `0223`
- PnP class: WPD
- WPD/MTP INF: `wpdmtp.inf`, section `MTP`
- Existing service: `WUDFWpdMtp`
- Existing Microsoft driver provider/version
- USB-compatible class/subclass/protocol compatible-ID values: `06 / 01 / 01`

It is not safe to infer PTP `StandardVersion`, vendor-extension fields, supported code arrays, capture formats, image formats, or serial number from these values.

## WPD limitation

The proposed read-only PTP interrogation cannot be completed through a demonstrated standard-only Windows API path:

1. `Get-PnpDevice` and `Get-PnpDeviceProperty` expose no raw PTP `DeviceInfo`.
2. Opening `IPortableDevice` and querying WPD capabilities may expose Windows WPD command/category data, but it does not map reliably to the raw PTP `DeviceInfo` arrays.
3. The MTP vendor-extension execute/read/end-data-transfer path is vendor-operation transport, not a verified standard `GetDeviceInfo` wrapper.
4. A direct standard PTP implementation is not installed or available in this workspace.
5. The user rules prohibit installing or downloading tools and replacing the existing WUDF/WPD driver.

No undocumented command, vendor operation, brute-force probe, or direct USB bypass was attempted.

## Recommended next step

STOP Phase 3C-3. Do not infer the `DeviceInfo` dataset or test any Nikon/vendor code.

The next decision should be whether to approve a separately source-reviewed standard PTP client that:

- uses the existing WUDF/WPD driver if a documented standard-only transport exists, or
- remains outside the camera until a standard-only client and exact packet path are verified.

Do not use the MTP vendor-extension commands merely to issue `0x1001` unless their operation is independently proven to transmit exactly that standard PTP command with no hidden session or follow-up operation.
