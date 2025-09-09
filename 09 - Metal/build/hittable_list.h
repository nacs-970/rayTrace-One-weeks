#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "02 - hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable{
  public:
    std::vector<shared_ptr<hittable>> objs;
    hittable_list() {}
    hittable_list(shared_ptr<hittable> obj) { add(obj); }
    void clear() {objs.clear();}
    void add(shared_ptr<hittable> obj){
      objs.push_back(obj);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
      hit_record temp_rec;
      bool hit_any = false;
      auto closest_so_far = ray_t.max;

      for(const auto& obj: objs){
        if(obj->hit(r, interval(ray_t.min, closest_so_far), temp_rec)){
          hit_any = true;
          closest_so_far = temp_rec.t;
          rec = temp_rec;
        }
      }

    return hit_any;
  }

};

#endif // !HITTABLE_LIST_H
