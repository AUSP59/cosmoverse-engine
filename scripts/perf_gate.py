
#!/usr/bin/env python3
import json, sys, pathlib
# Usage: python3 scripts/perf_gate.py perf.json baseline.json 1.20
cur = pathlib.Path(sys.argv[1]); base = pathlib.Path(sys.argv[2]) if len(sys.argv)>2 else None
limit = float(sys.argv[3]) if len(sys.argv)>3 else 1.20
if not cur.exists() or not base or not base.exists():
  print("No baseline found; skipping perf gate")
  sys.exit(0)
c=json.loads(cur.read_text()); b=json.loads(base.read_text())
def geomean(j): 
  import math
  times=[r["mean"] for r in j["results"] if "mean" in r]
  return math.prod(times)**(1.0/len(times)) if times else 0.0
gcur=geomean(c); gbase=geomean(b)
print(f"Perf geomean: current={gcur:.6f} base={gbase:.6f} ratio={gcur/gbase:.3f}")
sys.exit(1 if gcur>gbase*limit else 0)
