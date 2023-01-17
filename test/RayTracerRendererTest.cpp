#include <gtest/gtest.h>
#include "../src/raytracer/RayTracerRenderer.h"
#include "../src/raytracer/Transformations.h"
#include "../src/raytracer/shapes/Plane.h"

TEST(RayTracerRenderer, strikeNonReflective) {
    auto ray = Ray({ 0, 0, 0 }, { 0, 0, 1 });
    auto shape = Sphere();
    shape.withMaterial({ .ambient = 1, .reflectivity = 0 });
    auto is = Intersections();
    is.addIntersection(&shape, 1);
    auto comps = prepareComputations(is, ray);

    auto renderer = RayTracerRenderer(100, 100);
    auto color = renderer.reflectedColor(comps, 1);
    EXPECT_EQ(color, Color(0.0, 0.0, 0.0));
}

TEST(RayTracerRenderer, strikeReflective) {
    auto ray = Ray({ 0, 0, -3 }, { 0, -sqrt(2) / 2, sqrt(2) / 2 });
    auto shape = Plane();
    shape.withMaterial({ .ambient = 1, .reflectivity = 0.5 });
    shape.withTransformation(Transformations::translate(0, -1, 0));

    auto is = Intersections();
    is.addIntersection(&shape, sqrt(2));
    auto comps = prepareComputations(is, ray);

    auto renderer = RayTracerRenderer(1000, 1000);
    auto color = renderer.reflectedColor(comps, 2);
//    EXPECT_NEAR(color.r(), 0.19032, PRECISION);
//    EXPECT_NEAR(color.g(), 0.2379, PRECISION);
//    EXPECT_NEAR(color.b(), 0.14274, PRECISION);
}