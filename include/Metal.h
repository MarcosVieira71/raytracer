#include "Material.h"
#include "utils.h"

class Metal : public Material {
  public:
    Metal(const color& albedo, float fuzz);

    bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const;

  private:
    color _albedo;
    float _fuzz;
};