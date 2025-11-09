#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

class HittableContainer : public Hittable {
  public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableContainer();
    HittableContainer(std::shared_ptr<Hittable> object);
    void clear();
    void add(std::shared_ptr<Hittable> object);

    bool hit(const Ray& r, const Interval& ray_t, HitRecord& rec) const override;
};
