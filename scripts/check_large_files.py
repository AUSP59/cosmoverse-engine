
#!/usr/bin/env python3
import os, sys, pathlib
limit_mb = float(os.environ.get("COSMO_MAX_FILE_MB", "10"))
limit = int(limit_mb * 1024 * 1024)
bad = []
for p in pathlib.Path('.').rglob('*'):
    if p.is_file() and not any(str(p).startswith(x) for x in ['./.git/','./build/','./dist/','./node_modules/','./docs/site/']):
        if p.stat().st_size > limit:
            bad.append((str(p), p.stat().st_size))
if bad:
    print("Large files detected (> %.1f MB):" % (limit_mb,))
    for f,s in bad:
        print(" - %s (%.2f MB)" % (f, s/1024/1024))
    sys.exit(1)
print("No oversized files")
