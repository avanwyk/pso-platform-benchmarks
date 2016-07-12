package flock.math

import breeze.linalg.DenseVector
import flock.math.Domain._
import org.scalacheck.Prop._
import org.scalacheck._

object DomainProperties extends Properties("Domain") {

  import Prop.forAll

  val domain = for {
    x <- Arbitrary.arbitrary[Double]
    y <- Arbitrary.arbitrary[Double] suchThat (_ >= x)
    dim <- Gen.posNum[Int] suchThat (_ >= 1)
  } yield (x, y) ^ dim

    property("samples in domain bounds") = forAll(domain) {
      (domain) => {
        val sample: DenseVector[Double] = Domain.uniformSample(domain)(RNG.mersenneTwister)
        sample.length == domain.dim && sample.forall(v => v >= domain.lower && v <= domain.upper)
      }
    }


}
