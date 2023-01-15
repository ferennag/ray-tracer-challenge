#include <gtest/gtest.h>
#include "../src/raytracer/Camera.h"
#include "../src/raytracer/RayMath.h"

TEST(Camera, pixelSizeHorizontal) {
    auto camera = Camera(200, 125, PI / 2);

    EXPECT_NEAR(camera.getPixelSize(), 0.01, 0.01);
}

TEST(Camera, pixelSizeVertical) {
    auto camera = Camera(125, 200, PI / 2);

    EXPECT_NEAR(camera.getPixelSize(), 0.01, 0.01);
}