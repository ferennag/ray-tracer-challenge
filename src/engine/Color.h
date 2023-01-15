#ifndef RAY_TRACER_CHALLENGE_COLOR_H
#define RAY_TRACER_CHALLENGE_COLOR_H

#include <glm/glm.hpp>
#include <array>
#include <cstdint>

class Color {
public:
    Color();
    Color(float r, float g, float b, float a);
    explicit Color(const glm::vec4 &v);

    void setRGB(float r, float g, float b);
    void setRGBA(float r, float g, float b, float a);
    void copy(const Color &color);
    void setAlpha(uint8_t alpha);
    [[nodiscard]] uint32_t getUint32() const;

    Color operator*(float intensity) const;
    Color& operator*=(const Color& rhs);
    Color operator+(const Color &other) const;
    Color& operator+=(const Color& rhs);
    Color operator+(const float value) const;
private:
    float m_red { 0 }, m_green { 0 }, m_blue { 0 }, m_alpha { 1 };

    std::array<uint8_t, 4> toRGB() const;
    std::array<float, 4> fromRGB() const;
};


#endif //RAY_TRACER_CHALLENGE_COLOR_H
