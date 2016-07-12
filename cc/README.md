# C/C++ PSO
C++ based implementation of the Particle Swarm Optimization algorithm. The code is functional in style and uses the [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) linear algebra library.

## Implementation
The algorithm implemented is the synchronous modified gbest PSO with the inertia term as per:
* Shi, Yuhui, and Russell Eberhart. "A modified particle swarm optimizer." Evolutionary Computation Proceedings, 1998. IEEE World Congress on Computational Intelligence., The 1998 IEEE International Conference on. IEEE, 1998.

### Build instructions
The project is built using [Bazel](http://bazel.io/).

* Core

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
The project uses [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)
