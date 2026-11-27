# Nikon COOLPIX Firmware Research Rules

These instructions apply to every camera model in this repository. Full rules are in `RESEARCH-RULES.md`. The shared capability catalog and adopted goals are in `docs/standards/capability-vocabulary.md` and `docs/standards/goals.md`.

## Scope

- This project is for firmware and hardware research on the Nikon COOLPIX models listed in `README.md` (currently P510, P520, and P500).
- Physical-camera testing does not require written justification.
- Physical-camera testing is at Daqwan's discretion.
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
- For each capability, record Built in? (Native / Partial / Not native / Unknown), Unlock (Not needed / Unknown / Not possible / Possible / Achieved), evidence label, and evidence basis (Manual only / Observed on camera / Both).
- Absence from a manual alone caps the evidence label at STRONGLY SUPPORTED HYPOTHESIS.
- A finding about one model is never a fact about another model. If it might apply elsewhere, record it on the other model as HYPOTHESIS (from <MODEL> finding <ID>) and link the source. It becomes CONFIRMED only after evidence is gathered on that model itself.
- Nothing is CONFIRMED without Daqwan's approval.
- Do not assume a tool supports a COOLPIX model simply because it supports another Nikon camera.
- Every tool must include a risk/brick warning.

## Safety and approvals

- Do not flash firmware to any camera unless I explicitly approve that step.
- Ask for approval before installing software, cloning repositories, downloading tools, or executing unfamiliar third-party code.
- When executing a command that could modify firmware or interact with hardware, explain the command and affected files first.
- Users supply their own firmware. Nothing from Nikon is committed to the repository.
- Contributors may submit their own photos and files of their own camera with a statement that they own them and agree to the repository's MIT license. Remove hidden data (location, serial number) first.
- Do not submit any photo or file made by someone else. Record only the hash, size, source URL, and provenance.

## Adding a new model

- Follow the "Adding a new model" steps in `RESEARCH-RULES.md`.
- A new model's physical-camera status is tracked in its `safety-status.md`.
- Once a capability is adopted, track it for every model.
