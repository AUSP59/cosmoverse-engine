# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20)
project(cosmoverse_engine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(COSMO_BUILD_TESTS "Build tests" ON)
option(COSMO_BUILD_BENCH "Build benchmarks" ON)
option(COSMO_BUILD_DOCS "Build Doxygen docs" OFF)
option(COSMO_ENABLE_ASAN "Enable ASAN" OFF)
option(COSMO_ENABLE_UBSAN "Enable UBSAN" OFF)
option(COSMO_ENABLE_TSAN "Enable TSAN" OFF)

include(GNUInstallDirs)

if (COSMO_ENABLE_ASAN)
  add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address)
endif()
if (COSMO_ENABLE_UBSAN)
  add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=undefined)
endif()
if (COSMO_ENABLE_TSAN)
  add_compile_options(-fsanitize=thread -fno-omit-frame-pointer)
  add_link_options(-fsanitize=thread)
endif()

add_library(cosmoverse ${COSMO_LIB_TYPE}
  src/core/log.cpp
  src/core/config.cpp
  src/core/hash.cpp
  src/core/thread_pool.cpp
  src/core/log_env.cpp
  src/core/config_env.cpp
)

target_include_directories(cosmoverse PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(cosmoverse PRIVATE $<$<BOOL:${COSMO_BUILD_SHARED}>:COSMOVERSE_BUILD_SHARED>)
target_compile_definitions(cosmoverse PUBLIC  $<$<BOOL:${COSMO_BUILD_SHARED}>:COSMOVERSE_USE_SHARED>)

target_compile_definitions(cosmoverse PUBLIC COSMO_VERSION="\"${PROJECT_VERSION}\"")

# Preserve original sources for reference (not compiled by default)
add_custom_target(original_sources ALL COMMAND ${CMAKE_COMMAND} -E echo "Original sources preserved under src/original/")

add_executable(cosmoverse_cli apps/cosmoverse.cpp)
set_target_properties(cosmoverse_cli PROPERTIES OUTPUT_NAME cosmoverse)
target_link_libraries(cosmoverse_cli PRIVATE cosmoverse)

install(TARGETS cosmoverse cosmoverse_cli
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (COSMO_BUILD_TESTS)
  enable_testing()
  add_executable(cosmo_tests tests/test_main.cpp)
  target_link_libraries(cosmo_tests PRIVATE cosmoverse)
  add_test(NAME cosmoverse_unit COMMAND cosmo_tests)
endif()

if (COSMO_BUILD_BENCH)
  add_executable(cosmo_bench benchmarks/bench_main.cpp)
  target_link_libraries(cosmo_bench PRIVATE cosmoverse)
endif()

if (COSMO_BUILD_DOCS)
  find_package(Doxygen REQUIRED dot)
  set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
  add_custom_target(docs
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_IN}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API docs with Doxygen"
  )
endif()

include(CPack)
set(CPACK_PACKAGE_NAME "COSMOVERSE-ENGINE")
set(CPACK_PACKAGE_VENDOR "COSMOVERSE")
set(CPACK_PACKAGE_VERSION 1.0.0)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)


# ---- Build knobs ----
option(COSMO_BUILD_SHARED "Build shared library" ON)
option(COSMO_STRICT "Enable strict warnings" ON)
option(COSMO_ENABLE_IPO "Enable LTO/IPO when available" ON)
option(COSMO_ENABLE_COVERAGE "Enable coverage flags (GCC/Clang)" OFF)

include(CMakePackageConfigHelpers)

if (COSMO_STRICT)
  if (MSVC)
    add_compile_options(/W4 /permissive-)
  else()
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif()
endif()

