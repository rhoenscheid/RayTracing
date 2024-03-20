#include "VectorUtils.hpp"

namespace VecUtils
{
    double dot(const vec3 &v1, const vec3 &v2)
    {
        return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
    }

    vec3 operator*(vec3 const& v, double x)
    {
        vec3 v_new = {v[0] * x, v[1] * x, v[2] * x};
        return v_new;
    }

    vec3 operator+(vec3 const& v1, vec3 const &v2)
    {
        return {v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]};
    }

    vec3 operator-(vec3 const& v1, vec3 const &v2)
    {
        return {v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]};
    }

    vec3 norm(const vec3 &v)
    {
        double magnitude = sqrt(dot(v, v));
        if(magnitude == 0)
        {
            throw std::runtime_error("Attempt to normalise zero vector.");
        }
        return {v[0]/magnitude, v[1]/magnitude, v[2]/magnitude};
    }

    std::ostream& operator<<(std::ostream &os, const vec3 &v)
    {
        os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
        return os;
    }
}