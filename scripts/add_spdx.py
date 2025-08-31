
#!/usr/bin/env python3
import pathlib, sys
header = "// SPDX-License-Identifier: Apache-2.0\n"
exts = {'.c','.cc','.cpp','.cxx','.h','.hh','.hpp','.hxx','.ipp'}
for p in pathlib.Path('.').rglob('*'):
  if p.suffix in exts and p.is_file():
    txt = p.read_text(errors='ignore')
    if "SPDX-License-Identifier" not in txt.splitlines()[:3]:
      p.write_text(header + txt)
      print("Added SPDX to", p)