if (COSMO_ENABLE_COVERAGE AND (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"))
  add_compile_options(--coverage)
  add_link_options(--coverage)
endif()

include(CheckIPOSupported)
if (COSMO_ENABLE_IPO)
  check_ipo_supported(RESULT ipo_supported OUTPUT ipo_err)
  if (ipo_supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
  endif()
endif()

if (UNIX AND NOT APPLE)
  add_compile_options(-fvisibility=hidden)
endif()

set(COSMO_LIB_TYPE STATIC)
if (COSMO_BUILD_SHARED)
  set(COSMO_LIB_TYPE SHARED)
endif()

# Export & Package config
install(TARGETS cosmoverse cosmoverse_cli
  EXPORT cosmoverseTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/CosmoverseConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CosmoverseConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/CosmoverseConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cosmoverse
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/CosmoverseConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/CosmoverseConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cosmoverse
)

install(EXPORT cosmoverseTargets
  NAMESPACE Cosmoverse::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cosmoverse
)

# Pkg-config
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cosmoverse.pc.in
               ${CMAKE_CURRENT_BINARY_DIR}/cosmoverse.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cosmoverse.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# CPack generators
include(CPack)
set(CPACK_PACKAGE_NAME "COSMOVERSE-ENGINE")
set(CPACK_PACKAGE_VENDOR "COSMOVERSE")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_GENERATOR "TGZ;ZIP")
if (UNIX AND NOT APPLE)
  list(APPEND CPACK_GENERATOR "DEB;RPM")
endif()
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "COSMOVERSE ENGINE")
set(CPACK_PACKAGE_CONTACT "Maintainers <security@example.com>")


# ---- Fuzzing (Clang/libFuzzer) ----
option(COSMO_BUILD_FUZZ "Build fuzz targets (requires Clang/libFuzzer)" OFF)
if (COSMO_BUILD_FUZZ)
  add_executable(cosmo_fuzz_hash fuzz/hash_fuzz.cpp)
  target_link_libraries(cosmo_fuzz_hash PRIVATE cosmoverse)
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(cosmo_fuzz_hash PRIVATE -fsanitize=fuzzer,address,undefined -fno-omit-frame-pointer)
    target_link_options(cosmo_fuzz_hash PRIVATE -fsanitize=fuzzer,address,undefined)
  endif()
endif()


# Manpage & Shell Completions
install(FILES docs/man/cosmoverse.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
install(FILES scripts/completions/cosmoverse.bash DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/bash-completion/completions RENAME cosmoverse)
install(FILES scripts/completions/cosmoverse.zsh DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/zsh/site-functions RENAME _cosmoverse)
install(FILES scripts/completions/cosmoverse.fish DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/fish/vendor_completions.d RENAME cosmoverse.fish)


option(COSMO_GNU_SYMBOL_VERSION "Use GNU ld version script on Linux" OFF)
if (COSMO_GNU_SYMBOL_VERSION AND CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT COSMO_BUILD_SHARED)
  message(STATUS "GNU ld version script enabled")
  target_link_options(cosmoverse PUBLIC "-Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/scripts/ld-version-script.map")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/cosmoverse/version.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/generated/version.hpp @ONLY)
target_include_directories(cosmoverse PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/generated)


option(COSMO_OPT_SIZE "Optimize for size with section GC" OFF)
if (COSMO_OPT_SIZE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-ffunction-sections -fdata-sections)
  add_link_options(-Wl,--gc-sections)
endif()

option(COSMO_OPT_NATIVE "Enable -march=native locally" OFF)
if (COSMO_OPT_NATIVE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-march=native)
endif()


if (COSMO_BUILD_TESTS)
  add_executable(cosmo_ctest tests/test_c_api.c)
  target_link_libraries(cosmo_ctest PRIVATE cosmoverse)
  add_test(NAME cosmoverse_c_api COMMAND cosmo_ctest)
endif()


# ---- Warnings as errors (opt-in) ----
option(COSMO_WERROR "Treat warnings as errors" OFF)
if (COSMO_WERROR)
  if (MSVC)
    add_compile_options(/WX)
  else()
    add_compile_options(-Werror)
  endif()
endif()

# ---- RPATH & PIC ----
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
if (APPLE)
  set(CMAKE_INSTALL_RPATH "@loader_path/../lib")
elseif(UNIX)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()

set_target_properties(cosmoverse PROPERTIES POSITION_INDEPENDENT_CODE ON)


# ---- CLI integration tests ----
if (COSMO_BUILD_TESTS)
  add_test(NAME cli_version COMMAND $<TARGET_FILE:cosmoverse> version)
  add_test(NAME cli_wc_self COMMAND $<TARGET_FILE:cosmoverse> wc ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
  add_test(NAME cli_bench_json COMMAND $<TARGET_FILE:cosmoverse> bench 10000 2 --json)
  set_tests_properties(cli_bench_json PROPERTIES PASS_REGULAR_EXPRESSION ""tasks"")
endif()

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake)


# ---- Docs strict mode (Doxygen warnings as errors) ----
option(COSMO_DOCS_STRICT "Treat Doxygen warnings as errors" OFF)
if (COSMO_BUILD_DOCS)
  set(DOXYFILE_STRICT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.strict)
  if (EXISTS ${DOXYFILE_STRICT} AND COSMO_DOCS_STRICT)
    add_custom_target(docs_strict
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_STRICT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Generating API docs with Doxygen (strict)")
  endif()
endif()


# ---- Extra hardening (opt-in) ----
if (COSMO_HARDEN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-D_GLIBCXX_ASSERTIONS)
  if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_options(-fstack-clash-protection)
    add_link_options(-Wl,--as-needed)
  endif()
endif()

# Extra logger test
add_executable(cosmo_test_logger tests/test_logger.cpp)
target_link_libraries(cosmo_test_logger PRIVATE cosmoverse)
add_test(NAME cosmoverse_logger COMMAND cosmo_test_logger)


# ---- Profile-Guided Optimization (opt-in) ----
option(COSMO_PGO_GENERATE "Build with -fprofile-generate to collect profiles" OFF)
option(COSMO_PGO_USE "Build with -fprofile-use to apply collected profiles" OFF)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  if (COSMO_PGO_GENERATE)
    add_compile_options(-fprofile-generate)
    add_link_options(-fprofile-generate)
  endif()
  if (COSMO_PGO_USE)
    add_compile_options(-fprofile-use -fprofile-correction)
    add_link_options(-fprofile-use -fprofile-correction)
  endif()
endif()

# Reproducible builds: remove absolute paths in debug info (opt-in via COSMO_HARDEN or Release)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-ffile-prefix-map=${CMAKE_SOURCE_DIR}=. -ffile-prefix-map=${CMAKE_BINARY_DIR}=.)
endif()


if (COSMO_BUILD_TESTS)
  add_executable(cosmo_test_config_env tests/test_config_env.cpp)
  target_link_libraries(cosmo_test_config_env PRIVATE cosmoverse)
  add_test(NAME cosmoverse_config_env COMMAND cosmo_test_config_env)
endif()


# ---- MSVC hardening (opt-in via COSMO_HARDEN) ----
if (COSMO_HARDEN AND MSVC)
  add_compile_options(/guard:cf /Qspectre /sdl)
  add_link_options(/guard:cf /DYNAMICBASE /NXCOMPAT)
endif()


# ---- CPack metadata enrichments ----
set(CPACK_PACKAGE_VENDOR "COSMOVERSE")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "COSMOVERSE ENGINE — portable C++ library and CLI")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_CONTACT "Maintainers <security@example.com>")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/your-org/cosmoverse-engine")

