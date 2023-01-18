#include <gtest/gtest.h>
#include "../src/raytracer/lighting/Material.h"
#include "../src/engine/util/RayMath.h"

TEST(Material, default) {
    Material m;
    EXPECT_NEAR(m.ambient, 0.1, PRECISION);
    EXPECT_NEAR(m.diffuse, 0.9, PRECISION);
    EXPECT_NEAR(m.specular, 0.9, PRECISION);
    EXPECT_NEAR(m.shininess, 200, PRECISION);
}

TEST(Material, defaultTransparency) {
    Material m;
    EXPECT_NEAR(m.transparency, 0.0, PRECISION);
}

TEST(Material, defaultRefractiveIndex) {
    Material m;
    EXPECT_NEAR(m.refractiveIndex, 1.0, PRECISION);
}