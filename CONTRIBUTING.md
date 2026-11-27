# Contributing

Contributions that improve the accuracy, reproducibility, and preservation of
Nikon COOLPIX research are welcome. This repository covers several camera
models. Each model has its own folder under `models/`, and all models share the
same adopted capabilities, evidence rules, and safety rules.

Start with [README.md](README.md), [RESEARCH-RULES.md](RESEARCH-RULES.md),
[docs/standards/decisions.md](docs/standards/decisions.md),
[docs/standards/capability-vocabulary.md](docs/standards/capability-vocabulary.md),
and [docs/standards/goals.md](docs/standards/goals.md).

## Useful contributions

For any model in this repository:

- Authentic firmware/updater evidence and provenance (hashes, sizes, source
  URLs; not the files themselves).
- Service documentation references.
- Motherboard component and board-identifier research.
- Processor/SoC identification.
- Flash or other nonvolatile-storage identification.
- Credible model-specific Nikon service-tool evidence.
- Analysis and independent validation of captured PTP DeviceInfo data.
- Research toward the adopted capabilities: RAW capture, focus peaking, and clean HDMI.
  See [docs/standards/goals.md](docs/standards/goals.md) for the current list
  and each model's status.
- Fixes to broken links, unclear wording, or inconsistent formatting.

## Getting started

Owners may submit observations from their own cameras and fact-check source links. Good first issues include:

- Find the official manual URL for model X.
- Report your firmware version and region.

Do not upload materials made by Nikon or anyone else. For photos and files you created of your own camera, remove hidden photo data (location and serial number) and include a statement that you own the material and agree to the repository's MIT license. Nothing is marked **CONFIRMED** without Daqwan's approval.

Propose capability additions in an issue. Daqwan decides whether to adopt them.

## Where things go

- Model-specific work goes in `models/<model>/`, for example `models/p510/`.
- Work that compares models goes in `comparisons/`.
- Tools and notes shared by every model go in `common/`.
- Repository-wide standards go in `docs/standards/`.
- To propose a new camera model, open a "New model" issue. The steps for adding
  one are in [RESEARCH-RULES.md](RESEARCH-RULES.md) under "Adding a new model".
- To propose a capability, open an issue. Daqwan decides whether to adopt it;
  adopted capabilities apply to every model.

Use the issue forms for research findings, new goals, and new models.

## Evidence standards

Every claim names its evidence class and the model it applies to. Findings are
model-scoped: a finding about one model is not a fact about another.

- **CONFIRMED <MODEL>** - directly supported by hardware, a preserved capture,
  or authoritative documentation for that exact model (for example,
  CONFIRMED P510).
- **STRONGLY SUPPORTED HYPOTHESIS** - substantial but not conclusive evidence
  for the stated model.
- **HYPOTHESIS** - plausible interpretation that remains unverified.
- **UNKNOWN** - available evidence is insufficient to assign a meaning or
  conclusion.

Identify sources, model provenance, exact values, and hashes where applicable.
Keep observations, interpretations, and unknowns distinct. Do not assign
speculative meanings to unresolved Nikon/PTP codes.
Absence from a manual alone caps the evidence label at **STRONGLY SUPPORTED HYPOTHESIS**.

## Safety

- Do not treat one model's findings as another model's facts without
  independent evidence for that model.
- Do not submit unsupported names or interpretations for unknown Nikon codes.
- Physical-camera testing does not require written justification. Each
  proposed action still needs specific prior approval, as recorded in that
  model's `safety-status.md`; approval does not carry across actions or models.
- Do not flash firmware unless the repository owner explicitly approves it.
- Every tool must include a risk/brick warning.

## Third-party material

- Contributors may submit their own photos and files of their own camera, with
  a statement that they own them and agree to the repository's MIT license.
  Remove hidden data (location, serial number) first.
- Do not submit Nikon firmware, installers, manuals or other Nikon files, or
  any photo or file made by someone else. Record only the hash, size, source
  URL, and provenance.
- Users supply their own firmware. Firmware stays in the local, ignored
  `firmware/` folder. Only `firmware/README.md` is tracked.

The MIT license applies only to original material contributed to this
repository and does not relicense third-party material; see
[THIRD-PARTY-MATERIAL.md](THIRD-PARTY-MATERIAL.md).
