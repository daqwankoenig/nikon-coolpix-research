# Research goals

This is the master list of research goals. Every goal listed here is tracked for **every** model in this repository.

## Rule

Once a goal or feature is approved or planned for any camera model, it is added to this list and tracked for all models. A model that has not started on a goal shows **Not started**.

## Status values

| Status | Meaning |
|---|---|
| Not started | No work done on this goal for this model. |
| In progress | Active work with evidence being gathered. |
| Confirmed | Achieved or verified for this model, with evidence recorded. |
| Not possible | Shown to be infeasible for this model, with evidence recorded. |
| Blocked | Cannot proceed until a named blocker is resolved. |
| Not applicable | The goal does not apply to this model. A reason must be recorded. |
| Reference only | The model is used as evidence for other models, not as a target. |

## Goals

| ID | Goal | Definition of done | Added |
|---|---|---|---|
| G-01 | RAW capture | A documented, evidence-backed method to capture RAW image data on the model, or a documented reason it is not possible. | 2026-11-26 (existing P510 goal) |
| G-02 | Focus peaking | A documented, evidence-backed method to display focus peaking on the model, or a documented reason it is not possible. | 2026-11-26 (existing P510 goal) |
| G-03 | Clean HDMI output | A documented, evidence-backed method to output HDMI video without on-screen overlays, or a documented reason it is not possible. | 2026-11-26 (existing P510 goal) |

## Adding a goal

1. Add a row to the table above with the next ID, a name, a definition of done, and the date.
2. Add a row for the goal to every `models/<model>/goals.md`, starting at **Not started**.
3. Add a column for it to the status table in `README.md`.
4. Add a matching issue label (for example `G-04`).

## Evidence

A status of **Confirmed** or **Not possible** must link to evidence in that model's folder. Evidence from one model is only a hypothesis for another model until independently verified (see `RESEARCH-RULES.md`).
