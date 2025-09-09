#include <iostream>

/*
 * PPM: color store into text
 */

int main () {

  // Img
  int width = 256;
  int height = 256;

  // Rendering
  
  std::cout << "P3\n" << width << " " << height << "\n255\n";
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      auto r = double(w) / (width - 1); // 0 to 255 | black to red | left -> right
      auto g = double(h) / (height - 1); // 0 .. 255 | b to g | top -> bot
      auto b = 0; // pure black

      int ir = int(255.999 * r);
      int ig = int(255.999 * g);
      int ib = int(255.999 * b);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  std::clog << "\rDone. \n"; // logging
}
