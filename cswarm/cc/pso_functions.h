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

#ifndef CSWARM_CC_PSO_FUNCTIONS_H_
#define CSWARM_CC_PSO_FUNCTIONS_H_

#include <cmath>
#include <memory>
#include <tuple>

#include <Eigen/Core>

#include "particle.h"
#include "pso_functions.h"
#include "pso_parameters.h"
#include "random.h"

using Eigen::ArrayXd;
using std::make_tuple;
using std::get;
using std::shared_ptr;
using std::tuple;
using std::vector;
using std::unique_ptr;

namespace cswarm {
namespace pso {
  
  inline static ArrayXd std_position(const ArrayXd& pos, const ArrayXd& vel) {
    return pos + vel;
  }
  
  inline static ArrayXd std_velocity(const Particle& particle,
                              double w, double c_1, double c_2,
                              const ArrayXd& cognitive, const ArrayXd& social,
                              shared_ptr<Random> rng) {
    auto dimension = particle.position.size();
    auto c_1r_1 = rng.get()->random_vector(dimension, 0.0, c_1);
    auto c_2r_2 = rng.get()->random_vector(dimension, 0.0, c_2);
    return w * particle.velocity + c_1r_1 * (cognitive - particle.position) +
            c_2r_2 * (social - particle.position);
  }
  
  inline static ArrayXd clamp_velocity(const ArrayXd& velocity, double v_max) {
    ArrayXd result = velocity;
    double* data = result.data();
    for (int i = 0; i < velocity.size(); ++i) {
      double& d = data[i];
      if (d > v_max) {
        d = v_max;
      } else if (d < -v_max) {
        d = -v_max;
      }
    }
    return result;
  }
  
  inline static ArrayXd std_velocity_with_v_max(const Particle& particle,
                              double w, double c_1, double c_2, double v_max,
                              const ArrayXd& cognitive, const ArrayXd& social,
                              shared_ptr<Random> rng) {
    return clamp_velocity(
      std_velocity(particle, w, c_1, c_2, cognitive, social, rng), v_max);
  }
  
  inline static ArrayXd uniform_position(const Domain& domain,
                                  shared_ptr<Random> rng) {
    return rng->random_vector(domain);
  }
  
  inline static ArrayXd stationary_velocity(const Domain& domain) {
    return ArrayXd::Zero(domain.size);
  }
  
  inline static double max_fitness() {
    return std::numeric_limits<double>::max();
  }
  
  template <typename P, typename V, typename F>
  inline static Particle make_particle(const Domain& domain, P p, V v, F f,
                                shared_ptr<Random> rng) {
    return Particle(p(domain, rng), v(domain), f());
  }
  
  template <typename P, typename V, typename F>
  inline static vector<Particle> initialize_swarm(const int size,
                                           const Domain& domain,
                                           P p, V v, F f,
                                           shared_ptr<Random> rng) {
    vector<Particle> swarm;
    for (int i = 0; i < size; ++i) {
      swarm.push_back(make_particle(domain, p, v, f, rng));
    }
    return swarm;
  }
  
  inline static const int wrap_idx(const int swarm_size, const int idx) {
    if (idx < 0) { 
      return idx + swarm_size;
    } else if (idx >= swarm_size) {
      return idx - swarm_size;
    }
    return idx;
  }
    
  inline static const Particle& nbest(const vector<Particle>& swarm,
                                      int lower, int upper) {
    auto swarm_size = swarm.size();
    auto nbest_fitness = swarm[wrap_idx(swarm_size, lower)].pbest_fitness;
    auto nbest = lower; 
    for (int i = lower + 1; i < upper; ++i) {
      auto particle = swarm[wrap_idx(swarm_size, i)];
      if (particle.pbest_fitness < nbest_fitness) {
        nbest = i;
        nbest_fitness = particle.pbest_fitness;
      }
    }
    return swarm[wrap_idx(swarm_size, nbest)];
  }
  
  inline static const Particle& gbest(const vector<Particle>& swarm,
                                      const int particle_idx) {
    auto gbest = 0;
    for (uint i = 1; i < swarm.size(); ++i) {
      if (swarm[i].pbest_fitness < swarm[gbest].pbest_fitness) {
        gbest = i;
      }
    }
    return swarm[gbest];
  }
  
  inline static const Particle& gbest(const vector<Particle>& swarm) {
    return gbest(swarm, 0);
  }
  
  inline static const tuple<int, int> get_local_bounds(const int n_size,
                                                       const int idx) {
    auto div = n_size / 2;
    auto lower = idx - div;
    auto upper = idx + (n_size - div);
    return make_tuple(lower, upper);
  }
  
  inline static const Particle& lbest(const vector<Particle>& swarm,
                                      const int n_size,
                                      const int particle_idx) {
    auto bounds = get_local_bounds(n_size, particle_idx);
    return nbest(swarm, get<0>(bounds), get<1>(bounds));
  }
  
};  // namespace pso
};  // namespace cswarm

#endif  // CSWARM_CC_PSO_FUNCTIONS_H_
