# Phase 3B-1 — Offline WPD/PTP Transport Verification

**Status:** Source/documentation analysis only. The P510 was not connected, enumerated, or queried.  
**Target:** Owner-confirmed Nikon COOLPIX P510, installed Firmware Version 1.0.  
**Decision:** Phase 3C-1 (Windows USB/PnP identification) is suitable for separate approval. Phase 3C-2 (PTP `GetDeviceInfo`) remains **BLOCKED**: the identified WPD MTP-extension calls are for vendor-extended operations, and no Windows API path has been verified to send only the standard PTP request.

## Findings

- **Windows can obtain USB VID/PID without a PTP session.** USB bus enumeration retrieves descriptors before application-level PTP. Device Manager, `Get-PnpDevice`, and `Get-PnpDeviceProperty` read Windows PnP data; they do not issue PTP operations.
- This is not passive electrical monitoring: USB enumeration sends standard USB requests to the attached device. It does not open a PTP session or invoke camera capture, file, storage, or setting operations.
- `IPortableDevice::Open` opens a WPD application-to-device connection. Microsoft does not specify the underlying PTP transactions (if any) that the WPD driver performs during open.
- `IPortableDevice::SendCommand` sends a WPD command to the driver. The MTP-extension execute/read/end calls are documented for MTP **vendor-extended operation codes**, not as a documented route for standard `GetDeviceInfo (0x1001)`.
- The execute call initiates an MTP command/data transaction. The read and end calls continue and complete that transfer; they are not documented as separate PTP operations. The exact wire behavior for an attempted `0x1001`, including acceptance, session handling, and any hidden traffic, is not established.
- `IPortableDevice::Close` closes the WPD connection. Microsoft does not specify whether a given driver sends PTP `CloseSession (0x1003)` or other device traffic when it closes.
- PTP `GetDeviceInfo (0x1001)` is a standard, zero-parameter, device-to-host operation that can be sent before `OpenSession` under PTP. Do **not** open a session just to request it. Some devices may not tolerate a pre-session request; on an error, stop without retrying through another opcode.
- The locally available `nikon-firmware-tools` source contains no WPD transport implementation. Its transport DLLs are opaque and its NikonDump path is unsuitable; see [nikon-firmware-tools-source-audit.md](nikon-firmware-tools-source-audit.md). The checked-in emulator/IDA references are not Windows WPD driver source and do not resolve this transport.

## WPD call-path findings

| WPD API call and parameters/results | What Microsoft documents | PTP/USB consequence established by sources | Device effects established / unresolved |
|---|---|---|---|
| `IPortableDevice::Open(pszPnPDeviceID, pClientInfo)`; returns `HRESULT`. The client info may request `WPD_CLIENT_DESIRED_ACCESS=GENERIC_READ`. | Opens a connection between the application and device. | No explicit PTP opcode is part of the API. Whether the driver opens a PTP session or sends discovery commands is unspecified. | No property/object/capture write is defined by this call; implicit device traffic and temporary session behavior remain **UNKNOWN**. `GENERIC_READ` does not prove a read-only wire sequence. |
| `IPortableDevice::SendCommand(0, parameters, results)` with `WPD_COMMAND_MTP_EXT_EXECUTE_COMMAND_WITH_DATA_TO_READ`; required properties are `WPD_PROPERTY_MTP_EXT_OPERATION_CODE` (`VT_UI4`) and `WPD_PROPERTY_MTP_EXT_OPERATION_PARAMS` (parameter collection). Results include total data size, optional optimal buffer size, and transfer context. | Sends an MTP command block followed by device-to-host data. Its operation code is documented as a vendor-extended MTP operation code. | It attempts an MTP operation transaction. Setting the code to `0x1001` does not make this a documented standard-PTP call; acceptance, actual wire opcode, and session behavior are **UNKNOWN**. | The generic operation may have arbitrary effects; the API does not prove the attempted `0x1001` reached the camera as standard `GetDeviceInfo`. No Nikon opcode is intended, but the path is not approved. |
| `IPortableDevice::SendCommand(0, parameters, results)` with `WPD_COMMAND_MTP_EXT_READ_DATA`; parameters: transfer context (`VT_LPWSTR`), byte count (`VT_UI4`), receive-data vector. Results: bytes read and received data. | Reads data from the device after execute-with-data-to-read. | Continues the existing data phase; not documented as a new PTP operation. Exact lower-level driver traffic is unavailable. | No property/object/capture write is specified for this data-read step. As part of the unverified WPD path, not approved for Phase 3C-2. |
| `IPortableDevice::SendCommand(0, parameters, results)` with `WPD_COMMAND_MTP_EXT_END_DATA_TRANSFER`; parameter: transfer context (`VT_LPWSTR`). Results: response code and optional response parameters. | Completes the transfer and returns the operation response. | Completes the existing transaction; not documented as a new PTP operation. Exact lower-level driver traffic is unavailable. | No persistent write is specified for this completion step. The effect of the underlying operation remains unresolved; not approved for Phase 3C-2. |
| `IPortableDevice::Close()`; returns `HRESULT`. It can also occur when the final interface reference is released. | Closes the WPD connection. | No explicit PTP opcode is specified. Whether the driver sends `CloseSession` is **UNKNOWN**. | No property/object/capture write is defined by the API; persistent effects are not documented. Temporary session cleanup is possible but unverified. |

