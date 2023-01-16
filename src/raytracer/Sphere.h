#ifndef RAY_TRACER_CHALLENGE_SPHERE_H
#define RAY_TRACER_CHALLENGE_SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ray.h"
#include "Intersections.h"
#include "../engine/Color.h"
#include "Material.h"
#include "Shape.h"

class Sphere: public Shape {
public:
    Sphere();
    ~Sphere() override = default;

    [[nodiscard]] Intersections intersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getNormalAt(const glm::dvec4 &point) const override;

private:
    glm::dvec4 m_position { 0, 0, 0, 1 };
};


#endif //RAY_TRACER_CHALLENGE_SPHERE_H
