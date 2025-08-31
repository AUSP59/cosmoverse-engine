
#!/usr/bin/env python3
import json, sys, pathlib
p = pathlib.Path('scancode.json')
if not p.exists():
  print("scancode.json not found; run ScanCode workflow or place report here")
  sys.exit(0)
data = json.loads(p.read_text())
licenses = {}
for f in data.get('files', []):
  for l in f.get('licenses', []):
    key = l.get('spdx_license_key') or l.get('key')
    if not key: continue
    licenses.setdefault(key, 0); licenses[key]+=1
out = ["# THIRD-PARTY NOTICES
"]
for k,c in sorted(licenses.items()):
  out.append(f"- {k} (files: {c})")
pathlib.Path('THIRD_PARTY_NOTICES.md').write_text("\n".join(out))
print("Wrote THIRD_PARTY_NOTICES.md")
