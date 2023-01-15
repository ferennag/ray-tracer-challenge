#include <algorithm>
#include "Intersections.h"

std::optional<Intersection> Intersections::hit() {
    if (m_intersections.empty()) {
        return std::nullopt;
    }

    sort();

    auto result = std::find_if(m_intersections.begin(), m_intersections.end(), [](const Intersection &x) {
        return x.distance > 0;
    });

    if (result == m_intersections.end()) {
        return std::nullopt;
    } else {
        return std::make_optional<Intersection>(*result);
    }
}

void Intersections::addIntersection(const Sphere *object, float distance) {
    m_intersections.push_back({ .distance = distance, .object = object });
}

void Intersections::addIntersections(const Intersections &other) {
    for (const auto &x: other.m_intersections) {
        m_intersections.push_back(x);
    }
}

void Intersections::sort() {
    std::sort(m_intersections.begin(), m_intersections.end(), [](const Intersection &lhs, const Intersection &rhs) {
        return lhs.distance < rhs.distance;
    });
}
