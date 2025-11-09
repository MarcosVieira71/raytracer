#pragma once

#include <glm/glm.hpp>
#include <iostream>

using color = glm::vec3;

void write_color(std::ostream& out, const color& pixel) {
    
    int rbyte = int(255.999 * pixel.r);
    int gbyte = int(255.999 * pixel.g);
    int bbyte = int(255.999 * pixel.b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
