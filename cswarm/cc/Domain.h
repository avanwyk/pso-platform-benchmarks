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

#ifndef CSWARM_CC_DOMAIN_H_
#define CSWARM_CC_DOMAIN_H_

class Domain {
 public:
  Domain(double, double, int);
  ~Domain() { }
  
  double getLower() const;
  double getUpper() const;
  int getDim() const;
  int getSize() const;
  
 private:
  double lower;
  double upper;
  int dim;
};

#endif  // CSWARM_CC_DOMAIN_H_
