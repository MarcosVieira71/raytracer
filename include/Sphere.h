#pragma once

#include "Hittable.h"

class Ray;
class Material;

class Sphere : public Hittable
{
    public:
        Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> mat);

        bool hit(const Ray& r, const Interval& ray_t, 
                HitRecord& rec) const override;

        private:
            std::shared_ptr<Material> _material;
            glm::vec3 _center;
            float _radius;

};