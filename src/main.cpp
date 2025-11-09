#include "HittableContainer.h"

#include "Sphere.h"
#include "Camera.h"
#include "Metal.h"
#include "Lambertian.h"

#include <iostream>
#include <memory>



int main(void)
{
        

    HittableContainer world;

    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Metal>(color(0.8, 0.8, 0.8), 0.3f);
    auto material_right  = std::make_shared<Metal>(color(0.8, 0.8, 0.8), 1.0f);

    world.add(std::make_shared<Sphere>(glm::vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(glm::vec3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(std::make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(glm::vec3( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera cam;
    cam.render(world);

    return 0;
}