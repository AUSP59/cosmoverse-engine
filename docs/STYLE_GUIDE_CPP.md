
# C++ Style Guide (summary)
- C++20, RAII, no raw `new/delete` in high-level code.
- Prefer `std::unique_ptr`/`std::shared_ptr`, `std::span`, `std::string_view`.
- `constexpr` and `noexcept` where appropriate; avoid exceptions across API boundaries.
- Headers self-contained; minimal includes; IWYU guidance applies.
- Public API changes require ABI review and deprecation period per policy.
