#include <gtest/gtest.h>
#include "../src/raytracer/lighting/Material.h"
#include "../src/engine/util/RayMath.h"

TEST(Material, defaultTransparency) {
    Material m;
    EXPECT_NEAR(m.transparency, 0.0, PRECISION);
}

TEST(Material, defaultRefractiveIndex) {
    Material m;
    EXPECT_NEAR(m.refractiveIndex, 1.0, PRECISION);
}