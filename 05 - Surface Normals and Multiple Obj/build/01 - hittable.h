#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "04 - rtweekend.h"

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;


    // Set hit rec normal vec
    void set_face_normal(const ray& r, const vec3& outwar_normal){
      front_face = dot(r.direction(), outwar_normal) < 0;
      normal = front_face? outwar_normal : -outwar_normal;
    }
};

class hittable{
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif // !HITTABLE_H
