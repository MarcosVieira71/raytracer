#include "color.h"

#include <iostream>

int main(void)
{
    int width = 256;
    int height = 256;

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for(int j = 0; j < width; j++){
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;

        for(int i = 0; i < height; i++){
            auto pixel = color(double(i) / (width-1), double(j) / (height-1), 0.0);
            write_color(std::cout, pixel);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}