/*
Copyright 2016 Andrich van Wyk

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <Eigen/Core>
#include <iostream>

#include "domain.h"
#include "gtest/gtest.h"
#include "particle.h"
#include "pso.h"
#include "pso_functions.h"
#include "random.h"

using Eigen::ArrayXd;
using std::cout;
using std::endl;
using cswarm::pso::gbest;
using cswarm::pso::lbest;

double spherical(const ArrayXd& position) {
  return (position * position).sum();
}

TEST(PSOTest, should_construct) {
  auto rng = std::make_shared<Random>(1L);
  auto d = Domain(-5.0, 5.0, 30);
  auto p = PSOParameters(0.72, 1.4, 1.4, 1.0, 5);
  auto pso = PSO(5, d, p, spherical, lbest, rng);
}

TEST(PSOTest, should_optimize) {
  auto rng = std::make_shared<Random>(1L);
  auto d = Domain(-5.0, 5.0, 10);
  auto p = PSOParameters(0.72, 1.4, 1.4, 1.0, 5);
  auto pso = PSO(25, d, p, spherical, gbest, rng);
  
  auto result = pso.optimize(10);
}
