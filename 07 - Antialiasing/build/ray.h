#ifndef RAY_H
#define RAY_H
#include "vec3.h"

/*  one thing that all ray tracers have is a ray class and computation of color (along a ray)
 *  P(t) = A + tb
 *  P: 3d position along a line
 *  A: ray origin
 *  b: ray direction
 *  t: parameter, real numberA
 *  t=  -1    0    1
 *  < -- | -- | -- | -- >
 *       A--->b
 */ 

class ray {
  public:
    ray(){}
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction){}
  
    const point3& origin() const {return orig;}
    const vec3& direction() const {return dir;}
 
    // P(t)
    point3 at(double t) const{
      return orig + t*dir;
    }

  private:
    point3 orig;
    vec3 dir;

};

#endif // RAY_H
