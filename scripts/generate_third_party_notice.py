
#!/usr/bin/env python3
import pathlib, re
out = pathlib.Path('THIRD_PARTY_NOTICES.txt')
def gather():
  for p in pathlib.Path('.').rglob('*'):
    if p.is_file() and p.name.upper() in ('LICENSE','COPYING','NOTICE'):
      yield p
with out.open('w') as f:
  f.write("Third-Party Notices (generated)\n\n")
  for lic in gather():
    try:
      txt = lic.read_text(errors='ignore')
      f.write(f"===== {lic} =====\n")
      f.write(txt + "\n\n")
    except Exception as e:
      f.write(f"===== {lic} (unreadable: {e}) =====\n")
print("Wrote", out)
