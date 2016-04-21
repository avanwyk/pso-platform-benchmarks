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
#include <memory>
#include "gtest/gtest.h"
#include "pso_functions.h"
#include "random.h"

using std::shared_ptr;
using std::make_shared;
using cswarm::pso::std_position;
using cswarm::pso::std_velocity;
using cswarm::pso::initialize_swarm;
using cswarm::pso::max_fitness;
using cswarm::pso::stationary_velocity;
using cswarm::pso::uniform_position;
using cswarm::pso::update_fitness;

TEST(PSOFunctionsTest, std_position) {
  Random rng(1L);
  auto size = 3000;
  auto pos = rng.random_vector(size);
  auto vel = rng.random_vector(size);
  auto res = std_position(pos, vel);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(pos(i) + vel(i), res(i));
  }
}

TEST(PSOFunctionsTest, std_velocity) {
  auto rng = make_shared<Random>(1L);
  auto size = 3000;
  auto w = 0.72;
  auto c_1 = 1.4;
  auto c_2 = 1.4;
  auto cog = rng->random_vector(size, -1.0, 1.0);
  auto soc = rng->random_vector(size, -1.0, 1.0);
  auto pos = rng->random_vector(size, -1.0, 1.0);
  auto vel = rng->random_vector(size, -0.1, 0.1);
  auto particle = Particle(pos, vel, 0.0);
  
  auto updated_vel = std_velocity(particle, w, c_1, c_2, cog, soc, rng);
  EXPECT_EQ(updated_vel.size(), vel.size());
}

TEST(PSOFunctionsTest, should_initialize_swarm) {
  auto rng = std::make_shared<Random>(1L);
  auto d = Domain(-5.0, 5.0, 5);
  auto swarm_size = 5;
                 
  auto swarm = initialize_swarm(swarm_size, d, uniform_position, 
                                stationary_velocity, max_fitness, rng);
  
  EXPECT_EQ(swarm_size, swarm.size());  
}

TEST(PSOFunctionsTest, should_update_bests) {
  auto size = 10;
  auto rng = make_shared<Random>(1L);
  auto pos = rng->random_vector(size, -1.0, 1.0);
  auto n_pos = rng->random_vector(size, -1.0, 1.0);
  auto vel = rng->random_vector(size, -0.1, 0.1);
  
  auto swarm = vector<Particle>();
  swarm.push_back(Particle(pos, vel, 1.0));
  
  swarm[0].position = n_pos;
  
  update_fitness(&swarm[0], 0.0);
  
  ASSERT_TRUE(n_pos.isApprox(swarm[0].pbest_position));
  EXPECT_EQ(0.0, swarm[0].fitness);
  EXPECT_EQ(0.0, swarm[0].pbest_fitness);
}
