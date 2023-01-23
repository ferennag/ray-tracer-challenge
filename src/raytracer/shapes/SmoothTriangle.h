#ifndef RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H
#define RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H

#include "Triangle.h"

class SmoothTriangle : public Triangle {
public:
    explicit SmoothTriangle(const glm::dvec4 &a, const glm::dvec4 &b, const glm::dvec4 &c, const glm::dvec4 &na,
                            const glm::dvec4 &nb, const glm::dvec4 &nc, Shape *parent = nullptr);
    ~SmoothTriangle() override = default;

    [[nodiscard]] glm::dvec4 getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const override;
protected:
    glm::dvec4 m_na, m_nb, m_nc;
};


#endif //RAY_TRACER_CHALLENGE_SMOOTHTRIANGLE_H
