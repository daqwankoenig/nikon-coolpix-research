# Research goals

This is the master list of adopted capabilities. Every adopted capability is tracked for every model in this repository.

## Rule

A goal is a capability in [capability-vocabulary.md](capability-vocabulary.md) flagged as adopted. One capability is one yes/no test.

## Status fields

| Field | Values |
|---|---|
| Built in? | Native / Partial / Not native / Unknown |
| Unlock | Not needed / Unknown / Not possible / Possible / Achieved |
| Evidence label | CONFIRMED `<MODEL>` / STRONGLY SUPPORTED HYPOTHESIS / HYPOTHESIS / UNKNOWN |
| Evidence basis | Manual only / Observed on camera / Both |

Absence from a manual alone caps the evidence label at **STRONGLY SUPPORTED HYPOTHESIS**.

## Adopted capabilities

| ID | Capability | Definition of done | Added |
|---|---|---|---|
| CAP-001 | RAW capture | A documented, evidence-backed method to capture RAW image data on the model, or a documented reason it is not possible. | 2026-11-26 (existing P510 goal) |
| CAP-002 | Focus peaking | A documented, evidence-backed method to display focus peaking on the model, or a documented reason it is not possible. | 2026-11-26 (existing P510 goal) |
| CAP-003 | Clean HDMI output | A documented, evidence-backed method to output HDMI video without on-screen overlays, or a documented reason it is not possible. | 2026-11-26 (existing P510 goal) |

## Capability lifecycle

Capabilities may be added, adopted, changed, or retired. Daqwan alone decides adoption.

## Adding a capability

Propose a capability in an issue. Once adopted, add it to this list and track it for every model.

## Evidence

A status of **Achieved** or **Not possible** must link to evidence in that model's folder. Evidence from one model is only a hypothesis for another model until independently verified (see [RESEARCH-RULES.md](../../RESEARCH-RULES.md)).
