#include "World.h"
#include "Transformations.h"

World::World() {
    m_lights.push_back(PointLight({ -10, 10, -10, 1 }, 1.0));
    m_objects.push_back(Sphere().withTransformation(
            Transformations::translate(1, 0, 0)
//            * Transformations::scale(0.5, 0.5, 0.5)
    ));
    m_objects.push_back(Sphere().withTransformation(
            Transformations::translate(-1, 0.0, 0.0)
            * Transformations::scale(0.5, 0.5, 0.5)
    ));
}

Intersections World::intersect(const Ray &ray) {
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
