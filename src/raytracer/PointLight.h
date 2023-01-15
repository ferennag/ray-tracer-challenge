#ifndef RAY_TRACER_CHALLENGE_POINTLIGHT_H
#define RAY_TRACER_CHALLENGE_POINTLIGHT_H

#include <glm/glm.hpp>

class PointLight {
public:
    PointLight() = default;
    PointLight(const glm::vec4 &position, float intensity = 1.0f);

    float getIntensity() const { return m_intensity; }

    glm::vec4 getPosition() const { return m_position; }

private:
    glm::vec4 m_position { 0 };
    float m_intensity { 1 };
};


#endif //RAY_TRACER_CHALLENGE_POINTLIGHT_H
