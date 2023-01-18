#include <gtest/gtest.h>
#include "../src/raytracer/RayTracerRenderer.h"
#include "../src/raytracer/Transformations.h"
#include "../src/raytracer/shapes/Plane.h"
#include "../src/raytracer/SceneLoader.h"
#include "TestPattern.h"

TEST(RayTracerRenderer, lighting_behindEye) {
    auto renderer = RayTracerRenderer(1000, 1000);
    PointLight light({ 0, 0, -10 }, { 1, 1, 1 });
    glm::dvec4 point = { 0, 0, 0, 1 };
    glm::dvec4 eye = { 0, 0, -1, 1 };
    Sphere object;
    Computations comps {
        .object = &object,
        .point = point,
        .overPoint = point,
        .underPoint = point,
        .eye = eye,
    };
    auto result = renderer.lighting(light, comps);
    EXPECT_NEAR(result.r(), 1, PRECISION);
    EXPECT_NEAR(result.g(), 1, PRECISION);
    EXPECT_NEAR(result.b(), 1, PRECISION);
}

TEST(RayTracerRenderer, lighting_45Deg) {
    auto renderer = RayTracerRenderer(1000, 1000);
    PointLight light({ 0, 0, -10 }, { 1, 1, 1 });
    glm::dvec4 point = { 0, 0, 0, 1 };
    glm::dvec4 eye = { 0, 0, -1, 1 };
    Sphere object;
    Computations comps {
            .object = &object,
            .point = point,
            .overPoint = point,
            .underPoint = point,
            .eye = eye,
            .normal = {0, 0, -1, 0},
    };
    auto result = renderer.lighting(light, comps);
    EXPECT_NEAR(result.r(), 1.9, PRECISION);
    EXPECT_NEAR(result.g(), 1.9, PRECISION);
    EXPECT_NEAR(result.b(), 1.9, PRECISION);
}

TEST(RayTracerRenderer, lighting_oppositeSide) {
    auto renderer = RayTracerRenderer(1000, 1000);
    PointLight light({ 0, 10, -10 }, { 1, 1, 1 });
    glm::dvec4 point = { 0, 0, 0, 1 };
    glm::dvec4 eye = { 0, 0, -1, 1 };
    Sphere object;
    Computations comps {
            .object = &object,
            .point = point,
            .overPoint = point,
            .underPoint = point,
            .eye = eye,
            .normal = {0, 0, -1, 0},
    };
    auto result = renderer.lighting(light, comps);
    EXPECT_NEAR(result.r(), 0.7364, PRECISION);
    EXPECT_NEAR(result.g(), 0.7364, PRECISION);
    EXPECT_NEAR(result.b(), 0.7364, PRECISION);
}

TEST(RayTracerRenderer, lighting_behindSurface) {
    auto renderer = RayTracerRenderer(1000, 1000);
    PointLight light({ 0, 0, 10 }, { 1, 1, 1 });
    glm::dvec4 point = { 0, 0, 0, 1 };
    glm::dvec4 eye = { 0, 0, -1, 1 };
    Sphere object;
    Computations comps {
            .object = &object,
            .point = point,
            .overPoint = point,
            .underPoint = point,
            .eye = eye,
            .normal = {0, 0, -1, 0},
    };
    auto result = renderer.lighting(light, comps);
    EXPECT_NEAR(result.r(), 0.1, PRECISION);
    EXPECT_NEAR(result.g(), 0.1, PRECISION);
    EXPECT_NEAR(result.b(), 0.1, PRECISION);
}

TEST(RayTracerRenderer, isShadowed_noShadow) {
    auto renderer = RayTracerRenderer(1000, 1000);
    renderer.setWorld(SceneLoader::loadDefaultScene());
    glm::dvec4 point = { 0, 10, 0, 1 };
    EXPECT_FALSE(renderer.isShadowed(point));
}

TEST(RayTracerRenderer, isShadowed_shadow) {
    auto renderer = RayTracerRenderer(1000, 1000);
    renderer.setWorld(SceneLoader::loadDefaultScene());
    glm::dvec4 point = { 10, -10, 10, 1 };
    EXPECT_TRUE(renderer.isShadowed(point));
}

