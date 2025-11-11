#pragma once

#include <glm/glm.hpp>
#include "utils.h"
#include <functional>

class Hittable;
class Ray;
class PixelBuffer;


class Camera {
  public:
    Camera();

    void render(const Hittable& world, PixelBuffer& buffer, std::function<void(int)> updateCallback);
    int width();
    int height();

  private:

        float _aspect_ratio = 16.0f/9.0f;  
        int _width  = 1200; // largura da imagem a ser renderizada
        int _samples_per_pixel = 500;  
        int _max_depth = 50;   // numero maximo de raios bouncing na cena
        
        float _vfov = 20.0f;
        float _defocus_angle = 0.6f;  // angulo da variacao de raios em cada pixel
        float _focus_dist = 10.0f;    // distancia de ponto lookfrom

        glm::vec3 _lookfrom = glm::vec3(13.f,2.f,3.f);
        glm::vec3 _lookat = glm::vec3(0.f,0.f,0.f);  
        glm::vec3 _vup = glm::vec3(0.f,1.f,0.f);     

        float _pixel_samples_scale;

        int _height;   // altura da imagem a ser renderizada
        glm::vec3 _center;         
        glm::vec3 _pixel00_loc;    // localizacao  de pixel 0,0

        //Representa o tamanho do pixel no espaco da viewport
        glm::vec3 _pixel_delta_u; //horizontal
        glm::vec3 _pixel_delta_v; //vertical

        glm::vec3 _u, _v, _w; 

        // Defocus disck raio
        glm::vec3 _defocus_disk_u; //Horizontal 
        glm::vec3 _defocus_disk_v; //Vertical


    void initialize();

    color ray_color(const Ray& r, int depth, const Hittable& world) const;

    Ray getRay(int i, int j) const;

    glm::vec3 sample_square() const;

    glm::vec3 defocus_disk_sample() const;
};

