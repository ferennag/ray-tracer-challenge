#ifndef RAY_TRACER_CHALLENGE_COMPUTATIONS_H
#define RAY_TRACER_CHALLENGE_COMPUTATIONS_H

#include <algorithm>
#include "Intersections.h"
#include "Ray.h"
#include "shapes/Shape.h"
#include "../engine/util/RayMath.h"

struct Computations {
    const Shape *const object;
    double distance;
    glm::dvec4 point, overPoint, underPoint;
    glm::dvec4 eye;
    glm::dvec4 normal;
    glm::dvec4 reflect;
    double n1, n2;
};

static Computations prepareComputations(const Intersections &intersections, const Ray &ray) {
    auto hit = intersections.hit().value();
    auto point = ray.at(hit.distance);
    auto normal = hit.object->getNormalAt(point);
    auto overPoint = point + normal * PRECISION;
    auto underPoint = point - normal * PRECISION;
    auto reflect = glm::reflect(ray.getDirection(), normal);

    std::vector<const Shape *> containers;
    double n1 { 0 }, n2 { 0 };
    for (auto &i: intersections.getList()) {
        if (i.object == hit.object) {
            n1 = containers.empty() ? 1.0 : containers.back()->getMaterial().refractiveIndex;
        }

        auto includes = std::find_if(containers.begin(), containers.end(), [i](const Shape *object) {
            return object == i.object;
        }) != containers.end();

        if (includes) {
            std::remove(containers.begin(), containers.end(), i.object);
        } else {
            containers.push_back(i.object);
        }

        if (i.object == hit.object) {
            n2 = containers.empty() ? 1.0 : containers.back()->getMaterial().refractiveIndex;
            break;
        }
    }

    return {
            .object = hit.object,
            .distance = hit.distance,
            .point = point,
            .overPoint = overPoint,
            .underPoint = underPoint,
            .eye = -ray.getDirection(),
            .normal = normal,
            .reflect = reflect,
            .n1 = n1,
            .n2 = n2
    };
}
#endif //RAY_TRACER_CHALLENGE_COMPUTATIONS_H
