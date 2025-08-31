
# Securing CI
- Prefer pinned action SHAs where feasible.
- Minimize token permissions (use `permissions:` block).
- Run untrusted code on PRs with read-only tokens.
- Upload SARIF to security tab; review regularly.
