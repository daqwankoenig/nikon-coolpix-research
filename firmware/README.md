# Local firmware folder

This folder exists only on a researcher's own computer. Everything in it except this file is ignored by Git and must never be committed. Keep hashes, sizes, sources, and notes in the repository instead (see `models/<model>/firmware.md` and `models/<model>/checksums/`).

## Layout

```
firmware/
  original/<MODEL>/    untouched, authentic firmware for that model
  reference/<MODEL>/   reference samples and updaters
  extracted/<MODEL>/   extracted payloads and sections
  modified/<MODEL>/    derived or changed files (only if ever separately authorized)
```

Use the model name in capitals, for example `P510`.

## Rules

- `original/<MODEL>/` stays empty until authentic firmware for that model is obtained or dumped.
- Never modify or overwrite anything in `original/`.
- Record the SHA-256 before any analysis, and work on a copy.
- Another model's firmware is reference-only. Never flash it to a different model.

Full rules: [RESEARCH-RULES.md](../RESEARCH-RULES.md).
