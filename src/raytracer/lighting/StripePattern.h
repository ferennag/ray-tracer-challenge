#ifndef RAY_TRACER_CHALLENGE_STRIPEPATTERN_H
#define RAY_TRACER_CHALLENGE_STRIPEPATTERN_H


#include "Pattern.h"

class StripePattern: public Pattern {
public:
    StripePattern(const Color &first, const Color &second);
    StripePattern(const StripePattern& other);
    ~StripePattern() override = default;

    [[nodiscard]] Color colorAt(const glm::dvec3 &point) const override;
private:
    Color m_first { Color::black() }, m_second { Color::white() };
};


#endif //RAY_TRACER_CHALLENGE_STRIPEPATTERN_H
