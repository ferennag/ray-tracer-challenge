#ifndef RAY_TRACER_CHALLENGE_SHAPE_H
#define RAY_TRACER_CHALLENGE_SHAPE_H

#include <memory>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "../Ray.h"
#include "../Intersections.h"
#include "../lighting/Material.h"
#include "../../engine/Bounds.h"

class Shape {
public:
    Shape(Shape *parent = nullptr);
    virtual ~Shape() = default;

    [[nodiscard]] glm::dvec4 worldToObject(const glm::dvec4 &point) const;
    [[nodiscard]] glm::dvec4 normalToWorld(const glm::dvec4 &normal) const;

    [[nodiscard]] virtual Intersections intersect(const Ray &ray) const;
    [[nodiscard]] virtual Intersections localIntersect(const Ray &ray) const = 0;
    [[nodiscard]] virtual glm::dvec4 getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const = 0;
    [[nodiscard]] virtual Bounds calculateBounds() const = 0;
    [[nodiscard]] virtual glm::dvec4 getNormalAt(const glm::dvec4 &point, const Intersection &hit) const;
    [[nodiscard]] virtual Color getColorAt(const glm::dvec4 &point) const;

    virtual Shape &withTransformation(const glm::dmat4 &transformation);
    [[nodiscard]] glm::dmat4 getTransformation() const;
    virtual Shape &withMaterial(const Material &material);

    [[nodiscard]] const Material &getMaterial() const { return m_material; }
    [[nodiscard]] const Bounds &getBounds() const;

    [[nodiscard]] Shape *getParent() const;
    void setParent(Shape *parent);

    virtual void subdivide(int threshold) {};

protected:
    Shape *m_parent { nullptr };
    Material m_material;
    glm::dmat4 m_model { glm::identity<glm::dmat4>() };
    glm::dmat4 m_modelInverse { glm::identity<glm::dmat4>() };
    glm::dmat4 m_modelInverseTranspose { glm::identity<glm::dmat4>() };
    mutable Bounds m_bounds;
    mutable bool m_boundsReady;
};

#endif //RAY_TRACER_CHALLENGE_SHAPE_H
