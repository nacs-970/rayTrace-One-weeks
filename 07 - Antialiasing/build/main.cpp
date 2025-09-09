#include "01 - rtweekend.h"
#include "04 - camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main () {
  // world
  hittable_list world;
  world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

  camera cam;
  cam.aspect_ratio = 16.0/9.0;
  cam.img_width = 400;
  cam.sample_per_pixel = 100;

  cam.render(world);
}
