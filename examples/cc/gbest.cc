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
#include "particle.h"
#include "pso.h"
#include "random.h"

using Eigen::ArrayXd;
using std::cout;
using std::endl;

double sphericalF(const ArrayXd& solution) {
  return (solution * solution).sum();
}

int main() {
  auto rng = std::make_shared<Random>(15632435212L);
  auto d = Domain(-5.0, 5.0, 1000);
  auto p = PSOParameters(0.72, 1.4, 1.4, 1.0);
  auto pso = PSO(25, d, p, sphericalF, rng);
  
  auto result = pso.optimize(1000);
  cout << result.getFitness() << endl;
  return 0;
}
