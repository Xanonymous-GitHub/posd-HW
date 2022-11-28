#include "../../src/builder/shape_parser.h"

class ShapeParserTest : public ::testing::Test {
};

TEST_F(ShapeParserTest, ShouldCorrectlyParseSingleCircle) {
    // Arrange
    const std::string input = "Circle (Vector ((2.00, 2.00), (8.00, 2.00)))";
    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.at(0)->info(), input);
}

TEST_F(ShapeParserTest, ShouldCorrectlyParseSingleTriangle) {
    // Arrange
    const std::string input = "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))";
    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.at(0)->info(), input);
}

TEST_F(ShapeParserTest, ShouldCorrectlyParseSingleRectangle) {
    // Arrange
    const std::string input = "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))";
    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.at(0)->info(), input);
}

TEST_F(ShapeParserTest, ShouldCorrectlyParseMultipleCircles) {
    // Arrange
    // clang-format off
    const std::string input = 
        "Circle (Vector ((2.00, 7.40), (8.00, 2.00))), "
        "Circle (Vector ((-2.00, 2.00), (-8.00, 9.10)))";
    // clang-format on

    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0)->info(), "Circle (Vector ((2.00, 7.40), (8.00, 2.00)))");
    EXPECT_EQ(result.at(1)->info(), "Circle (Vector ((-2.00, 2.00), (-8.00, 9.10)))");
}

TEST_F(ShapeParserTest, ShouldCorrectlyParseMultipleTriangles) {
    // Arrange
    // clang-format off
    const std::string input = 
        "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00))), "
        "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))";
    // clang-format on

    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(1)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
}

TEST_F(ShapeParserTest, ShouldCorrectlyParseMultipleRectangles) {
    // Arrange
    // clang-format off
    const std::string input = 
        "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00))), "
        "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))";
    // clang-format on

    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
    EXPECT_EQ(result.at(1)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
}

TEST_F(ShapeParserTest, ShouldCorrectlyParseMixtureShapes) {
    // Arrange
    // clang-format off
    const std::string input = 
        "Circle (Vector ((2.00, 7.40), (8.00, 2.00))), "
        "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00))), "
        "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))";
    // clang-format on

    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result.at(0)->info(), "Circle (Vector ((2.00, 7.40), (8.00, 2.00)))");
    EXPECT_EQ(result.at(1)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(2)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
}

TEST_F(ShapeParserTest, ShouldCorrectlyParseMixtureShapesWithOneCompoundShape) {
    // Arrange
    // clang-format off
    const std::string input = 
        "Circle (Vector ((2.00, 7.40), (8.00, 2.00))), "
        "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00))), "
        "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00))), "
        "CompoundShape ("
            "Circle ("
                "Vector ((16.00, 14.00), (20.00, 14.00))"
            "), "
            "Rectangle ("
                "Vector ((0.00, 4.00), (6.00, 4.00)), "
                "Vector ((0.00, 4.00), (0.00, 8.00))"
            ")"
        ")"
        "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00))), "
        "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00))))";
    // clang-format on

    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result.at(0)->info(), "Circle (Vector ((2.00, 7.40), (8.00, 2.00)))");
    EXPECT_EQ(result.at(1)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(2)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
    EXPECT_EQ(result.at(3)->info(), "CompoundShape (Circle (Vector ((16.00, 14.00), (20.00, 14.00))), Rectangle (Vector ((0.00, 4.00), (6.00, 4.00)), Vector ((0.00, 4.00), (0.00, 8.00))))");
    EXPECT_EQ(result.at(4)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(5)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
}

TEST_F(ShapeParserTest, ShouldCorrectlyParseMixtureShapesWithComplexCompoundShapes) {
    // Arrange
    // clang-format off
    const std::string input = 
        "Circle (Vector ((2.00, 7.40), (8.00, 2.00))), "
        "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00))), "
        "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00))), "
        "CompoundShape ("
            "Circle ("
                "Vector ((16.00, 14.00), (20.00, 14.00))"
            "), "
            "Rectangle ("
                "Vector ((0.00, 4.00), (6.00, 4.00)), "
                "Vector ((0.00, 4.00), (0.00, 8.00))"
            "), "
            "CompoundShape ("
                "Circle ("
                    "Vector ((16.00, 14.00), (20.00, 14.00))"
                "), "
                "Rectangle ("
                    "Vector ((0.00, 4.00), (6.00, 4.00)), "
                    "Vector ((0.00, 4.00), (0.00, 8.00))"
                ")"
            ")"
        ")"
        "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00))), "
        "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00))))";
    // clang-format on

    ShapeParser parser{input};

    // Act
    parser.parse();

    // Expect
    auto result = parser.getResult();
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result.at(0)->info(), "Circle (Vector ((2.00, 7.40), (8.00, 2.00)))");
    EXPECT_EQ(result.at(1)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(2)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
    EXPECT_EQ(result.at(3)->info(),
              // clang-format off
        "CompoundShape ("
            "Circle ("
                "Vector ((16.00, 14.00), (20.00, 14.00))"
            "), "
            "Rectangle ("
                "Vector ((0.00, 4.00), (6.00, 4.00)), "
                "Vector ((0.00, 4.00), (0.00, 8.00))"
            "), "
            "CompoundShape ("
                "Circle ("
                    "Vector ((16.00, 14.00), (20.00, 14.00))"
                "), "
                "Rectangle ("
                    "Vector ((0.00, 4.00), (6.00, 4.00)), "
                    "Vector ((0.00, 4.00), (0.00, 8.00))"
                ")"
            ")"
        ")"
              // clang-format on
    );
    EXPECT_EQ(result.at(4)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(5)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
}
