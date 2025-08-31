
# Emergency Security Release Playbook
1. Create private security advisory; coordinate via SECURITY_CONTACTS.
2. Patch on main and backport branches (see BACKPORTING.md). Include tests.
3. Rotate keys if needed; rebuild with provenance; regenerate SBOM.
4. Sign assets (cosign) and publish release notes with CVE and VEX status.
5. Notify maintainers/users via security channels.
