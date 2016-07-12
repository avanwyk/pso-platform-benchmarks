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

#ifndef CSWARM_CC_PSO_PARAMETERS_H_
#define CSWARM_CC_PSO_PARAMETERS_H_

struct PSOParameters {
  PSOParameters(const double w, const double c_1, const double c_2,
                const double v_max, const int ns): w(w), c_1(c_1), c_2(c_2),
                v_max(v_max), ns(ns) {}
  
  const double w;
  const double c_1;
  const double c_2;
  const double v_max;
  const int ns;
};

#endif  // CSWARM_CC_PSO_PARAMETERS_H_
