#include <glm.hpp>
#include "Cube.h"

static std::pair<double, double> checkAxis(double origin, double direction) {
    auto tminNumerator = (-1 - origin);
    auto tmaxNumerator = (1 - origin);

    double tmin { 0 }, tmax { 0 };
    if (absd(direction) >= PRECISION) {
        tmin = tminNumerator / direction;
        tmax = tmaxNumerator / direction;
    } else {
        tmin = tminNumerator * INFINITY;
        tmax = tmaxNumerator * INFINITY;
    }

    if (tmin > tmax) { std::swap(tmin, tmax); }
    return { tmin, tmax };
}

Cube::Cube(Shape *parent): Shape(parent) {
}

Intersections Cube::localIntersect(const Ray &ray) const {
    auto [xtmin, xtmax] = checkAxis(ray.getOrigin().x, ray.getDirection().x);
    auto [ytmin, ytmax] = checkAxis(ray.getOrigin().y, ray.getDirection().y);
    auto [ztmin, ztmax] = checkAxis(ray.getOrigin().z, ray.getDirection().z);

    auto tmin = std::max(std::max(xtmin, ytmin), ztmin);
    auto tmax = std::min(std::min(xtmax, ytmax), ztmax);

    Intersections xs;

    if (tmin > tmax) { return xs; }

    xs.addIntersection(this, tmin);
    xs.addIntersection(this, tmax);
    return xs;
}

glm::dvec4 Cube::getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const {
    auto maxc = std::max(std::max(absd(point.x), absd(point.y)), absd(point.z));

    if (doubleEq(maxc, absd(point.x))) {
        return { point.x, 0, 0, 0 };
    } else if (doubleEq(maxc, absd(point.y))) {
        return { 0, point.y, 0, 0 };
    } else {
        return { 0, 0, point.z, 0 };
    }
}

Bounds Cube::bounds() const {
    return {{ -1, -1, -1, 1 }, { 1, 1, 1, 1 }};
}
