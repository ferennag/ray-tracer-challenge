#ifndef RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
#define RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H

#include <glm/glm.hpp>

class Transformations {
public:
    Transformations() = delete;
    Transformations(const Transformations &other) = delete;
    Transformations(const Transformations &&other) = delete;

    static glm::dmat4 identity();
    static glm::dmat4 translate(double x, double y, double z);
    static glm::dmat4 translate(const glm::dvec3 &factor);
    static glm::dmat4 scale(double x, double y, double z);
    static glm::dmat4 scale(const glm::dvec3 &factor);
    static glm::dmat4 rotate(const double angle, const glm::dvec3 &axes);
private:
};


#endif //RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
