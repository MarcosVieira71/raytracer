#include "Camera.h"

#include "Ray.h"
#include "Hittable.h"
#include "Interval.h"

#include <iostream>

color Camera::ray_color(const Ray& r, const Hittable& world) const{
    HitRecord rec;
    if (world.hit(r, Interval(0, infinity), rec)) {
        return 0.5f * (rec.normal + color(1,1,1));
    }
    glm::vec3 direction = glm::normalize(r.direction());
    auto a = 0.5f * (direction.y + 1.0f); //normaliza y de -1, 1 para [0,1]
    return (1.0f-a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); //Faz a interpolacao linear
}

void Camera::initialize(){

    _pixel_samples_scale = 1.0 / _samples_per_pixel;

    _height = static_cast<int>(_width / _aspect_ratio);
    _height = (_height < 1) ? 1 : _height;

    auto focal_length = 1.0f;

    auto viewport_height = 2.0f;
    auto viewport_width = viewport_height * (_width / (float)_height);

    _center = glm::vec3(0, 0, 0);

    //vetores para representar as dimensões físicas do viewport
    auto viewport_vu = glm::vec3(viewport_width, 0, 0);
    auto viewport_vv = glm::vec3(0, -viewport_height, 0);

    //Representa o tamanho do pixel no espaco da viewport
    _pixel_delta_u = viewport_vu / static_cast<float>(_width);
    _pixel_delta_v = viewport_vv / static_cast<float>(_height);


    auto viewport_upper_left = _center - glm::vec3(0, 0, focal_length) - viewport_vu / 2.0f - viewport_vv / 2.0f;

    //// Centro do pixel (0,0) dentro do viewport (meio pixel para dentro)
    _pixel00_loc = viewport_upper_left + 0.5f * (_pixel_delta_u + _pixel_delta_v);

}

void Camera::render(const Hittable& world){
    initialize();
    std::cout << "P3\n" << _width << ' ' << _height << "\n255\n";

    for(int j = 0; j < _height; j++){
        std::clog << "\rScanlines remaining: " << (_height - j) << ' ' << std::flush;

        for(int i = 0; i < _width; i++){
            color pixel_color(0,0,0);
            for (int sample = 0; sample < _samples_per_pixel; sample++) {
                Ray r = getRay(i, j);
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, _pixel_samples_scale * pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}

Ray Camera::getRay(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = _pixel00_loc
                    + ((i + offset.x) * _pixel_delta_u)
                    + ((j + offset.y) * _pixel_delta_v);

    auto origin = _center;
    auto direction = pixel_sample - origin;

    return Ray(origin, direction);
}

glm::vec3 Camera::sample_square() const{
    // algo entre [-0.5, +0.5]
    return glm::vec3(random_float() - 0.5f, random_float() - 0.5f, 0);
}
