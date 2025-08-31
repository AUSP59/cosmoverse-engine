
# CI Troubleshooting (first push friendly)

## I see a red ❌ — what now?
1) Open the failing workflow run → check the failing step's logs.
2) Common quick fixes:
   - **Docs Pages**: Enable Pages in Settings → Pages, then re-run the job.
   - **CodeQL**: If build step fails, it's advisory here; re-run or remove the custom build so CodeQL auto-build takes over.
   - **Permission errors** (`security-events: write`, `pages: write`): These workflows already declare permissions; if your org enforces restricted policies, allow those minimal scopes.
   - **Network hiccups** (npm/pip installs): Re-run the job. Our workflows are advisory initially to avoid blocking.
3) Once stable, make checks **blocking**: remove `continue-on-error: true` in the workflow, and mark them as **required** in Branch Protection.

## Recommended required checks (after first pass)
- Build (cmake) + **Sanitizers** (ASan/UBSan/TSan)
- **CodeQL**
- Coverage gate (if enabled)
- DCO / Commitlint (if your governance requires it)
