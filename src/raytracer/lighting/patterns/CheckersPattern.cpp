#include "CheckersPattern.h"

CheckersPattern::CheckersPattern(const Color &first, const Color &second) {
    m_first = first;
    m_second = second;
}

Color CheckersPattern::colorAt(const glm::dvec3 &point) const {
    auto sum = static_cast<int>(floor(point.x) + floor(point.y) + floor(point.z));
    if (sum % 2 == 0) {
        return m_first;
    } else {
        return m_second;
    }
}
