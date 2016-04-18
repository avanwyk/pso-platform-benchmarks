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

#include "random.h"

using Eigen::VectorXd;

Random::Random(int64_t seed): generator(seed) { }

VectorXd Random::random_vector(int size) {
  return VectorXd::NullaryExpr(size, [this] (VectorXd::Index) {
    return uniform(generator);
  });
}

VectorXd Random::random_vector(int size, double lower, double upper) {
  std::uniform_real_distribution<> distribution(lower, upper);
  
  return VectorXd::NullaryExpr(size, [this, &distribution] (VectorXd::Index) {
    return distribution(generator);
  });
}

VectorXd Random::random_vector(const Domain& domain) {
  return random_vector(domain.getDim(), domain.getLower(), domain.getUpper());
}
