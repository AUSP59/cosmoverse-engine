
# CI Checks: Advisory vs Blocking

This repository ships **many** CI checks. To avoid red ❌ on the very first push (before you configure secrets, tokens or packaging), most checks are **advisory** (`continue-on-error: true`).

## Make a check *blocking*
- Edit the corresponding workflow under `.github/workflows/*.yml` and remove the `continue-on-error: true` lines for that job.
- Optionally mark it as a **required status check** in GitHub branch protection rules (Settings → Branches → main).

## Recommended blocking set (once the repo is public)
- CodeQL
- clang-tidy (if configured), Sanitizers (ASan/UBSan/TSan)
- Coverage gate
- Build & Release (on tags)
- DCO / Commitlint (if you want strict governance)
- Dependency Review
- Scorecard

All other checks (REUSE, Lychee, Vale, Pa11y, Semgrep, Trivy/Grype, ClusterFuzzLite) can remain advisory initially and be tightened later.
