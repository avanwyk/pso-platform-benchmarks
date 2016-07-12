val breezeVersion = "0.12"
val scalaCheckVersion = "1.12.5"
val scalaTestVersion = "2.2.6"

lazy val buildSettings = Seq(
  organization := "com.avanwyk.flock",
  scalaVersion := "2.11.8"
)

lazy val commonSettings = Seq(
  scalacOptions ++= Seq(
    "-deprecation",
    "-encoding", "UTF-8",
    "-feature",
    "-unchecked",
    "-Xfatal-warnings",
    "-Xlint",
    "-Yno-adapted-args",
    "-Ywarn-dead-code",
    "-Ywarn-numeric-widen",
    "-Ywarn-value-discard",
    "-Xfuture"
  ),
  resolvers ++= Seq(
    Resolver.sonatypeRepo("releases")
  )
)

lazy val flockSettings = buildSettings ++ commonSettings

lazy val flock = project.in(file("."))
  .settings(flockSettings)
  .aggregate(math, core, tests)
  .dependsOn(math, core, tests)

lazy val math = project
  .settings(moduleName := "flock-math")
  .settings(flockSettings)
  .settings(Seq(
    libraryDependencies ++= Seq(
      "org.scalanlp" %% "breeze" % breezeVersion,
      "org.scalanlp" %% "breeze-natives" % breezeVersion
    )
  ))

lazy val core = project
  .dependsOn(math)
  .settings(moduleName := "flock-core")
  .settings(flockSettings)
  .settings(Seq(

  ))

lazy val tests = project
  .dependsOn(math, core)
  .settings(moduleName := "flock-tests")
  .settings(flockSettings)
  .settings(Seq(
    libraryDependencies ++= Seq(
      "org.scalacheck" %% "scalacheck" % scalaCheckVersion % "test"
    )
  ))
