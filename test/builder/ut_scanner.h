#include "../../src/builder/scanner.h"

class ScannerTest : public ::testing::Test {
protected:
    const double DEVIATION = 0.0001;
};

TEST_F(ScannerTest, ShouldCorrectlyFindNextToken) {
    // Arrange
    const std::string input = "Circle Rectangle ))(Circle)  ()(45.3)(),(  )";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_EQ(scanner.next(), "Circle");
    EXPECT_EQ(scanner.next(), "Rectangle");
    EXPECT_EQ(scanner.next(), ")");
    EXPECT_EQ(scanner.next(), ")");
    EXPECT_EQ(scanner.next(), "(");
    EXPECT_EQ(scanner.next(), "Circle");
    EXPECT_EQ(scanner.next(), ")");
    EXPECT_EQ(scanner.next(), "(");
    EXPECT_EQ(scanner.next(), ")");
    EXPECT_EQ(scanner.next(), "(");
    EXPECT_EQ(scanner.next(), ")");
    EXPECT_EQ(scanner.next(), "(");
    EXPECT_EQ(scanner.next(), ")");
    EXPECT_EQ(scanner.next(), ",");
    EXPECT_EQ(scanner.next(), "(");
    EXPECT_EQ(scanner.next(), ")");
}

TEST_F(ScannerTest, ShouldCorrectlyFindNextTokenWithSpaces) {
    // Arrange
    const std::string input = "Circle \nTriangle    Rectangle Vector";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_EQ(scanner.next(), "Circle");
    EXPECT_EQ(scanner.next(), "Triangle");
    EXPECT_EQ(scanner.next(), "Rectangle");
    EXPECT_EQ(scanner.next(), "Vector");
}

TEST_F(ScannerTest, ShouldCorrectlyFindNextTokenWithSpacesAndTabs) {
    // Arrange
    const std::string input = "Triangle \t     Rectangle";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_EQ(scanner.next(), "Triangle");
    EXPECT_EQ(scanner.next(), "Rectangle");
}

TEST_F(ScannerTest, ShouldCorrectlyFindNextTokenWithSomeNonCollectableTokens) {
    // Arrange
    const std::string input = "Triangle woefowifjowiejfwoi  CompoundShape";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_EQ(scanner.next(), "Triangle");
    EXPECT_EQ(scanner.next(), "CompoundShape");
}

TEST_F(ScannerTest, ShouldThrowWhileFindNextTokenWithEmptyString) {
    // Arrange
    const std::string input = "";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_THROW(scanner.next(), Scanner::ScannerTouchedTheEdgeException);
}

TEST_F(ScannerTest, ShouldThrowWhileFindNextTokenWithoutAnyToken) {
    // Arrange
    const std::string input = "wejgowejgwoiejgwoiejgow woeigwoiegjwoiegjow23gj \n\b\t\a weifjwoiefjwoeijfoweif";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_THROW(scanner.next(), Scanner::ScannerTouchedTheEdgeException);
}

TEST_F(ScannerTest, ShouldCorrectlyFindNextDoubleWithSpaces) {
    // Arrange
    const std::string input = "1.0 2.0 3.0";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_NEAR(scanner.nextDouble(), 1.0, DEVIATION);
    EXPECT_NEAR(scanner.nextDouble(), 2.0, DEVIATION);
    EXPECT_NEAR(scanner.nextDouble(), 3.0, DEVIATION);
}

TEST_F(ScannerTest, ShouldCorrectlyFindNextDoubleWithSpacesAndTabs) {
    // Arrange
    const std::string input = "1.0 \t 2.0";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_NEAR(scanner.nextDouble(), 1.0, DEVIATION);
    EXPECT_NEAR(scanner.nextDouble(), 2.0, DEVIATION);
}

TEST_F(ScannerTest, ShouldCorrectlyFindNextDoubleWithSomeNonCollectableTokens) {
    // Arrange
    const std::string input = "Triangle -2.0 woefowifjowiejfwoi 1 Rectangle";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_NEAR(scanner.nextDouble(), -2, DEVIATION);
    EXPECT_NEAR(scanner.nextDouble(), 1.0, DEVIATION);
}

TEST_F(ScannerTest, ShouldThrowWhileFindNextDoubleTokenWithEmptyString) {
    // Arrange
    const std::string input = "";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_THROW(scanner.nextDouble(), Scanner::ScannerTouchedTheEdgeException);
}

TEST_F(ScannerTest, ShouldThrowWhileFindNextDoubleTokenWithoutAnyDouble) {
    // Arrange
    const std::string input = "wejgowejgwoiejgwoiejgow Triangle woeigwoiegjwoiegjowgj \n\b\t\a weifjwoiefjwoeijfoweif";

    // Act
    Scanner scanner{input};

    // Expect
    EXPECT_THROW(scanner.nextDouble(), Scanner::ScannerTouchedTheEdgeException);
}

TEST_F(ScannerTest, ShouldThrowWhileFindNextDoubleIsDone) {
    // Arrange
    const std::string input = "Triangle 1.0, 2.0, 3.0";

    // Act
    Scanner scanner{input};
    for (int i = 0; i < 3; ++i) {
        scanner.nextDouble();
    }

    // Expect
    EXPECT_THROW(scanner.nextDouble(), Scanner::ScannerTouchedTheEdgeException);
}

TEST_F(ScannerTest, ShouldThrowWhileFindNextIsDone) {
    // Arrange
    const std::string input = "1 2 CompoundShape 3 4 5 Circle 6 7 ) 8 9 Vector 10";

    // Act
    Scanner scanner{input};
    for (int i = 0; i < 4; ++i) {
        scanner.next();
    }

    // Expect
    EXPECT_THROW(scanner.next(), Scanner::ScannerTouchedTheEdgeException);
}
