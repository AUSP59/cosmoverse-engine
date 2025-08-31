
#!/usr/bin/env python3
import re, sys, subprocess, json, pathlib
min_cov = float(sys.argv[1]) if len(sys.argv) > 1 else 50.0
info = pathlib.Path('coverage.info')
if not info.exists():
  print("coverage.info missing; skipping gate")
  sys.exit(0)
txt = info.read_text(errors='ignore')
m = re.findall(r'lines\.*\((\d+\.\d+)%\)', subprocess.check_output(['lcov','--summary','coverage.info']).decode())
pct = float(m[-1]) if m else 0.0
print(f"Coverage: {pct:.2f}% (min {min_cov}%)")
sys.exit(1 if pct < min_cov else 0)
