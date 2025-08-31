
load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")  # optional

cc_library(
    name = "cosmoverse",
    srcs = ["src/core/log.cpp","src/core/config.cpp","src/core/hash.cpp","src/core/thread_pool.cpp"],
    hdrs = glob(["include/cosmoverse/**/*.hpp"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "cosmoverse_cli",
    srcs = ["apps/cosmoverse.cpp"],
    deps = [":cosmoverse"],
)
