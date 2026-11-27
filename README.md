# Nikon COOLPIX Reverse Engineering Research

Open, evidence-led research into Nikon COOLPIX camera firmware and hardware. The same goals, methods, and evidence rules are used for every model, so results can be compared and reused across cameras.

> Formerly `nikon-p510-research`. Old links redirect here. Old file paths are mapped in [docs/history/PATH-MAP.md](docs/history/PATH-MAP.md).

## Purpose

This repository investigates whether locked features can be unlocked on specific COOLPIX models and aims to be a trusted public source on whether each is possible. It is for hobbyists and technical researchers: plain-language summaries come first, with technical details below. It does not contain Nikon firmware; users supply their own firmware.

Goals are shared by all models. Once a goal is approved or planned for any camera, it is tracked for every camera. The current goal list is in [docs/standards/goals.md](docs/standards/goals.md).

## Models

| Model | Role | Folder |
|---|---|---|
| Nikon COOLPIX P510 | Primary research target | [models/p510/](models/p510/) |
| Nikon COOLPIX P520 | Research target | [models/p520/](models/p520/) |
| Nikon COOLPIX P500 | Reference model (firmware analysis used as evidence) | [models/p500/](models/p500/) |

New models are added as a new folder under `models/`, following the same structure.

## Goal status by model

| Goal | P510 | P520 | P500 |
|---|---|---|---|
| **G-01 RAW capture** | Blocked (feasibility unknown) | Not started | Reference only |
| **G-02 Focus peaking** | Blocked (feasibility unknown) | Not started | Reference only |
| **G-03 Clean HDMI output** | Blocked (feasibility unknown) | Not started | Reference only |

- **Capabilities achieved:** [TO BE FILLED]
- **Capabilities resolved (Achieved + Not possible):** [TO BE FILLED]
- **Registered models with a complete, sourced matrix:** [TO BE FILLED]

**Status values:** Not started, In progress, Confirmed, Not possible, Blocked, Not applicable (with a recorded reason), and Reference only (used as evidence for other models, not a target).

**P510 note:** the primary blocker is that authentic P510 firmware has not been acquired. RAW, focus-peaking, and clean-HDMI feasibility are all UNKNOWN for the P510. Reference evidence from the P500 hints at a possible RAW path, but it is not a P510 fact without independent evidence.

## Evidence rules

- Findings are **model-scoped**. A fact proven for one model is only a hypothesis for another until it is independently verified.
- Interpretations keep the evidence classifications defined in [RESEARCH-RULES.md](RESEARCH-RULES.md): distinguish confirmed findings, hypotheses, and unknowns.
- Preserve immutable originals and record the SHA-256 before any firmware analysis.
- Never flash one model's firmware onto another model, assume binary compatibility between models, or copy one model's binaries into another model's folders.

## Current research status

### P510

- Physical P510 firmware version 1.0 has been confirmed.
- USB VID/PID: `04B0:0223`.
- A 293-byte PTP `GetDeviceInfo` dataset was captured successfully.
- The P510 processor and firmware-storage device remain unidentified, and no supported firmware-read mechanism is known.
- `firmware/original/P510/` is intentionally empty.
- The P510 work is paused pending new P510-specific evidence.

Key records:

- [P510-known-facts.md](models/p510/analysis/P510-known-facts.md): supported observations and unresolved questions.
- [P510-Phase4-final-status.md](models/p510/analysis/P510-Phase4-final-status.md): firmware acquisition and board-documentation status.
- [P510-Phase5-final-status.md](models/p510/analysis/P510-Phase5-final-status.md): RAW, focus-peaking, and HDMI feasibility conclusions.
- [P510-enhancement-research-checkpoint.md](models/p510/analysis/P510-enhancement-research-checkpoint.md): restart guide if authentic P510 firmware becomes available.

### P520

Initial analysis of the P520 updater and its payload is available in [models/p520/analysis/](models/p520/analysis/). It is compared with the P500 in [comparisons/](comparisons/).

### P500

Firmware container, section, payload, and Ghidra analysis notes are in [models/p500/analysis/](models/p500/analysis/). They are reference evidence for the other models.

## Safety status

Physical-camera communication always requires explicit authorization. See [RESEARCH-RULES.md](RESEARCH-RULES.md).

| Action | P510 | P520 | P500 |
|---|---|---|---|
| Working hardware investigation | NOT JUSTIFIED | Not assessed | Not assessed |
| Unknown PTP commands | NOT JUSTIFIED | Not assessed | Not assessed |
| Firmware modification | BLOCKED | BLOCKED | BLOCKED |
| Firmware flashing | BLOCKED | BLOCKED | BLOCKED |
| Donor camera acquisition | DEFERRED | Not assessed | Not assessed |

Any new model starts with all physical-camera actions blocked until they are explicitly assessed and authorized.

## Repository layout

| Location | Contents |
|---|---|
| `models/<model>/` | Analysis, checksums, and scripts for one camera model |
| `comparisons/` | Cross-model comparison reports |
| `common/` | Shared tool notes, shared checksums, and shared reference-media analysis |
| `docs/standards/` | Shared goals and research standards |
| `docs/history/` | Historical records (privacy audit, migration manifest, path map) |
| `firmware/` | **Local only, never committed** (`original`, `reference`, `extracted`, `modified`, each with a folder per model) |

See [PROJECT-MANIFEST.md](PROJECT-MANIFEST.md) for the full inventory and the provenance of excluded material.

## Using this research

This project is published so other researchers can verify, reuse, and continue COOLPIX research.

- Original repository material is licensed under the [MIT License](LICENSE).
- Third-party Nikon and external materials are **not** relicensed by this repository. See [THIRD-PARTY-MATERIAL.md](THIRD-PARTY-MATERIAL.md).
- Contributions should follow [CONTRIBUTING.md](CONTRIBUTING.md).

## Repository and Codespaces

GitHub Codespaces is intended for documentation, C source inspection and building, hash validation, and offline analysis. It cannot replace a local WSL/usbipd environment for physical USB work. No camera-control packages are installed or configured. Any later physical-camera interaction remains local-only and separately authorized.

See `.devcontainer/devcontainer.json` for the minimal C/research environment and `.gitignore` for the preservation and redistribution exclusions.
