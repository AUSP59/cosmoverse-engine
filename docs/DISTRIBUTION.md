
# Distribution Playbook
- **Homebrew**: update `packaging/homebrew/cosmoverse.rb` with tarball URL/SHA, open PR to homebrew-core.
- **Chocolatey**: fill `packaging/chocolatey/cosmoverse.nuspec`, push to community repo.
- **Snap**: `snap/snapcraft.yaml` then `snapcraft` to build and publish.
- **WinGet**: update `packaging/winget/manifest.yaml` and open PR to microsoft/winget-pkgs.
- **AUR**: publish `packaging/aur/PKGBUILD` to AUR.
- **PyPI**: use `python-wheels.yml`, then `twine upload` (with your credentials).
- **crates.io**: publish the Rust bindings crate if desired.
- **npm**: `npm-publish.yml` workflow with `NPM_TOKEN`.
- **Signing**: run `Sign Release Assets` workflow to sign `checksums.txt` with **cosign** (keyless via OIDC).
