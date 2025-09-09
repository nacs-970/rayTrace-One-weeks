#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color){
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // turn [0,1] into range of [0, 255]
  int rByte = int(255.999 * r);
  int gByte = int(255.999 * g);
  int bByte = int(255.999 * b);

  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif // !COLOR_H
