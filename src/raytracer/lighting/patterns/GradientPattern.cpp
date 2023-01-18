#include "GradientPattern.h"

GradientPattern::GradientPattern(const Color &first, const Color &second): Pattern() {
    m_first = first;
    m_second = second;
}

GradientPattern::GradientPattern(const GradientPattern &other): Pattern(other) {
    m_first = other.m_first;
    m_second = other.m_second;
}

Color GradientPattern::colorAt(const glm::dvec3 &point) const {
    auto distance = m_second - m_first;
    auto fraction = point.x - floor(point.x);
    return m_first + distance * fraction;
}
