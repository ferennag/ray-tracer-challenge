#include "Ray.h"

Ray::Ray(glm::vec3 point, glm::vec3 direction) {
    m_origin = glm::vec4(point, 1.0);
    m_direction = glm::vec4(direction, 0.0);
}

glm::vec4 Ray::at(float distance) {
    return m_origin + m_direction * distance;
}

Ray Ray::transform(glm::mat4 transformation) const {
    auto position = transformation * m_origin;
    auto direction = transformation * m_direction;
    return { position, glm::normalize(direction) };
}