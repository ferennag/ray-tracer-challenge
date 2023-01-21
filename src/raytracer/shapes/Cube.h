#ifndef RAY_TRACER_CHALLENGE_CUBE_H
#define RAY_TRACER_CHALLENGE_CUBE_H


#include "Shape.h"

class Cube: public Shape {
public:
    Cube();
    ~Cube() override = default;

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point) const override;
private:

};


#endif //RAY_TRACER_CHALLENGE_CUBE_H