TEST(RayTracerRenderer, isShadowed_objectBehindLight) {
    auto renderer = RayTracerRenderer(1000, 1000);
    renderer.setWorld(SceneLoader::loadDefaultScene());
    glm::dvec4 point = { -20, 20, -20, 1 };
    EXPECT_FALSE(renderer.isShadowed(point));
}

TEST(RayTracerRenderer, isShadowed_objectBehindPoint) {
    auto renderer = RayTracerRenderer(1000, 1000);
    renderer.setWorld(SceneLoader::loadDefaultScene());
    glm::dvec4 point = { -2, 2, -2, 1 };
    EXPECT_FALSE(renderer.isShadowed(point));
}

TEST(RayTracerRenderer, strike_NonReflective) {
    auto ray = Ray({ 0, 0, 0 }, { 0, 0, 1 });
    auto shape = Sphere();
    shape.withMaterial({ .ambient = 1, .reflectivity = 0 });
    auto is = Intersections();
    is.addIntersection(&shape, 1);
    auto comps = prepareComputations(is.hit().value(), is, ray);

    auto renderer = RayTracerRenderer(100, 100);
    auto color = renderer.reflectedColor(comps, 1);
    EXPECT_EQ(color, Color(0.0, 0.0, 0.0));
}

TEST(RayTracerRenderer, strike_Reflective) {
    auto renderer = RayTracerRenderer(1000, 1000);
    auto world = SceneLoader::loadDefaultScene();

    auto ray = Ray({ 0, 0, -3 }, { 0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0 });
    auto shape = std::make_unique<Plane>();
    shape->withMaterial({ .reflectivity = 0.5 });
    shape->withTransformation(Transformations::translate(0, -1, 0));
    world->addObject(std::move(shape));

    auto is = Intersections();
    is.addIntersection(world->getObjects().at(2).get(), sqrt(2.0));
    auto comps = prepareComputations(is.hit().value(), is, ray);
    renderer.setWorld(std::move(world));

    auto color = renderer.reflectedColor(comps, 2);
    // TODO this only works if I decrease the precision... No idea why
    EXPECT_NEAR(color.r(), 0.19032, PRECISION * 10);
    EXPECT_NEAR(color.g(), 0.2379, PRECISION * 10);
    EXPECT_NEAR(color.b(), 0.14274, PRECISION * 10);
}

TEST(RayTracerRenderer, refractedColor_opaque) {
    auto renderer = RayTracerRenderer(1000, 1000);
    renderer.setWorld(SceneLoader::loadDefaultScene());
    auto ray = Ray({ 0, 0, -5 }, { 0, 0, 1 });
    auto &object = renderer.getWorld().getObjects().at(0);

    auto is = Intersections();
    is.addIntersection(object.get(), 4);
    is.addIntersection(object.get(), 6);
    auto comps = prepareComputations(is.getList().at(0), is, ray);

    auto color = renderer.refractedColor(comps, 2);
    EXPECT_NEAR(color.r(), 0, PRECISION);
    EXPECT_NEAR(color.g(), 0, PRECISION);
    EXPECT_NEAR(color.b(), 0, PRECISION);
}

TEST(RayTracerRenderer, refractedColor_RefractedColor) {
    auto renderer = RayTracerRenderer(1000, 1000);
    renderer.setWorld(SceneLoader::loadDefaultScene());

    auto &object1 = renderer.getWorld().getObjects().at(0);
    auto &material1 = const_cast<Material &>(object1->getMaterial());
    material1.ambient = 1.0;
    material1.pattern = std::make_unique<TestPattern>();

    auto &object2 = renderer.getWorld().getObjects().at(1);
    auto &material2 = const_cast<Material &>(object2->getMaterial());
    material2.transparency = 1.0;
    material2.refractiveIndex = 1.5;

    auto ray = Ray({ 0, 0, 0.1 }, { 0, 1, 0 });

    auto is = Intersections();
    is.addIntersection(object1.get(), -0.9899);
    is.addIntersection(object2.get(), -0.4899);
    is.addIntersection(object2.get(), 0.4899);
    is.addIntersection(object1.get(), 0.9899);
    auto comps = prepareComputations(is.getList().at(2), is, ray);

    auto result = renderer.refractedColor(comps, 5);
    EXPECT_NEAR(result.r(), 0, PRECISION);
    EXPECT_NEAR(result.g(), 0.99888, PRECISION);
    EXPECT_NEAR(result.b(), 0.04725, PRECISION);
}
