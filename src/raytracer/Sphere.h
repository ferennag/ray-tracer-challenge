#ifndef RAY_TRACER_CHALLENGE_SPHERE_H
#define RAY_TRACER_CHALLENGE_SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ray.h"
#include "Intersections.h"
#include "../engine/Color.h"
#include "Material.h"

class Sphere {
public:
    Sphere();

    Intersections intersect(const Ray &ray) const;
    Sphere &withTransformation(const glm::mat4 &transformation);
    glm::mat4 getTransformation();

    glm::vec4 getNormalAt(const glm::vec4 &point) const;
    Color getColor() const { return m_color; }
    Material getMaterial() const { return m_material; }

private:
    Material m_material;
    glm::vec4 m_position { 0, 0, 0, 1 };
    glm::mat4 m_model { glm::identity<glm::mat4>() };
    glm::mat4 m_modelInverse { glm::identity<glm::mat4>() };
    glm::mat4 m_modelInverseTranspose { glm::identity<glm::mat4>() };
    Color m_color { 1, 1, 1, 1 };
};


#endif //RAY_TRACER_CHALLENGE_SPHERE_H
