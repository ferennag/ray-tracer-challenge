#include <algorithm>
#include "Intersections.h"

std::optional<Intersection> Intersections::hit() const {
    if (m_intersections.empty()) {
        return std::nullopt;
    }

    auto result = std::find_if(m_intersections.begin(), m_intersections.end(), [](const Intersection &x) {
        return x.distance > 0;
    });

    if (result == m_intersections.end()) {
        return std::nullopt;
    } else {
        return std::make_optional<Intersection>(*result);
    }
}

void Intersections::addIntersection(const Shape *object, double distance) {
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

std::vector<Intersection> &Intersections::getList() const {
    return m_intersections;
}
