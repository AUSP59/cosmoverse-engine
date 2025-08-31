
#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
import json, sys, os

ALLOW = {
  "Apache-2.0","MIT","BSD-2-Clause","BSD-3-Clause","ISC","Unlicense","MPL-2.0","0BSD"
}
BLOCK = {"AGPL-3.0-only","AGPL-3.0-or-later","GPL-3.0-only","GPL-2.0-only"}

def extract_licenses_cyclonedx(doc):
  # CycloneDX JSON: components[*].licenses[*].license.id
  comps = doc.get("components", [])
  res = []
  for c in comps:
    for lic in c.get("licenses", []):
      lid = None
      l = lic.get("license")
      if isinstance(l, dict):
        lid = l.get("id") or l.get("name")
      if lid: res.append(lid)
  return res

def main():
  candidates = ["sbom.json","bom.json","cyclonedx.json","build/sbom.json"]
  path = None
  for c in candidates:
    if os.path.exists(c):
      path = c; break
  if not path:
    print("SBOM not found; skipping (pass).")
    return 0
  with open(path) as f:
    doc = json.load(f)
  licenses = extract_licenses_cyclonedx(doc)
  bad = [l for l in licenses if l in BLOCK]
  warn = [l for l in licenses if (l not in ALLOW and l not in BLOCK)]
  if bad:
    print("Blocked licenses detected:", bad)
    return 1
  if warn:
    print("Warning: unrecognized licenses present (manual review recommended):", sorted(set(warn)))
  print("License gate passed.")
  return 0

if __name__ == "__main__":
  sys.exit(main())
