#include "Lambertian.h"

Lambertian::Lambertian(const color& albedo): _albedo(albedo)
{}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const 
{
    auto scatter_direction = rec.normal + random_unit_vector();
    if(near_zero(scatter_direction))
        scatter_direction = rec.normal;
    scattered = Ray(rec.p, scatter_direction);
    attenuation = _albedo;
    return true;
}