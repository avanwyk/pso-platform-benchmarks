# Cswarm
C++ based Particle Swarm Optimization. This library is still in the early development phases. Please check back soon.

### Build instructions
The project is built using [Bazel](http://bazel.io/).

* Core library

    ```shell
    bazel build cswarm/core -c opt
    ```
* Tests

    ```shell
    bazel test tests/cswarm -c opt
    ```
* Examples

    ```shell
    bazel run examples/gbest -c opt
    bazel run examples/lbest -c opt
    ```

### License
Cswarm uses the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)
