# GitHub Privacy Audit

## Categories searched

- Known local Windows/WSL account identifier and generic usernames.
- Windows profile paths and Linux home paths.
- Personal email addresses.
- Passwords, password assignments, saved logins, and credential files.
- GitHub, API, OAuth, and bearer tokens; authorization headers.
- Private/SSH keys; cookies and session credentials.
- Credential-bearing URLs and connection strings.
- Windows credential commands and environment/configuration files.
- Source, Markdown, TXT, logs, scripts, JSON/configuration, manifests, command output, and the P510 raw DeviceInfo capture.

## Files requiring sanitization

- `analysis/ghidra-logs/P500-D4-landmark-analysis.log`
- `analysis/ghidra-logs/P500-D4-source-context.log`
- `analysis/ghidra-logs/P500-expanded-analysis.log`
- `analysis/ghidra-logs/P500-expanded-inventory.log`
- `analysis/ghidra-logs/P500-ghidra-arm-import.log`
- `analysis/ghidra-logs/P500-init-continuation.log`
- `analysis/ghidra-logs/P500-limited-analysis.log`
- `analysis/ghidra-logs/P500-limited-drycheck.log`
- `analysis/ghidra-logs/P500-limited-inventory.log`
- `analysis/ghidra-logs/P500-limited-precheck.log`
- `analysis/ghidra-logs/P500-NPROG-primary-offsets-import.log`
- `analysis/ghidra-logs/P500-Phase5B-extended-trace.log`
- `analysis/P510-GetDeviceInfo-transport.log`
- `analysis/P510-Phase3C5A2-WSL-build-validation.md`
- `analysis/P510-Phase3C5A3-hardware-build-validation.md`
- `analysis/P510-Phase3C5B-physical-GetDeviceInfo.md`
- `analysis/P510-Phase3C5C-USB-descriptor-analysis.md`
- `analysis/P510-Phase3C5D-USB-permissions.md`
- `analysis/P510-Phase3C5E-WSL-USB-enumeration.md`
- `analysis/P510-USB-descriptors.txt`

## Type of information removed

- Local WSL/Linux account-name occurrences and the username component of local Windows profile paths were replaced with `<LOCAL_USER>`.
- No password, token, key, or other authentication secret was found or removed.

## Files intentionally excluded

- 205 files covered by `.gitignore`, including P500/P520 firmware, Nikon manuals/installers and extracted content, third-party board images and saved web-page bodies, build outputs, Ghidra databases/runtime state, and temporary files.
- Credential/configuration patterns are protected by `.gitignore`; no matching credential files were present.

## Second-pass result

- Repository-bound files scanned: **134** (133 text-readable files and the raw DeviceInfo capture).
- **PASSWORDS FOUND IN REPOSITORY-BOUND FILES: 0**
- **TOKENS/API KEYS FOUND: 0**
- **PRIVATE KEYS FOUND: 0**
- **UNINTENDED USERNAMES FOUND: 0**
- **UNINTENDED PERSONAL PATHS FOUND: 0**
- Personal email addresses, cookies/session credentials, authorization headers, and credential-bearing connection strings found: **0**
- **SECOND-PASS PRIVACY SCAN: PASSED**
