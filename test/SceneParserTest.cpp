#include <gtest/gtest.h>
#include "../src/raytracer/SceneLoader.h"

TEST(SceneLoader, LoadScene) {
    auto result = SceneLoader::loadScene("../resources/test-scene.yaml");
    EXPECT_TRUE(result);

    EXPECT_EQ(1, result->getLights().size());
    EXPECT_EQ(3, result->getObjects().size());
}