# Debian/RPM fields
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "COSMOVERSE Maintainers")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_ARCHIVE_TYPE "xz")
set(CPACK_RPM_PACKAGE_LICENSE "Apache-2.0")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_COMPRESSION_TYPE "xz")

# Strip binaries in packages for smaller size
set(CPACK_STRIP_FILES ON)

# Windows NSIS installer (if generator available)
if (WIN32)
  list(APPEND CPACK_GENERATOR "NSIS")
  set(CPACK_NSIS_DISPLAY_NAME "COSMOVERSE ENGINE")
  set(CPACK_NSIS_CONTACT "Maintainers <security@example.com>")
  set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/your-org/cosmoverse-engine")
endif()


# ---- Build info (git/compilers) ----
# Try to obtain git metadata; do not fail if not a git checkout.
execute_process(COMMAND git describe --tags --always --dirty
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_DESC OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET)
execute_process(COMMAND git rev-parse --short=12 HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_SHA OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET)
string(TIMESTAMP BUILD_TIME "%Y-%m-%dT%H:%M:%SZ" UTC)
set(COSMO_GIT_DESC "${GIT_DESC}")
set(COSMO_GIT_SHA "${GIT_SHA}")
set(COSMO_BUILD_TIME "${BUILD_TIME}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/cosmoverse/build_info.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/generated/build_info.hpp @ONLY)
# include dir for generated headers (already added for version.hpp; ensure present)
target_include_directories(cosmoverse PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/generated)


# ---- Crash handler (opt-in) ----
option(COSMO_CRASH_HANDLER "Install simple crash handler with backtrace on Unix" OFF)
if (COSMO_CRASH_HANDLER)
  target_compile_definitions(cosmoverse PUBLIC COSMO_CRASH_HANDLER=1)
  if (UNIX)
    include(CheckLibraryExists)
    check_library_exists(execinfo backtrace "" HAVE_EXECINFO)
    if (HAVE_EXECINFO)
      target_link_libraries(cosmoverse PRIVATE execinfo)
    endif()
  endif()
endif()


# ---- Optional OpenMP ----
option(COSMO_ENABLE_OPENMP "Enable OpenMP (bench-omp command)" OFF)
if (COSMO_ENABLE_OPENMP)
  find_package(OpenMP REQUIRED)
  target_link_libraries(cosmoverse PUBLIC OpenMP::OpenMP_CXX)
endif()


# ---- Library versioning ----
set_target_properties(cosmoverse PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR})


