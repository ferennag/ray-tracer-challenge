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
    void addIntersection(const Shape *object, double distance, double u, double v);
    void addIntersections(const Intersections &other);
    [[nodiscard]] std::optional<Intersection> hit() const;

    std::vector<Intersection> &getList() const;
private:
    mutable std::vector<Intersection> m_intersections;

    void sort();
};


#endif //RAY_TRACER_CHALLENGE_INTERSECTIONS_H