`SendCommand` is a general driver-command API. The MTP-extension execute/read/end commands are not Nikon opcodes, but their category and vendor-extended-code contract mean they cannot be treated as a verified standard-only `GetDeviceInfo` path. The earlier proposal to pass `0x1001` through this extension is withdrawn.

## PTP operations relevant to the minimum test

All opcodes below are standard PTP, not Nikon vendor operations. Only `GetDeviceInfo` is required to obtain the requested PTP identification and capability lists. The additional read operations are deliberately excluded.

| PTP operation | Opcode | Parameters | Data direction / result | State implications | Required for minimum test? | Classification |
|---|---:|---|---|---|---|---|
| `GetDeviceInfo` | `0x1001` | None | Device to host; `DeviceInfo` dataset includes standard version, vendor-extension metadata, supported operation/event/property codes, capture/image formats, and device strings; expected success response `OK (0x2001)` | Read-only by standard semantics; no persistent setting or object change | **Yes** | **STANDARD PTP READ** |
| `OpenSession` | `0x1002` | One session ID | Host command; expected success response `OK (0x2001)`; no data phase | Creates temporary PTP session state; not a persistent settings change, but outside this test's exact scope | **No** | **TEMPORARY SESSION MANAGEMENT** |
| `CloseSession` | `0x1003` | None | Host command; expected success response `OK (0x2001)`; no data phase | Ends temporary PTP session state; not a persistent settings change, but not permitted in this test | **No** | **TEMPORARY SESSION MANAGEMENT** |
| `GetStorageIDs` | `0x1004` | None | Device to host; storage identifiers; expected success response `OK (0x2001)` | Read-only operation, but reveals storage information not needed for identification | **No** | **STANDARD PTP READ** |
| `GetStorageInfo` | `0x1005` | Storage ID | Device to host; storage metadata; expected success response `OK (0x2001)` | Read-only operation, but not needed; does not retrieve the desired `DeviceInfo` fields | **No** | **STANDARD PTP READ** |
| `GetDevicePropDesc` | `0x1014` | Device-property code | Device to host; property description; expected success response `OK (0x2001)` | Read-only operation, but supported-property codes are already included in `GetDeviceInfo` | **No** | **STANDARD PTP READ** |
| `GetDevicePropValue` | `0x1015` | Device-property code | Device to host; property value; expected success response `OK (0x2001)` | Read-only by standard semantics, but not needed and would request an additional property value | **No** | **STANDARD PTP READ** |
| `SetDevicePropValue` | `0x1016` | Device-property code plus value data | Host to device | Can modify a setting | **Never** | **WRITE CAPABLE** |
| Capture, object, storage-format, reset/power, Nikon vendor, memory/register operations | Various | Varies | Varies | Could change settings/state, create/delete objects, or write device memory | **Never** | **NIKON VENDOR OPERATION**, **STATE CHANGING**, **WRITE CAPABLE**, or **UNKNOWN** |

PTP permits `GetDeviceInfo` before a session; `OpenSession` and `CloseSession` are not protocol prerequisites for this request. A particular Windows API may nevertheless perform implicit session management. That is why the PTP operation is safe by protocol semantics while the proposed WPD transport remains blocked.

## Exact operation sequence and safety classification

“Required” here means required for the proposed stage, not permission to connect. **UNKNOWN** entries block Phase 3C-2.

