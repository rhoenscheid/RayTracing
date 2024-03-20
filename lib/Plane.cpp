#include "Plane.hpp"

using namespace VecUtils;

bool Plane::Intersect(Ray ray, HitInfo &hit_info, bool internal)
{
    double denominator = dot(ray.direction, normal);
    if (denominator != 0)
    {
        double t = dot(origin - ray.origin, normal) / denominator;
        if (t < hit_info.t_entry && t > 0)
        {
            SetHitInfo(ray, hit_info, t, t);
            return true;
        }
    }
    return false;
}

void Plane::SetHitInfo(Ray ray, HitInfo &hit_info, double t_entry, double t_exit)
{
    hit_info.t_entry = t_entry;
    hit_info.t_exit = t_exit;
    hit_info.ray_direction = ray.direction;
    hit_info.position = ray.origin + (ray.direction * t_entry);
    hit_info.normal = normal;
    hit_info.exit_normal = normal * -1;
    hit_info.obj = this;
    hit_info.hit = true;
}
