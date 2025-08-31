#!/usr/bin/env python3
import os, subprocess, sys, re
def detect_base():
    # Prefer PR base if available
    base = os.environ.get('GITHUB_BASE_REF')
    if base:
        return f'origin/{base}'
    # Try origin/HEAD symbolic ref
    try:
        ref = subprocess.check_output(['git','symbolic-ref','refs/remotes/origin/HEAD'], text=True).strip()
        m = re.search(r'refs/remotes/(.*)', ref)
        if m: return m.group(1)
    except Exception:
        pass
    # Fallbacks
    for cand in ['origin/main','origin/master']:
        try:
            subprocess.check_call(['git','rev-parse','--verify',cand], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return cand
        except Exception:
            continue
    return 'HEAD~20'  # last 20 commits as ultimate fallback
base = detect_base()
out = subprocess.check_output(['git','log','--pretty=format:%H%n%B', f'{base}..HEAD'], text=True, stderr=subprocess.DEVNULL)
missing = []
blocks = [b for b in out.split('\n\n') if b.strip()]
for b in blocks:
    if 'Signed-off-by:' not in b:
        commit = b.split('\n',1)[0]
        missing.append(commit)
if missing:
    print('DCO check: missing Signed-off-by on commits:', *missing, sep='\n - ')
    sys.exit(1)
print('DCO check: OK')
