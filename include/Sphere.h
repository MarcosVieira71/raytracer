#pragma once

#include "Hittable.h"

class Ray;

class Sphere : public Hittable
{
    public:
        Sphere(const glm::vec3& center, float radius);

        bool hit(const Ray& r, const Interval& ray_t, 
                HitRecord& rec) const override;

        private:
            glm::vec3 _center;
            float _radius;

};