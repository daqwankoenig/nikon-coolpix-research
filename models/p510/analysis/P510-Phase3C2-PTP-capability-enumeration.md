# P510 Phase 3C-2: PTP/WPD Capability Enumeration

**Status:** STOPPED — safe Windows PnP enumeration was verified, but no approved WPD/PTP client tool was available. No PTP or vendor operation was sent.

**Observation date:** 2026-11-19  
**Target:** Nikon COOLPIX P510, physically confirmed Firmware Version 1.0  
**Known PnP identity:** `USB\VID_04B0&PID_0223\31100075`

## Tools used

The only physical-device-facing operation in this phase was existing Windows PnP enumeration:

```powershell
Get-PnpDevice -PresentOnly -InstanceId 'USB\VID_04B0&PID_0223\31100075'
Get-PnpDevice -PresentOnly -Class WPD
Get-PnpDeviceProperty -InstanceId 'USB\VID_04B0&PID_0223\31100075' -KeyName ...
```

No third-party utility, Nikon utility, WPD COM client, MTP extension call, or PTP packet tool was run. Windows PnP property queries were used because they do not require opening an application-level PTP/WPD session.

A local custom enumerator was prepared and removed before use because the local `dotnet` executable has no SDK/compiler available. No software installation or package download was performed.

## Observations

| Item | Result | Source | Classification |
|---|---|---|---|
| Camera reachable through Windows PnP | Yes | `Get-PnpDevice` | CONFIRMED FROM WINDOWS |
| PnP status | OK, `CM_PROB_NONE`, problem code 0 | PnP property query | CONFIRMED FROM WINDOWS |
| Manufacturer | Nikon Corporation | PnP property `DEVPKEY_Device_Manufacturer` | CONFIRMED FROM WINDOWS |
| Model/friendly name | P510 | PnP friendly name | CONFIRMED FROM WINDOWS |
| Device description | NIKON DSC COOLPIX P510-PTP | PnP bus-reported description | CONFIRMED FROM WINDOWS |
| Serial/device ID | `31100075` as the instance suffix | PnP instance ID | CONFIRMED FROM WINDOWS; treated only as Windows/USB instance data |
| Firmware version | 1.0 | Physical-camera observation before USB analysis | CONFIRMED PHYSICAL-CAMERA FACT |
| Functional category | WPD / Portable Device | PnP class | CONFIRMED FROM WINDOWS |
| PTP/MTP identification | Bus description contains PTP; INF is MTP and service is WUDFWpdMtp | PnP metadata | CONFIRMED FROM WINDOWS |
| Storage objects | No storage enumeration was performed | Safety boundary | UNKNOWN |
| Supported content types | Not exposed by passive PnP metadata | WPD limitation | UNKNOWN |
| Supported PTP operations | Raw PTP operation table was not exposed | WPD limitation | UNKNOWN |
| Supported PTP events | Raw PTP event table was not exposed | WPD limitation | UNKNOWN |
| Supported PTP device properties | Raw PTP property table was not exposed | WPD limitation | UNKNOWN |
| Supported capture formats | Not exposed by passive PnP metadata | WPD limitation | UNKNOWN |
| Supported image formats | Not exposed by passive PnP metadata | WPD limitation | UNKNOWN |
| Vendor-specific 0x9000-0xFFFF operations | None were executed or enumerated | Safety boundary | UNKNOWN / NOT ENUMERATED |

## Raw identifiers and codes

| Identifier | Value | Meaning/source |
|---|---|---|
| VID | `04B0` | Nikon USB vendor ID; derived from hardware ID |
| PID | `0223` | P510 PnP product ID; derived from hardware ID |
| Hardware ID | `USB\VID_04B0&PID_0223&REV_0100` | Windows PnP hardware ID |
| Instance ID | `USB\VID_04B0&PID_0223\31100075` | Windows USB/PnP instance |
| Compatible class | `06` | Still-image/USB image compatible-ID class code |
| Compatible subclass | `01` | PnP compatible-ID subclass |
| Compatible protocol | `01` | PnP compatible-ID protocol |
| INF | `wpdmtp.inf` | Windows MTP INF |
| INF section | `MTP` | Windows INF section |
| Service | `WUDFWpdMtp` | Microsoft WPD/MTP driver service |
| Driver provider | Microsoft | Windows PnP metadata |
| Driver version | `10.0.26100.9750` | Windows PnP metadata |
| Container ID | `{CAEE62BD-02B9-580A-B767-D5638119D24F}` | Windows PnP container identifier |

No raw PTP numeric operation/property codes were obtained.

## WPD limitation

Windows PnP metadata identifies the camera as a WPD/MTP/PTP-style device, but it does not expose the camera's raw PTP `GetDeviceInfo` dataset or the raw supported-operation/event/property arrays to `Get-PnpDevice` or `Get-PnpDeviceProperty`.

The following operations were considered but not used:

- `IPortableDevice::Open`
- `IPortableDevice::SendCommand`
- WPD MTP-extension execute/read/end-data-transfer commands
- PTP `GetDeviceInfo (0x1001)`
- PTP session open/close
- Storage/object enumeration
- property description/value reads beyond PnP

The WPD MTP-extension execute interface is classified in vendor-operation category and was not used. A direct standard PTP client was not available locally. No unknown, Nikon, or vendor-specific operation in the `0x9000-0xFFFF` range was executed.

## Safety confirmation

- **NO PTP COMMANDS WERE INTENTIONALLY SENT**
- **NO NIKON VENDOR COMMANDS WERE SENT**
- **NO WPD APPLICATION SESSION WAS OPENED**
- **NO CAMERA STORAGE WAS ACCESSED**
- **NO CAMERA FILES OR OBJECTS WERE ENUMERATED**
- **NO CAMERA SETTINGS WERE CHANGED**
- **NO PROPERTY WAS WRITTEN**
- **NO OBJECT WAS UPLOADED, DELETED, CREATED, OR MODIFIED**
- **NO CAPTURE OPERATION WAS ISSUED**
- **NO MEMORY, REGISTER, OR FIRMWARE OPERATION WAS ISSUED**
- **NO DRIVER WAS REPLACED**
- **NO SOFTWARE OR USB DRIVER WAS INSTALLED**
- **NO NikonDump or NikonFlags process was run**

## Recommended next step

**STOP.** Do not infer a PTP capability table from Windows PnP metadata.

The next action must be a separately reviewed standard-PTP transport design that can prove it sends exactly `GetDeviceInfo (0x1001)` with:

- zero operation parameters
- device-to-host data
- no `OpenSession`
- no `CloseSession`
- no storage/object enumeration
- no property reads/writes beyond the returned `DeviceInfo`
- no Nikon vendor operation
- no unknown vendor-extension call

Until that transport is independently verified, the PTP/WPD capability table remains UNKNOWN.
