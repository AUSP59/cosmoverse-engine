
#!/usr/bin/env python3
import re, sys, pathlib
bad = []
for p in pathlib.Path('.').rglob('*.yml'):
  if '/.github/workflows/' not in str(p): continue
  txt = p.read_text()
  for m in re.finditer(r'uses:\s*([\w\-/]+)@v?\d+(?:\.\d+)?', txt):
    # allow pinned @<sha> of 40 chars; warn on tag usage
    bad.append((str(p), m.group(1)))
if bad:
  print("WARNING: Found non-pinned GitHub Actions (use commit SHAs):")
  for f,a in bad[:50]:
    print(f" - {f}: {a}")
  sys.exit(0)