| Step | Windows API | PTP operation | Opcode | Parameters | Data direction | Temporary state change | Persistent state change | Vendor specific? | Required? | Safety classification |
|---:|---|---|---:|---|---|---|---|---|---|---|
| 1 | USB bus enumeration on attach | None; standard USB descriptor requests only | N/A | USB device/configuration/string descriptor indices selected by Windows | USB device to host | Device is enumerated; no PTP session | None specified | No | Yes, for USB identity | **PASSIVE USB DESCRIPTOR READ** |
| 2 | Device Manager or `Get-PnpDevice -PresentOnly` | None | N/A | Enumerate PnP nodes / present devices | Windows PnP store to host | None | None | No | Yes, Phase 3C-1 | **PASSIVE USB DESCRIPTOR READ** |
| 3 | `Get-PnpDeviceProperty` | None | N/A | Instance ID and selected read-only property keys | Windows PnP property store to host | None | None | No | Yes, Phase 3C-1 | **PASSIVE USB DESCRIPTOR READ** |
| 4 | `IPortableDevice::Open` | Not specified | Unknown | PnP device ID and client information; `GENERIC_READ` may be requested | Host opens WPD connection | Possible hidden PTP/session setup | No write documented; hidden behavior unknown | No Nikon opcode specified | No; blocked | **UNKNOWN** |
| 5 | WPD `EXECUTE_COMMAND_WITH_DATA_TO_READ` via `SendCommand` | Intended `GetDeviceInfo` | Intended `0x1001` | MTP extension operation code `0x1001`, empty operation-parameter collection; WPD flags `0` | Intended device to host | May involve hidden session handling | No persistent change expected from `GetDeviceInfo`; actual path unknown | MTP extension is vendor-operation category; not specifically Nikon | No; blocked | **UNKNOWN** |
| 6 | WPD `READ_DATA` via `SendCommand` | No new operation intended | None intended | Transfer context, byte count, receive buffer | Device to host | Continues same transfer | None specified | WPD vendor-operations category; not Nikon opcode | No; blocked with step 5 | **UNKNOWN** |
| 7 | WPD `END_DATA_TRANSFER` via `SendCommand` | No new operation intended | None intended | Transfer context | Device response to host | Completes same transfer | None specified | WPD vendor-operations category; not Nikon opcode | No; blocked with step 5 | **UNKNOWN** |
| 8 | `IPortableDevice::Close` or final interface release | Not specified | Unknown | None at API boundary | Host closes WPD connection | May end a hidden session | No persistent change documented; hidden behavior unknown | No Nikon opcode specified | No; blocked | **UNKNOWN** |
| 9 | A future verified standard-PTP transport only; no such Windows path is approved yet | `GetDeviceInfo` | `0x1001` | Zero operation parameters | Device to host | No PTP session needed by protocol | None by standard semantics | No | Yes, Phase 3C-2 if separately approved and transport validated | **STANDARD PTP READ** |
| 10 | Any transport that sends `OpenSession` / `CloseSession` | `OpenSession` / `CloseSession` | `0x1002` / `0x1003` | Open: session ID; close: none | Host command and device response | Starts/ends temporary session | No persistent settings change defined | No | **No** | **TEMPORARY SESSION MANAGEMENT** |
| 11 | Any transport that sends storage/property reads beyond `GetDeviceInfo` | `GetStorageIDs`, `GetStorageInfo`, `GetDevicePropDesc`, `GetDevicePropValue` | `0x1004`, `0x1005`, `0x1014`, `0x1015` | As listed above | Device to host | No persistent change defined | None defined | No | **No** | **STANDARD PTP READ** |
| 12 | Any transport that sends writes, capture, object changes, or Nikon extensions | Various | Various | Varies | Varies | May change camera state | May persist or modify objects/memory | Possibly | **Never** | **WRITE CAPABLE**, **STATE CHANGING**, **NIKON VENDOR OPERATION**, or **UNKNOWN** |

### Device properties and USB descriptor limits

Windows can report:

- **VID/PID:** commonly in `DEVPKEY_Device_HardwareIds` and the USB device instance ID, such as `USB\VID_xxxx&PID_yyyy`.
- **Manufacturer/product description:** `DEVPKEY_Device_BusReportedDeviceDesc`, `DEVPKEY_Device_Manufacturer`, and `DEVPKEY_Device_FriendlyName` are Windows/PnP-reported values. They are not guaranteed to preserve the raw USB `iManufacturer` and `iProduct` strings exactly.
- **Interface class/subclass/protocol:** inspect USB interface child nodes and their compatible IDs where Windows exposes them. These may not expose every raw interface descriptor field. Record unavailable fields as unavailable; do not install another tool or replace the driver.

