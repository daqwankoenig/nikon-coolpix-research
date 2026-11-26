# Contributing

Contributions that improve the accuracy, reproducibility, and preservation of
Nikon COOLPIX research are welcome. This repository covers several camera
models. Each model has its own folder under `models/`, and all models share the
same goals, evidence rules, and safety rules.

Start with [README.md](README.md), [RESEARCH-RULES.md](RESEARCH-RULES.md), and
[docs/standards/goals.md](docs/standards/goals.md).

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
- Research toward the shared goals: RAW capture, focus peaking, and clean HDMI.
  See [docs/standards/goals.md](docs/standards/goals.md) for the current list
  and each model's status.
- Fixes to broken links, unclear wording, or inconsistent formatting.

## Where things go

- Model-specific work goes in `models/<model>/`, for example `models/p510/`.
- Work that compares models goes in `comparisons/`.
- Tools and notes shared by every model go in `common/`.
- Repository-wide standards go in `docs/standards/`.
- To propose a new camera model, open a "New model" issue. The steps for adding
  one are in [RESEARCH-RULES.md](RESEARCH-RULES.md) under "Adding a new model".
- To propose a new goal, open a "New goal" issue. A new goal applies to every
  model once adopted.

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

## Safety

- Do not treat one model's findings as another model's facts without
  independent evidence for that model.
- Do not submit unsupported names or interpretations for unknown Nikon codes.
- Do not perform destructive experiments on a working camera.
- Physical-camera communication or testing requires explicit authorization,
  specific justification, and a bounded safety plan. Each model's
  `safety-status.md` records what is currently justified.
- Do not modify or flash firmware. Do not bypass signatures, access controls,
  or anti-tamper protections.

## Third-party material

- Do not submit third-party proprietary firmware, installers, manuals, images,
  or other copyrighted material unless redistribution rights are clear.
- Prefer hashes, filenames, source URLs, and provenance over copying external
  artifacts into the repository.
- Private firmware stays in the local, ignored `firmware/` folder. Only
  `firmware/README.md` is tracked.

Contributions should be original or clearly licensed for inclusion under the
repository's MIT license. The MIT license does not relicense third-party
material; see [THIRD-PARTY-MATERIAL.md](THIRD-PARTY-MATERIAL.md).
