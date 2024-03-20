#include "Object.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include <vector>
#include <array>
#include <fstream>
#include "ImageUtils.hpp"
#include <algorithm>
#include <iostream> 
#include "Rendering.hpp"
#include <stdexcept>

vec3 RefractedVector(vec3 incoming_dir, vec3 normal, double n1, double n2, vec3 position, Object* obj)
{
    incoming_dir = norm(incoming_dir);
    vec3 parallel = normal * dot(incoming_dir, normal);
    vec3 perp = incoming_dir - parallel;
    if (dot(perp, perp) > 0)
    {
        double sin1 = sqrt(dot(perp, perp));
        double sin2 = sin1 * n1 / n2;
        if(abs(sin2) > 1)
        {
            // Total internal reflection
            vec3 reflection = incoming_dir - normal * 2 * (dot(incoming_dir, normal));
            HitInfo secondary_hit;
            if(obj->Intersect(Ray(position + reflection * 0.0001, reflection), secondary_hit, true))
            {
                throw std::runtime_error("Total internal reflection failed");
            }
            vec3 next_pos = (position + reflection * 0.0001) + reflection * secondary_hit.t_exit;
            return RefractedVector(reflection, secondary_hit.normal, n1, n2, next_pos, obj);
            return norm(perp);
        }
        double cos2 = sqrt(1 - sin2 * sin2);
        auto new_parallel = dot(parallel, parallel) > 0 ? norm(parallel) * cos2 : vec3({0,0,0});
        auto new_perp = (norm(perp) * sin2);
        return new_parallel + new_perp;
    }
    else
    {
        return incoming_dir;
    }
}

vec3 Shading(vec3 ray_origin, SceneInfo &scene, HitInfo hit_info, int depth)
{
    Material &material = hit_info.obj->material;
    vec3 light_to_obj = norm(scene.lights[0] - hit_info.position);
    double ambient_strength = 0.3;

    // Diffuse term
    double diffuse_strength = std::max(dot(hit_info.normal, light_to_obj), 0.0);

    // Specular term
    vec3 reflection = hit_info.normal * (2 * diffuse_strength) - light_to_obj;
    double specular_strength =
        dot(ray_origin - hit_info.position, ray_origin - hit_info.position) > 0 ? std::pow(std::max(dot(reflection, norm(ray_origin - hit_info.position)), 0.0), material.specular_power) : 0;

    double shadow_multiplier = 1.0;
    calculateShadows(scene, hit_info, light_to_obj, shadow_multiplier);

    // Transparency term 
    // Calculates new rays 
    double refr_strength = 0.3;
    Colour transmitted_colour = {0,0,0};
    double int_distance = 0.0;
    double transmitted_fraction = 0.0;
    calculateTransmission(material, hit_info, transmitted_colour, scene, depth, int_distance, transmitted_fraction);

    // Reflective Term, also requires new rays
    double refl_strength = material.reflection_strength;
    Colour reflected_colour = {0,0,0};
    calculateReflection(refl_strength, hit_info, reflected_colour, scene, depth);
    Colour surface_colour =  (material.colour * diffuse_strength + Colour({255, 255, 255}) * specular_strength * material.specular_intensity) * shadow_multiplier + material.colour * ambient_strength;
    Colour interior_colour = transmitted_colour * transmitted_fraction + material.colour * (1-transmitted_fraction);
    return reflected_colour * refl_strength + interior_colour*(1-material.opacity) + surface_colour * (material.opacity-refl_strength);
}

void calculateShadows(SceneInfo &scene, HitInfo &hit_info, const VecUtils::vec3 &light_to_obj, double &shadow_multiplier)
{
    HitInfo shadow_hit_info;
    double t_light = sqrt(dot(scene.lights[0] - hit_info.position, scene.lights[0] - hit_info.position));
    shadow_hit_info.t_entry = t_light;
    for (auto &&obj : scene.objects)
    {
        if (obj != hit_info.obj)
        {
            obj->Intersect(Ray(hit_info.position, light_to_obj), shadow_hit_info);
        }
    }
    if (shadow_hit_info.hit)
    {
        shadow_multiplier = 1 - shadow_hit_info.obj->material.opacity;
    }
}

void calculateReflection(double refl_strength, HitInfo &hit_info, Colour &reflected_colour, SceneInfo &scene, int depth)
{
    if (refl_strength > 0)
    {
        vec3 reflected_dir = hit_info.ray_direction - hit_info.normal * 2 * dot(hit_info.ray_direction, hit_info.normal);
        reflected_colour = getRayColour(Ray(hit_info.position + reflected_dir * 0.001, reflected_dir), scene, depth + 1);
    }
}

void calculateTransmission(Material &material, HitInfo &hit_info, Colour &transmitted_colour, SceneInfo &scene, int depth, double &int_distance, double &transmitted_fraction)
{
    if (material.opacity < 1 && hit_info.obj->isVolume)
    {
        if (material.refractive_index != 1)
        {
            vec3 int_ray_dir = (RefractedVector(hit_info.ray_direction, hit_info.normal, 1.0, material.refractive_index, hit_info.position, hit_info.obj));
            HitInfo secondary_hit;
            hit_info.obj->Intersect(Ray(hit_info.position, int_ray_dir), secondary_hit, true);
            vec3 exit = (hit_info.position) + int_ray_dir * secondary_hit.t_exit;
            vec3 ext_ray_dir = (RefractedVector(int_ray_dir, secondary_hit.exit_normal, material.refractive_index, 1.0, exit, hit_info.obj));
            transmitted_colour = getRayColour(Ray(exit, ext_ray_dir), scene, depth + 1);
            int_distance = sqrt(dot(exit - hit_info.position, exit - hit_info.position));
        }
        else
        {
            vec3 exit = hit_info.position + hit_info.ray_direction * (hit_info.t_exit - hit_info.t_entry);
            transmitted_colour = getRayColour(Ray(exit + hit_info.ray_direction * 0.001, hit_info.ray_direction), scene, depth + 1);
            int_distance = sqrt(dot(exit - hit_info.position, exit - hit_info.position));
        }
        transmitted_fraction = exp(-int_distance * material.absorbtion);
    }
}

Colour getRayColour(Ray ray, SceneInfo &scene, int depth)
{
    // for the avoidance of infinite loops due to reflections
    if(depth > 10)
    {
        return Colour({0,0,0});
    }
    HitInfo hit_info;
    hit_info.t_entry = __DBL_MAX__;
    for(auto object : scene.objects)
    {
        object->Intersect(ray, hit_info);
    }
    if(hit_info.hit)
    {
        return Shading(ray.origin, scene, hit_info);
    }
    else
    {
        return Colour({0,0,0});
    }
}
