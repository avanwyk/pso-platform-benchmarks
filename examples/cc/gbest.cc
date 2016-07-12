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
#include <cstdlib>

#include "domain.h"
#include "particle.h"
#include "pso.h"
#include "pso_functions.h"
#include "random.h"

using Eigen::ArrayXd;
using cswarm::pso::gbest;
using std::cout;
using std::endl;

double spherical_f(const ArrayXd& solution) {
  return (solution * solution).sum();
}

int get_dimension(int argc, char* argv[]) {
  return argc < 2 ? 1000 : atoi(argv[1]);
}

int get_swarm_size(int argc, char* argv[]) {
  return argc < 3 ? 25 : atoi(argv[2]);
}

int main(int argc, char* argv[]) {
  auto rng = std::make_shared<Random>(15632435212L);
  int dimensions = get_dimension(argc, argv);
  int swarm_size = get_swarm_size(argc, argv);
  auto d = Domain(-5.0, 5.0, dimensions);
  auto p = PSOParameters(0.729844, 1.496180, 1.496180, 0.1, 5);
  auto pso = PSO(swarm_size, d, p, spherical_f, gbest, rng);
  
  auto result = pso.optimize(1000);
  cout << result.getFitness() << endl;
  return 0;
}
