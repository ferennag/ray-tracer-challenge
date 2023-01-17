#ifndef RAY_TRACER_CHALLENGE_RAYMATH_H
#define RAY_TRACER_CHALLENGE_RAYMATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const double PRECISION = 0.00001;
const double PI = glm::pi<double>();

static double absd(double a) {
    return a < 0 ? -a : a;
}

#endif //RAY_TRACER_CHALLENGE_RAYMATH_H
