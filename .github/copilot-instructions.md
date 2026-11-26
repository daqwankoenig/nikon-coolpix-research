# Nikon COOLPIX Firmware Research Rules

These instructions apply to every camera model in this repository. Full rules are in `RESEARCH-RULES.md`. The shared goals are in `docs/standards/goals.md`.

## Scope

- This project is for firmware and hardware research on the Nikon COOLPIX models listed in `README.md` (currently P510, P520, and P500).
- Physical-camera actions apply only to cameras the project owner has explicitly approved for that action. Approval for one camera does not cover another camera.
- Findings are model-scoped. A fact about one model is only a hypothesis for another model until independently confirmed.

## Firmware handling

- Firmware lives only in the local, Git-ignored `firmware/` folder, with a subfolder per model: `firmware/original/<MODEL>`, `firmware/reference/<MODEL>`, `firmware/extracted/<MODEL>`, and `firmware/modified/<MODEL>`.
- `firmware/original/<MODEL>` must stay empty until actual firmware for that model is obtained or dumped. Currently `firmware/original/P510` is empty.
- Never modify anything in `firmware/original`.
- Never overwrite an original firmware image.
- Calculate and record SHA-256 before working with firmware.
- Extracted firmware belongs in `firmware/extracted/<MODEL>`.
- Experimental modifications belong in `firmware/modified/<MODEL>`.
- Firmware from one model is a reference sample only for every other model (for example, P500 and P520 firmware in `firmware/reference/` when working on the P510).
- Never flash one model's firmware to a different model.
- Never assume binary compatibility between models.
- Never copy one model's binary into another model's original or modified directories.
- Reference firmware may be analyzed to understand Nikon firmware packaging, headers, compression, filesystem structure, architecture, checksums, naming conventions, and update mechanisms.
- Label all conclusions about a model that are based on neighboring models as hypotheses until confirmed from that model's hardware or actual firmware.
- Before modifying any firmware binary, create a verified backup.
- Never perform destructive operations on original firmware.
- Prefer read-only static analysis before any modification.

## File locations

- Analysis notes belong in `models/<model>/analysis/`.
- Cross-model reports belong in `comparisons/`.
- Scripts created for this project belong in `models/<model>/scripts/`.
- Third-party research utilities and tool notes belong in `common/tools/`.
- Checksums and integrity records belong in `models/<model>/checksums/` (shared ones in `common/checksums/`).
- Backups belong in `backups/` (local only, Git-ignored).
- Do not rewrite historical reports to update file paths. Use `docs/history/PATH-MAP.md` instead.
- Do not create files outside `C:\Dev\nikon-coolpix-research`.

## Evidence and tools

- Clearly distinguish confirmed findings, assumptions, and unknowns, using the labels in `RESEARCH-RULES.md`.
- Name the model for every finding.
- Do not assume a tool supports a COOLPIX model simply because it supports another Nikon camera.

## Safety and approvals

- Do not flash firmware to any camera unless I explicitly approve that step.
- Do not communicate with any camera over USB unless I explicitly approve it.
- Do not bypass cryptographic signatures, secure boot, access controls, or anti-tamper protections.
- Ask for approval before installing software, cloning repositories, downloading tools, or executing unfamiliar third-party code.
- When executing a command that could modify firmware or interact with hardware, explain the command and affected files first.
- Never commit firmware, installers, manuals, or third-party images. Record hashes, provenance, and notes instead.

## Adding a new model

- Follow the "Adding a new model" steps in `RESEARCH-RULES.md`.
- A new model starts with every physical-camera action blocked until I approve it.
- Once a goal exists for any model, track it for every model.
