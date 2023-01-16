#include "Pattern.h"

Pattern::Pattern(const Color &c1, const Color &c2) {
    m_first = c1;
    m_second = c2;
}

Color Pattern::colorAt(const glm::vec3 &point) const {
    return static_cast<int>(floor(point.x)) % 2 == 0 ? m_first : m_second;
}

Pattern &Pattern::withTransformation(const glm::dmat4 &transform) {
    m_transform = transform;
    return *this;
}

glm::dmat4 Pattern::getTransformation() const {
    return m_transform;
}
