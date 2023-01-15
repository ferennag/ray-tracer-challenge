#include "PointLight.h"

PointLight::PointLight(const glm::dvec4 &position, double intensity) {
    m_position = position;
    m_intensity = intensity;
}
