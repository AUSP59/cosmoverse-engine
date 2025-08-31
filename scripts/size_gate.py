
#!/usr/bin/env python3
import os, sys, pathlib
# Usage: python3 scripts/size_gate.py build/bin/cosmoverse 8_000_000
bin_path = pathlib.Path(sys.argv[1] if len(sys.argv) > 1 else "build/bin/cosmoverse")
limit = int(sys.argv[2]) if len(sys.argv) > 2 else 8_000_000
if not bin_path.exists():
  print(f"{bin_path} not found; skipping size gate"); sys.exit(0)
sz = bin_path.stat().st_size
print(f"Binary size: {sz} bytes (limit {limit})")
sys.exit(1 if sz > limit else 0)
