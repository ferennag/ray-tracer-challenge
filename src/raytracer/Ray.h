#ifndef RAY_TRACER_CHALLENGE_RAY_H
#define RAY_TRACER_CHALLENGE_RAY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Ray {
public:
    Ray(glm::dvec3 point, glm::dvec3 direction);

    glm::dvec4 at(double distance) const;

    [[nodiscard]] glm::dvec4 getOrigin() const { return m_origin; }

    [[nodiscard]] glm::dvec4 getDirection() const { return m_direction; }

    Ray transform(glm::dmat4 transformation) const;

private:
    glm::dvec4 m_origin, m_direction;
};


#endif //RAY_TRACER_CHALLENGE_RAY_H
