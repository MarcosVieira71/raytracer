#pragma once

#include "Interval.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include <iostream>
#include <limits>
#include <random>

using color = glm::vec3;
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.141592653;

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}



inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}


inline void write_color(std::ostream& out, const color& pixel) {
    
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(255.999 * intensity.clamp(linear_to_gamma(pixel.r)));
    int gbyte = int(255.999 * intensity.clamp(linear_to_gamma(pixel.g)));
    int bbyte = int(255.999 * intensity.clamp(linear_to_gamma(pixel.b)));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

inline float random_float() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}


inline float random_float(float min, float max) {
    return min + (max-min) * random_float();
}


inline glm::vec3 random_vec3() {
    return glm::vec3(random_float(), random_float(), random_float());
}

inline glm::vec3 random_vec3(float min, float max) {
    return glm::vec3(random_float(min,max), random_float(min,max), random_float(min,max));
}

inline glm::vec3  random_unit_vector() {
    while (true) {
        auto p = random_vec3(-1,1);
        auto lensq = glm::length2(p);
        if (lensq <= 1)
            return glm::normalize(p);
    }
}

inline glm::vec3 random_on_hemisphere(const glm::vec3& normal) {
    //Se o vetor gerado aleatriamente tem produto escalar > 0 com a normal da esfera
    //Está na mesma direcao (mesmo hemisferio)
    //Caso não esteja, preciasmos inverter ele
    glm::vec3 onSphereVec = random_unit_vector();
    if (glm::dot(onSphereVec, normal) > 0.0)
        return onSphereVec;
    else
        return -onSphereVec;
}

inline bool near_zero(const glm::vec3& v, float eps = 1e-8f) {
    return glm::all(glm::lessThan(glm::abs(v), glm::vec3(eps)));
}
