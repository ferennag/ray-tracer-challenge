#include <algorithm>
#include "Intersections.h"

std::optional<Intersection> Intersections::hit() const {
    if (m_intersections.empty()) {
        return std::nullopt;
    }

    for (auto &x: m_intersections) {
        if (x.distance > 0) {
            return std::make_optional<Intersection>(x);
        }
    }

    return std::nullopt;
}

void Intersections::addIntersection(const Sphere *object, float distance) {
    m_intersections.push_back({ .distance = distance, .object = object });
    sort();
}

void Intersections::addIntersections(const Intersections &other) {
    for (const auto &x: other.m_intersections) {
        m_intersections.push_back(x);
    }
    sort();
}

void Intersections::sort() {
    std::sort(m_intersections.begin(), m_intersections.end(), [](const Intersection &lhs, const Intersection &rhs) {
        return lhs.distance < rhs.distance;
    });
}
