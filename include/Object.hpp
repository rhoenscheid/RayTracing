#pragma once 

#include "Ray.hpp"
#include <tuple>
#include "ImageUtils.hpp"
#include "Material.hpp"

struct HitInfo;

class Object
{
public:
    Object() {};
    virtual ~Object() {};

    virtual bool Intersect(Ray, HitInfo&, bool internal=false) = 0;

    Colour colour;
    Material material;
    bool isVolume = true;
protected:
    virtual void SetHitInfo(Ray ray, HitInfo &hit_info, double t, double t_exit) = 0;
};

struct HitInfo
{
    double t_entry;
    double t_exit;
    VecUtils::vec3 normal;
    VecUtils::vec3 position;
    VecUtils::vec3 exit_normal;
    VecUtils::vec3 ray_direction;
    Object *obj;
    bool hit = false;
};