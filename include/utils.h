#pragma once

#include "Interval.h"

#include <glm/glm.hpp>
#include <iostream>

#include <limits>
#include <random>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.141592653;

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}


using color = glm::vec3;

inline void write_color(std::ostream& out, const color& pixel) {
    
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(255.999 * intensity.clamp(pixel.r));
    int gbyte = int(255.999 * intensity.clamp(pixel.g));
    int bbyte = int(255.999 * intensity.clamp(pixel.b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

inline float random_float() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}