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

#include <iostream>
#include "pso.h"

using std::function;
using std::shared_ptr;
using std::copy;
using std::cout;
using std::endl;
using cswarm::pso::gbest;
using cswarm::pso::stdPosition;
using cswarm::pso::stdVelocityWithVmax;
using cswarm::pso::initialize_swarm;
using cswarm::pso::max_fitness;
using cswarm::pso::stationary_velocity;
using cswarm::pso::uniform_position;
using cswarm::pso::clamp_velocity;
using cswarm::pso::update_fitness;

const Result PSO::optimize(const int iterations) {
  auto swarm = initialize_swarm(swarm_size_, domain_,
                                uniform_position, stationary_velocity,
                                max_fitness, rng_);
  
  for (int iteration = 0; iteration < iterations; ++iteration) {
    for (uint i = 0; i < swarm.size(); ++i) {
      Particle* particle = &swarm[i];
      particle->velocity = stdVelocityWithVmax(*particle,
                                 parameters_.w, parameters_.c_1,
                                 parameters_.c_2, parameters_.v_max,
                                 particle->pbest_position,
                                 gbest(swarm).pbest_position, rng_);
      particle->position = stdPosition(particle->position, particle->velocity);
    }
    
    for (uint i = 0; i < swarm.size(); ++i) {
      auto particle = &swarm[i];
      auto fitness = fitness_function_(particle->position);
      update_fitness(particle, fitness);
    }
  }
  
  return Result(gbest(swarm)); 
}
