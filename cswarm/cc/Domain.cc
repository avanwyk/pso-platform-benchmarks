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

#include "Domain.h"

Domain::Domain(double l, double u, int d) {
  lower = l;
  upper = u;
  dim = d;
}
  
double Domain::getLower() const {
  return lower;
}

double Domain::getUpper() const {
  return upper;
}

int Domain::getDim() const {
  return dim;
}

int Domain::getSize() const {
  return dim;
}
