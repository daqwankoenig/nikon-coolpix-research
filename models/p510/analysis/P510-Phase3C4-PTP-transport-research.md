# P510 Phase 3C-4: Safe PTP Transport Research

**Status:** Offline research only. No camera connection or PTP/USB command was made during this phase.  
**Target:** Nikon COOLPIX P510, VID `04B0`, PID `0223`, Firmware 1.0 from confirmed physical-camera observation.

## Executive result

The safest candidate for a future Phase 3C-5 test is a **source-reviewed, minimal libusb/libgphoto PTP client running in Linux or WSL**, not `gphoto2 --auto-detect`, not libmtp utilities, not NikonDump, and not the Windows WPD vendor-extension route.

The client should perform only:

1. Identify USB `04B0:0223`.
2. Open the PTP interface and claim its standard PTP bulk/interrupt endpoints.
3. Send PTP `GetDeviceInfo (0x1001)` with zero parameters.
4. Receive and decode the data phase.
5. Close USB cleanly without issuing any vendor operation or PTP session operation.

This would leave the existing Windows `WUDFWpdMtp` driver in place during Windows PnP/USB discovery. Transferring USB control of the device to WSL/Linux must be a separately approved, reversible USBIP/driver step. It may require USB ownership or driver rebinding outside Windows.

**No exact P510/PID 0223 support entry was found in the source paths reviewed.** The exact P510 VID/PID association is confirmed only in the local Nikon Wireshark table:
`0x04b00223` — `Nikon Coolpix P510`.

## Existing evidence search

### Local exact-reference search

Searched local project and tool trees for:

- `P510`
- `COOLPIX P510`
- `04B0`
- `0x04B0`
- `0223`
- `0x0223`
- `04B0:0223`

Findings:

| Source | Exact result |
|---|---|
| `nikon-firmware-tools/USB/wireshark/release/wireshark_usb_ptp_20130302.patch` | `0x04b00223`, `Nikon Coolpix P510` |
| `nikon-firmware-tools/USB/wireshark/release/wireshark_usb_ptp_20130305.patch` | `0x04b00223`, `Nikon Coolpix P510` |
| `nikon-firmware-tools/USB/wireshark/release/wireshark_usb_ptp_20130302.patch` | `0x04b00184`, `Nikon Coolpix P500` |
| `nikon-firmware-tools/USB/wireshark/release/wireshark_usb_ptp_20130305.patch` | `0x04b00184`, `Nikon Coolpix P500` |
| nikon-firmware-tools CameraModels | No P510 profile |
| nikon-firmware-tools NikonDump | No P510 profile; generic Nikon VID selection |
| libgphoto/libmtp source not already cloned | No exact P510/PID match established by local source evidence |

The exact Wireshark association is model-ID evidence, not proof of P510 firmware compatibility or that a capture/control library is suitable.

## Candidate tools

