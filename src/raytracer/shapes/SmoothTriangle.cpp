#include "SmoothTriangle.h"

SmoothTriangle::SmoothTriangle(const glm::dvec4 &a, const glm::dvec4 &b, const glm::dvec4 &c, const glm::dvec4 &na,
                               const glm::dvec4 &nb, const glm::dvec4 &nc, Shape *parent) : Triangle(a, b, c, parent) {
    m_na = na;
    m_nb = nb;
    m_nc = nc;
}

glm::dvec4 SmoothTriangle::getLocalNormalAt(const glm::dvec4 &point, const Intersection &hit) const {
    return m_nb * hit.u + m_nc * hit.v + m_na * (1 - hit.u - hit.v);
}

