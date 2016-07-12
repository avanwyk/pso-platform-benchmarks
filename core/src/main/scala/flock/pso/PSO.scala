package flock.pso

import breeze.linalg._
import flock.Fitness
import flock.math.{Domain, RNG}
import flock.pso.Swarm._

object PSO {

  val defaultParams = PSOParameters(0.729844, 1.496180, 1.496180, 1.0)

  def gbest(fitnessF: (DenseVector[Double]) => Fitness, size: Int, domain: Domain, params: PSOParameters = defaultParams, rng: RNG = RNG.mersenneTwister) = {
    new PSO(size, domain, gbestTopology, fitnessF, params, rng)
  }

  class PSO(size: Int, domain: Domain, topology: (Array[Particle], Int) => DenseVector[Double],
            fitnessF: (DenseVector[Double]) => Fitness, params: PSOParameters,
            implicit val rng: RNG) {

    def run(iterations: Int) = {
      (1 to iterations)
        .foldLeft(Swarm.initialize(size, domain, Particle.uniform, Particle.stationary, fitnessF)) {
          (swarm, iteration) => {
            swarm.mapParticle {
              case (particle, idx) =>
                val velocity = clamp(stdVelocity(particle, params.w, params.c1, params.c2, particle.pBestPosition, topology(swarm, idx)), params.vMax)
                val position = stdPosition(particle.position, velocity)
                particle.copy(position = position, velocity = velocity)
            }.map(particle => Particle.updateFitness(particle, fitnessF)).toArray
          }
        }.globalBest
    }
  }

  case class PSOParameters(w: Double, c1: Double, c2: Double, vMax: Double)

  def gbestTopology(swarm: Array[Particle], idx: Int) = {
    swarm.minBy(p => p.pBestFitness).pBestPosition
  }

  def stdVelocity(particle: Particle, w: Double, c1: Double, c2: Double,
                  cognitive: DenseVector[Double], social: DenseVector[Double])(implicit rng: RNG) = {
    val dimension = particle.velocity.length
    val c1r1 = c1 * DenseVector.rand[Double](dimension, rng.uniform)
    val c2r2 = c2 * DenseVector.rand[Double](dimension, rng.uniform)
    w * particle.velocity + c1r1 :* (cognitive - particle.position) + c2r2 :* (social - particle.position)
  }

  def stdPosition(position: DenseVector[Double], velocity: DenseVector[Double]) = {
    position + velocity
  }

  def clamp(velocity: DenseVector[Double], vMax: Double) = {
    velocity.map(v => if (Math.abs(v) > vMax) Math.signum(v) * vMax else v)
  }

}
