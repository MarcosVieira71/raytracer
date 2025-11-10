#include "HittableContainer.h"

#include "Sphere.h"
#include "Camera.h"
#include "Metal.h"
#include "Dieletric.h"
#include "Lambertian.h"

#include <iostream>
#include <memory>



int main(void)
{
        

    HittableContainer world;

    auto material_ground = std::make_shared<Lambertian>(color(0.8f, 0.8f, 0.0f));
    auto material_center = std::make_shared<Lambertian>(color(0.1f, 0.2f, 0.5f));
    auto material_left   = std::make_shared<Dieletric>(1.50f);
    auto material_bubble = std::make_shared<Dieletric>(1.00f / 1.50f);
    auto material_right  = std::make_shared<Metal>(color(0.8f, 0.6f, 0.2f), 1.0f);

    world.add(std::make_shared<Sphere>(glm::vec3( 0.0f, -100.5f, -1.0f), 100.0f, material_ground));
    world.add(std::make_shared<Sphere>(glm::vec3( 0.0f,    0.0f, -1.2f),   0.5f, material_center));
    world.add(std::make_shared<Sphere>(glm::vec3(-1.0f,    0.0f, -1.0f),   0.5f, material_left));
    world.add(std::make_shared<Sphere>(glm::vec3(-1.0f,    0.0f, -1.0f),   0.4f, material_bubble));
    world.add(std::make_shared<Sphere>(glm::vec3( 1.0f,    0.0f, -1.0f),   0.5f, material_right));


    Camera cam;
    cam.render(world);

    return 0;
}