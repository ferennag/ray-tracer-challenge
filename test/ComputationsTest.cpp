#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "../src/raytracer/Computations.h"
#include "../src/raytracer/shapes/Plane.h"

TEST(Computations, reflectVector) {
    auto shape = Plane();
    auto ray = Ray({ 0, 1, -1 }, { 0, -sqrt(2) / 2, sqrt(2) / 2 });
    Intersections is;
    is.addIntersection(&shape, sqrt(2));
    auto comps = prepareComputations(is, ray);
    EXPECT_NEAR(comps.reflect.x, 0, PRECISION);
    EXPECT_NEAR(comps.reflect.y, sqrt(2) / 2, PRECISION);
    EXPECT_NEAR(comps.reflect.z, sqrt(2) / 2, PRECISION);
}