#include "Camera.h"

#include "Ray.h"
#include "Hittable.h"
#include "Interval.h"
#include "Material.h"
#include "PixelBuffer.h"

#include <iostream>
#include <vector>
#include <omp.h>


Camera::Camera(){
    initialize();
}

color Camera::ray_color(const Ray& r, int depth, const Hittable& world) const{
    if (depth <= 0)
        return color(0,0,0); 

    HitRecord rec;
    if (world.hit(r, Interval(0.001f, infinity), rec)) {
        Ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth-1, world);
        return color(0,0,0);
    }
    glm::vec3 direction = glm::normalize(r.direction());
    auto a = 0.5f * (direction.y + 1.0f); //normaliza y de -1, 1 para [0,1]
    return (1.0f-a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); //Faz a interpolacao linear
}

void Camera::initialize(){

    _pixel_samples_scale = 1.0 / _samples_per_pixel;

    _height = static_cast<int>(_width / _aspect_ratio);
    _height = (_height < 1) ? 1 : _height;

    auto theta = degrees_to_radians(_vfov);
    auto h = std::tan(theta/2);

    auto viewport_height = 2 * h * _focus_dist;

    auto viewport_width = viewport_height * (_width / (float)_height);

    _center = _lookfrom;

    _w = glm::normalize(_lookfrom - _lookat);
    _u = glm::normalize(glm::cross(_vup, _w));
    _v = glm::cross(_w, _u);

    //vetores para representar as dimensões físicas do viewport
    glm::vec3 viewport_vu = viewport_width * _u;    
    glm::vec3 viewport_vv = viewport_height * - _v; 
    //Representa o tamanho do pixel no espaco da viewport
    _pixel_delta_u = viewport_vu / static_cast<float>(_width);
    _pixel_delta_v = viewport_vv / static_cast<float>(_height);


    auto viewport_upper_left = _center - (_focus_dist * _w) - viewport_vu/ 2.0f - viewport_vv/2.0f;

    //// Centro do pixel (0,0) dentro do viewport (meio pixel para dentro)
    _pixel00_loc = viewport_upper_left + 0.5f * (_pixel_delta_u + _pixel_delta_v);

    auto defocus_radius = _focus_dist * std::tan(degrees_to_radians(_defocus_angle / 2));
    _defocus_disk_u = _u * defocus_radius;
    _defocus_disk_v = _v * defocus_radius;
}

void Camera::render(const Hittable& world,
                    PixelBuffer& buffer)
{
    #pragma omp parallel
    {
        #pragma omp single
        std::cout << "OpenMP threads: "
                  << omp_get_num_threads()
                  << std::endl;
    }

    #pragma omp parallel for schedule(dynamic, 1)
    for (int j = 0; j < _height; j++) {
        for (int i = 0; i < _width; i++) {
            color pixel_color(0,0,0);

            for (int s = 0; s < _samples_per_pixel; s++) {
                Ray r = getRay(i, j);
                pixel_color += ray_color(r, _max_depth, world);
            }

            write_color(buffer.pixel(i, j),
                        _pixel_samples_scale * pixel_color);
        }
    }
}

Ray Camera::getRay(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = _pixel00_loc
                    + ((i + offset.x) * _pixel_delta_u)
                    + ((j + offset.y) * _pixel_delta_v);

    auto origin = _center;
    auto direction = pixel_sample - origin;
    auto ray_origin = (_defocus_angle <= 0) ? _center : defocus_disk_sample();

    return Ray(origin, direction);
}

glm::vec3 Camera::sample_square() const{
    // algo entre [-0.5, +0.5]
    return glm::vec3(random_float() - 0.5f, random_float() - 0.5f, 0);
}

glm::vec3 Camera::defocus_disk_sample() const {
    auto p = random_in_unit_disk();
    return _center + (p[0] * _defocus_disk_u) + (p[1] * _defocus_disk_v);
}

int Camera::width(){
    return _width;
}
int Camera::height(){
    return _height;
}