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

#ifndef CSWARM_CC_PSO_H_
#define CSWARM_CC_PSO_H_

#include <memory>
#include <vector>

#include <Eigen/Core>

#include "domain.h"
#include "particle.h"
#include "pso_functions.h"
#include "pso_parameters.h"
#include "random.h"
#include "result.h"

class PSO {
 public:
  PSO(int swarm_size, const Domain& domain, const PSOParameters& parameters,
      std::function<double(Eigen::ArrayXd)> fitness_function,
      shared_ptr<Random> rng)
      : swarm_size_(swarm_size),
        domain_(domain), parameters_(parameters),
        fitness_function_(fitness_function), rng_(rng) {}
         
  ~PSO() {}
  
  const Result optimize(const int);
  
  const std::vector<Particle>& get_swarm() const { return swarm_; }
  
 private:
  const int swarm_size_;
  const Domain& domain_;
  const PSOParameters& parameters_;
  const std::function<double(Eigen::ArrayXd)> fitness_function_;
  const std::shared_ptr<Random> rng_;
  std::vector<Particle> swarm_;
};

#endif  // CSWARM_CC_PSO_H_
