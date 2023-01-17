#include "StripePattern.h"

StripePattern::StripePattern(const Color &c1, const Color &c2): Pattern() {
    m_first = c1;
    m_second = c2;
}

StripePattern::StripePattern(const StripePattern &other): Pattern(other) {
    m_first = other.m_first;
    m_second = other.m_second;
}

Color StripePattern::colorAt(const glm::dvec3 &point) const {
    return static_cast<int>(floor(point.x)) % 2 == 0 ? m_first : m_second;
}
