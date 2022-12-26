#include "../../../src/graphics/observer/subject.h"
#include "./mock_observer.h"

class SubjectTest : public ::testing::Test {
   protected:
    Subject sub{};
};

TEST_F(SubjectTest, attachShouldWorkCorrectly) {
    const auto observer = new MockObserver{};
    sub.attach(observer);

    const auto justAddedObservers = sub.getObservers();
    ASSERT_FALSE(justAddedObservers.empty());

    const auto lastAddedObserver = static_cast<MockObserver*>(justAddedObservers.at(0));
    EXPECT_TRUE(lastAddedObserver != nullptr);
    EXPECT_TRUE(observer == lastAddedObserver);

    delete observer;
}

TEST_F(SubjectTest, detachShouldWorkCorrectly) {
    const auto observer = new MockObserver{};
    sub.attach(observer);
    sub.detach(observer);

    const auto justAddedObservers = sub.getObservers();
    EXPECT_TRUE(justAddedObservers.empty());

    delete observer;
}

TEST_F(SubjectTest, detachShouldThrowWhenNotFound) {
    const auto observer = new MockObserver{};
    EXPECT_THROW(sub.detach(observer), Subject::ObserverNotFoundException);

    delete observer;
}

TEST_F(SubjectTest, notifyShouldWorkCorrectly) {
    const auto observer = new MockObserver{};
    sub.attach(observer);
    sub.notify();

    EXPECT_TRUE(observer->isUpdated());

    delete observer;
}