The local USB patch lists a P510 name/ID, but this is not proof of the physical camera's actual VID/PID. Identify the camera by the before/after PnP node difference, not by assuming that candidate ID.

## Phase 3C-1 — Windows USB/PnP identification only

**Safety conclusion:** The source/documentation supports approving this limited stage as a future read-only identification test, after separate explicit approval to connect the camera. It has no PTP session or PTP operation. USB enumeration itself communicates standard descriptor requests and may wake the camera; it is not a guarantee of zero transient device activity.

1. Do not change camera settings or USB mode. Do not insert media, install software, or change drivers.
2. With the camera disconnected, capture the present PnP list using Device Manager or `Get-PnpDevice -PresentOnly`.
3. Only after separate approval, connect the camera using the existing Windows driver; do not open a WPD application or PTP client.
4. Capture the PnP list again and identify the new USB device/interface nodes by difference.
5. Read only the PnP properties for those nodes: `DEVPKEY_Device_HardwareIds`, `DEVPKEY_Device_CompatibleIds`, `DEVPKEY_Device_BusReportedDeviceDesc`, `DEVPKEY_Device_Manufacturer`, `DEVPKEY_Device_FriendlyName`, `DEVPKEY_Device_Service`, and `DEVPKEY_Device_Parent`.
6. Record VID, PID, available manufacturer/product descriptions, and available interface class/subclass/protocol data. Mark fields not exposed by Windows as unavailable. Redact serial-like instance-ID portions before retaining results.
7. Stop. Do not call `IPortableDevice::Open`, query WPD content/capabilities, or issue any PTP operation. If Windows requests a driver change or setup step, cancel and stop.

Example read-only PowerShell queries (not executed):

```powershell
$usbDevices = Get-PnpDevice -PresentOnly |
    Where-Object { $_.InstanceId -match '^USB\\VID_[0-9A-F]{4}&PID_[0-9A-F]{4}' }

$usbDevices | Select-Object Class, FriendlyName, Status, InstanceId

foreach ($device in $usbDevices) {
    Get-PnpDeviceProperty -InstanceId $device.InstanceId -KeyName @(
        'DEVPKEY_Device_HardwareIds',
        'DEVPKEY_Device_CompatibleIds',
        'DEVPKEY_Device_BusReportedDeviceDesc',
        'DEVPKEY_Device_Manufacturer',
        'DEVPKEY_Device_FriendlyName',
        'DEVPKEY_Device_Service',
        'DEVPKEY_Device_Parent'
    )
}
```

These queries read the Windows device tree/property store. They do not open a PTP session. The first call gathers present-device nodes; the second reads properties for a selected device instance.

## Phase 3C-2 — Standard PTP `GetDeviceInfo` only

**Safety conclusion:** **Not safe to approve yet. BLOCKED.** The protocol operation itself is standard/read-only, but no available Windows call path has been verified to transmit exactly that operation with no implicit `OpenSession`, vendor operation, or extra transaction.

The only acceptable camera-facing PTP request would be:

1. Use a transport that has been independently reviewed to send exactly one standard PTP `GetDeviceInfo` command (`0x1001`), with zero operation parameters and a device-to-host data phase.
2. Do not send `OpenSession`, `CloseSession`, `GetStorageIDs`, `GetStorageInfo`, `GetDevicePropDesc`, `GetDevicePropValue`, vendor extensions, or any other operation. If the device/transport requires a session or another operation, abort without fallback.
3. Parse only the standard `DeviceInfo` fields listed in this plan. Do not invoke any returned supported opcode. Discard/redact `SerialNumber`.
4. Stop after the response. No PTP connection lifecycle behavior is approved until its commands are verified.

This is the exact *PTP-level* procedure, not an executable Windows API recipe: Microsoft documents the WPD MTP-extension route as vendor-extended, and the WPD open/close wire behavior is not established. Do not substitute NikonDump, NikonFlags, a vendor operation, or a driver replacement. Further source review must identify a standard-only transport before Phase 3C-2 can be reconsidered.

## Required exclusions for any future approval

Phase 3C approval requires zero Nikon vendor operations; zero writes or write-capable calls; zero persistent changes; zero firmware, memory, or register operations; zero `SetDevicePropValue`; zero capture; zero object creation, modification, or deletion; and zero driver replacement. `OpenSession`/`CloseSession` are also excluded from the minimum test because `GetDeviceInfo` does not require a PTP session.

## Answers and current disposition

