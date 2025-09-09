#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera{
  public:
    double aspect_ratio = 1.0; // width orver height
    int img_width = 100;

    void render(const hittable& world){
      initialize();
      std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";
      for(int h = 0; h < img_height; h++){
        std::clog << "\rScanlines remaining: " << (img_height - h) << ' ' << std::flush;
        for(int w = 0; w < img_width; w++){
          auto pixel_center = pixel100_loc + (w * pixel_delta_u) + (h * pixel_delta_v);
          auto ray_dir = pixel_center - center;
          ray r(center, ray_dir);
          color pixel_color = ray_color(r, world);
          write_color(std::cout, pixel_color);
        }
      }
      std::clog << "\rDone.                                                   \n";
    }

  private:
    int img_height;
    point3 center;
    point3 pixel100_loc; // location of pixel 0,0
    vec3 pixel_delta_u; // offset to right
    vec3 pixel_delta_v; // offset below

    void initialize(){
      img_height = int(img_width/aspect_ratio);
      img_height = (img_height<1)?1:img_height;
      center = point3(0,0,0);
      
      // Determine viewport dimension
      auto focal_length = 1.0;
      auto viewport_height = 2.0;
      auto viewport_width = viewport_height * (double(img_width) / img_height);

      // Calculate vector across horizontal and down vertical viewpoint edges
      auto viewport_u = vec3(viewport_width, 0, 0);
      auto viewport_v = vec3(0, -viewport_height, 0);

      // Calculate horizontal and vertical delta vectors from pixel to pixel
      pixel_delta_u = viewport_u / img_width;
      pixel_delta_v = viewport_v / img_height;

      // Calculate location of upper left pixel
      auto viewport_upper_left = center - vec3(0 ,0, focal_length) - viewport_u/2 - viewport_v/2;
      pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, const hittable& world) const{
      hit_record rec;
      if(world.hit(r, interval(0, infinity), rec)){
        return 0.5 * (rec.normal + color(1,1,1));
      }

      vec3 unit_dir = unit_vector(r.direction());
      auto a = 0.5*(unit_dir.y() + 1.0);
      return  (1.0-a)*color(1.0,1.0,1.0)+ a*color(0.5,0.7,1.0);
    }
};


#endif // !CAMERA_H
