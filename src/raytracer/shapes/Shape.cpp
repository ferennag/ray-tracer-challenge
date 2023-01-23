#include "Shape.h"

Shape::Shape(Shape *parent) {
    withTransformation(glm::identity<glm::dmat4>());
    setParent(parent);
}

Shape &Shape::withTransformation(const glm::dmat4 &transformation) {
    m_model = transformation;
    m_modelInverse = glm::inverse(m_model);
    m_modelInverseTranspose = glm::transpose(m_modelInverse);
    return *this;
}


glm::dmat4 Shape::getTransformation() const {
    return m_model;
}

Shape &Shape::withMaterial(const Material &material) {
    m_material = material;
    return *this;
}

glm::dvec4 Shape::getNormalAt(const glm::dvec4 &point, const Intersection &hit) const {
    auto localPoint = worldToObject(point);
    auto localNormal = getLocalNormalAt(localPoint, hit);
    return normalToWorld(localNormal);
}

Intersections Shape::intersect(const Ray &ray) const {
    auto bs = getBounds();
    auto localRay = ray.transform(m_modelInverse);
    if (!bs.intersect(localRay)) {
        return {};
    }

    return localIntersect(localRay);
}

Color Shape::getColorAt(const glm::dvec4 &point) const {
    if (!m_material.pattern) {
        return m_material.color;
    }

    auto pattern = m_material.pattern.get();
    auto localPoint = worldToObject(point);
    auto patternPoint = pattern->getTransformation() * localPoint;
    return pattern->colorAt(patternPoint);
}

Shape *Shape::getParent() const {
    return m_parent;
}

void Shape::setParent(Shape *parent) {
    m_parent = parent;
}

glm::dvec4 Shape::worldToObject(const glm::dvec4 &point) const {
    glm::dvec4 result = point;
    if (m_parent) {
        result = m_parent->worldToObject(point);
    }

    result = m_modelInverse * result;
    return result;
}

glm::dvec4 Shape::normalToWorld(const glm::dvec4 &normal) const {
    auto result = m_modelInverseTranspose * normal;
    result.w = 0;
    result = glm::normalize(result);

    if (m_parent) {
        result = m_parent->normalToWorld(result);
        result.w = 0;
    }

    return result;
}

const Bounds &Shape::getBounds() const {
    if(!m_boundsReady) {
        m_bounds = calculateBounds();
        m_boundsReady = true;
    }

    return m_bounds;
}
