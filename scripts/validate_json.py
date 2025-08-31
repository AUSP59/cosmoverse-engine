
#!/usr/bin/env python3
import json, subprocess, sys
from jsonschema import validate, Draft202012Validator

def run(cmd):
    p = subprocess.run(cmd, capture_output=True, text=True)
    if p.returncode != 0:
        print("Command failed:", cmd, "\n", p.stdout, p.stderr)
        sys.exit(1)
    return p.stdout

def load_schema(path):
    with open(path) as f: return json.load(f)

ver = json.loads(run(['./build/bin/cosmoverse','version','--json']))
validate(ver, load_schema('schemas/version.schema.json'))
print("version JSON OK")

bench = json.loads(run(['./build/bin/cosmoverse','bench','200000','0','--json']))
validate(bench, load_schema('schemas/bench.schema.json'))
print("bench JSON OK")
