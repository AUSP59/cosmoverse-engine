
vcpkg_from_git(
    OUT_SOURCE_PATH SOURCE_PATH
    URL https://github.com/your-org/cosmoverse-engine.git
    REF v1.0.0
)
vcpkg_cmake_configure(SOURCE_PATH ${SOURCE_PATH})
vcpkg_cmake_build()
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME cosmoverse)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
