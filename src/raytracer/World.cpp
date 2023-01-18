#include <memory>
#include <optional>
#include "World.h"
#include "shapes/Sphere.h"
#include "Transformations.h"
#include "shapes/Plane.h"
#include "lighting/patterns/GradientPattern.h"
#include "lighting/patterns/CheckersPattern.h"

World::World(int width, int height) {
    m_camera = Camera(width, height, PI / 2);
    m_lights.push_back(PointLight({ -10, 10, -10, 1 }, 1));

    auto sphere1 = std::make_unique<Sphere>();
    auto pattern1 = std::make_shared<StripePattern>(Color { 0.2, 0.9, 0.3, 1.0 }, Color { 0.9, 0.9, 0.9, 1.0 });
    pattern1->withTransformation(Transformations::scale(15, 15, 15));
    sphere1->withTransformation(
            Transformations::translate(.5, 1.0, -1)
    ).withMaterial({
                           .color = { .5, .1, .1 },
                           .ambient = 0.1,
                           .diffuse = 0.1,
                           .specular = 1,
                           .shininess = 300,
                           .reflectivity = 1,
                           .transparency = 1,
                           .refractiveIndex = 1 });
    m_objects.push_back(std::move(sphere1));

    auto sphere2 = std::make_unique<Sphere>();
    auto pattern2 = std::make_shared<GradientPattern>(Color { 1, 0, 0 }, Color { 0, 0, 1 });
    sphere2->withTransformation(
            Transformations::translate(-1, 0.5, 1.0)
            * Transformations::scale(0.5, 0.5, 0.5)
    ).withMaterial({ .reflectivity = 0.1, .pattern = pattern2 });
    m_objects.push_back(std::move(sphere2));

    auto sphere3 = std::make_unique<Sphere>();
    auto pattern3 = std::make_shared<StripePattern>(Color { 0.2, 0.9, 0.3, 1.0 }, Color { 0.9, 0.9, 0.9, 1.0 });
    pattern3->withTransformation(Transformations::scale(2, 2, 2));
    sphere3->withTransformation(
            Transformations::translate(0, 0.3, 2)
            * Transformations::scale(0.3, 0.3, 0.3)
    ).withMaterial({ .pattern = pattern3 });
    m_objects.push_back(std::move(sphere3));

    auto wallPattern = std::make_shared<CheckersPattern>(Color::black(), Color::white());
    auto wallMaterial = Material { .specular = 0, .reflectivity = 0.1, .pattern = wallPattern };
    auto floor = std::make_unique<Plane>();
    floor->withMaterial(wallMaterial);
    m_objects.push_back(std::move(floor));

    auto leftWall = std::make_unique<Plane>();
    leftWall->withTransformation(
            Transformations::translate(0, 0, 5)
            * Transformations::rotate(glm::radians(-90.0), { 1, 0, 0 })
    );
    leftWall->withMaterial(wallMaterial);
    m_objects.push_back(std::move(leftWall));
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

std::unique_ptr<World> World::defaultWorld(int width, int height) {
    auto world = std::make_unique<World>(width, height);
    world->m_objects.erase(world->m_objects.begin(), world->m_objects.end());
    world->m_lights.erase(world->m_lights.begin(), world->m_lights.end());

    auto pointLight = PointLight({ -10, 10, -10, 1.0 }, 1.0);
    world->m_lights.push_back(pointLight);

    auto sphere1 = std::make_unique<Sphere>();
    sphere1->withMaterial({ .color = { 0.8, 1.0, 0.6 }, .diffuse = 0.7, .specular = 0.2 });
    world->m_objects.push_back(std::move(sphere1));

    auto sphere2 = std::make_unique<Sphere>();
    sphere2->withTransformation(Transformations::scale(0.5, 0.5, 0.5));
    world->m_objects.push_back(std::move(sphere2));

    return world;
}
