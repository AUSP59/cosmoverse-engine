
# Backporting Policy
- Security fixes are backported to the last two minor release lines.
- Use `backport/*` labels; cherry-pick with `-x`; open PRs targeting release branches.
- Each backport must include test coverage or a rationale.
