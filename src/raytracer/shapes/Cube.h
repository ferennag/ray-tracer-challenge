#ifndef RAY_TRACER_CHALLENGE_CUBE_H
#define RAY_TRACER_CHALLENGE_CUBE_H


#include "Shape.h"

class Cube: public Shape {
public:
    Cube(Shape *parent = nullptr);
    ~Cube() override = default;

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const override;
    [[nodiscard]] Bounds calculateBounds() const override;
private:

};


#endif //RAY_TRACER_CHALLENGE_CUBE_H
