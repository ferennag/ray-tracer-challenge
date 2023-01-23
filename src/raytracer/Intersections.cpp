#include <algorithm>
#include "Intersections.h"

std::optional<Intersection> Intersections::hit() const {
    if (!m_sorted) {
        sort();
    }

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
    addIntersection(object, distance, 0, 0);
}

void Intersections::addIntersection(const Shape *object, double distance, double u, double v) {
    m_intersections.push_back({ .distance = distance, .object = object, .u=u, .v=v });
    m_sorted = false;
}

void Intersections::addIntersections(const Intersections &other) {
    for (const auto &x: other.m_intersections) {
        m_intersections.push_back(x);
    }
    m_sorted = false;
}

void Intersections::sort() const {
    std::sort(m_intersections.begin(), m_intersections.end(), [](const Intersection &lhs, const Intersection &rhs) {
        return lhs.distance < rhs.distance;
    });
    m_sorted = true;
}

std::vector<Intersection> &Intersections::getList() const {
    if (!m_sorted) {
        sort();
    }

    return m_intersections;
}
