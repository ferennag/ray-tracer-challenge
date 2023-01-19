#ifndef RAY_TRACER_CHALLENGE_COLOR_H
#define RAY_TRACER_CHALLENGE_COLOR_H

#include <glm.hpp>
#include <array>
#include <cstdint>

class Color {
public:
    Color();
    Color(double r, double g, double b, double a = 1.0);
    explicit Color(const glm::dvec3 &v);
    explicit Color(const glm::dvec4 &v);

    void setRGB(double r, double g, double b);
    void setRGBA(double r, double g, double b, double a);
    void copy(const Color &color);
    void setAlpha(uint8_t alpha);
    [[nodiscard]] uint32_t getUint32() const;

    Color operator*(const glm::vec3 &intensity) const;
    Color operator*(double intensity) const;
    Color &operator*=(const Color &rhs);
    Color operator+(const Color &other) const;
    Color &operator+=(const Color &rhs);
    Color operator+(const double value) const;
    Color operator+(const glm::vec3 &value) const;
    Color operator-(const Color &other) const;

    bool operator==(const Color &rhs) const;

    static Color black() {
        return Color(0, 0, 0, 1);
    }

    static Color white() {
        return Color(1, 1, 1, 1);
    }

    double r() const { return m_red; }

    double g() const { return m_green; }

    double b() const { return m_blue; }

private:
    double m_red { 0 }, m_green { 0 }, m_blue { 0 }, m_alpha { 1 };

    std::array<uint8_t, 4> toRGB() const;
    std::array<double, 4> fromRGB() const;
};


#endif //RAY_TRACER_CHALLENGE_COLOR_H
