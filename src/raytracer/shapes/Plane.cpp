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

glm::dvec4 Plane::getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const {
    return { 0, 1, 0, 0 };
}

Bounds Plane::bounds() const {
    return {{ -INFINITY, 0, -INFINITY, 1 },
            { INFINITY,  0, INFINITY,  1 }};
}

