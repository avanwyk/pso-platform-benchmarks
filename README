# Flock
Flock is a [particle swarm optimization](https://en.wikipedia.org/wiki/Particle_swarm_optimization) implementation in Scala. Flock is implemented using [Scala Breeze](https://github.com/scalanlp/breeze) for scalability and efficiency.

## Implementation
Flock currently implements the synchronous modified gbest PSO with the inertia term as per:
* Shi, Yuhui, and Russell Eberhart. "A modified particle swarm optimizer." Evolutionary Computation Proceedings, 1998. IEEE World Congress on Computational Intelligence., The 1998 IEEE International Conference on. IEEE, 1998.

## Usage
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