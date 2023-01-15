#include <gtest/gtest.h>
#include "../src/raytracer/Sphere.h"
#include "../src/raytracer/Transformations.h"
#include "../src/raytracer/RayMath.h"

TEST(SphereTest, normalAtWithTranslation) {
    Sphere s;
    s.withTransformation(Transformations::translate(0, 1, 0));
    auto normal = s.getNormalAt({ 0, 1.70711, -0.70711, 1.0 });
    EXPECT_NEAR(normal.x, 0, PRECISION);
    EXPECT_NEAR(normal.y, 0.70711, PRECISION);
    EXPECT_NEAR(normal.z, -0.70711, PRECISION);
    EXPECT_NEAR(normal.w, 0, PRECISION);
}

TEST(SphereTest, normalAtWithScaling) {
    Sphere s;
    s.withTransformation(
            Transformations::scale(1, 0.5, 1)
            * Transformations::rotate(PI / 5.0f, { 0, 0, 1 })
    );
    auto normal = s.getNormalAt({ 0, sqrt(2) / 2.0f, -sqrt(2) / 2.0f, 1.0 });
    EXPECT_NEAR(normal.x, 0, PRECISION);
    EXPECT_NEAR(normal.y, 0.97014, PRECISION);
    EXPECT_NEAR(normal.z, -0.24254, PRECISION);
    EXPECT_NEAR(normal.w, 0, PRECISION);
}