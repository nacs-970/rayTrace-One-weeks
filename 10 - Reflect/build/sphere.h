#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere: public hittable {
public:
  // fmax = float max
  sphere(const point3& center, double radius, shared_ptr<material> mat): center(center), radius(std::fmax(0, radius)), mat(mat) {
    // TODO
  }
  bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
    vec3 ori_pos = center - r.origin();
    auto a = r.direction().length_sqrt();
    auto h = dot(r.direction(), ori_pos);
    auto c = ori_pos.length_sqrt() - radius*radius;

    auto discriminant = h*h - a*c;

    if(discriminant < 0)
      return false;

    auto sqrtd = std::sqrt(discriminant);

    // FInd nearest root in acceptable range
    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)){
      root = (h + sqrtd) / a;
      if(!ray_t.surrounds(root))
        return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;
    return true;
  }

private:
  point3 center;
  double radius;
  shared_ptr<material> mat;
};


#endif // !SPHERE_H
