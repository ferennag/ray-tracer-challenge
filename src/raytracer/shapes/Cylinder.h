#ifndef RAY_TRACER_CHALLENGE_CYLINDER_H
#define RAY_TRACER_CHALLENGE_CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape {
public:
    explicit Cylinder(Shape *parent = nullptr);
    ~Cylinder() override = default;

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point) const override;
    void intersectCaps(const Ray &ray, Intersections &xs) const;

    void setMinimum(double min);
    void setMaximum(double max);
    void setClosed(bool closed);

private:
    double m_minimum { -INFINITY };
    double m_maximum { INFINITY };
    bool m_closed { false };
};


#endif //RAY_TRACER_CHALLENGE_CYLINDER_H
