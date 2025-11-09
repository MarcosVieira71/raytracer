#pragma once

#include "Hittable.h"
#include "utils.h"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const 
    {
        return false;
    }
};