| Candidate | Transport/source | Windows direct support | WSL/Linux support | P510-specific evidence | Can isolate GetDeviceInfo? | Risk / recommendation |
|---|---|---|---|---|---|---|
| Custom minimal PTP client using libusb plus libgphoto PTP source (`ptp.c`, `ptp-pack.c`, `usb.c`) | USB bulk transfer/endpoint packets | Possible only with WinUSB/libusb binding, typically replacing WPD ownership; not recommended | Yes, via WSL/libusb or native Linux | USB table confirms VID/PID model name; no P510 source support entry found | Yes, if custom code sends only `0x1001` and no session | **PROMISING / future Phase 3C-5 candidate after USB ownership and source review** |
| libgphoto2 PTP backend | libusb, PTP/IP, USB port abstractions | Some Windows builds exist, but direct use may require WinUSB/libusb and is not established as preserving WUDF | Yes with USB transfer to WSL/Linux | Generic PTP backend; exact P510 PID support not established | Source-level possible, but normal library init may add session/storage/property operations | **RESEARCH ONLY** |
| gphoto2 command-line | Calls libgphoto2 | Not established as a safe native Windows path | Linux/WSL after USB attachment | No exact P510 support entry established | Not safely isolated: normal startup/abilities may enumerate device, open session, query storage, and probe capabilities | **NOT RECOMMENDED for minimum test** |
| libmtp | libusb 1.0 plus copied libgphoto PTP code | Windows support is uncertain and may depend on libusb; not an established WPD preserve path | Yes | No exact P510 entry established | Not isolated: initialization is MTP-oriented and may request storage/files/properties | **NOT RECOMMENDED for DeviceInfo-only test** |
| `mtp-detect` / libmtp utilities | libmtp initialization | Native Windows support not established | Linux/WSL | Generic MTP only | No: detection commonly initializes MTP and storage state | **NOT RECOMMENDED** |
| Windows WPD COM APIs | Existing `WUDFWpdMtp` | Direct/native support | Not required | PnP confirms WPD/MTP/PTP | Raw PTP DeviceInfo wrapper is unavailable; MTP-extension execute is vendor-operation category | **NOT CURRENTLY SUFFICIENT** |
| NikonDump | WPD plus Nikon vendor paths | Windows | Not the safest Linux target | No P510 profile; generic Nikon VID match | No | **DO NOT USE** |
| PTP-over-USB browser/other GUI tools | Usually libgphoto/libmtp or vendor SDK | Varies | Varies | Model support unknown | Usually not isolated | **NOT RECOMMENDED** |

## libgphoto2 source findings

Relevant public source locations:

- `camlibs/ptp2/ptp.h`
  - defines PTP USB container format
  - defines standard `PTP_OC_GetDeviceInfo` as `0x1001`
  - defines `PTP_OC_OpenSession` `0x1002`
  - defines `PTP_OC_CloseSession` `0x1003`
  - defines standard storage, object, capture, property, format, and vendor extension opcodes
- `camlibs/ptp2/ptp.c`
  - implements `ptp_transaction_new`
  - builds operation containers
  - sends request, optional data phase, and response
- `camlibs/ptp2/usb.c`
  - implements USB bulk request/data/response transactions
  - sends PTP bulk command packets
  - reads device-to-host data
  - can clear endpoint stalls
- `camlibs/ptp2/library.c`
  - contains `print_debug_deviceinfo`, which prints all `PTPDeviceInfo` fields and supported code arrays
  - contains fixups that may add vendor operations or set MTP-specific properties for particular vendors/models
- `camlibs/ptp2/cameras/`
  - holds camera-specific logs/support notes
- `camlibs/ptp2/ptp-bugs.h` / `device-flags.h`
  - contains Nikon and device-specific behavior flags

For an identification-only implementation, the promising route is to use libgphoto/libmtp PTP packet and parsing code, but **not normal `gphoto2` camera initialization** unless it is source-inspected and constrained.

`ptp_getdeviceinfo` would send only `0x1001` if called directly with a live PTP parameter block and no later helper calls. The function itself is not proof that normal camera initialization will remain so limited.

### First-connection behavior of established tools

#### libgphoto2/gphoto2

Normal initialization can include:

1. USB port enumeration or explicit USB URI selection.
2. Claim/open PTP USB interface.
3. PTP parameter/session setup.
4. `OpenSession (0x1002)`, depending on camera and port initialization path.
5. `GetDeviceInfo (0x1001)`.
6. Additional standard operations, especially storage and object enumeration, depending on the requested command or camera filesystem setup.
7. Vendor or fixup operations for devices recognized by existing tables/flags.

A tool such as `gphoto2 --summary` or `gphoto2 --auto-detect` is **not an exact-only GetDeviceInfo probe**. `--auto-detect` itself is primarily discovery; source initialization may issue session/device queries and storage/object operations.

A custom `ptp_getdeviceinfo` call before session may avoid `OpenSession`, storage, and object enumeration, but P510 acceptance is unknown and must be experimentally bounded.

#### libmtp

libmtp is MTP-oriented. It uses libgphoto PTP packet code, libusb, and an MTP device table. Normal detection in `libusb1-glue.c`:

