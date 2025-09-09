#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "vec3.h"
#include "interval.h"

using color = vec3;
inline double linear_to_gamma(double linear_componet){
  if(linear_componet > 0)
    return std::sqrt(linear_componet);
  return 0;
}

void write_color(std::ostream& out, const color& pixel_color){
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // applay gamma transform
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  // turn [0,1] into range of [0, 255]
  static const interval intensity(0.000, 0.999);

  // select random sample
  int rByte = int(256 * intensity.clamp(r));
  int gByte = int(256 * intensity.clamp(g));
  int bByte = int(256 * intensity.clamp(b));
  //int rByte = int(255 * r);
  //int gByte = int(255 * g);
  //int bByte = int(255 * b);

  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif // !COLOR_H
