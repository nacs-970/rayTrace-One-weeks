#ifndef MATERIAL_H
#define MATERIAL_H

#include "04 - vec3.h"
#include "color.h"
#include "02 - hittable.h"

// Produce a scattered ray (or say it absorbed the incident ray).
// If scattered, say how much the ray should be attenuated.

class material {
  public:
    virtual ~material() = default;
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const{
      return false;
    }
};

class lambertian : public material{
  public:
    lambertian(const color& albedo) : albedo(albedo) {} // albedo = whiteness in Latin
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
      auto scatter_dir = rec.normal + random_unit_vector();

      if(scatter_dir.near_zero())
        scatter_dir = rec.normal;

      scattered = ray(rec.p, scatter_dir);
      attenuation = albedo;
      return true;
    }
  private:
    color albedo;
};

class metal: public material{
  public:
    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1){}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
      vec3 reflected = reflect(r_in.direction(), rec.normal);
      reflected = unit_vector(reflected) + (fuzz * random_unit_vector()); // add fuzzy effect
      scattered = ray(rec.p, reflected);
      attenuation = albedo;
      return (dot(scattered.direction(), rec.normal) > 0);
    }

  private:
    color albedo;
    double fuzz;

};
#endif // !MATERIAL_H
