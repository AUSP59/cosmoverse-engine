
# NIST SSDF v1.1 Mapping
- **PS.1** (Define security requirements): THREAT MODEL, SECURITY.md, GOVERNANCE.md.
- **PW.4** (Review): Code review via PR + CODEOWNERS + DCO + Conventional Commits.
- **PW.8** (Config hardening): COSMO_HARDENED, container distroless, Kubernetes hardening.
- **PW.9** (Code analysis): CodeQL, Semgrep, cppcheck, clang-tidy, iwyu.
- **PW.10** (Build integrity): SLSA provenance, cosign signing, SBOM generation, reproducible builds.
- **RV.1** (Penetration testing): fuzzing (OSS-Fuzz style), sanitizers.
- **RV.3** (Vulnerability response): INCIDENT_RESPONSE.md, SECURITY_CONTACTS, VEX template.
