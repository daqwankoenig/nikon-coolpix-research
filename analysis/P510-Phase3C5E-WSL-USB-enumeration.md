# P510 Phase 3C-5E: WSL USB Enumeration and Non-Root Access

**Final status: WSL ENUMERATION READY + NON-ROOT ACCESS READY - NO PTP COMMAND SENT**

## Scope and outcome

This phase tested usbipd-win transport and passive libusb access only. The P510 enumerated in Ubuntu-24.04 after one attach, its USB node received the intended `root:plugdev` / `0660` permissions, and a single `libusb_open()` as `<LOCAL_USER>` succeeded and was immediately closed.

No PTP client was executed, no interface was claimed, and no PTP operation or application-level USB data transfer was performed. USB enumeration and descriptor inspection were the only USB activity. The camera was detached and Windows ownership via `WUDFWpdMtp` was verified.

## Windows and usbipd state

- usbipd-win version: `5.3.0-54+Branch.master.Sha.aa3db8b82c4cb5071fd31bc54211606c70886912.aa3db8b82c4cb5071fd31bc54211606c70886912`
- Intended device: BUSID `4-1`, VID/PID `04b0:0223`, description `P510`
- Windows PnP instance: `USB\VID_04B0&PID_0223\31100075`
- Windows PnP status: `OK`; driver service after cleanup: `WUDFWpdMtp`

Initial `usbipd list` state:

```text
BUSID 4-1  VID:PID 04b0:0223  DEVICE P510  STATE Shared
```

The camera was already shared/bound. No bind or unbind command was run, and no unrelated USB device was shared.

## WSL health

`wsl --status`:

```text
Default Distribution: Ubuntu-24.04
Default Version: 2
```

`wsl --version`:

```text
WSL version: 3.0.5.0
Kernel version: 6.18.58.1-microsoft-standard-WSL2
WSLg version: 1.0.79
MSRDC version: 1.2.7391
Direct3D version: 1.611.1-81528511
DXCore version: 10.0.26100.1-240331-1435.ge-release
Windows version: 10.0.26340.10013
```

`wsl -l -v` initially showed Ubuntu-24.04 stopped, version 2. Ubuntu was started and kept running for the USB attach.

Inside Ubuntu:

```text
uname -a
Linux 9VY9X54 6.18.58.1-microsoft-standard-WSL2 #1 SMP PREEMPT_DYNAMIC Tue Oct 27 00:24:11 UTC 2026 x86_64 x86_64 x86_64 GNU/Linux

whoami
<LOCAL_USER>
```

## Attach and enumeration

Exact attach command:

```powershell
& 'C:\Program Files\usbipd-win\usbipd.exe' attach --wsl --busid 4-1
```

Complete attach output and exit code:

```text
STDOUT: [empty]
STDERR:
usbipd: info: Using WSL distribution 'Ubuntu-24.04' to attach; the device will be available in all WSL 2 distributions.
usbipd: info: Loading vhci_hcd module.
usbipd: info: Detected networking mode 'nat'.
usbipd: info: Using IP address 172.19.48.1 to reach the host.
EXIT_CODE=0
```

usbipd changed the P510 state from `Shared` to `Attached`. Only BUSID `4-1` was attached.

`lsusb`, `lsusb -d 04b0:0223`, and `lsusb -v -d 04b0:0223` were each attempted. All returned exit code `127` with `bash: lsusb: command not found`. No packages were installed. Passive sysfs inspection and libusb enumeration were used instead.

WSL sysfs reported:

```text
/sys/bus/usb/devices/1-1 04b0:0223
```

Thus WSL-observed VID/PID was `04b0:0223`.

The P510 USB node was:

```text
/dev/bus/usb/001/002
crw-rw---- 1 root plugdev 189, 1 Nov 20 08:27 /dev/bus/usb/001/002
```

| Property | Observed value |
|---|---|
| Owner | `root` |
| Group | `plugdev` |
| Mode | `0660` |

## Rule and user permissions

`id <LOCAL_USER>`:

```text
uid=1000(<LOCAL_USER>) gid=1000(<LOCAL_USER>) groups=1000(<LOCAL_USER>),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),100(users)
```

Existing rule contents, unchanged in this phase:

```udev
SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device", ATTR{idVendor}=="04b0", ATTR{idProduct}=="0223", MODE="0660", GROUP="plugdev"
```

The rule matches only USB device `04b0:0223`; `<LOCAL_USER>` is a member of its assigned `plugdev` group. No permission broadening or chmod was performed.

## Passive libusb validation

The non-root test enumerated USB devices through the already-installed `libusb-1.0.so.0`, read descriptors to identify the exact VID/PID, called `libusb_open()` once, and immediately called `libusb_close()`.

```text
WHOAMI=<LOCAL_USER>
LIBUSB_LIBRARY=libusb-1.0.so.0
LIBUSB_INIT=0
LIBUSB_DEVICE_COUNT=3
MATCH=04b0:0223
LIBUSB_OPEN_RC=0
LIBUSB_OPEN_RESULT=SUCCESS
LIBUSB_CLOSE=SUCCESS
PASSIVE_OPEN_EXIT=0
```

No interface claim, bulk transfer, interrupt transfer, or PTP operation was attempted.

## Cleanup and safety confirmation

Exact detach command:

```powershell
& 'C:\Program Files\usbipd-win\usbipd.exe' detach --busid 4-1
```

The detach command had empty stdout and stderr and exit code `0`. After detach:

- usbipd no longer listed the P510 as connected/attached; the remembered P510 binding remains in usbipd's persisted list.
- WSL reported zero `04b0:0223` sysfs devices.
- Windows again reported P510 status `OK`, class `WPD`, service `WUDFWpdMtp`.
- The Windows driver was not changed.

`P510PTPGetDeviceInfo-hardware` was not executed. The PTP client source and executable were not modified. No PTP operation was sent.

## Final status

**WSL ENUMERATION READY + NON-ROOT ACCESS READY - NO PTP COMMAND SENT**

Stop here. Do not resume Phase 3C-5B automatically.
