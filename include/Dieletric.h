#pragma once

#include "Material.h"

class Dieletric : public Material
{
    public:
        Dieletric(float refraction_index);

        bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;

    private:
        float _refraction_index;

        static float reflectance(float cosine, float refraction_index);
};