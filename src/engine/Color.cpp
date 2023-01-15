#include <cmath>
#include "Color.h"

Color::Color() = default;

Color::Color(float r, float g, float b, float a) {
    setRGBA(r, g, b, a);
}

Color::Color(const glm::vec4 &v) {
    setRGBA(v.x, v.y, v.z, v.w);
}


void Color::setRGB(float r, float g, float b) {
    setRGBA(r, g, b, m_alpha);
}

uint32_t Color::getUint32() const {
    auto components = toRGB();
    return (components[0] << 24) | (components[1] << 16) | (components[2] << 8) | (components[3] << 0);
}

void Color::setAlpha(uint8_t alpha) {
    m_alpha = alpha;
}

void Color::copy(const Color &color) {
    m_red = color.m_red;
    m_green = color.m_green;
    m_blue = color.m_blue;
    m_alpha = color.m_alpha;
}

Color Color::operator*(float intensity) const {
    Color result;
    result.copy(*this);
    result.m_red *= intensity;
    result.m_green *= intensity;
    result.m_blue *= intensity;
    return result;
}

std::array<uint8_t, 4> Color::toRGB() const {
    return {
            static_cast<uint8_t>(round(m_red * 255)),
            static_cast<uint8_t>(round(m_green * 255)),
            static_cast<uint8_t>(round(m_blue * 255)),
            static_cast<uint8_t>(round(m_alpha * 255))
    };
}

std::array<float, 4> Color::fromRGB() const {
    return {
            static_cast<float>(m_red / 255),
            static_cast<float>(m_green / 255),
            static_cast<float>(m_blue / 255),
            static_cast<float>(m_alpha / 255)
    };
}

void Color::setRGBA(float r, float g, float b, float a) {
    m_red = std::max(std::min(r, 1.0f), 0.0f);
    m_green = std::max(std::min(g, 1.0f), 0.0f);
    m_blue = std::max(std::min(b, 1.0f), 0.0f);
    m_alpha = std::max(std::min(a, 1.0f), 0.0f);
}

Color Color::operator+(const Color &other) const {
    return {
        m_red + other.m_red,
        m_green + other.m_green,
        m_blue + other.m_blue,
        m_alpha,
    };
}

Color Color::operator+(const float value) const {
    return {
        m_red + value,
        m_green + value,
        m_blue + value,
        m_alpha
    };
}

Color &Color::operator*=(const Color& rhs) {
    m_red *= rhs.m_red;
    m_green *= rhs.m_green;
    m_blue *= rhs.m_blue;
    return *this;
}

Color &Color::operator+=(const Color &rhs) {
    m_red += rhs.m_red;
    m_green += rhs.m_green;
    m_blue += rhs.m_blue;
    return *this;
}