- enumerates/libusb-opens MTP-like interfaces
- can probe string descriptors
- can inspect WUSB/vendor behavior
- initializes PTP/MTP parameters
- normally continues into MTP device initialization/storage enumeration

It is not the preferred isolation candidate.

## P510/VID-PID support evidence

### Confirmed database/reference association

The local Nikon Wireshark patch table associates:

- VID: `04B0`
- PID: `0223`
- packed Nikon USB ID: `0x04b00223`
- device name: `Nikon Coolpix P510`

This is directly consistent with Windows PnP observation. It does not prove that P510 appears in libgphoto2 or libmtp's model database.

### libgphoto2

No exact P510 or PID `0223` match was established from the available public-source review. GitHub's anonymous code search required sign-in and was not used as evidence.

The public source has generic Nikon PTP support and Nikon-specific flags/functions. It may recognize P510 through a generic USB PTP device entry rather than a model name. Generic support must not be interpreted as P510-specific validation.

### libmtp

No exact P510 or PID `0223` match was established from the public source reviewed. libmtp's device table is primarily an MTP device table and should not be treated as P510 support.

The public source can include Nikon-related vendor behavior, but source presence does not establish P510 applicability.

## Nikon-specific operation risk

Public gphoto/libmtp PTP headers contain Nikon operation/property constants and fixups for Nikon-specific device behavior. Relevant examples include:

- Nikon vendor operations and vendor properties
- `PTP_VENDOR_NIKON`
- Nikon capture/device flags
- Nikon event/property handling

These values are not evidence that a particular Nikon operation applies to P510. The P510 should remain in unknown state until the camera's own `GetDeviceInfo` reports vendor-extension ID and operations.

NikonDump/nikon-firmware-tools was reviewed previously and is unsuitable:

- no P510 CameraModels profile
- first NIkon WPD device can be selected without P510 PID verification
- intended path includes Nikon vendor operations and service-mode state changes
- memory/EEPROM write paths exist in source

## USB and Windows/WSL constraints

### Native Windows + WPD

Advantages:

- existing WUDFWpdMtp driver remains in place
- no permanent WinUSB/libusb binding
- PnP and basic device metadata remain available

Limitation:

- normal WPD interfaces do not provide a demonstrated standard-only `GetDeviceInfo` wrapper
- WPD MTP-extension execute/read/end-transfer APIs belong to vendor-operation category
- open/close/session behavior is not fully source-verifiable

### Native Windows + libusb

Would probably require detaching WUDFWpdMtp or rebinding the PTP interface to WinUSB/libusb. This conflicts with the "without replacing the Windows driver" objective unless a reversible temporary route is approved separately.

### WSL/Linux

WSL may reach the camera through USB/IP only after a separate USB attachment step. The established mechanism is external USB forwarding (for example usbipd), but this requires software/privileges and changes Windows ownership of the camera's USB interface.

There would be no permanent WinUSB binding to the P510 if an approved USB/IP session is detached afterward and Windows reclaims WUDF. This must still be reviewed and approved before use.

The camera USB interface may also be retained by Windows WPD while USB/IP forwarding is attempted. The bus must not be forcibly rebound or reset without approval.

## Risk table

