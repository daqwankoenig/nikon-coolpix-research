# P510 Phase 3C-5B: Future GetDeviceInfo Execution Plan

**Status:** PLANNING ONLY — NOT EXECUTED and NOT AUTHORIZED by Phase 3C-5A.

## Objective

After separate approval, retrieve only the P510 PTP `GetDeviceInfo (0x1001)` dataset using a reversible WSL/USB transport.

## 1. WSL/usbipd preparation

Do not perform until a separate approval names the exact software/install step.

1. Verify WSL is already installed. Do not install WSL for this phase.
2. Do not install `usbipd`, libusb, compiler, or packages yet.
3. If software installation is later approved, record exact versions and package sources.
4. Pin the libgphoto2 source revision `31a2f4089f19aec6caca7920b03e3eb7a251c5b6`.
5. Review and build the purpose-built source only. Do not build gphoto2, libmtp, NikonDump, or NikonFlags.
6. Compile the source with hardware enablement only after source review:
   - `P510_ALLOW_USB=1`
   - no arbitrary operation option
   - operation allowlist locked to `0x1001`

## 2. Reversible attachment

Do not perform now.

1. With the P510 still controlled by Windows, record the WPD PnP node.
2. Do not attach any other USB device.
3. Use Windows USB forwarding only after the exact usbipd/device command set is approved.
4. Attach only bus/device matching VID `04B0`, PID `0223`.
5. Do not replace or detach `WUDFWpdMtp` outside the reversible USB forwarding mechanism.
6. If Windows or usbipd offers an unrelated device, cancel.

## 3. Linux confirmation

In WSL/Linux, after attachment:

```text
lsusb -d 04b0:0223
```

Before running the client, confirm:

- exactly one `04b0:0223` device
- one still-image/PTP interface `06/01/01`
- bulk IN endpoint
- bulk OUT endpoint
- interrupt endpoint, if present

Do not enumerate storage or objects.

## 4. Exact client invocation

Run the purpose-built client exactly once.

No command-line operation code is permitted. The source may expose no generic operation option.

The expected outgoing container is:

```text
length=12
type=command 0x0001
code=GetDeviceInfo 0x1001
transaction=1
session=0
parameters=none
```

The client must:

- refuse unexpected VID/PID
- refuse unexpected interface
- require exactly one match
- perform exactly one PTP operation
- not call `OpenSession`
- not call `CloseSession`
- not poll vendor operation codes
- not read storage, objects, properties, memory, or firmware

## 5. Capture raw output

Capture:

- command-line stdout
- selected USB bus/device/interface
- endpoint addresses
- outgoing container hex
- received container lengths/types/codes
- transaction IDs
- PTP response code
- raw `P510-GetDeviceInfo.raw.bin`
- parsed fields

The serial number must be redacted in text logs while retaining it only inside the raw file if the user later approves retention.

Save the raw file only inside the project workspace. Compute SHA-256 immediately after transfer.

## 6. Immediate detachment

Stop the client as soon as:

- PTP OK is received and parsed, or
- a failure, unexpected response, session-required response, or transaction mismatch occurs.

Immediately detach only the P510 USB bus/device from WSL.

Do not leave USB forwarding attached.

Do not detach other devices or reset the host controller.

## 7. Windows recovery confirmation

After USB detachment:

1. Verify the P510 PnP node appears normally.
2. Verify Windows class remains WPD.
3. Verify service remains `WUDFWpdMtp`.
4. Verify no libusb/WinUSB device remains.
5. Verify no third-party driver or software prompt remains.
6. Capture PnP status and problem code.
7. If WUDFWpdMtp does not return, stop and do not retry PTP.

## Success criteria

Phase 3C-5B is successful only if:

- exactly one standard PTP `GetDeviceInfo (0x1001)` operation was sent
- no OpenSession/CloseSession operation was sent
- no vendor or 0x9000-0xFFFF operation was sent
- no property, object, storage, capture, memory, or firmware operation was sent
- a PTP OK response and raw DeviceInfo payload were captured
- Windows reclaimed WUDFWpdMtp normally

## Abort criteria

Stop without retry if:

- the P510 requires OpenSession
- the response is not PTP OK
- transaction or container mismatch occurs
- a vendor operation appears necessary
- USB ownership/driver state is not reversible
- Windows prompts for a driver replacement
- any property or object operation is attempted by the tool

The P510 should not be tested again until the exact failure is documented.
