#ifndef RAY_TRACER_CHALLENGE_CONE_H
#define RAY_TRACER_CHALLENGE_CONE_H


#include "Shape.h"

class Cone: public Shape {
public:
    explicit Cone(Shape *parent = nullptr);
    ~Cone() override = default;

    [[nodiscard]] Intersections localIntersect(const Ray &ray) const override;
    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const override;
    [[nodiscard]] Bounds bounds() const override;
    void intersectCaps(const Ray &ray, Intersections &xs) const;

    void setMinimum(double min);
    void setMaximum(double max);
    void setClosed(bool closed);
private:
    double m_minimum { -INFINITY };
    double m_maximum { INFINITY };
    bool m_closed { false };
};


#endif //RAY_TRACER_CHALLENGE_CONE_H
