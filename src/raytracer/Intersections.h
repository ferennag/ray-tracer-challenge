#ifndef RAY_TRACER_CHALLENGE_INTERSECTIONS_H
#define RAY_TRACER_CHALLENGE_INTERSECTIONS_H

#include <vector>
#include <optional>
#include "Intersection.h"

class Shape;

class Intersections {
public:
    Intersections() = default;
    void addIntersection(const Shape *object, double distance);
    void addIntersections(const Intersections &other);
    [[nodiscard]] std::optional<Intersection> hit();
private:
    std::vector<Intersection> m_intersections;

    void sort();
};


#endif //RAY_TRACER_CHALLENGE_INTERSECTIONS_H
