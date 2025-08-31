
# GitHub Setup (Post-import)
1. **Enable GHCR** (Packages) and **Pages** (from `docs-pages.yml`).
2. **Protect `main`**: require up-to-date branch, require status checks to pass (pick: CodeQL, Semgrep, clang-tidy, coverage gate, sanitizers, Scorecard).
3. **Install Apps (optional)**: OpenSSF Allstar, DCO App.
4. **Dependabot alerts**: enable security updates, secret scanning & push protection.
5. **Actions permissions**: restrict to `Allow GitHub Actions, and approved reusable workflows`.
6. **Environments**: set rules for `release` if you want manual approval.
7. **Repository description & topics**: add badges once the first CI run completes.
