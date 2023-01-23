#ifndef RAY_TRACER_CHALLENGE_GROUP_H
#define RAY_TRACER_CHALLENGE_GROUP_H

#include <vector>
#include "Shape.h"

class Group : public Shape {
public:
    explicit Group(Shape *parent = nullptr);
    ~Group() override = default;

    [[nodiscard]] bool isEmpty() const;
    void addChild(const std::shared_ptr<Shape> &child);
    void addChildren(const std::vector<std::shared_ptr<Shape>> &children);

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const override;
    [[nodiscard]] Bounds calculateBounds() const override;

    Shape &withMaterial(const Material &material) override;

    void subdivide(int threshold) override;

private:
    std::vector<std::shared_ptr<Shape>> m_children;
    std::pair<std::vector<std::shared_ptr<Shape>>, std::vector<std::shared_ptr<Shape>>> partitionChildren();
};


#endif //RAY_TRACER_CHALLENGE_GROUP_H
