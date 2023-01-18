#ifndef RAY_TRACER_CHALLENGE_TESTPATTERN_H
#define RAY_TRACER_CHALLENGE_TESTPATTERN_H

#include "../src/raytracer/lighting/patterns/Pattern.h"

class TestPattern : public Pattern {
public:
    ~TestPattern() override = default;

    virtual Color colorAt(const glm::dvec3 &point) const override {
        return Color(point.x, point.y, point.z);
    };
};

#endif //RAY_TRACER_CHALLENGE_TESTPATTERN_H
