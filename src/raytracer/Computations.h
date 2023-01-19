#ifndef RAY_TRACER_CHALLENGE_COMPUTATIONS_H
#define RAY_TRACER_CHALLENGE_COMPUTATIONS_H

#include <iostream>
#include <algorithm>
#include <glm/gtx/string_cast.hpp>
#include <string>
#include <sstream>
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

    [[nodiscard]] std::string toString() const {
        std::stringstream ss;
        ss << "---------------------Computation--------------------------\n";
        ss << "Shape: " << object << "\n";
        ss << "Distance: " << distance << "\n";
        ss << "Point: " << glm::to_string(point) << "\n";
        ss << "OverPoint: " << glm::to_string(overPoint) << "\n";
        ss << "UnderPoint: " << glm::to_string(underPoint) << "\n";
        ss << "Eye: " << glm::to_string(eye) << "\n";
        ss << "Normal: " << glm::to_string(normal) << "\n";
        ss << "Reflect: " << glm::to_string(reflect) << "\n";
        ss << "N1: " << n1 << "\n";
        ss << "N2: " << n2 << "\n";
        ss << "----------------------------------------------------------" << std::endl;
        return ss.str();
    }

    [[nodiscard]] double schlick() const {
        auto angle = glm::dot(eye, normal);

        if (n1 > n2) {
            auto n = n1 / n2;
            auto sin2T = pow(n, 2) * (1.0 - pow(angle, 2));
            if (sin2T > 1.0) {
                return 1.0;
            }

            auto cosT = sqrt(1.0 - sin2T);
            angle = cosT;
        }

        double r0 = pow((n1 - n2) / (n1 + n2), 2.0);
        auto result = r0 + (1.0 - r0) * pow((1.0 - angle), 5.0);
        return result;
    }
};

static Computations prepareComputations(const Intersection &hit, const Intersections &intersections, const Ray &ray) {
    auto point = ray.at(hit.distance);
    auto eye = -ray.getDirection();
    auto normal = hit.object->getNormalAt(point);

    if (glm::dot(normal, eye) < 0) {
        normal = -normal;
    }

    auto overPoint = point + normal * PRECISION;
    auto underPoint = point - normal * PRECISION;
    auto reflect = glm::reflect(ray.getDirection(), normal);

    std::vector<const Shape *> containers;
    double n1 { 0 }, n2 { 0 };
    for (auto &i: intersections.getList()) {
        if (i == hit) {
            n1 = containers.empty() ? 1.0 : containers.back()->getMaterial().refractiveIndex;
        }

        auto includes = std::find_if(containers.begin(), containers.end(), [i](const Shape *object) {
            return object == i.object;
        }) != containers.end();

        if (includes) {
            auto removeStart = std::remove_if(containers.begin(), containers.end(), [i](const Shape *object) {
                return object == i.object;
            });
            containers.erase(removeStart, containers.end());
        } else {
            containers.push_back(i.object);
        }

        if (i == hit) {
            n2 = containers.empty() ? 1.0 : containers.back()->getMaterial().refractiveIndex;
            break;
        }
    }

//    if (n1 == n2 == 1) {
//        std::cout << "Intersections for: " << n1 << " "  << n2 << std::endl;
//        std::cout << "Hit: " << hit.object << " "  << hit.distance << std::endl;
//        for (auto &i: intersections.getList()) {
//            std::cout << i.object << " " << i.distance << std::endl;
//        }
//        std::cout << "--------------------------------" << std::endl;
//    }

    return {
            .object = hit.object,
            .distance = hit.distance,
            .point = point,
            .overPoint = overPoint,
            .underPoint = underPoint,
            .eye = eye,
            .normal = normal,
            .reflect = reflect,
            .n1 = n1,
            .n2 = n2
    };
}

#endif //RAY_TRACER_CHALLENGE_COMPUTATIONS_H
