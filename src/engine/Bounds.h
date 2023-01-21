#ifndef RAY_TRACER_CHALLENGE_BOUNDS_H
#define RAY_TRACER_CHALLENGE_BOUNDS_H

#include <vector>
#include <glm.hpp>
#include "../raytracer/Ray.h"

class Bounds {
public:
    glm::dvec4 aa { 0 }, bb { 0 };

    Bounds() = default;
    Bounds(const glm::dvec4 &aa, const glm::dvec4 &bb);
    virtual ~Bounds() = default;

    [[nodiscard]] Bounds transform(const glm::dmat4 &t) const;
    [[nodiscard]] Bounds extend(const Bounds &rhs) const;
    [[nodiscard]] bool intersect(const Ray &ray) const;

private:
    [[nodiscard]] std::vector<glm::dvec4> getAllPoints() const;
};


#endif //RAY_TRACER_CHALLENGE_BOUNDS_H
