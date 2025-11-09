#include "color.h"
#include "Ray.h"
#include <iostream>

bool hit_sphere(const glm::vec3& center, double radius, const Ray& r) {
    glm::vec3 ocvec = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0f * dot(r.direction(), ocvec);
    auto c = dot(ocvec, ocvec) - radius*radius;
    auto delta = b*b - 4*a*c; 
    return (delta >= 0); //Delta < 0 -> Não intercepta a esfera, = 0 intercepta em 1 ponto, > 0 intercepta em dois pontos 
}

color ray_color(const Ray& r) {
    if (hit_sphere(glm::vec3(0,0,-1), 0.5f, r))
        return color(0.5f, 0.0f, 0.5f);
    glm::vec3 direction = glm::normalize(r.direction());
    auto a = 0.5f * (direction.y + 1.0f); //normaliza y de -1, 1 para [0,1]
    return (1.0f-a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); //Faz a interpolacao linear
}


int main(void)
{
        
    auto aspect_ratio = 16.0 / 9.0;
    int width = 400;

    int height = int(width / aspect_ratio);
    height = (height < 1) ? 1 : height;

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(width)/height);


    auto focal_length = 1.0;
    auto camera_center = glm::vec3(0, 0, 0);


    //vetores para representar as dimensões físicas do viewport
    auto viewport_vu = glm::vec3(viewport_width, 0, 0);
    auto viewport_vv = glm::vec3(0, -viewport_height, 0);

    //Representa o tamanho do pixel no espaco da viewport
    auto pixel_delta_u = viewport_vu / static_cast<float>(width);
    auto pixel_delta_v = viewport_vv / static_cast<float>(height);


    auto viewport_upper_left = camera_center
                             - glm::vec3(0, 0, focal_length) - viewport_vu / 2.0f - viewport_vv / 2.0f;

    //// Centro do pixel (0,0) dentro do viewport (meio pixel para dentro)

    auto pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);


    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for(int j = 0; j < height; j++){
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;

        for(int i = 0; i < width; i++){
            auto pixel_center = pixel00_loc + (static_cast<float>(i) * pixel_delta_u) + (static_cast<float>(j) * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            color pixel = ray_color(r);
            write_color(std::cout, pixel);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}