#pragma once

#include <vector>

class PixelBuffer {
public:
    int width, height;
    std::vector<unsigned char> data;

    PixelBuffer(int w, int h)
        : width(w), height(h), data(w * h * 3, 0) {}

    inline unsigned char* pixel(int x, int y) {
        return &data[3 * (y * width + x)];
    }
};
