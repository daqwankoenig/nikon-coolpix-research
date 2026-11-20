# P510 Phase 3C-1: Passive Windows USB/PnP Identification

**Observation date:** 2026-11-19  
**Observation time:** 15:33 (local, from the approved session context)  
**Scope:** Windows Plug-and-Play enumeration and PnP property reads only. No PTP/WPD application session was opened.

## Summary

| Item | Value | Source/classification |
|---|---|---|
| Physical camera model | Nikon COOLPIX P510 | Confirmed from the physical-camera record; also reported by Windows as P510 |
| Confirmed Firmware Version | 1.0 | Confirmed physical-camera observation |
| Windows device name | P510 | CONFIRMED FROM WINDOWS |
| Windows bus-reported description | NIKON DSC COOLPIX P510-PTP | CONFIRMED FROM WINDOWS |
| Manufacturer | Nikon Corporation | CONFIRMED FROM WINDOWS |
| VID | VID_04B0 | DERIVED FROM HARDWARE ID and Windows instance ID |
| PID | PID_0223 | DERIVED FROM HARDWARE ID and Windows instance ID |
| Complete primary hardware ID | `USB\VID_04B0&PID_0223&REV_0100` | CONFIRMED FROM WINDOWS |
| Complete secondary hardware ID | `USB\VID_04B0&PID_0223` | CONFIRMED FROM WINDOWS |
| Device instance ID | `USB\VID_04B0&PID_0223\31100075` | CONFIRMED FROM WINDOWS |
| Windows class | WPD | CONFIRMED FROM WINDOWS |
| Windows classification | Portable Device (PnP class WPD) | CONFIRMED FROM WINDOWS |
| USB interface class | 06 | DERIVED FROM COMPATIBLE ID |
| USB interface subclass | 01 | DERIVED FROM COMPATIBLE ID |
| USB interface protocol | 01 | DERIVED FROM COMPATIBLE ID |
| USB interface descriptor interpretation | Image / Still Image | CONFIRMED as a USB class code only, via class 06; Windows does not expose raw descriptor fields here |
| PTP/MTP in passive metadata | MTP is explicit in active INF section `MTP`; description contains `PTP` | CONFIRMED FROM WINDOWS |
| Active Windows service | `WUDFWpdMtp` | CONFIRMED FROM WINDOWS |
| Active INF | `wpdmtp.inf` | CONFIRMED FROM WINDOWS |
| INF section | `MTP` | CONFIRMED FROM WINDOWS |
| Driver provider | Microsoft | CONFIRMED FROM WINDOWS |
| Driver version | `10.0.26100.9750` | CONFIRMED FROM WINDOWS |
| INF driver date | 2006-06-20 | CONFIRMED FROM WINDOWS |
| Driver status | OK; problem code 0; install state 0 | CONFIRMED FROM WINDOWS |
| Parent | `USB\ROOT_HUB30\5&75E0CAA&0&0` | CONFIRMED FROM WINDOWS |
| Parent device name | USB Root Hub (USB 3.0) | CONFIRMED FROM WINDOWS |
| Parent manufacturer | (Standard USB HUBs) | CONFIRMED FROM WINDOWS |
| Parent service | `USBHUB3` | CONFIRMED FROM WINDOWS |
| Parent provider | Microsoft | CONFIRMED FROM WINDOWS |
| Parent driver version | `10.0.26100.10013` | CONFIRMED FROM WINDOWS |
| Container ID | `{CAEE62BD-02B9-580A-B767-D5638119D24F}` | CONFIRMED FROM WINDOWS |

## Complete PnP properties

### Camera/PnP node

- **Status:** OK
- **Problem:** `CM_PROB_NONE`
- **Problem description:** This device is working properly.
- **Class:** WPD
- **Friendly name:** P510
- **Bus-reported description:** NIKON DSC COOLPIX P510-PTP
- **Manufacturer:** Nikon Corporation
- **Enumerator:** USB
- **Hardware IDs:**
  - `USB\VID_04B0&PID_0223&REV_0100`
  - `USB\VID_04B0&PID_0223`
- **Compatible IDs:**
  - `USB\COMPAT_VID_04B0&Class_06&SubClass_01&Prot_01`
  - `USB\COMPAT_VID_04B0&Class_06&SubClass_01`
  - `USB\COMPAT_VID_04B0&Class_06`
  - `USB\Class_06&SubClass_01&Prot_01`
