#include <exception>
#include "Group.h"

bool Group::isEmpty() const {
    return m_children.empty();
}

void Group::addChild(std::unique_ptr<Shape> child) {
    child->setParent(this);
    m_children.push_back(std::move(child));
}

Intersections Group::localIntersect(const Ray &ray) const {
    Intersections xs;

    for (auto &child: m_children) {
        xs.addIntersections(child->intersect(ray));
    }

    return xs;
}

glm::dvec4 Group::getLocalNormalAt(const glm::dvec4 &point) const {
    throw std::runtime_error("ERROR: calling local_normal_at on Group!");
}

Group::Group(Shape *parent) : Shape(parent) {
}

