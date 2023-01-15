#ifndef RAY_TRACER_CHALLENGE_RAY_H
#define RAY_TRACER_CHALLENGE_RAY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Ray {
public:
    Ray(glm::vec3 point, glm::vec3 direction);

    glm::vec4 at(float distance);

    [[nodiscard]] glm::vec4 getOrigin() const { return m_origin; }

    [[nodiscard]] glm::vec4 getDirection() const { return m_direction; }

    Ray transform(glm::mat4 transformation) const;

private:
    glm::vec4 m_origin, m_direction;
};


#endif //RAY_TRACER_CHALLENGE_RAY_H
