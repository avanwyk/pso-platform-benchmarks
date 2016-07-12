# Scala PSO
Scala based implementation of the [particle swarm optimization](https://en.wikipedia.org/wiki/Particle_swarm_optimization) algorithm. The algorithm is implemented using [Scala Breeze](https://github.com/scalanlp/breeze) for scalability and efficiency.

## Implementation
The algorithm implemented is the synchronous modified gbest PSO with the inertia term as per:
* Shi, Yuhui, and Russell Eberhart. "A modified particle swarm optimizer." Evolutionary Computation Proceedings, 1998. IEEE World Congress on Computational Intelligence., The 1998 IEEE International Conference on. IEEE, 1998.

### Build instructions
The project is built using [SBT](http://www.scala-sbt.org/)

* Build

    ```shell
    sbt compile
    ```
* Tests

    ```shell
    sbt test
    ```

* Usage

    ```scala
    import breeze.linalg._
    import flock.Fitness
    import flock.math.Domain._
    import flock.math.RNG
    import flock.pso.PSO
    
    object Main extends App {

      // Spherical benchmark function
      def spherical(x: DenseVector[Double]) = sum(x :* x)
    
      val result = PSO.gbest(Fitness.minimizeF(spherical _), 25, (-5.12, 5.12) ^ 3000, PSO.defaultParams, RNG.mersenneTwister).run(1000)
    
    }
    ```

### License
The project uses [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)
