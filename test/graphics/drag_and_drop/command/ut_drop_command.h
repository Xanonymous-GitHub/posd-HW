#include "../../../../src/graphics/drag_and_drop/command/drop_command.h"
#include <typeinfo>

class DropCommandTest : public ::testing::Test {
protected:
    const double DEVIATION = 0.0001;
    const double mouseX = 85.23;
    const double mouseY = 232.7;
    MockDragAndDrop dad{};
    CommandHistory history{};
    DropCommand cmd{&dad, &history};
};

TEST_F(DropCommandTest, executeShouldCallDropMethodWithCorrectMousePosition) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();
    EXPECT_NEAR(mouseX, dad.getDropX(), DEVIATION);
    EXPECT_NEAR(mouseY, dad.getDropY(), DEVIATION);
}

TEST_F(DropCommandTest, undoShouldCallGrabMethodWithCorrectMousePosition) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();
    cmd.undo();
    EXPECT_NEAR(mouseX, dad.getGrabX(), DEVIATION);
    EXPECT_NEAR(mouseY, dad.getGrabY(), DEVIATION);
}

TEST_F(DropCommandTest, historyShouldSaveExecutedDropCmd) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();

    const auto storedCmds = history.getHistory();
    ASSERT_FALSE(storedCmds.empty());

    const auto justAddedCmd = static_cast<DropCommand *>(storedCmds.top());
    ASSERT_TRUE(justAddedCmd != nullptr);
    EXPECT_TRUE(typeid(justAddedCmd) == typeid(DropCommand *));
    EXPECT_NEAR(mouseX, justAddedCmd->getX(), DEVIATION);
    EXPECT_NEAR(mouseY, justAddedCmd->getY(), DEVIATION);
}

TEST_F(DropCommandTest, addCommandShouldThrow) {
    const auto mockCmd = new MockCommand{};
    EXPECT_THROW(cmd.addCommand(mockCmd), Command::FailedToAddCommandException);
    delete mockCmd;
}

TEST_F(DropCommandTest, getCommandShouldThrow) {
    EXPECT_THROW(cmd.getCommands(), Command::FailedToGetCommandException);
}
