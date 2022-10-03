#include "../../src/iterator/null_iterator.h"

class NullIteratorTest : public ::testing::Test {
protected:
    NullIterator null_it_{};
};

TEST_F(NullIteratorTest, ShouldThrowWhenFirstIsCalled) {
    EXPECT_THROW({ null_it_.first(); }, Iterator::MethodShouldNotBeRunError);
}

TEST_F(NullIteratorTest, ShouldThrowWhenNextIsCalled) {
    EXPECT_THROW({ null_it_.next(); }, Iterator::MethodShouldNotBeRunError);
}

TEST_F(NullIteratorTest, ShouldThrowWhenCurrentItemIsCalled) {
    EXPECT_THROW({ null_it_.currentItem(); }, Iterator::MethodShouldNotBeRunError);
}

TEST_F(NullIteratorTest, ShouldAlwaysBeDone) {
    EXPECT_TRUE(null_it_.isDone());
}
