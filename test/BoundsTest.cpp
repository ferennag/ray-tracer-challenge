#include <gtest/gtest.h>
#include "../src/engine/Bounds.h"

TEST(Bounds, creation) {
    glm::dvec4 aa = { -1, -1, -1, 1 };
    glm::dvec4 bb = { 1, 1, 1, 1 };
    Bounds b(aa, bb);
    EXPECT_EQ(b.aa, aa);
    EXPECT_EQ(b.bb, bb);
}

TEST(Bounds, split_perfectCube) {
    glm::dvec4 aa = { -1, -4, -5, 1 };
    glm::dvec4 bb = { 9, 6, 5, 1 };
    Bounds b(aa, bb);
    auto result = b.split();

    EXPECT_EQ(result.first.aa, glm::dvec4(-1, -4, -5, 1));
    EXPECT_EQ(result.first.bb, glm::dvec4(4, 6, 5, 1));
    EXPECT_EQ(result.second.aa, glm::dvec4(4, -4, -5, 1));
    EXPECT_EQ(result.second.bb, glm::dvec4(9, 6, 5, 1));
}

TEST(Bounds, split_xWideBox) {
    glm::dvec4 aa = { -1, -2, -3, 1 };
    glm::dvec4 bb = { 9, 5.5, 3, 1 };
    Bounds b(aa, bb);
    auto result = b.split();

    EXPECT_EQ(result.first.aa, glm::dvec4(-1, -2, -3, 1));
    EXPECT_EQ(result.first.bb, glm::dvec4(4, 5.5, 3, 1));
    EXPECT_EQ(result.second.aa, glm::dvec4(4, -2, -3, 1));
    EXPECT_EQ(result.second.bb, glm::dvec4(9, 5.5, 3, 1));
}

TEST(Bounds, split_yWideBox) {
    glm::dvec4 aa = { -1, -2, -3, 1 };
    glm::dvec4 bb = { 5, 8, 3, 1 };
    Bounds b(aa, bb);
    auto result = b.split();

    EXPECT_EQ(result.first.aa, glm::dvec4(-1, -2, -3, 1));
    EXPECT_EQ(result.first.bb, glm::dvec4(5, 3, 3, 1));
    EXPECT_EQ(result.second.aa, glm::dvec4(-1, 3, -3, 1));
    EXPECT_EQ(result.second.bb, glm::dvec4(5, 8, 3, 1));
}

TEST(Bounds, split_zWideBox) {
    glm::dvec4 aa = { -1, -2, -3, 1 };
    glm::dvec4 bb = { 5, 3, 7, 1 };
    Bounds b(aa, bb);
    auto result = b.split();

    EXPECT_EQ(result.first.aa, glm::dvec4(-1, -2, -3, 1));
    EXPECT_EQ(result.first.bb, glm::dvec4(5, 3, 2, 1));
    EXPECT_EQ(result.second.aa, glm::dvec4(-1, -2, 2, 1));
    EXPECT_EQ(result.second.bb, glm::dvec4(5, 3, 7, 1));
}