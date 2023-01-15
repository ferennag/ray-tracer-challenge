#include <gtest/gtest.h>
#include "../src/raytracer/Ray.h"
#include "../src/raytracer/Transformations.h"

TEST(Ray, translateRay) {
    auto ray = Ray({ 1, 2, 3 }, { 0, 1, 0 });
    auto result = ray.transform(Transformations::translate({ 3, 4, 5 }));

    EXPECT_EQ(ray.getOrigin(), glm::vec4(1, 2, 3, 1));
    EXPECT_EQ(ray.getDirection(), glm::vec4(0, 1, 0, 0));
    EXPECT_EQ(result.getOrigin(), glm::vec4(4, 6, 8, 1));
    EXPECT_EQ(result.getDirection(), glm::vec4(0, 1, 0, 0));
}

TEST(Ray, scaleRay) {
    auto ray = Ray({ 1, 2, 3 }, { 0, 1, 0 });
    auto result = ray.transform(Transformations::scale({ 2, 3, 4 }));

    EXPECT_EQ(result.getOrigin(), glm::vec4(2, 6, 12, 1));
    EXPECT_EQ(result.getDirection(), glm::vec4(0, 3, 0, 0));
}