- **Service:** `WUDFWpdMtp`
- **Driver INF:** `wpdmtp.inf`
- **INF section:** `MTP`
- **Driver provider:** Microsoft
- **Driver version:** `10.0.26100.9750`
- **Driver INF date:** 2006-06-20
- **Device address:** 1
- **Device bus number:** 0
- **PDO name:** `\Device\USBPDO-21`
- **Container ID:** `{CAEE62BD-02B9-580A-B767-D5638119D24F}`
- **Config flags:** 0
- **Capabilities:** 148
- **Install state:** 0

### USB parent/root-hub node

- **Status:** OK
- **Problem:** `CM_PROB_NONE`
- **Class:** USB
- **Friendly name:** USB Root Hub (USB 3.0)
- **Instance ID:** `USB\ROOT_HUB30\5&75E0CAA&0&0`
- **Manufacturer:** `(Standard USB HUBS)`; capitalization/homographic exactness may differ only in Windows text formatting
- **Hardware IDs:**
  - `USB\ROOT_HUB30&VID1022&PID15C1&REV0000`
  - `USB\ROOT_HUB30&VID1022&PID15C1`
  - `USB\ROOT_HUB30`
- **Service:** `USBHUB3`
- **Driver provider:** Microsoft
- **Driver version:** `10.0.26100.10013`
- **Parent:** `PCI\VEN_1022&DEV_15C1&SUBSYS_0CA91028&REV_00\4&dede588&0&0443`
- **Container ID:** `{00000000-0000-0000-FFFF-FFFFFFFFFFFF}`

## USB class/subclass/protocol

The Windows PnP compatible-ID set exposes:

- Class: `06`
- Subclass: `01`
- Protocol: `01`

**Classification:** DERIVED FROM HARDWARE ID / COMPATIBLE ID.

Windows exposed only these PnP-compatible-ID fields. It did not expose raw USB device descriptors or raw endpoint/interface descriptor fields in the queried PnP properties. The PnP node is classed as `WPD`, and the installed INF route is `wpdmtp.inf` / `MTP`.

## Nikon/P510-specific identifiers

Confirmed or derived P510-specific identifiers:

- Bus-reported description: `NIKON DSC COOLPIX P510-PTP`
- VID/PID: `04B0` / `0223`
- Windows-friendly name: `P510`
- Windows instance ID: `USB\VID_04B0&PID_0223\31100075`
- Manufacturer: `Nikon Corporation`

No P510 firmware, processor, or internal camera-platform identifier was exposed by these PnP fields.

## Unexpected devices or interfaces

When observed, Windows exposed:

- One PnP node in the WPD class: `P510`
- Its USB parent/root-hub node: `USB Root Hub (USB 3.0)`
- No additional P510-specific child/interface node was exposed

No extra `Nikon`, `Still Image`, `MTP`, or P510 node outside the single WPD/PnP node was identified.

## Requested values not exposed

- Raw USB `iManufacturer` string: **NOT EXPOSED** as a raw descriptor; only the Windows manufacturer property was available.
- Raw USB `iProduct` string: **NOT EXPOSED** as a raw descriptor; Windows exposed the friendly name and bus-reported description.
- Raw USB configuration/interface/endpoint descriptors: **NOT EXPOSED** by the PnP properties queried.
- Raw USB subclass/protocol from a raw interface descriptor: **NOT EXPOSED**; only derived compatible-ID values were available.
- Windows `DEVPKEY_Device_Model`: **NOT EXPOSED**
- Windows `DEVPKEY_Device_UINumber`: **NOT EXPOSED**
- Windows `DEVPKEY_Device_DevType`: **NOT EXPOSED**
- Raw USB device description separate from PnP: PnP-friendly/bus-reported values were exposed, but raw descriptor data was not.

## Safety and no-contact boundary

- **NO PTP COMMANDS WERE INTENTIONALLY SENT**
- **NO NIKON VENDOR COMMANDS WERE SENT**
- **NO CAMERA FILES WERE ACCESSED**
- **NO CAMERA SETTINGS WERE CHANGED**
- **NO DRIVER WAS REPLACED**
- **NO FIRMWARE OPERATION WAS PERFORMED**
- **NO WPD APPLICATION SESSION WAS OPENED**
- **NO `IPortableDevice::Open`, `SendCommand`, or `Close` call was issued**
- **NO NikonDump or NikonFlags process was run**
- **NO WinUSB or libusb driver was installed**
- **NO third-party driver or software installation was requested or performed**

The camera was already physically connected when the PnP observation began. Windows reported the P510 as working correctly through the existing Microsoft WUDF WPD/MTP driver. The PnP-only queries did not emit a PTP operation.
