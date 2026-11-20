# Nikon COOLPIX P510 Reverse Engineering Research

## Purpose

Long-term, evidence-led research into the Nikon COOLPIX P510, with three principal enhancement goals:

1. RAW capture
2. Focus peaking
3. Clean HDMI output

This repository is for research and preservation. It does not contain P510 firmware or authorize camera operations or firmware changes.

## Current status

The project is paused pending new P510-specific evidence.

- The physical P510 displays firmware version **1.0**.
- USB identity observed: **VID 04B0 / PID 0223**.
- A standard PTP `GetDeviceInfo` response was successfully captured and preserved.
- Authentic P510 firmware has not been acquired; [`firmware/original/P510/`](firmware/original/P510/) remains empty.
- The processor and firmware-storage device remain unidentified.
- No supported firmware-read mechanism is known.
- RAW, focus-peaking, and clean-HDMI feasibility on P510 each remain **UNKNOWN**.
- P500/P520 results are reference-model evidence only and must never be treated as P510 facts without independent evidence.

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

The intended private GitHub repository name is `nikon-p510-research`. This workspace is being prepared for preservation only; it has not been initialized or pushed to GitHub.

GitHub Codespaces is intended for documentation, C source inspection/building, hash validation, and offline analysis. It cannot replace the local WSL/usbipd environment for physical USB work. No camera-control packages are installed or configured. Any later physical-camera interaction remains local-only and separately authorized.

See [.devcontainer/devcontainer.json](.devcontainer/devcontainer.json) for the minimal C/research environment and [.gitignore](.gitignore) for preservation and redistribution exclusions.

## Project handling

P500 and P520 firmware are reference samples only. Never flash them to the P510, assume binary compatibility, or copy their binaries into P510 original/modified directories. Preserve immutable originals and record SHA-256 before firmware analysis. Keep analysis, scripts, and checksum records in their project areas. Distinguish confirmed findings, hypotheses, and unknowns.
