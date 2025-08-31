
#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
import sys, zipfile, os, time, pathlib
FIX_TS = (2000,1,1,0,0,0)
def add(z, path, arcname):
    st = os.stat(path)
    info = zipfile.ZipInfo(arcname, FIX_TS)
    info.external_attr = (st.st_mode & 0xFFFF) << 16
    with open(path, "rb") as f:
        z.writestr(info, f.read(), compress_type=zipfile.ZIP_DEFLATED)
def main():
    if len(sys.argv)<3:
        print("usage: repro_zip <directory> <out.zip>"); sys.exit(2)
    base = pathlib.Path(sys.argv[1])
    with zipfile.ZipFile(sys.argv[2], "w") as z:
        for p in sorted(base.rglob("*")):
            if p.is_file():
                add(z, str(p), str(p.relative_to(base)))
if __name__=="__main__": main()
