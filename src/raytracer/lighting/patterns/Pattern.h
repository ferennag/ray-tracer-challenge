#ifndef RAY_TRACER_CHALLENGE_PATTERN_H
#define RAY_TRACER_CHALLENGE_PATTERN_H


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "../../../engine/Color.h"

class Pattern {
public:
    Pattern() = default;
    virtual ~Pattern() = default;

    virtual Color colorAt(const glm::dvec3 &point) const = 0;

    Pattern &withTransformation(const glm::dmat4 &transform);
    [[nodiscard]] glm::dmat4 getTransformation() const;

protected:
    glm::dmat4 m_transform { glm::identity<glm::dmat4>() };
};


#endif //RAY_TRACER_CHALLENGE_PATTERN_H
