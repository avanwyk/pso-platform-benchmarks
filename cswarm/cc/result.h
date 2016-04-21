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

#ifndef CSWARM_CC_RESULT_H_
#define CSWARM_CC_RESULT_H_

#include <memory>

using std::shared_ptr;

class Result {
 public:
  explicit Result(const Particle& particle) {
    auto pbest = particle.pbest_position.data();
    auto size = particle.pbest_position.size();
    solution_ = shared_ptr<double>(new double[size]);
    std::copy(pbest, pbest + size, &*solution_);
    fitness_ = particle.pbest_fitness;
  }
  
  const shared_ptr<double> getSolution() const {
    return solution_;
  }
  
  const double getFitness() const {
    return fitness_;
  }
 private:
  shared_ptr<double> solution_;
  double fitness_;
};

#endif  // CSWARM_CC_RESULT_H_
