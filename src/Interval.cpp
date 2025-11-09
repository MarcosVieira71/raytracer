#include "Interval.h"

#include <algorithm>

#include "utils.h"

Interval::Interval() : min(+infinity), max(-infinity) {} 

Interval::Interval(float min, float max) : min(min), max(max) {}

float Interval::size() const {
    return max - min;
}

bool Interval::contains(float x) const {
    return min <= x && x <= max;
}

bool Interval::surrounds(float x) const {
    return min < x && x < max;
}

float Interval::clamp(float x) const
{
    return std::clamp(x, min, max);       
}

const Interval Interval::empty    = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);
