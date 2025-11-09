#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

class HitRecord
{
    public: 
        glm::vec3 p;
        glm::vec3 normal;
        float t;
};

class Hittable
{
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& r, float ray_tMin,
                        float ray_tMax, HitRecord& rec) const = 0;
};