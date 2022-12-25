#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include <typeinfo>

class GrabCommandTest : public ::testing::Test {
protected:
    const double DEVIATION = 0.0001;
    const double mouseX = 85.23;
    const double mouseY = 232.7;
    MockDragAndDrop dad{};
    CommandHistory history{};
    GrabCommand cmd{&dad, &history};
};

TEST_F(GrabCommandTest, executeShouldCallGrabMethodWithCorrectMousePosition) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();
    EXPECT_NEAR(mouseX, dad.getGrabX(), DEVIATION);
    EXPECT_NEAR(mouseY, dad.getGrabY(), DEVIATION);
}

TEST_F(GrabCommandTest, undoShouldCallMoveAndDropMethodWithCorrectMousePosition) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();
    cmd.undo();
    EXPECT_NEAR(mouseX, dad.getDropX(), DEVIATION);
    EXPECT_NEAR(mouseY, dad.getDropY(), DEVIATION);
    EXPECT_NEAR(mouseX, dad.getMoveX(), DEVIATION);
    EXPECT_NEAR(mouseY, dad.getMoveY(), DEVIATION);
}

TEST_F(GrabCommandTest, historyShouldSaveExecutedGrabCmd) {
    MousePosition::getInstance()->setPos(mouseX, mouseY);
    cmd.execute();

    const auto storedCmds = history.getHistory();
    ASSERT_FALSE(storedCmds.empty());

    const auto justAddedCmd = static_cast<MacroCommand *>(storedCmds.top());
    ASSERT_TRUE(justAddedCmd != nullptr);
    EXPECT_TRUE(typeid(justAddedCmd) == typeid(MacroCommand *));

    const auto justAddedAtomicCmds = justAddedCmd->getCommands();
    ASSERT_FALSE(justAddedAtomicCmds.empty());

    const auto justAddedGrabCmd = static_cast<GrabCommand *>(justAddedAtomicCmds[0]);
    EXPECT_TRUE(typeid(justAddedGrabCmd) == typeid(GrabCommand *));
    EXPECT_NEAR(mouseX, justAddedGrabCmd->getX(), DEVIATION);
    EXPECT_NEAR(mouseY, justAddedGrabCmd->getY(), DEVIATION);
}

TEST_F(GrabCommandTest, addCommandShouldThrow) {
    const auto mockCmd = new MockCommand{};
    EXPECT_THROW(cmd.addCommand(mockCmd), Command::FailedToAddCommandException);
    delete mockCmd;
}

TEST_F(GrabCommandTest, getCommandShouldThrow) {
    EXPECT_THROW(cmd.getCommands(), Command::FailedToGetCommandException);
}
