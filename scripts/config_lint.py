
#!/usr/bin/env python3
import os, sys, configparser, pathlib, json

ALLOWED = {
  "log": {"level": {"type": "str", "enum": ["trace","debug","info","warn","error"]}},
}
def lint(path):
  cp = configparser.ConfigParser()
  cp.read(path)
  ok = True
  for sect in cp.sections():
    if sect not in ALLOWED:
      print(f"[WARN] Unknown section: {sect}")
      continue
    for k,v in cp[sect].items():
      if k not in ALLOWED[sect]:
        print(f"[WARN] Unknown key in [{sect}]: {k}")
        continue
      rule = ALLOWED[sect][k]
      if rule.get("enum") and v not in rule["enum"]:
        print(f"[ERROR] Invalid value for [{sect}].{k}: {v} not in {rule['enum']}"); ok=False
  return ok

paths = []
env = os.getenv("COSMO_CONFIG")
if env and os.path.exists(env): paths.append(env)
default_candidates = [
  "etc/cosmoverse.ini",
  os.path.expanduser("~/.config/cosmoverse/cosmoverse.ini")
]
for p in default_candidates:
  if os.path.exists(p): paths.append(p)

if not paths:
  print("No config file found; linter is a no-op."); sys.exit(0)

ok = True
for p in paths:
  print(f"LINT {p}")
  ok = lint(p) and ok
sys.exit(0 if ok else 1)
