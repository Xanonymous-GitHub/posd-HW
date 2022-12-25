#include "../../../../src/graphics/drag_and_drop/command/move_command.h"
#include <typeinfo>

class MoveCommandTest : public ::testing::Test {
protected:
    const double DEVIATION = 0.0001;
    const double mouseX = 85.23;
    const double mouseY = 232.7;
    MockDragAndDrop dad{};
    CommandHistory history{};
    MoveCommand cmd{&dad, &history};
};

TEST_F(MoveCommandTest, executeShouldCalMoveMethodWithCorrectMousePosition) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();
    EXPECT_NEAR(mouseX, dad.getMoveX(), DEVIATION);
    EXPECT_NEAR(mouseY, dad.getMoveY(), DEVIATION);
}

TEST_F(MoveCommandTest, undoShouldCallMoveMethodWithCorrectMousePosition) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();
    cmd.undo();
    EXPECT_NEAR(mouseX, dad.getMoveX(), DEVIATION);
    EXPECT_NEAR(mouseY, dad.getMoveY(), DEVIATION);
}

TEST_F(MoveCommandTest, historyShouldSaveExecutedDropCmd) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();

    const auto storedCmds = history.getHistory();
    ASSERT_FALSE(storedCmds.empty());

    const auto justAddedCmd = static_cast<MoveCommand *>(storedCmds.top());
    ASSERT_TRUE(justAddedCmd != nullptr);
    EXPECT_TRUE(typeid(justAddedCmd) == typeid(MoveCommand *));
    EXPECT_NEAR(mouseX, justAddedCmd->getX(), DEVIATION);
    EXPECT_NEAR(mouseY, justAddedCmd->getY(), DEVIATION);
}

TEST_F(MoveCommandTest, addCommandShouldThrow) {
    const auto mockCmd = new MockCommand{};
    EXPECT_THROW(cmd.addCommand(mockCmd), Command::FailedToAddCommandException);
    delete mockCmd;
}

TEST_F(MoveCommandTest, getCommandShouldThrow) {
    EXPECT_THROW(cmd.getCommands(), Command::FailedToGetCommandException);
}
