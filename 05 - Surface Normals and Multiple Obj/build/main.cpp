#include "04 - rtweekend.h"
#include "01 - hittable.h"
#include "02 - hittable_list.h"
#include "03 - sphere.h"

// return color of given scene ray
color ray_color(const ray& r, const hittable& world){
  hit_record rec;

  if(world.hit(r, interval(0, infinity), rec)){
    return 0.5 * (rec.normal + color(1,1,1));
  }

  vec3 unit_dir = unit_vector(r.direction());
  auto a  =  0.5*(unit_dir.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main () {

  // Img
  auto aspect_ratio = 16.0 / 9.0; // ideal ratio
  int width = 400;

  int height = int(width / aspect_ratio);
  height = (height < 1) ? 1: height; // ensure that image height is at least 1
 
  // world
  hittable_list world;
  world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

  // Camre ray
  auto focal_length = 1.0; // fixed length for camera and viewport
  auto camera_center = point3(0, 0, 0);

  // Viewport, width less that one are ok
  auto viewport_height = 2.0;
  auto Viewport_width = viewport_height * (double(width) / height);

  // Calculate vector across horizontal and down vertical viewpoint edges
  auto viewport_u = vec3(Viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  // Calculate horizontal and vertical delta vectors from pixel to pixel
  auto pixel_delta_u = viewport_u / width;
  auto pixel_delta_v = viewport_v / height;

  // Calculate location of upper left pixel
  auto viewport_upper_left = camera_center - vec3(0 ,0, focal_length) - viewport_u/2 - viewport_v/2;
  auto pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


  // Rendering out as ppm
  std::cout << "P3\n" << width << " " << height << "\n255\n";

  for (int h = 0; h < height; h++) {

    std::clog << "\rScanelines remaining: "<< (height - h) << ' ' << std::flush;

    for (int w = 0; w < width; w++) {

      auto pixel_center = pixel100_loc + (w *pixel_delta_u) + (h * pixel_delta_v);
      auto ray_dir = pixel_center -camera_center;
      ray r(camera_center, ray_dir);

      color pixel_color = ray_color(r, world);
      write_color(std::cout, pixel_color);

    }
  }

  std::clog << "\rDone. \n"; // logging
}
