# Bazel macro that instantiates a native cc_test rule for an S2 test.
def s2test(name, deps = [], size = "small"):
    native.cc_test(
        name = name,
        srcs = ["%s.cc" % (name)],
        copts = [
            "-Iexternal/gtest/include",
            "-DS2_TEST_DEGENERACIES",
            "-DS2_USE_GFLAGS",
            "-DS2_USE_GLOG",
            "-DHASH_NAMESPACE=std",
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
        ],
        deps = [":s2testing"] + deps,
        size = size,
    )
