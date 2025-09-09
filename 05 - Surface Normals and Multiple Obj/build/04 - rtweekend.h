#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// std using
using std::make_shared;
using std::shared_ptr;

// remove redundancy

// const
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// util func
inline double degrees_to_radians(double degrees){
  return degrees * pi / 180.0;
}

// common headers
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "interval.h"

#endif // !RTWEEKEND_H
