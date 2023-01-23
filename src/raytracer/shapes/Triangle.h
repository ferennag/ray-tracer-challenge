#ifndef RAY_TRACER_CHALLENGE_TRIANGLE_H
#define RAY_TRACER_CHALLENGE_TRIANGLE_H


#include "Shape.h"

class Triangle : public Shape {
public:
    explicit Triangle(const glm::dvec4 &a, const glm::dvec4 &b, const glm::dvec4 &c, Shape *parent = nullptr);
    explicit Triangle(const glm::dvec4 &a, const glm::dvec4 &b, const glm::dvec4 &c, const glm::dvec4 &normal,
                      Shape *parent = nullptr);
    ~Triangle() override = default;

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const override;
    [[nodiscard]] Bounds calculateBounds() const override;

protected:
    glm::dvec4 m_a, m_b, m_c;
    glm::dvec3 m_e1, m_e2;
    glm::dvec4 m_normal;
};


#endif //RAY_TRACER_CHALLENGE_TRIANGLE_H
