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

#include "pso.h"

using std::copy;
using std::function;
using std::shared_ptr;

using cswarm::pso::gbest;
using cswarm::pso::lbest;
using cswarm::pso::initialize_swarm;
using cswarm::pso::max_fitness;
using cswarm::pso::stationary_velocity;
using cswarm::pso::std_position;
using cswarm::pso::std_velocity_with_v_max;
using cswarm::pso::uniform_position;

const Result PSO::optimize(const int iterations) {
  auto swarm = initialize_swarm(swarm_size_, domain_,
                                uniform_position, stationary_velocity,
                                max_fitness, rng_);
  
  for (int iteration = 0; iteration < iterations; ++iteration) {
    for (int i = 0; i < swarm_size_; ++i) {
      Particle& particle = swarm[i];
      auto nbest = gbest(swarm, i);
      particle.velocity = std_velocity_with_v_max(particle,
                                 parameters_.w, parameters_.c_1,
                                 parameters_.c_2, parameters_.v_max,
                                 particle.pbest_position,
                                 nbest.pbest_position, rng_);
                                 
      particle.position = std_position(particle.position, particle.velocity);
    }
    
    for (int i = 0; i < swarm_size_; ++i) {
      Particle& particle = swarm[i];
      auto fitness = fitness_function_(particle.position);
      particle.fitness = fitness;
      
      if (fitness < particle.pbest_fitness) {
        particle.pbest_fitness = fitness;
        particle.pbest_position = particle.position;
      }
    }
  }
  
  return Result(gbest(swarm)); 
}
