# Nikon COOLPIX P510 Reverse Engineering Research

## Purpose

Long-term, evidence-led research into the Nikon COOLPIX P510, with three principal enhancement goals:

1. RAW capture
2. Focus peaking
3. Clean HDMI output

This repository is for research and preservation. It does not contain P510 firmware or authorize camera operations or firmware changes.

## Using This Research

This project is being published so other researchers can verify, reuse, and
continue Nikon COOLPIX P510 research.

- Original repository material is licensed under the [MIT License](LICENSE).
- Third-party Nikon and external materials are not relicensed by this
  repository. See [THIRD-PARTY-MATERIAL.md](THIRD-PARTY-MATERIAL.md).
- P500 and P520 findings are reference-model evidence only and are not P510
  facts without independent evidence.
- Interpretations must retain the evidence classifications in
  [RESEARCH-RULES.md](RESEARCH-RULES.md).
- Contributions should follow [CONTRIBUTING.md](CONTRIBUTING.md).

## Current Research Status

> **Primary blocker: authentic P510 firmware has not been acquired.**
> `firmware/original/P510/` is intentionally empty.

- Physical P510 firmware version **1.0** has been confirmed.
- P510 USB VID/PID: **04B0:0223**.
- A 293-byte PTP `GetDeviceInfo` dataset was captured successfully.
- P510 processor and firmware-storage device remain unidentified; no supported
  firmware-read mechanism is known.
- **RAW feasibility: UNKNOWN**
- **Focus-peaking feasibility: UNKNOWN**
- **Clean-HDMI feasibility: UNKNOWN**
- The project is paused pending new P510-specific evidence.

Key records:

- [P510-known-facts.md](analysis/P510-known-facts.md)
- [P510-Phase4-final-status.md](analysis/P510-Phase4-final-status.md)
- [P510-Phase5-final-status.md](analysis/P510-Phase5-final-status.md)
- [P510-enhancement-research-checkpoint.md](analysis/P510-enhancement-research-checkpoint.md)
- [PROJECT-MANIFEST.md](PROJECT-MANIFEST.md)

## Safety status

- **Working P510 hardware investigation:** NOT JUSTIFIED
- **Unknown PTP commands:** NOT JUSTIFIED
- **Firmware modification:** BLOCKED
- **Firmware flashing:** BLOCKED
- **Donor acquisition:** DEFERRED

Physical-camera communication requires explicit authorization. Never bypass signatures, access controls, or anti-tamper protections. See [RESEARCH-RULES.md](RESEARCH-RULES.md).

## Research status and evidence

- [P510-known-facts.md](analysis/P510-known-facts.md) — P510-supported observations and unresolved questions.
- [P510-Phase4-final-status.md](analysis/P510-Phase4-final-status.md) — firmware acquisition and board-documentation status.
- [P510-Phase5-final-status.md](analysis/P510-Phase5-final-status.md) — RAW, focus-peaking, and HDMI feasibility conclusions.
- [P510-enhancement-research-checkpoint.md](analysis/P510-enhancement-research-checkpoint.md) — restart guide if authentic P510 firmware becomes available.
- [PROJECT-MANIFEST.md](PROJECT-MANIFEST.md) — project inventory and excluded-artifact provenance.

## Repository and Codespaces

The intended public GitHub repository is `nikon-p510-research`. Publication is
being prepared locally; no push is authorized as part of this change.

GitHub Codespaces is intended for documentation, C source inspection/building, hash validation, and offline analysis. It cannot replace the local WSL/usbipd environment for physical USB work. No camera-control packages are installed or configured. Any later physical-camera interaction remains local-only and separately authorized.

See [.devcontainer/devcontainer.json](.devcontainer/devcontainer.json) for the minimal C/research environment and [.gitignore](.gitignore) for preservation and redistribution exclusions.

## Project handling

P500 and P520 firmware are reference samples only. Never flash them to the P510, assume binary compatibility, or copy their binaries into P510 original/modified directories. Preserve immutable originals and record SHA-256 before firmware analysis. Keep analysis, scripts, and checksum records in their project areas. Distinguish confirmed findings, hypotheses, and unknowns.
