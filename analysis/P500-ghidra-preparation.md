# P500 Ghidra Preparation — Phase 2A

> **Phase 2B update:** Following explicit approval, Ghidra 12.2 and Temurin JDK 25.0.5+8 were downloaded from official sources, SHA-256 verified, and extracted under `C:\GitHub\Tools\`. The current installation and launch record is in [tool-installation-record.md](./tool-installation-record.md). This supersedes the proposed C:\Tools paths and commands below.

## Readiness inspection

The Phase 2A inspection was read-only. At that time, no software had been installed or downloaded, no Ghidra project had been created, and no firmware had been imported or analyzed.

| Check | Result |
|---|---|
| Ghidra installed | **Not found.** No Ghidra installation was found in the common C: install roots, user program folders, likely software folders on the other local drives, PATH, or installed-app registry entries. |
| 64-bit Java JDK installed | **Not found.** `java` and `javac` are not on PATH; `JAVA_HOME` is unset; no Java/JDK installation was found in the checked install roots or installed-app registry. The OS is 64-bit. |
| Installed Java version/vendor | **None detected.** Not applicable. |
| Compatible with current official Ghidra | **Not ready.** The current official release is Ghidra 12.2, whose official Getting Started guide requires a 64-bit Java 25 Runtime and Development Kit. No Java installation is present to meet that requirement. |
| Free disk space | **700.51 GiB** available on C:, exceeding the requested 10 GB. |
| Primary target SHA-256 | `42B9EFA22A14CC6000054BB11F2C321B0AA3D4148616096F375880B6AD355A29`; **matches** the value in `checksums/P500-section-hashes.txt`. |

The secondary `P500-SG583SLAVE-payload.bin` remains reserved for later analysis. `P500-SFIRM-composite-payload.bin` is explicitly excluded as an independent image because it wraps the slave record and trailer.

## Missing prerequisites and official sources

1. **Ghidra:** Recommend the official NSA release **Ghidra 12.2**. Official release page: <https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.2_build>. Official archive: `ghidra_12.2_PUBLIC_20261016.zip`; published SHA-256: `2c2cd776db3c1f6a097ba418922378ac3649cadd5e844a6f5f088ae628a7be67`.
2. **Java:** Recommend the 64-bit **Eclipse Temurin JDK 25.0.5+8** ZIP. Official Adoptium release: <https://github.com/adoptium/temurin25-binaries/releases/tag/jdk-25.0.5%2B8>. Official package SHA-256: `636bdc13dc649ddc7d5921c5c7d23cca6e44fd19d662b45cc9c02135a6c96c42`.

The official Ghidra release guide states that Ghidra is distributed as an archive and does not require a traditional installer. The proposed extraction locations are `C:\Tools\Ghidra\` and `C:\Tools\Java\jdk-25.0.5+8\`. Download archives would be staged under `C:\GitHub\Nikon P510\tools\downloads\` so they remain within the project workspace.

**Administrator rights:** Not normally needed for extracting the ZIP distributions for personal use. Creating or writing to `C:\Tools\` may require elevation depending on this computer's directory permissions. No command below was run. Because `C:\Tools\` is outside the project's established exclusive root, explicit authorization to relax that project rule is also needed before creating files there.

## Phase 2A proposed commands — superseded; not run

These were the Phase 2A proposal and were not run. Phase 2B used the newly approved `C:\GitHub\Tools\` locations and the installation record linked above. No project or firmware was created/imported and no automatic analysis was run.

```powershell
$ErrorActionPreference = 'Stop'
$downloadDir = 'C:\GitHub\Nikon P510\tools\downloads'
$jdkZip = Join-Path $downloadDir 'OpenJDK25U-jdk_x64_windows_hotspot_25.0.5_8.zip'
$ghidraZip = Join-Path $downloadDir 'ghidra_12.2_PUBLIC_20261016.zip'
$jdkHome = 'C:\Tools\Java\jdk-25.0.5+8'
$ghidraHome = 'C:\Tools\Ghidra\ghidra_12.2_PUBLIC'

New-Item -ItemType Directory -Path $downloadDir -Force | Out-Null
if (Test-Path -LiteralPath $jdkZip) { throw "Refusing to overwrite $jdkZip" }
if (Test-Path -LiteralPath $ghidraZip) { throw "Refusing to overwrite $ghidraZip" }
if (Test-Path -LiteralPath $jdkHome) { throw "Refusing to overwrite $jdkHome" }
if (Test-Path -LiteralPath $ghidraHome) { throw "Refusing to overwrite $ghidraHome" }
New-Item -ItemType Directory -Path 'C:\Tools\Java','C:\Tools\Ghidra' -Force | Out-Null

Invoke-WebRequest -Uri 'https://github.com/adoptium/temurin25-binaries/releases/download/jdk-25.0.5%2B8/OpenJDK25U-jdk_x64_windows_hotspot_25.0.5_8.zip' -OutFile $jdkZip
if ((Get-FileHash -LiteralPath $jdkZip -Algorithm SHA256).Hash -ne '636bdc13dc649ddc7d5921c5c7d23cca6e44fd19d662b45cc9c02135a6c96c42') { throw 'Temurin JDK archive SHA-256 mismatch' }
Expand-Archive -LiteralPath $jdkZip -DestinationPath 'C:\Tools\Java'

Invoke-WebRequest -Uri 'https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_12.2_build/ghidra_12.2_PUBLIC_20261016.zip' -OutFile $ghidraZip
if ((Get-FileHash -LiteralPath $ghidraZip -Algorithm SHA256).Hash -ne '2c2cd776db3c1f6a097ba418922378ac3649cadd5e844a6f5f088ae628a7be67') { throw 'Ghidra archive SHA-256 mismatch' }
Expand-Archive -LiteralPath $ghidraZip -DestinationPath 'C:\Tools\Ghidra'

$env:JAVA_HOME = $jdkHome
$env:Path = "$jdkHome\bin;$env:Path"
& "$jdkHome\bin\java.exe" -version
if (-not (Test-Path -LiteralPath (Join-Path $ghidraHome 'ghidraRun.bat'))) { throw 'Ghidra extraction check failed' }
```

The commands above are proposals only. No installation, download, project creation, firmware import, automatic analysis, emulation, or debugging has been performed.
