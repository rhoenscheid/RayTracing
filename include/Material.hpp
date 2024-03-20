#pragma once
#include "ImageUtils.hpp"


class Material
{
    public:
    Material() {}
    Material(Colour col) : colour(col){}

    Colour colour = {255, 255, 255};
    double refractive_index = 1.0;
    double opacity = 1.0;
    double reflection_strength = 0.0;
    double specular_power = 4.0;
    double specular_intensity = 1.0;
    double absorbtion = 0.0;
};