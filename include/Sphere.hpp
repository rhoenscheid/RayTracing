#pragma once

#include "Object.hpp"
#include "VectorUtils.hpp"

class Sphere : public Object
{
    public:
    Sphere(double radius, VecUtils::vec3 position) : r(radius), centre(position)
    {
    }
    Sphere(double radius, VecUtils::vec3 position, Colour col) : r(radius), centre(position)
    {
        material.colour = col;
    }
    Sphere(double radius, VecUtils::vec3 position, Material mat) : r(radius), centre(position)
    {
        material = mat;
    }

    bool Intersect(Ray ray, HitInfo &hit_info, bool internal=false);

    private:
    double r;
    VecUtils::vec3 centre;
    void SetHitInfo(Ray ray, HitInfo &hit_info, double t_entry, double t_exit);
    double n_refr = 1.5;
};