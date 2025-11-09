
#include "Sphere.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>


Sphere::Sphere(const glm::vec3& center, float radius) : _center(center), _radius(std::fmax(0,radius))
{}


bool Sphere::hit(const Ray& r, const Interval& ray_t, HitRecord& rec) const
{
    glm::vec3 ocvec = _center - r.origin();
    auto a = glm::length2(r.direction());
    auto h = glm::dot(r.direction(), ocvec);
    auto c = glm::length2(ocvec) - _radius * _radius;
    auto delta = h*h - a*c; 
    
    //Delta < 0 -> Não intercepta a esfera, = 0 intercepta em 1 ponto, > 0 intercepta em dois pontos 
    if(delta < 0.0f) return false;

    auto sqrtd = std::sqrt(delta);

    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    glm::vec3 outwardNormal = (rec.p - _center) / _radius; //Normalizado
    rec.setFaceNormal(r, outwardNormal);
    return true;
}
