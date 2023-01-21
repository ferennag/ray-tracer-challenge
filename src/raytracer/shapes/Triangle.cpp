#include <glm.hpp>
#include "Triangle.h"

Triangle::Triangle(const glm::dvec4 &a, const glm::dvec4 &b, const glm::dvec4 &c, Shape *parent) : Shape(parent) {
    m_a = a;
    m_b = b;
    m_c = c;

    m_e1 = m_b - m_a;
    m_e2 = m_c - m_a;
    m_normal = { glm::normalize(glm::cross(m_e2, m_e1)), 0 };
}

Intersections Triangle::localIntersect(const Ray &ray) const {
    auto dirCrossE2 = glm::cross(glm::dvec3(ray.getDirection()), m_e2);
    auto det = glm::dot(m_e1, dirCrossE2);
    if (absd(det) < PRECISION) { return {}; }

    auto f = 1.0 / det;
    auto aToOrigin = ray.getOrigin() - m_a;
    auto u = f * glm::dot(aToOrigin, { dirCrossE2, 0 });
    if (u < 0 || u > 1) { return {}; }

    auto originCrossE1 = glm::cross(glm::dvec3(aToOrigin), m_e1);
    auto v = f * glm::dot(ray.getDirection(), { originCrossE1, 0 });
    if (v < 0 || (u + v) > 1) { return {}; }

    auto t = f * glm::dot(m_e2, originCrossE1);
    Intersections xs;
    xs.addIntersection(this, t);
    return xs;
}

glm::dvec4 Triangle::getLocalNormalAt(const glm::dvec4 &point) const {
    return m_normal;
}

Bounds Triangle::bounds() const {
    return {{ -1, -1, 0, 1 },
            { 1,  1,  0, 1 }};
}
