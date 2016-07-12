package flock

sealed trait Fitness extends Ordered[Fitness]

case class Minimization(value: Double) extends Fitness {
  val order = Ordering.Double
  override def compare(that: Fitness): Int = that match {
    case Minimization(other) =>
      order.compare(value, other)
    case Maximization(_) => sys.error("Fitness error: minimizing entity cannot be compared to maximizing entity.")
  }
}
case class Maximization(value: Double) extends Fitness {
  val order = Ordering.Double.reverse
  override def compare(that: Fitness): Int = that match {
    case Maximization(other) => order.compare(value, other)
    case Minimization(_) => sys.error("Fitness error: maximizing entity cannot be compared to minimizing entity.")
  }
}

object Fitness {
  def minimize(value: Double) = Minimization(value)
  def maximize(value: Double) = Maximization(value)

  def minimizeF[T](f: T => Double) = f andThen minimize
  def maximizeF[T](f: T => Double) = f andThen maximize
}
