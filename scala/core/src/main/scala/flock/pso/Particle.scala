package flock.pso

import breeze.linalg.DenseVector
import flock.Fitness
import flock.math.{Domain, RNG}

case class Particle(position: DenseVector[Double],
                    pBestPosition: DenseVector[Double],
                    velocity: DenseVector[Double],
                    fitness: Fitness,
                    pBestFitness: Fitness)

object Particle {

  def uniform(domain: Domain)(implicit rng: RNG) = Domain.uniformSample(domain)

  def stationary(domain: Domain) = DenseVector.zeros[Double](domain.dim)

  def updateFitness(particle: Particle, fitnessF: (DenseVector[Double]) => Fitness) = {
    val fitness = fitnessF(particle.position)
    if (fitness < particle.pBestFitness) {
      particle.copy(pBestFitness = fitness, pBestPosition = particle.position, fitness = fitness)
    } else {
      particle.copy(fitness = fitness)
    }
  }

}
