#pragma once

#include <glm/glm.hpp>
#include "utils.h"

class Hittable;
class Ray;


class Camera {
  public:
    void render(const Hittable& world);

  private:

        double _aspect_ratio = 16.0f/9.0f;  
        int _width  = 400; // largura da imagem a ser renderizada
        int _samples_per_pixel = 100;  
        int _max_depth = 100;   // numero maximo de raios bouncing na cena
        float _vfov = 90;

        glm::vec3 _lookfrom = glm::vec3(-2,2,1);
        glm::vec3 _lookat = glm::vec3(0,0,-1);  
        glm::vec3 _vup = glm::vec3(0,1,0);     

        float _pixel_samples_scale;  // Color scale factor for a sum of pixel samples

        int _height;   // altura da imagem a ser renderizada
        glm::vec3 _center;         
        glm::vec3 _pixel00_loc;    // localizacao  de pixel 0,0

        //Representa o tamanho do pixel no espaco da viewport
        glm::vec3 _pixel_delta_u; //horizontal
        glm::vec3 _pixel_delta_v; //vertical

        glm::vec3 _u, _v, _w; 


    void initialize();

    color ray_color(const Ray& r, int depth, const Hittable& world) const;

    Ray getRay(int i, int j) const;

    glm::vec3 sample_square() const;
};

