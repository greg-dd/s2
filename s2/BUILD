# Cloned from https://github.com/google/s2geometry/tree/v0.9.0
#
# The following modifications were made so as to compile with Bazel and
# integrate into our existing codebase:
#
# i) introducing a testing bazel macro instantiating an `cc_test` rule for S2 tests
#      under s2test.bzl;
#
# ii) deleting `third_party/cmake`;
#
package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

DEFAULT_COPTS = [
    "-DS2_USE_GFLAGS",
    "-DS2_USE_GLOG",
    "-DS2_USE_EXACTFLOAT",
    "-DHASH_NAMESPACE=std",
    "-Wno-attributes",
    "-Wno-deprecated-declarations",
    "-Wno-format",
    "-Wno-non-virtual-dtor",
    "-Wno-parentheses",
    "-Wno-sign-compare",
    "-Wno-strict-aliasing",
    "-Wno-unused-function",
    "-Wno-unused-private-field",
    "-Wno-unused-variable",
    "-Wno-unused-function",
]

cc_library(
    name = "s2",
    srcs = glob(
        ["**/*.cc"],
        exclude = [
            "*_test.cc",
            "*_testing.cc",
            "doc/**",
        ],
    ),
    hdrs = glob(
        ["**/*.h"],
        exclude = ["*_testing.h"],
    ),
    copts = DEFAULT_COPTS,
    linkstatic = False,
    deps = [
        "@boringssl//:crypto",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_absl//absl/algorithm",
        "@com_google_absl//absl/base",
	"@com_google_absl//absl/cleanup:cleanup",
	"@com_google_absl//absl/container:btree",
        "@com_google_absl//absl/container:container_memory",
        "@com_google_absl//absl/container:fixed_array",
	"@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/container:inlined_vector",
        "@com_google_absl//absl/container:layout",
	"@com_google_absl//absl/container:node_hash_map",
	"@com_google_absl//absl/flags:flag",
	"@com_google_absl//absl/flags:reflection",
	"@com_google_absl//absl/hash",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/meta:type_traits",
        "@com_google_absl//absl/numeric:int128",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
        "@com_google_absl//absl/types:span",
        "@com_google_absl//absl/utility",
        "@com_google_glog//:glog",
    ],
)

# Common deps for tests.
cc_library(
    name = "s2testing",
    srcs = glob(["*testing.*"]),
    copts = DEFAULT_COPTS,
    deps = [
        ":s2",
        "@com_google_googletest//:gtest_main",
    ],
)

# For running all tests.
test_suite(
    name = "smoke_tests",
)

# Load testing macro.
load(":s2test.bzl", "s2test")
