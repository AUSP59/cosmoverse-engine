
#!/usr/bin/env python3
import re, sys, json, pathlib
cfg = json.loads(pathlib.Path('docs/doc_budget.json').read_text())
max_w = int(cfg.get('max_warnings', 200))
log = pathlib.Path('warnings.log')
if not log.exists():
    print('WARN: warnings.log not found; passing.')
    sys.exit(0)
txt = log.read_text(errors='ignore')
warnings = len(re.findall(r'warning:', txt))
print(f'Doxygen warnings: {warnings} (budget {max_w})')
sys.exit(1 if warnings > max_w else 0)
