#include <gtest/gtest.h>
#include "../src/raytracer/shapes/Cube.h"
#include "../src/raytracer/Ray.h"

struct TestCase {
    glm::dvec4 origin;
    glm::dvec4 direction;
    double t1, t2;
};

using TestCase = struct TestCase;

TEST(Cube, ray_intersect) {
    const TestCase testCases[] = {
            {
                    .origin = { 5, 0.5, 0, 1 },
                    .direction = { -1, 0, 0, 0 },
                    .t1 = 4,
                    .t2 = 6,
            },
            {
                    .origin = { -5, 0.5, 0, 1 },
                    .direction = { 1, 0, 0, 0 },
                    .t1 = 4,
                    .t2 = 6,
            },
            {
                    .origin = { 0.5, 5, 0, 1 },
                    .direction = { 0, -1, 0, 0 },
                    .t1 = 4,
                    .t2 = 6,
            },
            {
                    .origin = { 0.5, -5, 0, 1 },
                    .direction = { 0, 1, 0, 0 },
                    .t1 = 4,
                    .t2 = 6,
            },
            {
                    .origin = { 0.5, 0, 5, 1 },
                    .direction = { 0, 0, -1, 0 },
                    .t1 = 4,
                    .t2 = 6,
            },
            {
                    .origin = { 0.5, 0, -5, 1 },
                    .direction = { 0, 0, 1, 0 },
                    .t1 = 4,
                    .t2 = 6,
            },
            {
                    .origin = { 0, 0.5, 0, 1 },
                    .direction = { 0, 0, 1, 0 },
                    .t1 = -1,
                    .t2 = 1,
            },
    };

    auto cube = Cube();
    for (auto &testCase: testCases) {
        auto ray = Ray(testCase.origin, testCase.direction);
        auto intersections = cube.localIntersect(ray);
        EXPECT_EQ(intersections.getList().size(), 2);
        EXPECT_NEAR(intersections.getList()[0].distance, testCase.t1, PRECISION);
        EXPECT_NEAR(intersections.getList()[1].distance, testCase.t2, PRECISION);
    }
}

TEST(Cube, ray_miss) {
    const TestCase testCases[] = {
            {
                    .origin = { -2, 0, 0, 1 },
                    .direction = { 0.2673, 0.5345, 0.8018, 0 },
            },
            {
                    .origin = { 0, -2, 0, 1 },
                    .direction = { 0.8018, 0.2673, 0.5345, 0 },
            },
            {
                    .origin = { 0, 0, -2, 1 },
                    .direction = { 0.5345, 0.8018, 0.2673, 0 },
            },
            {
                    .origin = { 2, 0, 2, 1 },
                    .direction = { 0, 0, -1, 0 },
            },
            {
                    .origin = { 0, 2, 2, 1 },
                    .direction = { 0, -1, 0, 0 },
            },
            {
                    .origin = { 2, 2, 0, 1 },
                    .direction = { -1, 0, 0, 0 },
            },
    };

    auto cube = Cube();
    for (auto &testCase: testCases) {
        auto ray = Ray(testCase.origin, testCase.direction);
        auto intersections = cube.localIntersect(ray);
        EXPECT_EQ(intersections.getList().size(), 0);
    }
}