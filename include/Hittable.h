#pragma once

#include <glm/glm.hpp>

#include "Ray.h"
#include "Interval.h"
#include <memory>

class Material;

class HitRecord
{
    public: 
        glm::vec3 p;
        glm::vec3 normal;
        float t;
        bool isFrontFace;
        std::shared_ptr<Material> mat;
    
    void setFaceNormal(const Ray&  r, const glm::vec3& outwardNormal)
    {
        isFrontFace = glm::dot(r.direction(), outwardNormal) < 0;
        normal = isFrontFace ? outwardNormal : -outwardNormal;
    }
    
};

class Hittable
{
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& r, const Interval& ray_t, HitRecord& rec) const = 0;
};