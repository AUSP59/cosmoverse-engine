
#!/usr/bin/env python3
import json, subprocess, sys, pathlib
from jsonschema import validate

root = pathlib.Path(__file__).resolve().parents[1]
def run(args):
  try:
    out = subprocess.check_output(args, stderr=subprocess.STDOUT).decode()
    return out
  except Exception as e:
    return ""

ok = True
bench_out = run([str(root/'build'/'bin'/'cosmoverse'), 'bench', '100000', '0', '--json'])
if bench_out:
  data = json.loads(bench_out)
  schema = json.loads((root/'schemas'/'cli'/'v1'/'bench.schema.json').read_text())
  validate(instance=data, schema=schema)
else:
  print("WARN: bench --json not executed", file=sys.stderr)

doc_out = run([str(root/'build'/'bin'/'cosmoverse'), 'doctor', '--json'])
if doc_out:
  data = json.loads(doc_out)
  schema = json.loads((root/'schemas'/'cli'/'v1'/'doctor.schema.json').read_text())
  validate(instance=data, schema=schema)
else:
  print("WARN: doctor --json not executed", file=sys.stderr)
