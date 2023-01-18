#include "PointLight.h"

PointLight::PointLight(const glm::dvec3 &position, const glm::dvec3 &intensity) {
    m_position = glm::dvec4(position, 1.0);
    m_intensity = intensity;
}
