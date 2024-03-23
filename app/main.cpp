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
#include <mpi.h>

using namespace::VecUtils;

/**
 * @brief Fills an image array by calculating the colour of one ray per pixel.
 * Modify to add anti-aliasing by calculating multiple rays per pixel. 
 * @param image 
 * @param scene 
 */
void RenderScene(Image &image, SceneInfo &scene)
{
    // These can be left as defaults
    double frustum_halfwidth = 1.5;
    double frustum_halfheight = (double)image.n_cols / (double)image.n_rows * frustum_halfwidth;
    double frustum_distance = -1; // distance from camera to drawing plane
    vec3 camera_position = {0, 0, 10};

    // Iterate over pixels to generate the image
    for(uint y = 0; y < image.n_rows; y++)
    {
        for(uint x = 0; x < image.n_cols; x++)
        {
            double x_dir = ((double) x / (double) image.n_cols * frustum_halfwidth * 2) - frustum_halfwidth;
            double y_dir = ((double) (image.n_rows - y) / (double) image.n_rows * frustum_halfheight * 2) - frustum_halfheight;
            vec3 direction = norm({x_dir, y_dir, frustum_distance});
            Colour pixel_colour;
            Ray camera_ray(camera_position, direction);
            image.image_data[y][x] = getRayColour(camera_ray, scene);
        }
    }
}

int main()
{
    // create a translucent, refractive sphere
    Sphere sphere(1, {-0.5, -0.5, 4}, Colour({255,0,255}));
    sphere.material.refractive_index = 1.5;
    sphere.material.opacity = 0.1;
    sphere.material.specular_power = 10;
    sphere.material.specular_intensity = 4;

    // create a reflective sphere
    Sphere sphere2(4, {3, 0,-3}, Colour({0, 255, 0}));
    sphere2.material.reflection_strength = 0.3;

    // create a solid red sphere
    Sphere sphere3(1, {-2, 0.5, 0}, Colour({255, 0, 0}));

    // create a "room" with mirrored walls
    Plane floor({0.0, -5, 0.0}, {0.0, 1.0, 0.0}, Colour({0, 0, 255}));
    Plane wall1({0.0, 0, -20.0}, norm({1, 0, 1}), Colour({0,255,255}));
    Plane wall2({0.0, 0, -20.0}, norm({-1, 0, 1}), Colour({0,255,255}));
    wall1.material.reflection_strength = .9;
    wall2.material.reflection_strength = .9;
    
    // create a simple light; we don't cover different kinds of light in this
    vec3 light_position = {3, 10, 2};
    
    // add all of these into a single scene
    // a scene is a vector<Object *> and a vector<vec3> of lighting directions
    SceneInfo scene;
    scene.objects.push_back(&sphere);
    scene.objects.push_back(&sphere2);
    scene.objects.push_back(&sphere3);
    scene.objects.push_back(&floor);
    scene.objects.push_back(&wall1);
    scene.objects.push_back(&wall2);
    scene.lights.push_back(light_position);

    // Define an image and render the scene
    Image sphereImage(1000,1000);
    RenderScene(sphereImage, scene);
    SaveToFile(sphereImage.image_data, "SphereRender.pbm");

    return 0;
}