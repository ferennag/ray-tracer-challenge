#include <gtest/gtest.h>
#include "../src/raytracer/SceneParser.h"

TEST(SceneParser, LoadScene) {
    SceneParser parser;
    auto result = parser.loadScene("../resources/test-scene.yaml");
    EXPECT_TRUE(result);

    EXPECT_EQ(1, result->getLights().size());
    EXPECT_EQ(3, result->getObjects().size());
}