# ---- pkg-config file ----
include(GNUInstallDirs)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/pkgconfig/cosmoverse.pc.in
               ${CMAKE_CURRENT_BINARY_DIR}/cosmoverse.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cosmoverse.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)


# ---- Link Time Optimization (LTO/IPO) ----
option(COSMO_LTO "Enable Interprocedural Optimization (LTO/IPO)" OFF)
if (COSMO_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_supported OUTPUT ipo_msg)
  if (ipo_supported)
    message(STATUS "IPO/LTO enabled")
    set_property(TARGET cosmoverse PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(WARNING "IPO not supported: ${ipo_msg}")
  endif()
endif()

# ---- LeakSanitizer ----
option(COSMO_ENABLE_LSAN "Enable LeakSanitizer" OFF)
if (COSMO_ENABLE_LSAN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-fsanitize=leak -fno-omit-frame-pointer)
  add_link_options(-fsanitize=leak)
endif()

# ---- Default hidden visibility (export via COSMO_API) ----
option(COSMO_DEFAULT_HIDDEN "Use -fvisibility=hidden by default" ON)
if (COSMO_DEFAULT_HIDDEN AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden)
endif()


# ---- Split debug symbols (Linux) ----
option(COSMO_SPLIT_DEBUG "Split debug symbols into .debug directory" OFF)
if (COSMO_SPLIT_DEBUG AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_custom_target(split-debug ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:cosmoverse>/.debug
    COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:cosmoverse> $<TARGET_FILE_DIR:cosmoverse>/.debug/cosmoverse.debug
    COMMAND ${CMAKE_STRIP} --strip-debug --strip-unneeded $<TARGET_FILE:cosmoverse>
    COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=$<TARGET_FILE_DIR:cosmoverse>/.debug/cosmoverse.debug $<TARGET_FILE:cosmoverse>
    COMMENT "Splitting debug symbols"
    VERBATIM)
endif()


# ---- Optional faster linker (LLD/mold) ----
option(COSMO_USE_LLD "Use lld (or mold via -fuse-ld=lld) when available" OFF)
if (COSMO_USE_LLD AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_link_options(-fuse-ld=lld)
endif()


# ---- Strict linking: fail on undefined symbols ----
option(COSMO_STRICT_LINK "Disallow undefined symbols at link time" ON)
if (COSMO_STRICT_LINK)
  if (APPLE)
    add_link_options(-Wl,-undefined,error)
  elseif (UNIX)
    add_link_options(-Wl,--no-undefined -Wl,-z,defs)
  endif()
endif()


# ---- Optional allocators ----
option(COSMO_USE_MIMALLOC "Link with mimalloc if found" OFF)
option(COSMO_USE_JEMALLOC "Link with jemalloc if found" OFF)
if (COSMO_USE_MIMALLOC)
  find_library(MIMALLOC_LIB mimalloc)
  if (MIMALLOC_LIB)
    target_link_libraries(cosmoverse PUBLIC ${MIMALLOC_LIB})
    message(STATUS "Using mimalloc: ${MIMALLOC_LIB}")
  else()
    message(WARNING "mimalloc not found")
  endif()
endif()
if (COSMO_USE_JEMALLOC)
  find_library(JEMALLOC_LIB jemalloc)
  if (JEMALLOC_LIB)
    target_link_libraries(cosmoverse PUBLIC ${JEMALLOC_LIB})
    message(STATUS "Using jemalloc: ${JEMALLOC_LIB}")
  else()
    message(WARNING "jemalloc not found")
  endif()
endif()


# ---- Extra linker hardening (RELRO/NOW, noexecstack) ----
if (COSMO_HARDEN AND UNIX AND NOT APPLE)
  add_link_options(-Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack)
endif()


if (COSMO_BUILD_TESTS)
  add_executable(cosmo_headers_selfcheck tests/headers_selfcheck.cpp)
  target_link_libraries(cosmo_headers_selfcheck PRIVATE cosmoverse)
  add_test(NAME headers_selfcheck COMMAND cosmo_headers_selfcheck)
endif()


# ---- Sample plugin build ----
if (WIN32)
  add_library(cosmo_sample_plugin SHARED plugins/sample/sample_plugin.cpp)
else()
  add_library(cosmo_sample_plugin MODULE plugins/sample/sample_plugin.cpp)
endif()
set_target_properties(cosmo_sample_plugin PROPERTIES PREFIX "")
target_include_directories(cosmo_sample_plugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (COSMO_BUILD_TESTS)
  add_test(NAME plugin_sample COMMAND cosmoverse plugin $<TARGET_FILE:cosmo_sample_plugin> --ping)
endif()

# Ensure plugin loader is part of library
if (TARGET cosmoverse)
  target_sources(cosmoverse PRIVATE src/core/plugin_loader.cpp)
endif()


# ---- CMake package exports ----
include(GNUInstallDirs)
install(TARGETS cosmoverse
        EXPORT CosmoverseTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT CosmoverseTargets
        NAMESPACE Cosmoverse::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cosmoverse)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CosmoverseConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/CosmoverseConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cosmoverse
  )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CosmoverseConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/CosmoverseConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cosmoverse)


# ---- CPack DMG for macOS ----
if (APPLE)
  list(APPEND CPACK_GENERATOR "DragNDrop")
  set(CPACK_DMG_VOLUME_NAME "COSMOVERSE")
  set(CPACK_DMG_FORMAT "UDBZ")
endif()


# ---- Internationalization (gettext) ----
option(COSMO_I18N "Enable gettext-based i18n for CLI strings" OFF)
if (COSMO_I18N)
  find_package(Gettext)
  if (Gettext_FOUND)
    add_compile_definitions(HAVE_GETTEXT=1 COSMO_I18N=1)
    if (UNIX AND NOT APPLE)
      # link libintl if needed
      find_library(LIBINTL intl)
      if (LIBINTL) target_link_libraries(cosmoverse PRIVATE ${LIBINTL}) endif()
    endif()
  else()
    message(WARNING "Gettext not found; i18n disabled")
  endif()
endif()


# ---- Hardening defaults for Release ----
option(COSMO_HARDEN_DEFAULTS "Apply strong hardening flags in Release" ON)
include(CheckCXXCompilerFlag)
macro(add_if_supported flag)
  string(REPLACE "-" "_" flag_var ${flag})
  string(REPLACE "=" "_" flag_var ${flag_var})
  check_cxx_compiler_flag(${flag} HAVE_${flag_var})
  if (HAVE_${flag_var})
    add_compile_options(${flag})
  endif()
endmacro()

if (CMAKE_BUILD_TYPE MATCHES "Release" AND COSMO_HARDEN_DEFAULTS)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_if_supported(-fstack-protector-strong)
    add_if_supported(-D_FORTIFY_SOURCE=3)
    add_if_supported(-fPIE)
    if (UNIX AND NOT APPLE)
      add_link_options(-pie)
      add_link_options(-Wl,-z,relro -Wl,-z,now)
    endif()
    # Control Flow Protection (x86/Clang)
    add_if_supported(-fcf-protection=full)
    add_if_supported(-fno-omit-frame-pointer)
  endif()
endif()


# ---- macOS universal2 build option ----
option(COSMO_MACOS_UNIVERSAL2 "Build universal2 (x86_64 + arm64) on macOS" OFF)
if (APPLE AND COSMO_MACOS_UNIVERSAL2)
  set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)
endif()


# (Docs & toolchain file for WASI are provided under cmake/toolchains and docs/WASI.md)


# ---- Plugin allowlist (OpenSSL SHA-256) ----
option(COSMO_PLUGIN_VERIFY_SHA256 "Enable plugin SHA-256 allowlist via OpenSSL if available" ON)
if (COSMO_PLUGIN_VERIFY_SHA256)
  find_package(OpenSSL)
  if (OpenSSL_FOUND)
    target_link_libraries(cosmoverse PRIVATE OpenSSL::Crypto)
    target_compile_definitions(cosmoverse PRIVATE COSMO_HAVE_OPENSSL=1)
  else()
    message(WARNING "OpenSSL not found; plugin allowlist check will be disabled at runtime")
  endif()
endif()


# ---- Unity builds (faster compile) ----
option(COSMO_UNITY "Enable CMake unity builds for faster compilation" OFF)
if (COSMO_UNITY)
  set(CMAKE_UNITY_BUILD ON)
endif()


# ---- Precompiled headers ----
option(COSMO_PCH "Enable precompiled headers for core target" ON)
if (COSMO_PCH AND TARGET cosmoverse)
  target_precompile_headers(cosmoverse PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/cosmoverse/pch.hpp>")
endif()


# ---- Optional Google Benchmark harness ----
option(COSMO_ENABLE_BENCHMARKS "Build Google Benchmark harness if benchmark is available" OFF)
if (COSMO_ENABLE_BENCHMARKS)
  find_package(benchmark QUIET)
  if (benchmark_FOUND)
    add_executable(cosmo_bench benchmarks/google_bench.cpp)
    target_link_libraries(cosmo_bench PRIVATE cosmoverse benchmark::benchmark)
    target_include_directories(cosmo_bench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  else()
    message(WARNING "benchmark library not found; skipping cosmo_bench")
  endif()
endif()


# ---- Link Time Optimization (optional) ----
option(COSMO_ENABLE_LTO "Enable -flto if supported" OFF)
include(CheckIPOSupported)
if (COSMO_ENABLE_LTO)
  check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
  if (ipo_supported)
    set_property(TARGET cosmoverse PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(WARNING "IPO/LTO not supported: ${ipo_error}")
  endif()
endif()


# ---- Sanitizers wiring ----
set(COSMO_SANITIZE "OFF" CACHE STRING "Enable sanitizer: OFF/ASAN/UBSAN/TSAN/MSAN")
string(TOUPPER "${COSMO_SANITIZE}" _COSMO_SAN)
if (NOT _COSMO_SAN STREQUAL "OFF")
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    if (_COSMO_SAN STREQUAL "ASAN")
      add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
      add_link_options(-fsanitize=address)
    elseif (_COSMO_SAN STREQUAL "UBSAN")
      add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer)
      add_link_options(-fsanitize=undefined)
    elseif (_COSMO_SAN STREQUAL "TSAN")
      add_compile_options(-fsanitize=thread -fno-omit-frame-pointer)
      add_link_options(-fsanitize=thread)
    elseif (_COSMO_SAN STREQUAL "MSAN")
      add_compile_options(-fsanitize=memory -fno-omit-frame-pointer)
      add_link_options(-fsanitize=memory)
    endif()
  endif()
endif()


# ---- Control exported symbols ----
if (TARGET cosmoverse)
  if (APPLE)
    target_link_options(cosmoverse PRIVATE -Wl,-exported_symbols_list,${CMAKE_CURRENT_SOURCE_DIR}/cmake/symbols/exported_symbols.list)
  elseif(UNIX)
    target_link_options(cosmoverse PRIVATE -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/cmake/symbols/cosmoverse.map)
  endif()
endif()


# ---- LibFuzzer targets (advisory) ----
option(COSMO_BUILD_FUZZERS "Build libFuzzer targets (requires Clang)" OFF)
if (COSMO_BUILD_FUZZERS)
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_executable(fuzz_fnv1a tests/fuzz/fuzz_fnv1a.cc)
    target_link_libraries(fuzz_fnv1a PRIVATE cosmoverse)
    target_compile_options(fuzz_fnv1a PRIVATE -fsanitize=fuzzer,address -fno-omit-frame-pointer)
    target_link_options(fuzz_fnv1a PRIVATE -fsanitize=fuzzer,address)
  else()
    message(WARNING "Fuzzers require Clang; skipping")
  endif()
endif()


# ---- Optional allocators ----
set(COSMO_ALLOCATOR "default" CACHE STRING "Memory allocator: default|mimalloc|jemalloc")
if (COSMO_ALLOCATOR STREQUAL "mimalloc")
  find_package(mimalloc QUIET)
  if (mimalloc_FOUND)
    target_link_libraries(cosmoverse PRIVATE mimalloc)
    target_compile_definitions(cosmoverse PRIVATE COSMO_USE_MIMALLOC=1)
  else()
    message(WARNING "mimalloc not found; falling back to default allocator")
  endif()
elseif (COSMO_ALLOCATOR STREQUAL "jemalloc")
  find_library(JEMALLOC_LIB jemalloc)
  if (JEMALLOC_LIB)
    target_link_libraries(cosmoverse PRIVATE ${JEMALLOC_LIB})
    target_compile_definitions(cosmoverse PRIVATE COSMO_USE_JEMALLOC=1)
  else()
    message(WARNING "jemalloc not found; falling back to default allocator")
  endif()
endif()


add_executable(cosmo_plugin_runner apps/cosmo_plugin_runner.cpp)
target_link_libraries(cosmo_plugin_runner PRIVATE cosmoverse)
install(TARGETS cosmo_plugin_runner RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# ---- Reproducible build knobs ----
option(COSMO_REPRO_BUILD "Enable reproducible-build flags when possible" ON)
if (COSMO_REPRO_BUILD)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Strip build paths from debug info and __FILE__
    add_compile_options(-ffile-prefix-map=${CMAKE_SOURCE_DIR}=. -fdebug-prefix-map=${CMAKE_SOURCE_DIR}=.)
    # Avoid embedding link-time build-id that varies
    if (UNIX AND NOT APPLE)
      add_link_options(-Wl,--build-id=none)
    endif()
  endif()
  # AR deterministic mode is default in modern binutils; ensure for older
  if (CMAKE_AR)
    message(STATUS "Using AR: ${CMAKE_AR}")
  endif()
endif()


# ---- Compiler cache (ccache/sccache) ----
option(COSMO_USE_CCACHE "Enable ccache/sccache if available" ON)
if (COSMO_USE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  find_program(SCCACHE_PROGRAM sccache)
  if (CCACHE_PROGRAM)
    message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER   ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
  elseif(SCCACHE_PROGRAM)
    message(STATUS "Using sccache: ${SCCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER   ${SCCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${SCCACHE_PROGRAM})
  endif()
endif()


option(COSMO_HARDENED "Enable portable hardening flags where supported" ON)
if (COSMO_HARDENED)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-D_FORTIFY_SOURCE=3 -fstack-protector-strong -fvisibility=hidden -fvisibility-inlines-hidden)
    if (UNIX AND NOT APPLE)
      add_link_options(-Wl,-z,relro -Wl,-z,now)
    endif()
  elseif (MSVC)
    add_compile_options(/guard:cf)
    add_link_options(/GUARD:CF)
  endif()
endif()

include(GNUInstallDirs)
set(COSMO_PC ${CMAKE_CURRENT_BINARY_DIR}/cosmoverse.pc)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/pkgconfig/cosmoverse.pc.in ${COSMO_PC} @ONLY)
install(FILES ${COSMO_PC} DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)


# Extra Windows linker security
if (MSVC)
  add_link_options(/NXCOMPAT /DYNAMICBASE /HIGHENTROPYVA)
endif()


# ---- Compile-time knobs ----
option(COSMO_UNITY_BUILD "Enable Unity/Jumbo builds to speed up compilation" OFF)
if (COSMO_UNITY_BUILD)
  set(CMAKE_UNITY_BUILD ON)
endif()

option(COSMO_IPO "Enable Interprocedural Optimization (LTO/IPO) if supported" OFF)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_msg)
if (COSMO_IPO AND ipo_supported)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

set(COSMO_PGO "OFF" CACHE STRING "PGO mode: OFF|GENERATE|USE")
set_property(CACHE COSMO_PGO PROPERTY STRINGS OFF GENERATE USE)
set(COSMO_PGO_DIR "${CMAKE_BINARY_DIR}/pgo" CACHE PATH "Directory for PGO profiles")
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  if (COSMO_PGO STREQUAL "GENERATE")
    add_compile_options(-fprofile-generate=${COSMO_PGO_DIR})
    add_link_options(-fprofile-generate=${COSMO_PGO_DIR})
  elseif (COSMO_PGO STREQUAL "USE")
    add_compile_options(-fprofile-use=${COSMO_PGO_DIR} -fprofile-correction)
    add_link_options(-fprofile-use=${COSMO_PGO_DIR} -fprofile-correction)
  endif()
endif()


# ---- CPU feature toggles ----
set(COSMO_CPU "" CACHE STRING "Enable CPU-specific optimizations: sse2;avx2;neon (semicolon-separated)")
if (COSMO_CPU)
  foreach(f IN LISTS COSMO_CPU)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
      if (f STREQUAL "sse2")  add_compile_options(-msse2)
      if (f STREQUAL "avx2")  add_compile_options(-mavx2)
      if (f STREQUAL "neon")  add_compile_options(-mfpu=neon)
    elseif (MSVC)
      if (f STREQUAL "avx2")  add_compile_options(/arch:AVX2)
      if (f STREQUAL "sse2")  add_compile_options(/arch:SSE2)
    endif()
  endforeach()
endif()

add_executable(test_compiles tests/compiles.cpp)
add_test(NAME test_compiles COMMAND test_compiles)
