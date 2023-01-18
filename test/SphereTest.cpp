#include <gtest/gtest.h>
#include "../src/raytracer/shapes/Sphere.h"
#include "../src/raytracer/Transformations.h"

TEST(Sphere, withDefaultMaterial) {
    Sphere s;
    Material m;
    EXPECT_NEAR(s.getMaterial().ambient, m.ambient, PRECISION);
    EXPECT_NEAR(s.getMaterial().diffuse, m.diffuse, PRECISION);
    EXPECT_NEAR(s.getMaterial().specular, m.specular, PRECISION);
    EXPECT_EQ(s.getMaterial().color, m.color);
}

TEST(Sphere, normalAt) {
    Sphere s;
    auto normal = s.getNormalAt({ 1, 0, 0, 1.0 });
    EXPECT_NEAR(normal.x, 1, PRECISION);
    EXPECT_NEAR(normal.y, 0, PRECISION);
    EXPECT_NEAR(normal.z, 0, PRECISION);
    EXPECT_NEAR(normal.w, 0, PRECISION);
}

TEST(Sphere, normalAtNonAxial) {
    auto x = sqrt(3) / 3;

    Sphere s;
    auto normal = s.getNormalAt({ x, x, x, 1.0 });
    EXPECT_NEAR(normal.x, x, PRECISION);
    EXPECT_NEAR(normal.y, x, PRECISION);
    EXPECT_NEAR(normal.z, x, PRECISION);
    EXPECT_NEAR(normal.w, 0, PRECISION);
}

TEST(Sphere, normalAtIsNormalized) {
    Sphere s;
    auto normal = s.getNormalAt({ 1, 0, 0, 1.0 });
    auto normalized = glm::normalize(normal);
    EXPECT_NEAR(normal.x, normalized.x, PRECISION);
    EXPECT_NEAR(normal.y, normalized.y, PRECISION);
    EXPECT_NEAR(normal.z, normalized.z, PRECISION);
    EXPECT_NEAR(normal.w, normalized.w, PRECISION);
}

TEST(Sphere, normalAtWithTranslation) {
    Sphere s;
    s.withTransformation(Transformations::translate(0, 1, 0));
    auto normal = s.getNormalAt({ 0, 1.70711, -0.70711, 1.0 });
    EXPECT_NEAR(normal.x, 0, PRECISION);
    EXPECT_NEAR(normal.y, 0.70711, PRECISION);
    EXPECT_NEAR(normal.z, -0.70711, PRECISION);
    EXPECT_NEAR(normal.w, 0, PRECISION);
}

TEST(Sphere, normalAtWithScaling) {
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