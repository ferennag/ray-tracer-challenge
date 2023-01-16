#ifndef RAY_TRACER_CHALLENGE_PATTERN_H
#define RAY_TRACER_CHALLENGE_PATTERN_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../engine/Color.h"

class Pattern {
public:
    Pattern() = default;
    Pattern(const Color &c1, const Color &c2);
    virtual ~Pattern() = default;

    virtual Color colorAt(const glm::vec3 &point) const;

    Pattern &withTransformation(const glm::dmat4 &transform);
    glm::dmat4 getTransformation() const;

protected:
    Color m_first { Color::black() }, m_second { Color::white() };
    glm::dmat4 m_transform { glm::identity<glm::dmat4>() };
};


#endif //RAY_TRACER_CHALLENGE_PATTERN_H
