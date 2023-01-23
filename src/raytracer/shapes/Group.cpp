#include "Group.h"

Group::Group(Shape *parent) : Shape(parent) {
}

bool Group::isEmpty() const {
    return m_children.empty();
}

void Group::addChild(const std::shared_ptr<Shape> &child) {
    child->setParent(this);
    m_children.push_back(child);
    m_boundsReady = false;
}

void Group::addChildren(const std::vector<std::shared_ptr<Shape>> &children) {
    for (auto &child: children) {
        child->setParent(this);
        m_children.push_back(child);
    }
    m_boundsReady = false;
}

Intersections Group::localIntersect(const Ray &ray) const {
    Intersections xs;

    for (auto &child: m_children) {
        xs.addIntersections(child->intersect(ray));
    }

    return xs;
}

glm::dvec4 Group::getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const {
    throw std::runtime_error("ERROR: calling local_normal_at on Group!");
}

Bounds Group::calculateBounds() const {
    if (m_children.empty()) {
        return {{ 0, 0, 0, 1 },
                { 0, 0, 0, 1 }};
    } else {
        Bounds result;
        for (auto &child: m_children) {
            auto bounds = child->calculateBounds();
            auto groupSpaceBounds = bounds.transform(child->getTransformation());
            result = result.extend(groupSpaceBounds);
        }
        return result;
    }
}

void Group::subdivide(int threshold) {
    if (m_children.size() >= threshold) {
        auto [left, right] = partitionChildren();

        if (m_children.empty() && (left.empty() || right.empty())) {
            // Prevent infinite recursion
            // If a group is divided into 2 parts by consuming all it's children, and moving all of them
            // in either the left or the right side ONLY, then it will cause an infinite recursion.
            // So we stop here and revert the division back.
            m_children.insert(m_children.end(), left.begin(), left.end());
            m_children.insert(m_children.end(), right.begin(), right.end());
        } else {
            if (!left.empty()) {
                auto leftGroup = std::make_shared<Group>();
                leftGroup->addChildren(left);
                addChild(leftGroup);
            }

            if (!right.empty()) {
                auto rightGroup = std::make_shared<Group>();
                rightGroup->addChildren(right);
                addChild(rightGroup);
            }
        }
    }

    for (auto &child: m_children) {
        child->subdivide(threshold);
    }

    calculateBounds();
}

std::pair<std::vector<std::shared_ptr<Shape>>, std::vector<std::shared_ptr<Shape>>>
Group::partitionChildren() {
    std::pair<std::vector<std::shared_ptr<Shape>>, std::vector<std::shared_ptr<Shape>>> result;

    auto [leftBound, rightBound] = calculateBounds().split();

    std::vector<std::shared_ptr<Shape>> remainingChildren;
    for (auto &child: m_children) {
        auto childBounds = child->calculateBounds();
        if (leftBound.includes(childBounds)) {
            result.first.push_back(child);
        } else if (rightBound.includes(childBounds)) {
            result.second.push_back(child);
        } else {
            remainingChildren.push_back(child);
        }
    }

    m_children = remainingChildren;
    return result;
}

Shape &Group::withMaterial(const Material &material) {
    Shape::withMaterial(material);

    for (auto &child: m_children) {
        child->withMaterial(material);
    }

    return *this;
}
