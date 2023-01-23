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

Triangle::Triangle(const glm::dvec4 &a, const glm::dvec4 &b, const glm::dvec4 &c, const glm::dvec4 &normal,
                   Shape *parent) : Shape(parent) {
    m_a = a;
    m_b = b;
    m_c = c;
    m_normal = normal;
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
    xs.addIntersection(this, t, u, v);
    return xs;
}

glm::dvec4 Triangle::getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const {
    return m_normal;
}

Bounds Triangle::calculateBounds() const {
    auto minX = std::min(std::min(m_a.x, m_b.x), m_c.x);
    auto minY = std::min(std::min(m_a.y, m_b.y), m_c.y);
    auto minZ = std::min(std::min(m_a.z, m_b.z), m_c.z);

    auto maxX = std::max(std::max(m_a.x, m_b.x), m_c.x);
    auto maxY = std::max(std::max(m_a.y, m_b.y), m_c.y);
    auto maxZ = std::max(std::max(m_a.z, m_b.z), m_c.z);

    return {{ minX, minY, minZ, 1 },
            { maxX, maxY, maxZ, 1 }};
}

