#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <limits>

// std using
using std::make_shared;
using std::shared_ptr;

// remove redundancy

// const
const double pi = 3.1415926535897932385;
const double infinity = std::numeric_limits<double>::infinity();

// util func
inline double degrees_to_radians(double degrees){
  return degrees * pi / 180.0;
}

inline double random_double(){
  // [0, 1)
  return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max){
  // return a random real in [min, max)
  return min + (max-min)*random_double();
}

// common headers
//#include "vec3.h"
//#include "color.h"
//#include "ray.h"
//#include "interval.h"

#endif // !RTWEEKEND_H
