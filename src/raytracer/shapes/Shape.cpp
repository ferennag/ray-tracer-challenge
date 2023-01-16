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

glm::dvec4 Shape::getNormalAt(const glm::dvec4 &point) const {
    auto localPoint = m_modelInverse * point;
    auto localNormal = getLocalNormalAt(localPoint);
    auto worldNormal = m_modelInverseTranspose * localNormal;
    worldNormal.w = 0.0f;
    return glm::normalize(worldNormal);
}

Intersections Shape::intersect(const Ray &ray) const {
    auto localRay = ray.transform(m_modelInverse);
    return localIntersect(localRay);
}
