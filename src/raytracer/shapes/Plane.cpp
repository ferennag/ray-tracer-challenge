#include "Plane.h"
#include "../util/RayMath.h"

static double absd(double x) {
    return x < 0 ? -x : x;
}

Intersections Plane::localIntersect(const Ray &ray) const {
    Intersections result;

    if (absd(ray.getDirection().y) < PRECISION) {
        return result;
    }

    auto t = -ray.getOrigin().y / ray.getDirection().y;
    result.addIntersection(this, t);
    return result;
}

glm::dvec4 Plane::getLocalNormalAt(const glm::dvec4 &point) const {
    return { 0, 1, 0, 0 };
}
