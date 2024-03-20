#pragma once
#include <array> 
#include <math.h>
#include <stdexcept>
#include <iostream> 

namespace VecUtils
{
    using vec3 = std::array<double, 3>;

    double dot(const vec3 &v1, const vec3 &v2);

    vec3 operator*(vec3 const& v, double x);

    vec3 operator+(vec3 const& v1, vec3 const &v2);

    vec3 operator-(vec3 const& v1, vec3 const &v2);

    vec3 norm(const vec3 &v);

    std::ostream& operator<<(std::ostream &os, const vec3 &v);
}