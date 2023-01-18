#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "../src/raytracer/Computations.h"
#include "../src/raytracer/shapes/Plane.h"
#include "../src/raytracer/shapes/Sphere.h"
#include "../src/raytracer/Transformations.h"

TEST(Computations, reflectVector) {
    auto shape = Plane();
    auto ray = Ray({ 0, 1, -1 }, { 0, -sqrt(2) / 2, sqrt(2) / 2 });
    Intersections is;
    is.addIntersection(&shape, sqrt(2));
    auto comps = prepareComputations(is.hit().value(), is, ray);
    EXPECT_NEAR(comps.reflect.x, 0, PRECISION);
    EXPECT_NEAR(comps.reflect.y, sqrt(2) / 2, PRECISION);
    EXPECT_NEAR(comps.reflect.z, sqrt(2) / 2, PRECISION);
}

TEST(Computations, overPoint) {
    auto shape = Sphere();
    shape.withMaterial({ .transparency = 1.0, .refractiveIndex = 1.5 });
    shape.withTransformation(Transformations::translate(0, 0, 1));

    auto ray = Ray({ 0, 0, -5 }, { 0, 0, 1 });
    Intersections is;
    is.addIntersection(&shape, 5);
    auto comps = prepareComputations(is.hit().value(), is, ray);
    EXPECT_LT(comps.overPoint.z, PRECISION / 2);
    EXPECT_LT(comps.overPoint.z, comps.point.z);
}

TEST(Computations, underPoint) {
    auto shape = Sphere();
    shape.withMaterial({ .transparency = 1.0, .refractiveIndex = 1.5 });
    shape.withTransformation(Transformations::translate(0, 0, 1));

    auto ray = Ray({ 0, 0, -5 }, { 0, 0, 1 });
    Intersections is;
    is.addIntersection(&shape, 5);
    auto comps = prepareComputations(is.hit().value(), is, ray);
    EXPECT_GT(comps.underPoint.z, PRECISION / 2);
    EXPECT_GT(comps.underPoint.z, comps.point.z);
}

TEST(Computations, n1n2) {
    auto a = Sphere();
    a.withTransformation(Transformations::scale(2, 2, 2));
    a.withMaterial({ .transparency = 1.0, .refractiveIndex = 1.5 });

    auto b = Sphere();
    b.withTransformation(Transformations::translate(0, 0, -0.25));
    b.withMaterial({ .transparency = 1.0, .refractiveIndex = 2.0 });

    auto c = Sphere();
    c.withTransformation(Transformations::translate(0, 0, 0.25));
    c.withMaterial({ .transparency = 1.0, .refractiveIndex = 2.5 });

    auto ray = Ray({ 0, 0, -4 }, { 0, 0, 1 });
    Intersections is;
    is.addIntersection(&a, 2.0);
    is.addIntersection(&b, 2.75);
    is.addIntersection(&c, 3.25);
    is.addIntersection(&b, 4.75);
    is.addIntersection(&c, 5.25);
    is.addIntersection(&a, 6.0);

    auto comps1 = prepareComputations(is.getList().at(0), is, ray);
    EXPECT_NEAR(comps1.n1, 1.0, PRECISION);
    EXPECT_NEAR(comps1.n2, 1.5, PRECISION);

    auto comps2 = prepareComputations(is.getList().at(1), is, ray);
    EXPECT_NEAR(comps2.n1, 1.5, PRECISION);
    EXPECT_NEAR(comps2.n2, 2, PRECISION);

    auto comps3 = prepareComputations(is.getList().at(2), is, ray);
    EXPECT_NEAR(comps3.n1, 2, PRECISION);
    EXPECT_NEAR(comps3.n2, 2.5, PRECISION);

    auto comps4 = prepareComputations(is.getList().at(3), is, ray);
    EXPECT_NEAR(comps4.n1, 2.5, PRECISION);
    EXPECT_NEAR(comps4.n2, 2.5, PRECISION);

    auto comps5 = prepareComputations(is.getList().at(4), is, ray);
    EXPECT_NEAR(comps5.n1, 2.5, PRECISION);
    EXPECT_NEAR(comps5.n2, 1.5, PRECISION);

    auto comps6 = prepareComputations(is.getList().at(5), is, ray);
    EXPECT_NEAR(comps6.n1, 1.5, PRECISION);
    EXPECT_NEAR(comps6.n2, 1.0, PRECISION);
}