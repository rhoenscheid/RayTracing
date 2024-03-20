#pragma once 
#include <array>
#include <VectorUtils.hpp>

class Ray
{
    public:
    Ray(VecUtils::vec3 origin, VecUtils::vec3 direction) : origin(origin), direction(direction) {}
    Ray()
    {
        origin = {0, 0, 0};
        direction = {0, 0, 0};
    }

    VecUtils::vec3 origin;
    VecUtils::vec3 direction;
};
