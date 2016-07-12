package flock.pso

import breeze.linalg.DenseVector
import flock.Fitness
import flock.math.Domain

object Swarm {

  implicit class SwarmOps(val swarm: Array[Particle]) extends AnyVal {
    def mapParticle[U](f: ((Particle, Int)) => Particle) = {
      swarm.view.zipWithIndex.map(f)
    }

    def globalBest = {
      swarm.minBy(p => p.pBestFitness)
    }
  }

  def initialize(size: Int, domain: Domain,
                 initPos: Domain => DenseVector[Double],
                 initVel: Domain => DenseVector[Double],
                 initFitness: (DenseVector[Double]) => Fitness) = {
    Array.fill(size) {
      val pos = initPos(domain)
      val fitness = initFitness(pos)
      Particle(pos, pos, initVel(domain), fitness, fitness)
    }
  }

}
