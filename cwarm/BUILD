cc_library(
    name = "core",
    hdrs = glob(["cc/*.h"]),
    srcs = glob(
        ["cc/*.cc"]
    ),
    copts = ["-Icwarm/cc"],
    deps = [
        "@eigen//:main"
    ],
    visibility = ["//visibility:public"]
)