1. **Were all necessary WPD calls resolved?** No. Their documented API roles are known, but their exact driver-level behavior on open/close is not. The MTP extension does not document standard `GetDeviceInfo` as a supported operation.
2. **Which calls actually transmit PTP/MTP commands?** The WPD execute-with-data-to-read call explicitly sends an MTP command block. Read-data and end-data-transfer continue/complete that transaction, not documented new operations. Open/close have no specified PTP opcode, and hidden behavior remains unknown.
3. **Is `OpenSession`/`CloseSession` required?** No for standard `GetDeviceInfo` under PTP. They create/end temporary session state and are excluded.
4. **Can `GetDeviceInfo` be performed without a PTP session?** Yes by PTP protocol semantics; whether this P510 accepts it and whether a Windows transport can send it alone remain untested/unverified.
5. **Can Windows obtain VID/PID without PTP?** Yes, through USB enumeration and Windows PnP properties.
6. **Exact Phase 3C-1 procedure:** Follow the seven steps above; PnP-only, no WPD open or PTP.
7. **Exact Phase 3C-2 procedure:** One standard `0x1001`, zero parameters, data-in; no session or follow-up operation. It is not currently executable through a verified Windows API.
8. **Is Phase 3C-1 safe to approve?** The limited PnP-only procedure is suitable for separate approval. This phase itself did not authorize or perform it.
9. **Is Phase 3C-2 safe to approve?** No. It remains blocked.
10. **What remains UNKNOWN?** Whether WPD `Open` or `Close` causes implicit PTP/session traffic; whether WPD MTP-extension execute accepts or emits standard opcode `0x1001`; and the exact USB/PTP wire behavior of the Windows WPD driver for this camera. The P510's actual response to pre-session `GetDeviceInfo` also remains unknown.

## Sources

- [Microsoft: `IPortableDevice::Open`](https://learn.microsoft.com/en-us/windows/win32/api/portabledeviceapi/nf-portabledeviceapi-iportabledevice-open) — connection API and recommendation to request `GENERIC_READ` for read-only clients.
- [Microsoft: `IPortableDevice::SendCommand`](https://learn.microsoft.com/en-us/windows/win32/api/portabledeviceapi/nf-portabledeviceapi-iportabledevice-sendcommand) — sends driver commands; API alone does not establish wire behavior.
- [Microsoft: `IPortableDevice::Close`](https://learn.microsoft.com/en-us/windows/win32/api/portabledeviceapi/nf-portabledeviceapi-iportabledevice-close) — closes the WPD connection.
- [Microsoft: WPD MTP execute-with-data-to-read](https://learn.microsoft.com/en-us/windows/win32/wpd_sdk/wpd-command-mtp-ext-execute-command-with-data-to-read), [read-data](https://learn.microsoft.com/en-us/windows/win32/wpd_sdk/wpd-command-mtp-ext-read-data), and [end-data-transfer](https://learn.microsoft.com/en-us/windows/win32/wpd_sdk/wpd-command-mtp-ext-end-data-transfer) — operation category, vendor-extended code parameter, transfer data, and response completion.
- [Microsoft: PTP required commands](https://learn.microsoft.com/en-us/windows-hardware/drivers/image/ptp-required-commands) — standard PTP command opcodes.
- [Microsoft: `Get-PnpDevice`](https://learn.microsoft.com/en-us/powershell/module/pnpdevice/get-pnpdevice?view=windowsserver2025-ps) and [`Get-PnpDeviceProperty`](https://learn.microsoft.com/en-us/powershell/module/pnpdevice/get-pnpdeviceproperty?view=windowsserver2025-ps) — Windows PnP enumeration/property queries.
- [Microsoft: `DEVPKEY_Device_HardwareIds`](https://learn.microsoft.com/en-us/windows-hardware/drivers/install/devpkey-device-hardwareids), [`DEVPKEY_Device_BusReportedDeviceDesc`](https://learn.microsoft.com/en-us/windows-hardware/drivers/install/devpkey-device-busreporteddevicedesc), and [Compatible IDs](https://learn.microsoft.com/en-us/windows-hardware/drivers/install/devpkey-device-compatibleids) — Windows PnP identifiers and reported descriptions.
- [libgphoto2 PTP implementation](https://github.com/gphoto/libgphoto2/blob/master/camlibs/ptp2/ptp.c) — implementation reference for no-parameter `GetDeviceInfo` and pre-session use; not evidence for the P510 or Windows WPD transport.
- [Nikon firmware-tools source audit](nikon-firmware-tools-source-audit.md) — local-source availability and opaque transport dependencies.
