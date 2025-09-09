#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color){
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

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
