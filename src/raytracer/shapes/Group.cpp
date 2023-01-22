#include <exception>
#include "Group.h"

Group::Group(Shape *parent) : Shape(parent) {
}

bool Group::isEmpty() const {
    return m_children.empty();
}

void Group::addChild(std::unique_ptr<Shape> child) {
    child->setParent(this);
    m_children.push_back(std::move(child));
    m_boundsReady = false;
}

Intersections Group::localIntersect(const Ray &ray) const {
    Intersections xs;

    auto bs = bounds();

    if (!bs.intersect(ray)) {
        return xs;
    }

    for (auto &child: m_children) {
        xs.addIntersections(child->intersect(ray));
    }

    return xs;
}

glm::dvec4 Group::getLocalNormalAt(const glm::dvec4 &point) const {
    throw std::runtime_error("ERROR: calling local_normal_at on Group!");
}

Bounds Group::bounds() const {
    if (!m_boundsReady) {
        calculateBounds();
    }

    return m_bounds;
}

void Group::calculateBounds() const {
    if (m_children.empty()) {
        m_bounds = {{ 0, 0, 0, 1 },
                    { 0, 0, 0, 1 }};
    } else {
        Bounds result;
        for (auto &child: m_children) {
            auto bounds = child->bounds();
            auto groupSpaceBounds = bounds.transform(child->getTransformation());
            result = result.extend(groupSpaceBounds);
        }
        m_bounds = result;
    }

    m_boundsReady = true;
}

