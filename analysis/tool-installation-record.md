# Tool Installation Record — Phase 2B

## Authorization and scope

- User approved Phase 2B and expanded the authorized locations to `C:\GitHub\Nikon P510\` and `C:\GitHub\Tools\`.
- Java and Ghidra are reusable tools and are installed under `C:\GitHub\Tools\`. Downloads are retained in `C:\GitHub\Tools\Downloads\`.
- Ghidra first-launch state was redirected to `C:\GitHub\Nikon P510\analysis\ghidra-projects\ghidra-runtime\`. No project database was created.
- No other repository or directory under `C:\GitHub\` was modified. No Windows system directories or global environment settings were changed.

## Official source and checksum verification

| Tool | Official source | Version / filename | Downloaded file | Published SHA-256 | Download SHA-256 | Status |
|---|---|---|---|---|---|---|
| Eclipse Temurin JDK | [Adoptium Temurin 25 release](https://github.com/adoptium/temurin25-binaries/releases/tag/jdk-25.0.5%2B8); official binary URL: `https://github.com/adoptium/temurin25-binaries/releases/download/jdk-25.0.5%2B8/OpenJDK25U-jdk_x64_windows_hotspot_25.0.5_8.zip` | 25.0.5+8, Windows x64, JDK ZIP | `C:\GitHub\Tools\Downloads\OpenJDK25U-jdk_x64_windows_hotspot_25.0.5_8.zip` | `636bdc13dc649ddc7d5921c5c7d23cca6e44fd19d662b45cc9c02135a6c96c42` | `636bdc13dc649ddc7d5921c5c7d23cca6e44fd19d662b45cc9c02135a6c96c42` | **MATCH — verified before extraction** |
| NSA Ghidra | [Official NSA Ghidra 12.2 release](https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.2_build); [official Getting Started requirements](https://github.com/NationalSecurityAgency/ghidra/blob/Ghidra_12.2_build/GhidraDocs/GettingStarted.md); official archive URL: `https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_12.2_build/ghidra_12.2_PUBLIC_20261016.zip` | Ghidra 12.2 public release | `C:\GitHub\Tools\Downloads\ghidra_12.2_PUBLIC_20261016.zip` | `2c2cd776db3c1f6a097ba418922378ac3649cadd5e844a6f5f088ae628a7be67` | `2c2cd776db3c1f6a097ba418922378ac3649cadd5e844a6f5f088ae628a7be67` | **MATCH — verified before extraction** |

The official Ghidra 12.2 guide requires a **64-bit Java 25 Runtime and Development Kit**. The official NSA release page identified Ghidra 12.2 as the latest release when reconfirmed before download. Both archives matched the officially published SHA-256 values; no mismatch occurred.

## Installed locations and verification

- **Java:** `C:\GitHub\Tools\Java\jdk-25.0.5+8\`
- **Ghidra:** `C:\GitHub\Tools\Ghidra\ghidra_12.2_PUBLIC\`
- **Java executable tested:** `C:\GitHub\Tools\Java\jdk-25.0.5+8\bin\java.exe`
- `java -version` output:

  ```text
  openjdk version "25.0.5" 2026-10-20 LTS
  OpenJDK Runtime Environment Temurin-25.0.5+8 (build 25.0.5+8-LTS)
  OpenJDK 64-Bit Server VM Temurin-25.0.5+8 (build 25.0.5+8-LTS, mixed mode, sharing)
  ```

- Java properties confirmed `java.vendor=Eclipse Adoptium`, `java.version=25.0.5`, and `sun.arch.data.model=64`.
- Ghidra's extracted `Ghidra/application.properties` reports `application.version=12.2`.
- **Launch result: successful.** Ghidra logged `Ghidra startup complete`, and a visible `javaw.exe` process from the approved JDK was observed with window title `Ghidra: NO ACTIVE PROJECT`.
- Ghidra selected the approved JDK. Process-local `JAVA_HOME` and `PATH` were used only for the launch; process-local `USERPROFILE`, `APPDATA`, `LOCALAPPDATA`, `TEMP`, and `TMP` kept first-launch state within the authorized project directory.
- User- and machine-level `JAVA_HOME` remain unchanged; neither user nor machine `PATH` was modified. No administrator elevation was used.

## Scope limits and unexpected output

- No firmware analysis project was created; no firmware was imported; no automatic analysis, emulation, debugging, patching, or camera interaction occurred.
- The launch wrapper printed `ERROR: Input redirection is not supported, exiting the process immediately.` in the noninteractive command shell. Despite that console message, Ghidra proceeded to log startup complete and displayed the no-active-project window; the application log contained no `ERROR`, `FATAL`, or exception markers.
- A redundant extraction retry was refused because the Ghidra destination was already populated by the successful extraction. No existing files were overwritten.
