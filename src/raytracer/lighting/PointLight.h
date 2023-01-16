#ifndef RAY_TRACER_CHALLENGE_POINTLIGHT_H
#define RAY_TRACER_CHALLENGE_POINTLIGHT_H

#include <glm/glm.hpp>

class PointLight {
public:
    PointLight() = default;
    PointLight(const glm::dvec4 &position, double intensity = 1.0f);

    double getIntensity() const { return m_intensity; }

    glm::dvec4 getPosition() const { return m_position; }

private:
    glm::dvec4 m_position { 0 };
    double m_intensity { 1 };
};


#endif //RAY_TRACER_CHALLENGE_POINTLIGHT_H
