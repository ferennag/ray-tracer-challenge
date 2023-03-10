#ifndef RAY_TRACER_CHALLENGE_POINTLIGHT_H
#define RAY_TRACER_CHALLENGE_POINTLIGHT_H

#include <glm.hpp>

class PointLight {
public:
    PointLight() = default;
    PointLight(const glm::dvec3 &position, const glm::dvec3 &intensity = {1.0, 1.0, 1.0});

    [[nodiscard]] glm::dvec3 getIntensity() const { return m_intensity; }

    [[nodiscard]] glm::dvec4 getPosition() const { return m_position; }

private:
    glm::dvec4 m_position { 0 };
    glm::dvec3 m_intensity { 1 };
};


#endif //RAY_TRACER_CHALLENGE_POINTLIGHT_H
