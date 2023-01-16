#include "Ray.h"

Ray::Ray(glm::dvec3 point, glm::dvec3 direction) {
    m_origin = glm::dvec4(point, 1.0);
    m_direction = glm::dvec4(direction, 0.0);
}

glm::dvec4 Ray::at(double distance) const {
    return m_origin + m_direction * distance;
}

Ray Ray::transform(const glm::dmat4 &transformation) const {
    auto position = transformation * m_origin;
    auto direction = transformation * m_direction;
    return { position, direction };
}