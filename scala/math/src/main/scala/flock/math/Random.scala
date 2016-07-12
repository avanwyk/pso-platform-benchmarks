package flock.math

import breeze.stats.distributions.{RandBasis, ThreadLocalRandomGenerator}
import org.apache.commons.math3.random.MersenneTwister

class RNG(seed: Long) {
  lazy val basis = new RandBasis(new ThreadLocalRandomGenerator(new MersenneTwister(seed)))

  val uniform = basis.uniform
}

object RNG {
  lazy val defaultSeed = System.currentTimeMillis + System.identityHashCode(this) + Thread.currentThread().getId

  lazy val mersenneTwister = new RNG(defaultSeed)

  def seed(seed: Long) = new RNG(seed)
}
