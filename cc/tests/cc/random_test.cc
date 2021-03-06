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

#include "gtest/gtest.h"
#include "random.h"

TEST(RandomTest, should_create_vector_with_size) {
  Random random(1L);
  int size = 10;
  auto v = random.random_vector(size);
  EXPECT_EQ(size, v.size());
}

TEST(RandomTest, should_create_vector_with_size_in_bounds) {
  Random random(1L);
  auto size = 100000;
  auto lower = -5.0;
  auto upper = 5.0;
  auto v = random.random_vector(size, lower, upper);
  EXPECT_EQ(size, v.size());
  for (auto i = 0; i < v.size(); ++i) {
    EXPECT_LT(v[i], upper);
    EXPECT_GT(v[i], lower);
  }
}

TEST(RandomTest, should_create_vector_in_domain) {
  Random random(1L);
  auto size = 100000;
  auto lower = -5.0;
  auto upper = 5.0;
  auto domain = Domain(lower, upper, size);
  auto v = random.random_vector(domain.size);
  EXPECT_EQ(size, v.size());
  for (auto i = 0; i < v.size(); ++i) {
    EXPECT_GT(v[i], domain.lower);
    EXPECT_LT(v[i], domain.upper);
  }
}
