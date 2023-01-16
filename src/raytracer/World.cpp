#include <memory>
#include <optional>
#include "World.h"
#include "shapes/Sphere.h"
#include "Transformations.h"
#include "util/RayMath.h"
#include "shapes/Plane.h"

World::World(int width, int height) {
    m_camera = Camera(width, height, PI / 2);
    m_lights.push_back(PointLight({ -10, 10, -10, 1 }, 1));

    auto sphere1 = std::make_unique<Sphere>();
    sphere1->withTransformation(
            Transformations::translate(1, 0.3, 0)
            * Transformations::rotate(PI / 2, glm::vec3(0, 1, 0))
            * Transformations::scale(0.3, 0.3, 0.3)
    ).withMaterial({ .pattern = Pattern({ 0.2, 0.9, 0.3, 1.0 }, { 0.9, 0.9, 0.9, 1.0 }).withTransformation(
            Transformations::scale(15, 15, 15)) });
    m_objects.push_back(std::move(sphere1));

    auto sphere2 = std::make_unique<Sphere>();
    sphere2->withTransformation(
            Transformations::translate(-1, 0.5, 0.0)
            * Transformations::scale(0.5, 0.5, 0.5)
    ).withMaterial({ .pattern = Pattern({ 0.2, 0.9, 0.3, 1.0 }, { 0.9, 0.9, 0.9, 1.0 }).withTransformation(
            Transformations::scale(5, 5, 5)) });
    m_objects.push_back(std::move(sphere2));

    auto sphere3 = std::make_unique<Sphere>();
    sphere3->withTransformation(
            Transformations::translate(0, 0.3, -1)
            * Transformations::scale(0.3, 0.3, 0.3)
    ).withMaterial({ .pattern = Pattern({ 0.2, 0.9, 0.3, 1.0 }, { 0.9, 0.9, 0.9, 1.0 }).withTransformation(
            Transformations::scale(2, 2, 2)) });
    m_objects.push_back(std::move(sphere3));

    auto wallMaterial = Material { .specular = 0, .pattern = Pattern({ 1, 0.9, 0.9, 1.0 }, { 0.8, 0.5, 0.5, 1.0 }) };
    auto floor = std::make_unique<Plane>();
    floor->withMaterial(wallMaterial);
    m_objects.push_back(std::move(floor));
}

Intersections World::intersect(const Ray &ray) const {
    Intersections result;

    for (const auto &object: m_objects) {
        auto xs = object->intersect(ray);
        result.addIntersections(xs);
    }

    return result;
}

std::vector<PointLight> World::getLights() const {
    return m_lights;
}

Camera World::getCamera() const {
    return m_camera;
}
