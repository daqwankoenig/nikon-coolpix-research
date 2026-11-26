# Path map: repository layout change (2026-11-26)

On 2026-11-26 this repository changed from a single-model (P510) layout to a multi-model layout. The old layout is preserved in the Git tag `p510-standalone-final`.

Historical reports under `models/*/analysis/` record the file paths that were correct **when each report was written**. They were deliberately not rewritten, so they stay a faithful record of the evidence. Use this table to find where an old path lives now.

| Old path (before 2026-11-26) | Current path |
|---|---|
| `analysis/P500-P520-*.md` | `comparisons/P500-P520-*.md` |
| `analysis/P500-*` | `models/p500/analysis/P500-*` |
| `analysis/ghidra-logs/` | `models/p500/analysis/ghidra-logs/` |
| `analysis/P510-*` | `models/p510/analysis/P510-*` |
| `analysis/P520-*` | `models/p520/analysis/P520-*` |
| `analysis/nikon-firmware-tools-source-audit.md`, `analysis/tool-installation-record.md` | `common/tools/` |
| `checksums/P500-*` | `models/p500/checksums/` |
| `checksums/P510-*` | `models/p510/checksums/` |
| `checksums/P520-*` | `models/p520/checksums/` |
| `checksums/NX-Studio-*` | `common/checksums/` |
| `scripts/P500*` | `models/p500/scripts/` |
| `scripts/P510*`, `scripts/Validate-P510*` | `models/p510/scripts/` |
| `reference-media/analysis/NX-Studio/NX-Studio-P510-findings.md` | `models/p510/analysis/NX-Studio-P510-findings.md` |
| `reference-media/analysis/NX-Studio/NX-Studio-static-analysis.md` | `common/reference-media/NX-Studio-static-analysis.md` |
| `GITHUB-PRIVACY-AUDIT.md`, `GITHUB-MIGRATION-MANIFEST.sha256` | `docs/history/` |

## Local-only folders (not in Git)

These folders are ignored by Git and exist only on a researcher's own computer. Their layout did not change:

- `firmware/original/<MODEL>/`
- `firmware/reference/<MODEL>/`
- `firmware/extracted/<MODEL>/`
- `firmware/modified/<MODEL>/`
- `reference-media/original/` and `reference-media/software/` (proprietary Nikon media)
