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

#ifndef CSWARM_CC_RANDOM_H_
#define CSWARM_CC_RANDOM_H_

#include <stdint.h>
#include <random>
#include <Eigen/Core>

#include "domain.h"

class Random {
 public:
  explicit Random(int64_t seed): generator_(seed) { }
  ~Random() {}
  
  Eigen::VectorXd random_vector(int size);
  Eigen::VectorXd random_vector(int size, double lower, double upper);
  Eigen::VectorXd random_vector(const Domain&);

 private:
  Random(const Random& other) { }
 
  std::mt19937_64 generator_;
  std::uniform_real_distribution<> uniform_;
};

#endif  // CSWARM_CC_RANDOM_H_
