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

#include "domain.h"
#include "gtest/gtest.h"

TEST(DomainTest, should_have_values) {
  auto lower = -5.0;
  auto upper = 5.0;
  auto size = 30;
  auto d = Domain(lower, upper, size);
  EXPECT_EQ(lower, d.lower);
  EXPECT_EQ(upper, d.upper);
  EXPECT_EQ(size, d.size);
}
