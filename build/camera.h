#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "interval.h"
#include "hittable.h"
#include "material.h"

class camera{
  public:
    double aspect_ratio = 1.0; // width orver height
    int img_width = 100;
    int sample_per_pixel = 10; // random sample for each pixel
    int max_depth = 10; // max num of ray bounces into scene
    
    double vfov = 90; // Veritcal fov
    point3 lookfrom = point3(0, 0, 0); // point cam from
    point3 lookat = point3(0, 0, -1); // point cam to
    vec3 vup = vec3(0, 1, 0); // cam up direction

    double defocus_angle = 0;
    double focus_dist = 10;

    void render(const hittable& world){
      initialize();
      std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

      for(int h = 0; h < img_height; h++){
        std::clog << "\rScan lines remaining: " << (img_height - h) << ' ' << std::flush;
        for(int w = 0; w < img_width; w++){
          color pixel_color(0, 0, 0);
          for(int sample = 0; sample < sample_per_pixel; sample++){
            ray r = get_ray(w, h);
            pixel_color += ray_color(r, max_depth, world);
          }
          write_color(std::cout, pixel_sample_scale * pixel_color);
        }
      }
      std::clog << "\rDone.                                                   \n";
    }

  private:
    int img_height;
    double pixel_sample_scale; // color factor for sum pixel samples
    point3 center;
    point3 pixel100_loc; // location of pixel 0,0
    vec3 pixel_delta_u; // offset to right
    vec3 pixel_delta_v; // offset below
    vec3 u, v, w; // cam frame basis vectors
    vec3 defocus_disk_u; // horizontal disk radius
    vec3 defocus_disk_v; // vertical 

    void initialize(){
      img_height = int(img_width/aspect_ratio);
      img_height = (img_height<1) ? 1:img_height;

      pixel_sample_scale = 1.0 / sample_per_pixel;
      center = lookfrom;
      
      // Determine viewport dimension
      //auto focal_length = (lookfrom - lookat).length();
      auto theta = degrees_to_radians(vfov);
      auto h = std::tan(theta/2); // h = tan(zeta / 2)
      auto viewport_height = 2 * h * focus_dist;
      auto viewport_width = viewport_height * (double(img_width) / img_height);

      // Calculate u, v, w unit basis vector for cam coordinate frame.
      w = unit_vector(lookfrom - lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);

      // Calculate vector across horizontal and down vertical viewpoint edges
      vec3 viewport_u = viewport_width * u; // vector across horizontal edge
      vec3 viewport_v = viewport_height * -v; // across vertical

      // Calculate horizontal and vertical delta vectors from pixel to pixel
      pixel_delta_u = viewport_u / img_width;
      pixel_delta_v = viewport_v / img_height;

      // Calculate location of upper left pixel
      auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
      pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

      // Calculate cam defocus disk
      auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle/2));
      defocus_disk_u = u * defocus_radius;
      defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int w, int h) const{
        // Construct a camera ray originating from origin and randomly sampled
        // point around the pixel location w, h.
        auto offset = sample_square();
        auto pixel_sample = pixel100_loc + ((w + offset.x()) * pixel_delta_u) + ((h + offset.y()) * pixel_delta_v);
        auto ray_ori = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_dir = pixel_sample - ray_ori;

        return ray(ray_ori, ray_dir);
    }

    vec3 sample_square() const{
      // random vector in [-.5, -.5] [.5, .5] unit square
      return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 defocus_disk_sample() const{
      // random point in cam defocus disk
      auto p = random_in_unit_disk();
      return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const{

      // no more light is gathered
      if (depth <= 0)
        return color(0, 0, 0);

      hit_record rec;

      // remove shadow acne
      if(world.hit(r, interval(0.001, infinity), rec)){
        ray scattered;
        color attenuation;
        if(rec.mat->scatter(r, rec, attenuation, scattered))
          return attenuation * ray_color(scattered, depth-1, world);
        return color(0, 0, 0);
      }

      vec3 unit_dir = unit_vector(r.direction());
      auto a = 0.5*(unit_dir.y() + 1.0);
      return  (1.0-a)*color(1.0,1.0,1.0)+ a*color(0.5,0.7,1.0);
    }
};


#endif // !CAMERA_H
