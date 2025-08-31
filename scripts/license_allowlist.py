
#!/usr/bin/env python3
import json, sys, pathlib
ALLOW = {"Apache-2.0","MIT","BSD-2-Clause","BSD-3-Clause","ISC","MPL-2.0","Zlib","Unicode-DFS-2016"}
p = pathlib.Path("sbom.cdx.json")
if not p.exists():
  print("No CycloneDX SBOM found (sbom.cdx.json)")
  sys.exit(0)
data = json.loads(p.read_text())
viol = set()
for comp in data.get("components", []):
  lic = comp.get("licenses") or []
  for l in lic:
    id = (l.get("license") or {}).get("id")
    if id and id not in ALLOW:
      viol.add(id)
if viol:
  print("Disallowed licenses:", ", ".join(sorted(viol)))
  sys.exit(1)
print("License allowlist check passed.")
