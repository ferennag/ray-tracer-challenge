#include "Shape.h"

Shape &Shape::withTransformation(const glm::dmat4 &transformation) {
    m_model = transformation;
    m_modelInverse = glm::inverse(m_model);
    m_modelInverseTranspose = glm::transpose(m_modelInverse);
    return *this;
}

Shape &Shape::withMaterial(const Material &material) {
    m_material = material;
    return *this;
}

