#include "PointLight.h"

PointLight::PointLight(const glm::vec4 &position, float intensity) {
    m_position = position;
    m_intensity = intensity;
}
