#include "Dielectric.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
Dielectric::Dielectric(float refraction_index) : _refraction_index(refraction_index) 
{}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
{
    attenuation = color(1.0, 1.0, 1.0);
    float ri = rec.isFrontFace ? (1.0/_refraction_index) : _refraction_index;

    glm::vec3 unit_direction = glm::normalize(r_in.direction());
    float cos_theta = std::fmin(glm::dot(-unit_direction, rec.normal), 1.0);
    float sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    glm::vec3 direction;

    if (cannot_refract || reflectance(cos_theta, ri) > random_float())
        direction = glm::reflect(unit_direction, rec.normal);
    else
        direction = glm::refract(unit_direction, rec.normal, ri);

    scattered = Ray(rec.p, direction);
    return true;
    
}
float Dielectric::reflectance(float cosine, float refraction_index) {
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0*r0;
    return r0 + (1-r0)*std::pow((1 - cosine),5);
}