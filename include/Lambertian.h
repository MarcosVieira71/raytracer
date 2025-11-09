#include "Material.h"

class Lambertian : public Material {
  public:
    Lambertian(const color& albedo);

    bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;

  private:
    color _albedo;
};