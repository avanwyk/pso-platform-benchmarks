package flock.math

import breeze.linalg.DenseVector

case class Domain(bounds: (Double, Double), dim: Int) {
  def lower = bounds._1

  def upper = bounds._2
}

object Domain {

  implicit class IntervalOps(val bounds: (Double, Double)) extends AnyVal {
    def ^(n: Int): Domain = new Domain((bounds._1, bounds._2), n)
  }

  def uniformSample(domain: Domain)(implicit rng: RNG) = {
    val scale = domain.upper - domain.lower
    DenseVector.rand[Double](domain.dim, rng.uniform) * scale :+ domain.lower
  }

}