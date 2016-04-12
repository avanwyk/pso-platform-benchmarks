cc_test(
    name = "cwarm",
    srcs = glob(
        ["cc/*.cc"]
    ),
    copts = [
        "-Iexternal/gtest/include",
        "-Icwarm/cc"
    ],
    deps = [
        "@gtest//:main",
        "//cwarm:core"
    ]
)
