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
#include "domain.h"
#include "gtest/gtest.h"
#include "particle.h"
#include "random.h"

using Eigen::ArrayXd;

TEST(ParticleTest, should_have_values) {
  Random rng(1L);
  auto domain = Domain(-5.0, 5.0, 30);
  
  auto position = rng.random_vector(domain);
  auto velocity = ArrayXd::Zero(domain.size);
  auto fitness = std::numeric_limits<double>::max();
  
  auto p = Particle(position, velocity, fitness);
  
  ASSERT_TRUE(position.isApprox(p.position));
  ASSERT_TRUE(velocity.isApprox(p.velocity));
  ASSERT_TRUE(position.isApprox(p.pbest_position));
  EXPECT_EQ(fitness, p.fitness);
  EXPECT_EQ(fitness, p.pbest_fitness);
}
