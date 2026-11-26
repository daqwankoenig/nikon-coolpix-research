# P510 Phase 3C-5D: Narrowly Scoped USB Permissions

**Final status: NON-ROOT USB ACCESS FAILED - NO PTP COMMAND SENT**

## Result summary

Phase 3C-5C established that the previous `libusb_open()` failure as `<LOCAL_USER>` was `LIBUSB_ERROR_ACCESS`, despite matching VID/PID, interface, and endpoint descriptors. A narrowly scoped udev rule was installed for only USB device `04b0:0223`, assigning its device node to the existing `plugdev` group with mode `0660`.

The rule could not be validated: after usbipd reported the P510 attached, WSL created no `04b0:0223` sysfs device or device node. Kernel logs stopped at the USB address assignment request. Since the device did not enumerate, `libusb_open()` was not attempted. Non-root access is therefore **not confirmed**, and this phase stops without retries.

## WSL udev/systemd behavior

Read-only inspection of Ubuntu-24.04 found:

- WSL2 distribution: `Ubuntu-24.04`; `/etc/wsl.conf` has `systemd=true`.
- `systemctl is-system-running`: `running`.
- `systemd-udevd.service`: `active`; udev version `255`.
- `systemd-logind.service`: `active`; `<LOCAL_USER>` had an active login session.
- The installed `/usr/lib/udev/rules.d/70-uaccess.rules` includes `SUBSYSTEM=="usb", ENV{ID_USB_INTERFACES}=="*:060101:*", TAG+="uaccess"` for PTP/MTP interfaces.
- `<LOCAL_USER>` was already a member of `plugdev` (GID 46). No group membership change, logout/login, or WSL restart was required.
- `udevadm control --ping` as `<LOCAL_USER>` returned `Permission denied`; the rule reload itself was performed successfully as root.

The existence of systemd, udev, logind, and the standard `uaccess` rule did not by itself establish working device-node permissions. The actual P510 did not enumerate in WSL during this validation, so the new rule's effect remains unverified.

## Rule installed

Exact file: `/etc/udev/rules.d/99-p510-usb.rules`

Exact contents:

```udev
SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device", ATTR{idVendor}=="04b0", ATTR{idProduct}=="0223", MODE="0660", GROUP="plugdev"
```

Recorded metadata:

| Property | Value |
|---|---|
| Owner | `root` |
| Group on rule file | `root` |
| File mode | `0644` |
| Device-node group assigned by rule | `plugdev` |
| Device-node mode assigned by rule | `0660` |
| `<LOCAL_USER>` member of `plugdev` | Yes |

The rule matches only USB device nodes with both vendor ID `04b0` and product ID `0223`; `ENV{DEVTYPE}=="usb_device"` limits the rule to the device node. It does not grant access to unrelated USB devices. No broad Nikon-wide rule or chmod change was made.

### Configuration commands

The rule was written in the Ubuntu-24.04 system filesystem as root. PowerShell passed the rule line through base64 to avoid quoting changes; the resulting command was:

```powershell
wsl.exe -d Ubuntu-24.04 -u root -- bash -lc "echo U1VCU1lTVEVNPT0idXNiIiwgRU5We0RFVlRZUEV9PT0idXNiX2RldmljZSIsIEFUVFJ7aWRWZW5kb3J9PT0iMDRiMCIsIEFUVFJ7aWRQcm9kdWN0fT09IjAyMjMiLCBNT0RFPSIwNjYwIiwgR1JPVVA9InBsdWdkZXYiCg== | base64 -d > /etc/udev/rules.d/99-p510-usb.rules && chown root:root /etc/udev/rules.d/99-p510-usb.rules && chmod 0644 /etc/udev/rules.d/99-p510-usb.rules && udevadm control --reload-rules && stat -c 'owner=%U group=%G mode=%a path=%n' /etc/udev/rules.d/99-p510-usb.rules && cat /etc/udev/rules.d/99-p510-usb.rules"
```

The decoded rule line and permission/reload operations were:

```sh
printf '%s\n' 'SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device", ATTR{idVendor}=="04b0", ATTR{idProduct}=="0223", MODE="0660", GROUP="plugdev"' > /etc/udev/rules.d/99-p510-usb.rules
chown root:root /etc/udev/rules.d/99-p510-usb.rules
chmod 0644 /etc/udev/rules.d/99-p510-usb.rules
udevadm control --reload-rules
```

The rule file is outside the project root and was created only after explicit user authorization for this single WSL system rule.

## Device attachment and passive validation

usbipd-win version:

```text
5.3.0-54+Branch.master.Sha.aa3db8b82c4cb5071fd31bc54211606c70886912.aa3db8b82c4cb5071fd31bc54211606c70886912
```

Before attachment, usbipd listed exactly one connected device matching the target VID/PID:

```text
BUSID 4-1  VID:PID 04b0:0223  DEVICE P510  STATE Shared
```

Windows identified `P510`, instance `USB\VID_04B0&PID_0223\31100075`, with service `WUDFWpdMtp`.

The exact attach command was:

```powershell
& 'C:\Program Files\usbipd-win\usbipd.exe' attach --wsl --busid 4-1
```

usbipd reported attachment to Ubuntu-24.04. WSL's USB/IP kernel log showed a virtual host controller attachment and a high-speed device address assignment request, but the device never appeared with readable `idVendor`/`idProduct` attributes. No P510 device node was created.

| Check | Result |
|---|---|
| WSL target VID/PID | Not observable; target did not enumerate |
| Device-node path | None for the P510 |
| Device-node owner/group/mode before | No P510 node while detached; prior Phase 3C-5C did not preserve node metadata |
| Device-node owner/group/mode after | No P510 node was created |
| Passive `libusb_open()` as `<LOCAL_USER>` | Not attempted; no matching libusb device was enumerable |
| Interface claim / bulk OUT / USB or PTP command | None |
| `P510PTPGetDeviceInfo-hardware` execution | Not executed |

The result is an enumeration failure, not evidence that the udev rule granted or denied access. No retry or alternate permission workaround was attempted.

## Integrity and safety regression

Phase 3C-5A.4 final hardware executable SHA-256:

```text
4CDAA7F497010A131419420C42D2A980100D21BBB69914482746C619172E6CAA
```

Current hardware executable SHA-256:

```text
4CDAA7F497010A131419420C42D2A980100D21BBB69914482746C619172E6CAA
```

The executable remains unchanged. The client source was not modified; its current SHA-256 remains `31A76A18943D416B24E0DF746DCF9E3E1ACFECC948D76B06E2A3C1A073FF11BE`.

No PTP operation was transmitted. No interface was claimed. No Windows driver or P510 firmware was modified.

## Cleanup

The exact detach command was:

```powershell
& 'C:\Program Files\usbipd-win\usbipd.exe' detach --busid 4-1
```

After detach:

- usbipd listed bus ID `4-1` as not shared/attached.
- WSL reported zero `04b0:0223` sysfs devices.
- Windows again detected `P510`, status `OK`, as WPD using `WUDFWpdMtp`.
- The Windows driver was not changed.

## Final status

**NON-ROOT USB ACCESS FAILED - NO PTP COMMAND SENT**

The permission rule is installed but unvalidated because WSL did not enumerate the attached camera. Stop here; do not run the PTP client or resume Phase 3C-5B automatically.
