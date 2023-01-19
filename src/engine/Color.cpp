#include <cmath>
#include "Color.h"
#include "./util/RayMath.h"


static double min(double a, double b) {
    return a < b ? a : b;
}

static double max(double a, double b) {
    return a > b ? a : b;
}


Color::Color() = default;

Color::Color(double r, double g, double b, double a) {
    setRGBA(r, g, b, a);
}

Color::Color(const glm::dvec3 &v) {
    setRGBA(v.x, v.y, v.z, 1.0);
}

Color::Color(const glm::dvec4 &v) {
    setRGBA(v.x, v.y, v.z, v.w);
}

void Color::setRGB(double r, double g, double b) {
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

Color Color::operator*(const double intensity) const {
    return {
            m_red * intensity,
            m_green * intensity,
            m_blue * intensity,
            m_alpha,
    };
}

Color Color::operator*(const glm::vec3 &intensity) const {
    return {
            m_red * intensity.x,
            m_green * intensity.y,
            m_blue * intensity.z,
            m_alpha,
    };
}

std::array<uint8_t, 4> Color::toRGB() const {
    return {
            static_cast<uint8_t>(max(min(round(m_red * 255), 255), 0)),
            static_cast<uint8_t>(max(min(round(m_green * 255), 255), 0)),
            static_cast<uint8_t>(max(min(round(m_blue * 255), 255), 0)),
            static_cast<uint8_t>(max(min(round(m_alpha * 255), 255), 0))
    };
}

std::array<double, 4> Color::fromRGB() const {
    return {
            static_cast<double>(m_red / 255),
            static_cast<double>(m_green / 255),
            static_cast<double>(m_blue / 255),
            static_cast<double>(m_alpha / 255)
    };
}

void Color::setRGBA(double r, double g, double b, double a) {
    m_red = r;
    m_green = g;
    m_blue = b;
    m_alpha = a;
}

Color Color::operator+(const Color &other) const {
    return {
            m_red + other.m_red,
            m_green + other.m_green,
            m_blue + other.m_blue,
            m_alpha,
    };
}

Color Color::operator+(const double value) const {
    return {
            m_red + value,
            m_green + value,
            m_blue + value,
            m_alpha
    };
}

Color Color::operator+(const glm::vec3 &value) const {
    return {
            m_red + value.x,
            m_green + value.y,
            m_blue + value.z,
            m_alpha
    };
}

Color &Color::operator*=(const Color &rhs) {
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

Color Color::operator-(const Color &other) const {
    return {
            m_red - other.m_red,
            m_green - other.m_green,
            m_blue - other.m_blue,
            m_alpha
    };
}

bool Color::operator==(const Color &rhs) const {
    return std::fabs(m_red - rhs.m_red) < PRECISION
           && std::fabs(m_green - rhs.m_green) < PRECISION
           && std::fabs(m_blue - rhs.m_blue) < PRECISION
           && std::fabs(m_alpha - rhs.m_alpha) < PRECISION;
}

Color Color::mix(const Color &rhs) const {
    return {
        glm::mix(m_red, rhs.r(), 0.5),
        glm::mix(m_green, rhs.g(), 0.5),
        glm::mix(m_blue, rhs.b(), 0.5),
        glm::mix(m_alpha, rhs.m_alpha, 0.5)
    };
}
