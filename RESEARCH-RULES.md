# Nikon COOLPIX Research Rules

These rules apply to every camera model in this repository (P500, P510, P520, and any model added later). Where a rule names a specific model, it is an example or a current status, not a limit on the rule.

## Evidence labels

Use these labels consistently and identify the **model** and the **source** for each finding. Replace `<MODEL>` with the model the evidence actually supports, for example `CONFIRMED P510` or `CONFIRMED P520`.

- **CONFIRMED `<MODEL>`**: directly supported by the physical camera of that model, its preserved captures, firmware obtained for that model, or authoritative model-specific documentation.
- **STRONGLY SUPPORTED HYPOTHESIS**: supported by substantial evidence but not directly confirmed for the stated model.
- **HYPOTHESIS**: plausible interpretation that remains unverified.
- **UNKNOWN**: evidence is insufficient to assign a meaning or conclusion.

### Model-scoped findings

- A finding confirmed for one model is **not** a fact for any other model. When it is applied to another model, it is a **STRONGLY SUPPORTED HYPOTHESIS** or a **HYPOTHESIS** until independently supported for that model.
- State model provenance next to every transferred comparison (for example, "CONFIRMED P500, applied to P510 as a hypothesis").
- Never imply compatibility from model numbering, package similarities, shared strings, or architectural resemblance.
- A model may serve as a **reference** for another model. Its findings stay labeled with its own name.

### Unknown values

Do not assign speculative meanings to unknown numeric PTP operations, properties, events, or image-format codes. Preserve exact values and mark them **UNKNOWN** until an exact, provenance-qualified mapping is established.

## Shared goals

- Goals are defined once in [docs/standards/goals.md](docs/standards/goals.md).
- Once a goal is approved or planned for any model, it is tracked for **every** model. A model that has not started on it shows **Not started**.
- A status of **Confirmed** or **Not possible** must link to evidence in that model's folder.

## Firmware preservation and handling

Firmware is stored only on the researcher's local computer, in the ignored `firmware/` folder, with one subfolder per model:

- `firmware/original/<MODEL>/`: untouched, authentic firmware for that model.
- `firmware/reference/<MODEL>/`: reference samples and updaters.
- `firmware/extracted/<MODEL>/`: extracted payloads and sections.
- `firmware/modified/<MODEL>/`: experimental modifications, only if ever separately authorized.

Rules:

- `firmware/original/<MODEL>/` stays empty until authentic firmware for that model is obtained or dumped. Never place another model's firmware there.
- Never modify or overwrite anything in `firmware/original/`.
- Calculate and record SHA-256 before working with any firmware; analyze a separate working copy.
- One model's firmware is reference-only for every other model. Never flash it to a different model, copy it into another model's original or modified folders, or treat its code as that model's code.
- Before any future firmware-binary modification, create and verify a backup. **No firmware write or flash is currently authorized for any model.**
- Do not bypass cryptographic signatures, secure boot, access controls, or anti-tamper protections.

## Physical-camera safety

Physical-camera testing requires explicit justification and a bounded safety plan stating the exact question, equipment and commands, expected effects, stop conditions, and recovery path. Authorization for one operation does not authorize other operations, and authorization for one model does not carry over to another.

Do not connect to, communicate with, open, probe, modify, or flash a camera without specific prior approval for the proposed action. Codespaces is not a physical-camera test environment.

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
- Do not commit third-party firmware, installers, manuals, proprietary binaries, or research images unless redistribution is clearly appropriate. Prefer source URL, provenance, filename, size, and SHA-256 metadata.
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
