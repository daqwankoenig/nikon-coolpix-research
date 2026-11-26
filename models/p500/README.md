# Nikon COOLPIX P500

| Item | Value |
|---|---|
| Role | Reference model (firmware analysis used as evidence for other models) |
| Status | Firmware container, section, payload, and Ghidra analysis completed to the level recorded in `analysis/`. |

## Key records

- [P500-initial-analysis.md](analysis/P500-initial-analysis.md): first look at the updater and its contents.
- [P500-section-map.md](analysis/P500-section-map.md): firmware section map.
- [P500-payload-analysis.md](analysis/P500-payload-analysis.md): payload analysis.
- `analysis/ghidra-logs/`: text logs from Ghidra runs. Ghidra project databases are not committed.
- [P500-reference-hashes.txt](checksums/P500-reference-hashes.txt): hashes of the reference firmware.

## Other files in this folder

- [goals.md](goals.md) and [safety-status.md](safety-status.md).
- `scripts/`: project-authored analysis scripts.

The P500 firmware is stored only locally in `firmware/reference/P500/`. See [PROJECT-MANIFEST.md](../../PROJECT-MANIFEST.md). Findings here are evidence for other models only as hypotheses; see [RESEARCH-RULES.md](../../RESEARCH-RULES.md).
