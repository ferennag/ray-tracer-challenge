#ifndef RAY_TRACER_CHALLENGE_GROUP_H
#define RAY_TRACER_CHALLENGE_GROUP_H

#include <vector>
#include "Shape.h"

class Group : public Shape {
public:
    explicit Group(Shape *parent = nullptr);
    ~Group() override = default;

    [[nodiscard]] bool isEmpty() const;
    void addChild(std::unique_ptr<Shape> child);

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point) const override;
    [[nodiscard]] Bounds bounds() const override;
private:
    std::vector<std::unique_ptr<Shape>> m_children;
    mutable Bounds m_bounds;
    mutable bool m_boundsReady { false };

    [[nodiscard]] void calculateBounds() const;
};


#endif //RAY_TRACER_CHALLENGE_GROUP_H
