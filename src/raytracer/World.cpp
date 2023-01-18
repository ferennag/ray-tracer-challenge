#include <yaml-cpp/yaml.h>
#include "World.h"
#include "shapes/Plane.h"

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