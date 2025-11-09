#pragma once

#include "Hittable.h"

class Ray;

class Sphere : public Hittable
{
    public:
        Sphere(const glm::vec3& center, float radius);

        bool hit(const Ray& r, float ray_tMin, float ray_tMax, 
                HitRecord& rec) const override;

        private:
            glm::vec3 _center;
            float _radius;

};