#ifndef RAY_TRACER_CHALLENGE_GRADIENTPATTERN_H
#define RAY_TRACER_CHALLENGE_GRADIENTPATTERN_H


#include "Pattern.h"

class GradientPattern: public Pattern {
public:
    GradientPattern(const Color &first, const Color &second);
    GradientPattern(const GradientPattern &other);
    ~GradientPattern() override = default;

    [[nodiscard]] Color colorAt(const glm::dvec3 &point) const override;
private:
    Color m_first { Color::black() }, m_second { Color::white() };
};


#endif //RAY_TRACER_CHALLENGE_GRADIENTPATTERN_H
