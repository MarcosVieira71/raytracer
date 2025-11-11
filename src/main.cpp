#include "HittableContainer.h"

#include "Sphere.h"
#include "Camera.h"
#include "PixelBuffer.h"
#include "Metal.h"
#include "WindowSDL.h"
#include "Dielectric.h"
#include "Lambertian.h"

#include <iostream>
#include <memory>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>


int main(void)
{
        

    HittableContainer world;

    auto ground = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
    world.add(std::make_shared<Sphere>(glm::vec3(0.f,-1000.f,0.f), 1000, ground));


    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_float();
            glm::vec3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    auto albedo = random_vec3() * random_vec3();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    auto albedo = random_vec3(0.5f, 1.f);
                    auto fuzz = random_float(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0, material3));

    Camera cam;
    PixelBuffer buffer(cam.width(), cam.height());
    WindowSDL window(cam.width(), cam.height());

    cam.render(world, buffer, [&](int line) {
        window.update(buffer);  // desenha a textura
    });    
    stbi_write_jpg("../images/output.jpg", buffer.width, buffer.height, 3, buffer.data.data(), 100);

    return 0;
}