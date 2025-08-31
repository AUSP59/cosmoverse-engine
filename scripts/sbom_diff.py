
#!/usr/bin/env python3
import json, sys, pathlib
a = pathlib.Path(sys.argv[1]) if len(sys.argv)>1 else pathlib.Path("base.cdx.json")
b = pathlib.Path(sys.argv[2]) if len(sys.argv)>2 else pathlib.Path("sbom.cdx.json")
def load(p):
  return json.loads(p.read_text()) if p.exists() else {"components":[]}
def comps(x): 
  out=set()
  for c in x.get("components", []):
    name = c.get("name"); ver = (c.get("version") or "")
    if name: out.add(f"{name}@{ver}")
  return out
A=comps(load(a)); B=comps(load(b))
print("Removed:", sorted(A-B)[:50])
print("Added:", sorted(B-A)[:50])
print(f"Base={len(A)} Current={len(B)}")
