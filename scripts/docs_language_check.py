
#!/usr/bin/env python3
import sys, pathlib
markers = [" que ", " y ", " de ", " por ", " con ", " para "]
hits = []
for p in pathlib.Path('.').rglob('*.md'):
  txt = p.read_text(errors='ignore').lower()
  if any(m in txt for m in markers):
    hits.append(str(p))
if hits:
  print("FYI: Non-English markers detected in docs:")
  for h in hits[:50]: print(" -", h)
