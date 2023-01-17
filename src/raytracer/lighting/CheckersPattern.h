#ifndef RAY_TRACER_CHALLENGE_CHECKERSPATTERN_H
#define RAY_TRACER_CHALLENGE_CHECKERSPATTERN_H


#include "Pattern.h"

class CheckersPattern: public Pattern {
public:
    CheckersPattern(const Color &first, const Color &second);
    ~CheckersPattern() override = default;

    [[nodiscard]] Color colorAt(const glm::vec3 &point) const override;
private:
    Color m_first { Color::black() }, m_second { Color::white() };
};


#endif //RAY_TRACER_CHALLENGE_CHECKERSPATTERN_H
