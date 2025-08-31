 Security Policy

**Project:** COSMOVERSE ENGINE  
**Contacts:** `@AUSP59` (GitHub) · alanursapu@gmail.com

## Report a Vulnerability

- **Preferred:** Open a *private* report via **GitHub Security Advisories**  
  Repository → **Security** → **Advisories** → **Report a vulnerability**.
- **Alternative (email):** `alanursapu@gmail.com` with subject `[security] <short title>`.

Please include:
- Affected versions/commit SHA, environment (OS/arch, compiler), and config flags.
- Impact and exploitability, minimal PoC, and reproduction steps.
- Any temporary mitigations.  
- Whether you request a **CVE**.

> 🔒 Encryption: GitHub Advisories are private by default. If you require PGP, mention it in your report and we’ll arrange a key exchange.

## Triage & SLAs (best-effort)

- **Acknowledgment:** within **48 hours**.
- **Initial triage:** within **7 days** (validity, severity, scope).
- **Fix or mitigation target windows:**
  - **Critical (CVSS ≥ 9.0):** 7 days
  - **High (7.0–8.9):** 14 days
  - **Medium (4.0–6.9):** 30 days
  - **Low (≤ 3.9):** next regular release

We use **CVSS v3.1/v4** for severity; we may request clarifications to score accurately.

## Coordinated Disclosure

- Default embargo up to **90 days**, or shorter once a fix/mitigation is ready.
- We will publish a **GitHub Security Advisory (GHSA)** with details, credits (opt-in), and fixed versions.
- **CVE**: We request CVE IDs via GitHub’s CNA process for exploitable issues.

## Supported Versions

Security fixes target:
- `main` and the **latest stable** minor release.
- Any declared **LTS** branches defined in `docs/LTS_POLICY.md`.

Older, unsupported versions may receive advisory notes but not patches.

## Scope

**In scope**
- This repository’s code, build artifacts, and release pipelines.
- Published container images (GHCR), Helm charts, and release bundles.
- Docs website build (MkDocs) as distributed by this repo.

**Out of scope**
- Social engineering, physical attacks, third-party services not controlled by this project.
- Automated DoS/volumetric attacks, spam, or privacy violations.
- Vulnerabilities in dependencies **unless** exploitable through our integration.

## Testing Guidelines

- Use your own environments/tenants; **no disruption** of others.
- No data exfiltration beyond proof of access; use synthetic data.
- Respect rate limits; coordinate if your tests are resource-intensive.

## Safe Harbor

We will not pursue legal action for **good-faith** security research that follows this policy, respects privacy, and avoids service disruption.

## Verifying Official Releases

- **Containers (keyless, Sigstore/Fulcio):**
  ```bash
  cosign verify ghcr.io/ausp59/cosmoverse-engine:TAG \
    --certificate-identity-regexp 'github.com/AUSP59/cosmoverse-engine' \
    --certificate-oidc-issuer 'https://token.actions.githubusercontent.com'
SBOM & provenance are attached to releases; verify checksums from SHA256SUMS.txt.

Credits
We are grateful to reporters who follow Coordinated Disclosure. Credit is opt-in; please state your preferred name/handle.

yaml
Copiar código

### 2) `.well-known/security.txt`  *(sirve para GitHub Pages o cualquier dominio que uses)*
```txt
# security.txt (RFC 9116)
Contact: mailto:alanursapu@gmail.com
Contact: https://github.com/AUSP59
Policy: https://github.com/AUSP59/cosmoverse-engine/blob/main/.github/SECURITY.md
Preferred-Languages: en, es
Expires: 2026-08-30T00:00:00Z
3) SECURITY_CONTACTS (opcional, lectura humana rápida)
txt
Copiar código
Primary: @AUSP59 (GitHub)
Email: alanursapu@gmail.com
Backup: Use GitHub → Security → Advisories → Report a vulnerability (private)