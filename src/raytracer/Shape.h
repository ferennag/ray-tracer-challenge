#ifndef RAY_TRACER_CHALLENGE_SHAPE_H
#define RAY_TRACER_CHALLENGE_SHAPE_H

#include <memory>
#include "Ray.h"
#include "Intersections.h"
#include "Material.h"

class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;

    [[nodiscard]] virtual Intersections intersect(const Ray &ray) const = 0;
    [[nodiscard]] virtual glm::dvec4 getNormalAt(const glm::dvec4 &point) const = 0;

    Shape &withTransformation(const glm::dmat4 &transformation);
    Shape &withMaterial(const Material &material);

    [[nodiscard]] glm::dmat4 getTransformation() { return m_model; };

    [[nodiscard]] Material getMaterial() const { return m_material; }

protected:
    Material m_material;
    glm::dmat4 m_model { glm::identity<glm::dmat4>() };
    glm::dmat4 m_modelInverse { glm::identity<glm::dmat4>() };
    glm::dmat4 m_modelInverseTranspose { glm::identity<glm::dmat4>() };
};

#endif //RAY_TRACER_CHALLENGE_SHAPE_H
