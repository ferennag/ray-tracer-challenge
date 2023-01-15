#include "World.h"
#include "Transformations.h"
#include "RayMath.h"

World::World(int width, int height) {
    m_camera = Camera(width, height, PI / 2);
    m_lights.push_back(PointLight({ -10, 10, -10, 1 }, 1.0));
    m_objects.push_back(Sphere().withTransformation(
            Transformations::translate(1, 0, 0)
            * Transformations::scale(0.5, 0.5, 0.5)
    ));
    m_objects.push_back(Sphere().withTransformation(
            Transformations::translate(-1, 0.0, 0.0)
            * Transformations::scale(0.5, 0.5, 0.5)
    ));

    m_objects.push_back(Sphere().withTransformation(
            Transformations::translate(0, 0.0, -1)
            * Transformations::scale(0.3, 0.3, 0.3)
    ).withMaterial({ .color = { 0.3, 0.9, 0.4, 1 }}));

    // Floor
    auto wallMaterial = Material { .color = { 1, 0.9, 0.9, 1.0 }, .specular = 0 };
    m_objects.push_back(Sphere().withTransformation(
            Transformations::translate(0, -1, 0)
            * Transformations::scale(10, 0.01, 10)
    ).withMaterial(wallMaterial));

    // Left wall
    m_objects.push_back(Sphere().withTransformation(
            Transformations::translate(0, 0, 5)
            * Transformations::rotate(-PI / 4, glm::vec3(0, 1, 0))
            * Transformations::rotate(-PI / 2, glm::vec3(1, 0, 0))
            * Transformations::scale(10, 0.01, 10)
    ).withMaterial(wallMaterial));

    // Right wall
    m_objects.push_back(Sphere().withTransformation(
            Transformations::translate(0, 0, 5)
            * Transformations::rotate(PI / 4, glm::vec3(0, 1, 0))
            * Transformations::rotate(PI / 2, glm::vec3(1, 0, 0))
            * Transformations::scale(10, 0.01, 10)
    ).withMaterial(wallMaterial));
}

Intersections World::intersect(const Ray &ray) const {
    Intersections result;
    for (const auto &object: m_objects) {
        auto xs = object.intersect(ray);
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
