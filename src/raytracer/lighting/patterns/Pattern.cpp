#include "Pattern.h"

Pattern &Pattern::withTransformation(const glm::dmat4 &transform) {
    m_transform = transform;
    return *this;
}

glm::dmat4 Pattern::getTransformation() const {
    return m_transform;
}
