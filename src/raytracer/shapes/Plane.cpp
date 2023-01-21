#include "Plane.h"
#include "../../engine/util/RayMath.h"

Plane::Plane(Shape *parent) : Shape(parent) {
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

