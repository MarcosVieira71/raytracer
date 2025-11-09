#include "Metal.h"

Metal::Metal(const color& albedo, float fuzz) : _albedo(albedo), _fuzz(fuzz < 1 ? fuzz : 1) {}


bool Metal::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
{
    glm::vec3 reflected = glm::reflect(r_in.direction(), rec.normal);
    reflected = glm::normalize(reflected) + (_fuzz * random_unit_vector());
    scattered = Ray(rec.p, reflected);
    attenuation = _albedo;
    return (glm::dot(scattered.direction(), rec.normal) > 0);
}