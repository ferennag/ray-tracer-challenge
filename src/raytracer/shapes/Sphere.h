#ifndef RAY_TRACER_CHALLENGE_SPHERE_H
#define RAY_TRACER_CHALLENGE_SPHERE_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "../Ray.h"
#include "../Intersections.h"
#include "../../engine/Color.h"
#include "../lighting/Material.h"
#include "Shape.h"

class Sphere: public Shape {
public:
    explicit Sphere(Shape *parent = nullptr);
    ~Sphere() override = default;

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point) const override;

private:
    glm::dvec4 m_position { 0, 0, 0, 1 };
};


#endif //RAY_TRACER_CHALLENGE_SPHERE_H
