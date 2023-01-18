#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(int w, int h, double fov) {
    m_w = w;
    m_h = h;
    double halfView = tanf(fov / 2.0f);
    double aspect = static_cast<double>(w) / static_cast<double>(h);
    if (aspect >= 1) {
        m_halfW = halfView;
        m_halfH = halfView / aspect;
    } else {
        m_halfW = halfView * aspect;
        m_halfH = halfView;
    }

    m_pixelSize = m_halfW * 2.0f / static_cast<double>(h);
    computeViewMatrices();
}

glm::dmat4 Camera::getViewMatrix() const {
    if (m_dirty) {
        computeViewMatrices();
    }

    return m_view;
}

glm::dmat4 Camera::getInverseViewMatrix() const {
    if (m_dirty) {
        computeViewMatrices();
    }

    return m_inverseView;
}

void Camera::setPosition(const glm::dvec3 &pos) {
    m_position = glm::dvec4(pos, 1.0);
    m_dirty = true;
}

void Camera::setTarget(const glm::dvec3 &target) {
    m_target = glm::dvec4(target, 1.0);
    m_dirty = true;
}

double Camera::getPixelSize() const {
    return m_pixelSize;
}

double Camera::getHalfWidth() const {
    return m_halfW;
}

double Camera::getHalfHeight() const {
    return m_halfH;
}

int Camera::getWidth() const {
    return m_w;
}

int Camera::getHeight() const {
    return m_h;
}

void Camera::computeViewMatrices() const {
    m_view = glm::lookAt(glm::dvec3(m_position), glm::dvec3(m_target), { 0, 1, 0 });
    m_inverseView = glm::inverse(m_view);
    m_dirty = false;
}
