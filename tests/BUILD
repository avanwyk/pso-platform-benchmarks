cc_test(
    name = "cswarm",
    srcs = glob(
        ["cc/*.cc"]
    ),
    copts = [
        "-Iexternal/gtest/include",
        "-Icswarm/cc"
    ],
    deps = [
        "@gtest//:main",
        "//cswarm:core"
    ]
)
