# Nikon COOLPIX Research Rules

These rules apply to every camera model in this repository (P500, P510, P520, and any model added later). Where a rule names a specific model, it is an example or a current status, not a limit on the rule.

## Evidence labels

Use these labels consistently and identify the **model** and the **source** for each finding. Replace `<MODEL>` with the model the evidence actually supports, for example `CONFIRMED P510` or `CONFIRMED P520`.

- **CONFIRMED `<MODEL>`**: directly supported by the physical camera of that model, its preserved captures, firmware obtained for that model, or authoritative model-specific documentation.
- **STRONGLY SUPPORTED HYPOTHESIS**: supported by substantial evidence but not directly confirmed for the stated model.
- **HYPOTHESIS**: plausible interpretation that remains unverified.
- **UNKNOWN**: evidence is insufficient to assign a meaning or conclusion.

For each capability, record:

- **Built in?** Native / Partial / Not native / Unknown
- **Unlock:** Not needed / Unknown / Not possible / Possible / Achieved
- **Evidence label**
- **Evidence basis:** Manual only / Observed on camera / Both

Absence from a manual alone caps the evidence label at **STRONGLY SUPPORTED HYPOTHESIS**.

### Model-scoped findings

- A finding about one model is never a fact about another model. If it might apply elsewhere, record it on the other model as HYPOTHESIS (from `<MODEL>` finding `<ID>`) and link the source. It becomes CONFIRMED only after evidence is gathered on that model itself.
- Never imply compatibility from model numbering, package similarities, shared strings, or architectural resemblance.
- A model may serve as a **reference** for another model. Its findings stay labeled with its own name.

### Unknown values

Do not assign speculative meanings to unknown numeric PTP operations, properties, events, or image-format codes. Preserve exact values and mark them **UNKNOWN** until an exact, provenance-qualified mapping is established.

## Shared goals

- Goals are defined once in [docs/standards/goals.md](docs/standards/goals.md).
- Once a goal is approved or planned for any model, it is tracked for **every** model. A model that has not started on it shows **Not started**.
- A status of **Confirmed** or **Not possible** must link to evidence in that model's folder.

## Firmware preservation and handling

Users supply their own firmware. It is stored only in the user's local, ignored `firmware/` folder, with one subfolder per model:

- `firmware/original/<MODEL>/`: untouched, authentic firmware for that model.
- `firmware/reference/<MODEL>/`: reference samples and updaters.
- `firmware/extracted/<MODEL>/`: extracted payloads and sections.
- `firmware/modified/<MODEL>/`: experimental modifications, only if ever separately authorized.

Rules:

- `firmware/original/<MODEL>/` stays empty until authentic firmware for that model is obtained or dumped. Never place another model's firmware there.
- Never modify or overwrite anything in `firmware/original/`.
- Calculate and record SHA-256 before working with any firmware; analyze a separate working copy.
- One model's firmware is reference-only for every other model. Never flash it to a different model, copy it into another model's original or modified folders, or treat its code as that model's code.
- Extracted firmware belongs in `firmware/extracted/<MODEL>/`; experimental modifications belong in `firmware/modified/<MODEL>/`.
- Nothing from Nikon is committed to the repository.

## Physical-camera safety

Physical-camera testing does not require written justification. Authorization for one operation does not authorize other operations, and authorization for one model does not carry over to another.

Do not connect to, communicate with, open, probe, modify, or flash a camera without specific prior approval for the proposed action. Codespaces is not a physical-camera test environment.
Every tool must include a risk/brick warning.

### Current status

| Action | P510 | P520 | P500 |
|---|---|---|---|
| Working hardware investigation | **NOT JUSTIFIED** | Not assessed | Not assessed |
| Unknown PTP command execution | **NOT JUSTIFIED** | Not assessed | Not assessed |
| Firmware modification | **BLOCKED** | **BLOCKED** | **BLOCKED** |
| Firmware flashing | **BLOCKED** | **BLOCKED** | **BLOCKED** |
| Donor acquisition | **DEFERRED** | Not assessed | Not assessed |

A model that is newly added starts with every physical-camera action blocked until it is explicitly assessed and approved. Each model's own status is kept in its `safety-status.md`.

## Project hygiene and redistribution

- Keep each model's reports in `models/<model>/analysis/`, its scripts in `models/<model>/scripts/`, and its checksums and manifests in `models/<model>/checksums/`. Cross-model reports go in `comparisons/`. Shared tool notes and checksums go in `common/`.
- Keep credentials, tokens, private keys, passwords, cookies, and local authentication data out of the repository.
- Contributors may submit their own photos and files of their own camera, with a statement that they own them and agree to the repository's MIT license. Remove hidden data (location, serial number) first.
- Do not submit Nikon firmware, installers, manuals or other Nikon files, or any photo or file made by someone else. Record only the hash, size, source URL, and provenance.
- Do not delete historical reports or artifacts merely because they are excluded from Git. Do not rewrite historical reports to update file paths; use [docs/history/PATH-MAP.md](docs/history/PATH-MAP.md) instead.
- Make no change that publishes sensitive material, or that changes the repository's visibility, without explicit authorization from the repository owner.

## Adding a new model

1. Copy `templates/model/` to `models/<model>/` and fill in the files.
2. Add the model to the status table in `README.md` and to `PROJECT-MANIFEST.md`.
3. Add a row for every goal in `docs/standards/goals.md` to the model's `goals.md`, starting at **Not started**.
4. Create `firmware/original/<MODEL>/` and the other firmware subfolders locally. They are ignored by Git.
5. Record the model's safety status. All physical-camera actions start **BLOCKED** or **Not assessed** until approved.
6. Add a model label for GitHub issues.

See [PROJECT-MANIFEST.md](PROJECT-MANIFEST.md) for the current inventory, preservation decisions, and excluded-artifact records.
