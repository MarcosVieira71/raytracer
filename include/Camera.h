#pragma once

#include <glm/glm.hpp>
#include "utils.h"

class Hittable;
class Ray;


class Camera {
  public:
        double _aspect_ratio = 16.0f/9.0f;  
        int _width  = 400; // largura da imagem a ser renderizada
        int _samples_per_pixel = 10;  


    void render(const Hittable& world);

  private:
        float _pixel_samples_scale;  // Color scale factor for a sum of pixel samples

        int _height;   // altura da imagem a ser renderizada
        glm::vec3 _center;         
        glm::vec3 _pixel00_loc;    // localizacao  de pixel 0,0

        //Representa o tamanho do pixel no espaco da viewport
        glm::vec3 _pixel_delta_u; //horizontal
        glm::vec3 _pixel_delta_v; //vertical

    void initialize();

    color ray_color(const Ray& r, const Hittable& world) const;

    Ray getRay(int i, int j) const;

    glm::vec3 sample_square() const;
};

