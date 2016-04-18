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
#include "Domain.h"

TEST(DomainTest, shouldHaveValues) {
  auto lower = -5.0;
  auto upper = 5.0;
  auto dim = 30;
  auto d = Domain(lower, upper, dim);
  EXPECT_EQ(lower, d.getLower());
  EXPECT_EQ(upper, d.getUpper());
  EXPECT_EQ(dim, d.getDim());
}
