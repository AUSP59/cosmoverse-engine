
# 1. Use CMake as primary build system

* Status: accepted
* Deciders: maintainers
* Date: 2025-08-30

## Context and Problem Statement
We need a cross-platform, widely-supported build system for C++ with first-class IDE integration and packaging.

## Decision Drivers
- Ubiquity on Linux/macOS/Windows
- Generator support (Ninja, VS, Xcode)
- Integration with packaging (CPack, Conan/vcpkg) and CI

## Considered Options
- CMake, Meson, Bazel, plain Make

## Decision Outcome
Chosen CMake as the primary system. Meson/Bazel files are provided for integrators.

## Consequences
- Standardize presets and package exports
- Keep Meson/Bazel in advisory CI to avoid duplication of mandatory checks
