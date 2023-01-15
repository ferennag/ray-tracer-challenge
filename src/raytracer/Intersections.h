#ifndef RAY_TRACER_CHALLENGE_INTERSECTIONS_H
#define RAY_TRACER_CHALLENGE_INTERSECTIONS_H

#include <vector>
#include <optional>
#include "Intersection.h"

class Sphere;

class Intersections {
public:
    Intersections() = default;
    void addIntersection(const Sphere *object, float distance);
    void addIntersections(const Intersections &other);
    [[nodiscard]] std::optional<Intersection> hit() const;
private:
    std::vector<Intersection> m_intersections;

    void sort();
};


#endif //RAY_TRACER_CHALLENGE_INTERSECTIONS_H
