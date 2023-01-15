#include "Sphere.h"

Sphere::Sphere() {
    withTransformation(glm::identity<glm::mat4>());
}

Intersections Sphere::intersect(const Ray &ray) const {
    Intersections result;

    auto r = ray.transform(m_modelInverse);

    auto sphereToRay = r.getOrigin() - m_position;
    auto a = glm::dot(r.getDirection(), r.getDirection());
    auto b = 2 * glm::dot(r.getDirection(), sphereToRay);
    auto c = glm::dot(sphereToRay, sphereToRay) - 1;
    auto discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0) {
        return result;
    }

    auto t1 = (-b - sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t1 == t2) {
        result.addIntersection(this, t1);
    } else {
        result.addIntersection(this, t1);
        result.addIntersection(this, t2);
    }

    return result;
}

glm::mat4 Sphere::getTransformation() {
    return m_model;
}

glm::vec4 Sphere::getNormalAt(const glm::vec4 &point) const {
    auto localPoint = m_modelInverse * point;
    auto localNormal = localPoint - m_position;
    auto worldNormal = m_modelInverseTranspose * localNormal;
    worldNormal.w = 0.0f;
    return glm::normalize(worldNormal);
}

Sphere &Sphere::withTransformation(const glm::mat4 &transformation) {
    m_model = transformation;
    m_modelInverse = glm::inverse(m_model);
    m_modelInverseTranspose = glm::transpose(m_modelInverse);
    return *this;
}

Sphere &Sphere::withMaterial(const Material &material) {
    m_material = material;
    return *this;
}
