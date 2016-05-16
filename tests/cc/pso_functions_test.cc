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

#include <memory>
#include <tuple>

#include "gtest/gtest.h"

#include "pso_functions.h"
#include "random.h"

using std::get;
using std::shared_ptr;
using std::make_shared;

using cswarm::pso::get_local_bounds;
using cswarm::pso::initialize_swarm;
using cswarm::pso::max_fitness;
using cswarm::pso::stationary_velocity;
using cswarm::pso::std_position;
using cswarm::pso::std_velocity;
using cswarm::pso::uniform_position;
using cswarm::pso::wrap_idx;

TEST(PSOFunctionsTest, get_local_bounds_span_odd_n_size) {
  auto bounds = get_local_bounds(5, 2);
  EXPECT_EQ(0, get<0>(bounds));
  EXPECT_EQ(5, get<1>(bounds));
}
  
TEST(PSOFunctionsTest, get_local_bounds_span_even_n_size) {
  auto bounds = get_local_bounds(4, 2);
  EXPECT_EQ(0, get<0>(bounds));
  EXPECT_EQ(4, get<1>(bounds));
}

TEST(PSOFunctionsTest, get_local_bounds_span_singular_n_size) { 
  auto bounds = get_local_bounds(1, 2);
  EXPECT_EQ(2, get<0>(bounds));
  EXPECT_EQ(3, get<1>(bounds));
}

TEST(PSOFunctionsTest, get_local_bounds_allows_negative_lower) {
  auto bounds = get_local_bounds(5, 0);
  EXPECT_EQ(-2, get<0>(bounds));
  EXPECT_EQ(3, get<1>(bounds));
}

TEST(PSOFunctionsTest, wrap_idx_should_wrap_lower) {
  EXPECT_EQ(9, wrap_idx(10, -1));
  EXPECT_EQ(8, wrap_idx(10, -2));
}

TEST(PSOFunctionsTest, wrap_idx_should_wrap_upper) {
  EXPECT_EQ(0, wrap_idx(10, 10));
  EXPECT_EQ(1, wrap_idx(10, 11));
}

TEST(PSOFunctionsTest, wrap_idx_should_index) {
  EXPECT_EQ(0, wrap_idx(10, 0));
  EXPECT_EQ(9, wrap_idx(10, 9));
  EXPECT_EQ(5, wrap_idx(10, 5));
}

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
