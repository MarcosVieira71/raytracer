#include "HittableContainer.h"

#include "Sphere.h"
#include "Camera.h"

#include <iostream>
#include <memory>



int main(void)
{
        

    HittableContainer world;

    world.add(std::make_shared<Sphere>(glm::vec3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(glm::vec3(0,-100.5,-1), 100));

    Camera cam;
    cam.render(world);

    return 0;
}