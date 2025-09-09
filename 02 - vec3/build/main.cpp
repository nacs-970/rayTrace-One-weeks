#include <iostream>

#include "01 - vec3.h"
#include "02 -color.h"

int main () {

  // Img
  int width = 256;
  int height = 256;

  // Rendering
  std::cout << "P3\n" << width << " " << height << "\n255\n";
  for (int h = 0; h < height; h++) {
    std::clog << "\rScanelines remaining: "<< (height - h) << ' ' << std::flush;
    for (int w = 0; w < width; w++) {
      auto pixel_color = color(double(w)/(width-1), double(h)/(height-1), 0);
      write_color(std::cout, pixel_color);
    }
  }
  
  // result should be the same as 01 - ppm

  std::clog << "\rDone. \n"; // logging
}
