#include "Sphere.h"

Sphere::Sphere(Shape *parent) : Shape(parent) {
}

Intersections Sphere::localIntersect(const Ray &ray) const {
    Intersections result;

    auto sphereToRay = ray.getOrigin() - m_position;
    auto a = glm::dot(ray.getDirection(), ray.getDirection());
    auto b = 2 * glm::dot(ray.getDirection(), sphereToRay);
    auto c = glm::dot(sphereToRay, sphereToRay) - 1;
    auto discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0) {
        return result;
    }

    auto t1 = (-b - sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t1 == t2) {
        result.addIntersection(this, t1);
    } else {
        result.addIntersection(this, t1);
        result.addIntersection(this, t2);
    }

    return result;
}

glm::dvec4 Sphere::getLocalNormalAt(const glm::dvec4 &point) const {
    return point - m_position;
}

Bounds Sphere::bounds() const {
    return {{ -1, -1, -1, 1 }, { 1, 1, 1, 1 }};
}
