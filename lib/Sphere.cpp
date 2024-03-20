#include "Sphere.hpp"
#include <math.h>
#include <iostream> 

using namespace VecUtils;

bool Sphere::Intersect(Ray ray, HitInfo &hit_info, bool internal)
{
    // Solving quadratic equation for t parameter: at^2 + bt + c = 0
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(ray.direction, ray.origin - centre);
    double c = dot(centre, centre) + dot(ray.origin, ray.origin) - (2 * dot(centre, ray.origin)) - r*r;

    double discriminant = b*b - 4*a*c;
    if(discriminant > 0)  // two roots i.e. enter and exit 
    {
        double t1 = (-b + sqrt(discriminant)) / (2*a);
        double t2 = (-b - sqrt(discriminant)) / (2*a);
        double t_entry = std::min(t1, t2);
        double t_exit = std::max(t1, t2);
        if((t_entry > 0 && t_entry < hit_info.t_entry) || (internal))
        {   
            SetHitInfo(ray, hit_info, t_entry, t_exit);
            return (t_entry > 0);
        }
    }
    if(internal)
    {
        throw std::runtime_error("Internal with no soluation");
    }
    return false;
}

void Sphere::SetHitInfo(Ray ray, HitInfo &hit_info, double t_entry, double t_exit)
{
    hit_info.t_entry = t_entry;
    hit_info.t_exit = t_exit;
    hit_info.position = ray.origin + (ray.direction * t_entry);
    hit_info.ray_direction = ray.direction;
    hit_info.normal = norm(hit_info.position - centre);
    hit_info.exit_normal = norm(ray.origin + (ray.direction * t_exit) - centre);
    hit_info.obj = this;
    hit_info.hit = true;
}