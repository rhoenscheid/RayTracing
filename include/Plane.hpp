#pragma once 

#include "Object.hpp"
#include "VectorUtils.hpp"

class Plane : public Object
{
    public:
    Plane(VecUtils::vec3 origin, VecUtils::vec3 normal, Colour col) : origin(origin), normal(normal) 
    {
        material.colour = col;
        isVolume = false;
    }

    bool Intersect(Ray, HitInfo &, bool internal=false);

    private:
    VecUtils::vec3 origin;
    VecUtils::vec3 normal;
    void SetHitInfo(Ray ray, HitInfo &hit_info, double t_entry, double t_exit);
};