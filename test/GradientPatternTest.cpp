#include <gtest/gtest.h>
#include "../src/raytracer/lighting/GradientPattern.h"

TEST(GradientPattern, linerlyInterpolates) {
    auto pattern = GradientPattern(Color::white(), Color::black());
    EXPECT_EQ(pattern.colorAt({ 0, 0, 0 }), Color::white());
    EXPECT_EQ(pattern.colorAt({ 0.25, 0, 0 }), Color(0.75, 0.75, 0.75));
    EXPECT_EQ(pattern.colorAt({ 0.5, 0, 0 }), Color(0.5, 0.5, 0.5));
    EXPECT_EQ(pattern.colorAt({ 0.75, 0, 0 }), Color(0.25, 0.25, 0.25));
}