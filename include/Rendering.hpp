#pragma once 

#include "Object.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include <vector>
#include <array>
#include "ImageUtils.hpp"

using std::vector;
using namespace VecUtils;

struct SceneInfo
{
    vector<Object *> objects;
    vector<vec3> lights;
};

/**
 * @brief Calculates the outcome of a refraction at a boundary between two materials
 * 
 * @param incoming_dir 
 * @param normal normal to the boundary surface
 * @param n1 refractive index of origin material
 * @param n2 refractive index of exit material
 * @param position 
 * @param obj 
 * @return vec3 the direction of the refracted ray
 */
vec3 RefractedVector(vec3 incoming_dir, vec3 normal, double n1, double n2, vec3 position, Object* obj);

/**
 * @brief Get the colour of a ray by its interactions with objects
 * depth is tracked to avoid infinite recursions
 * @param ray 
 * @param scene 
 * @param depth 
 * @return Colour 
 */
Colour getRayColour(Ray ray, SceneInfo &scene, int depth=0);

/**
 * @brief Calculate the colour of an object surface
 * 
 * @param ray_origin 
 * @param scene 
 * @param hit_info 
 * @param depth 
 * @return vec3 Colour information
 */
vec3 Shading(vec3 ray_origin, SceneInfo &scene, HitInfo hit_info, int depth = 0);

/**
 * @brief Model rays transmitted through materials. Includes refractions and total internal reflection.
 * 
 * @param material 
 * @param hit_info 
 * @param transmitted_colour 
 * @param scene 
 * @param depth 
 * @param int_distance 
 * @param transmitted_fraction 
 */
void calculateTransmission(Material &material, HitInfo &hit_info, Colour &transmitted_colour, SceneInfo &scene, int depth, double &int_distance, double &transmitted_fraction);

/**
 * @brief Calculate contribution from rays reflected off of a material.
 * 
 * @param refl_strength 
 * @param hit_info 
 * @param reflected_colour 
 * @param scene 
 * @param depth 
 */
void calculateReflection(double refl_strength, HitInfo &hit_info, Colour &reflected_colour, SceneInfo &scene, int depth);

/**
 * @brief Crude approximation of shadows cast by objects between material and light source
 * 
 * @param scene 
 * @param hit_info 
 * @param light_to_obj 
 * @param shadow_multiplier 
 */
void calculateShadows(SceneInfo &scene, HitInfo &hit_info, const VecUtils::vec3 &light_to_obj, double &shadow_multiplier);