#ifndef RAY_TRACER_CHALLENGE_CAMERA_H
#define RAY_TRACER_CHALLENGE_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera() = default;
    Camera(int w, int h, double fov);

    void setPosition(const glm::dvec3 &pos);
    void setTarget(const glm::dvec3 &target);
    [[nodiscard]] double getPixelSize() const;
    [[nodiscard]] double getHalfWidth() const;
    [[nodiscard]] double getHalfHeight() const;

    [[nodiscard]] glm::dmat4 getViewMatrix() const;
private:
    glm::dvec4 m_position { 0, 1, -3, 1 };
    glm::dvec4 m_target { 0, 0, 0, 1 };
    double m_halfW { 0 }, m_halfH { 0 };
    double m_pixelSize { 0 };
};


#endif //RAY_TRACER_CHALLENGE_CAMERA_H