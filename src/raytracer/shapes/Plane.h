#ifndef RAY_TRACER_CHALLENGE_PLANE_H
#define RAY_TRACER_CHALLENGE_PLANE_H

#include "Shape.h"

class Plane : public Shape {
public:
    ~Plane() override = default;

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point) const override;
};


#endif //RAY_TRACER_CHALLENGE_PLANE_H