| Method | P510 evidence | Camera connection | Writes camera? | Driver change? | Firmware risk | Bricking risk | Expected output | Confidence | Recommendation |
|---|---|---|---|---|---|---|---|---|---|
| PnP only | Direct Windows PnP | USB enumeration | No PTP write | No | None known | None | VID/PID, name, WPD/MTP metadata | High | **SAFE COMPLETED** |
| WPD vendor-extension execute/read/end | Generic Microsoft API | WPD application session | Potentially vendor/operation-dependent | No permanent binding | Unknown | Low-to-unknown | Vendor operation response only | Low | **NOT RECOMMENDED** |
| gphoto2 normal commands | Generic PTP/Nikon support | USB/libusb | Can enumerate/read but may support writes/capture | Native Win: likely binding; WSL: USB forwarding | Low for read-only commands, but startup behavior can expand | Low/unknown | Device summary/storage/files | Medium for transport, low for isolation | **NOT RECOMMENDED as minimum test** |
| libmtp tools | Generic MTP support | USB/libusb | Potentially property/file operations | Native Win: likely binding; WSL: USB forwarding | Low for detection, startup behavior unknown | Low/unknown | MTP device/storage/properties | Low for P510 | **NOT RECOMMENDED** |
| NikonDump/NikonFlags | Nikon DSLR source only | WPD/vendor | Yes, EEPROM/RAM/write paths exist | No established WPD support | High | High | EEPROM/memory dumps | Low P510; high risk | **NOT RECOMMENDED** |
| Minimal libusb+PTP client | Generic PTP source plus exact VID/PID database evidence | USB/libusb | No if source allows exact packet path | Native Win: driver change; WSL: reversible USB forwarding | Low if only 0x1001 | Low; unknown P510 pre-session behavior | Raw DeviceInfo | High transport feasibility, medium P510 acceptance | **PROMISING / safest candidate** |

## Recommended Phase 3C-5 procedure

**Do not execute now.** The following is an approval-gated proposal.

1. **Obtain separate approval** for USB communication and for a reversible Linux/WSL USB transfer. Do not use it in Windows WPD mode.
2. **Do not install software or usbipd until explicitly approved.** If approved, verify source/commit and packages offline or through an approved package process.
3. **Choose a Linux/WSL environment** with libusb and source code pinned to an exact commit. Use a custom, read-only PTP client rather than normal gphoto2/libmtp utilities.
4. **Preflight in Windows PnP only:** record USB VID/PID and `WUDFWpdMtp`; verify no third-party software/driver prompt appears.
5. **Attach only the P510** to WSL/Linux using usbipd or an equivalent reversible mechanism; do not attach other USB devices.
6. **Do not issue USB descriptors beyond normal enumeration** inside the PTP client. Identify endpoints by USB configuration/interface.
7. **Open only the PTP interface** and claim it. Do not clear stalls, reboot, reset, or send control/vendor requests.
8. **Send exactly one PTP command:** `GetDeviceInfo (0x1001)`, `Nparam=0`, no operation parameters, device-to-host data phase.
9. **Do not send `OpenSession (0x1002)` initially.** PTP allows a pre-session `GetDeviceInfo` in the protocol implementation; P510 acceptance is unknown. If the P510 requires a session, stop rather than retrying.
10. **Receive and parse the data phase** using a bounded DeviceInfo parser. Do not follow operationsSupported arrays or send them.
11. **Record** all raw fields, response code, supported operations/events/properties, capture/image formats, and exact packet bytes/checksum, while redacting serial number by default.
12. **Close only the USB interface** and detach WSL; do not send `CloseSession (0x1003)` unless session state was opened.
13. **Verify Windows** has reclaimed `WUDFWpdMtp` and no third-party driver remains bound.
14. **Stop.** Do not execute any vendor or 0x9000-0xFFFF code and do not access storage, objects, capture, memory, properties, or firmware.

Phase 3C-5 should be separately approved as camera communication. It is not approved by this research report.

## Recommended candidate

**A source-pinned minimal libusb/PTP implementation**, derived only from the standard PTP transaction and parser code in libgphoto2's `ptp.c`, `ptp-pack.c`, and `usb.c`, is the safest established transport candidate.

It is preferred over gphoto2/libmtp because it can be source-bounded to exactly one read-only PTP operation. It is still not considered safe until:

- the USB ownership/WSL transfer step is explicitly approved,
- the PTP client source is reviewed,
- no automatic fixups/vendor flags/camera init routines are included,
- and the user approves Phase 3C-5 itself.

## Conclusion

The exact P510 USB product table association is established in the Nikon Wireshark source. P510-specific support in libgphoto2/libmtp is not established in the source reviewed. A normal gphoto2 or libmtp utility is likely to do more than minimal identification. The safest research candidate is a minimal standard PTP implementation that sends only `GetDeviceInfo`, with reversible WSL USB forwarding as a future transport and no permanent Windows driver replacement.
