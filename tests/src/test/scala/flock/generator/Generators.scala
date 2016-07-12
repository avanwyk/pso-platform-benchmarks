package flock.generator

import breeze.linalg.DenseVector
import org.scalacheck.{Arbitrary, Gen}

object Generators {

  implicit def arbitraryDeepVector: Arbitrary[DenseVector[Double]] = Arbitrary {
    Gen.sized {
      size => for {
        data <- Gen.listOfN(size, Arbitrary.arbitrary[Double])
      } yield new DenseVector[Double](data.toArray)
    }
  }

}