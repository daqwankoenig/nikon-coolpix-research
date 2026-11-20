# Nikon COOLPIX P510 Research Rules

## Evidence labels

Use these labels consistently and identify the model and source for each finding:

- **CONFIRMED P510** — directly supported by the physical P510, its preserved captures, or authoritative P510-specific documentation.
- **CONFIRMED REFERENCE MODEL** — directly supported for a named reference model, such as P500 or P520; not evidence of P510 behavior.
- **STRONGLY SUPPORTED HYPOTHESIS** — supported by substantial evidence but not directly confirmed for the stated model.
- **HYPOTHESIS** — plausible interpretation that remains unverified.
- **UNKNOWN** — evidence is insufficient to assign a meaning or conclusion.

P500/P520 findings are reference evidence only unless independently supported on P510. State model provenance next to every transferred comparison. Never imply compatibility from model numbering, package similarities, shared strings, or architectural resemblance.

Do not assign speculative meanings to unknown numeric PTP operations, properties, events, or image-format codes. Preserve exact values and mark them **UNKNOWN** until an exact, provenance-qualified mapping is established.

## Firmware preservation and handling

- `firmware/original/P510/` remains empty until authentic P510 firmware is obtained or dumped.
- Never modify or overwrite anything in `firmware/original/`.
- Calculate and record SHA-256 before working with any firmware; analyze a separate working copy.
- Extracted firmware belongs in `firmware/extracted/`; experimental modifications, if ever separately authorized, belong in `firmware/modified/`.
- P500/P520 firmware is reference-only. Never flash it to P510, copy it into P510 original/modified directories, or treat its code as P510 code.
- Before any future firmware-binary modification, create and verify a backup. No firmware write or flash is currently authorized.
- Do not bypass cryptographic signatures, secure boot, access controls, or anti-tamper protections.

## Physical-camera safety

Physical-camera testing requires explicit justification and a bounded safety plan stating the exact question, equipment/commands, expected effects, stop conditions, and recovery path. Authorization for one operation does not authorize other operations.

Current status:

- Working P510 hardware investigation: **NOT JUSTIFIED**
- Unknown PTP command execution: **NOT JUSTIFIED**
- Firmware modification: **BLOCKED**
- Firmware flashing: **BLOCKED**
- Donor acquisition: **DEFERRED**

Do not connect to, communicate with, open, probe, modify, or flash the camera without specific prior approval for the proposed action. Codespaces is not a physical-camera test environment.

## Project hygiene and redistribution

- Keep reports in `analysis/`, source and validation scripts in `scripts/`, checksums/manifests in `checksums/`, and third-party utilities in `tools/`.
- Keep credentials, tokens, private keys, passwords, cookies, and local authentication data out of the repository.
- Do not commit third-party firmware, installers, manuals, proprietary binaries, or research images unless redistribution is clearly appropriate. Prefer source URL, provenance, filename, size, and SHA-256 metadata.
- Do not delete historical reports or artifacts merely because they are excluded from Git.
- Do not initialize, publish, or push a repository without explicit user authorization.

See [PROJECT-MANIFEST.md](PROJECT-MANIFEST.md) for the current inventory, preservation decisions, and excluded-artifact records.
