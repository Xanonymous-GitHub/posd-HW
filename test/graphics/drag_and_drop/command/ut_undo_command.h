#include "../../../../src/graphics/drag_and_drop/command/undo_command.h"
#include <typeinfo>

class UndoCommandTest : public ::testing::Test {
protected:
    MockDragAndDrop dad{};
    CommandHistory history{};
    UndoCommand cmd{&dad, &history};
};

TEST_F(UndoCommandTest, executeShouldCalHistoryUndo) {
    const auto mockCmd = new MockCommand{};
    history.addCommand(mockCmd);
    cmd.execute();
    EXPECT_TRUE(mockCmd->isUndoCalled());
}

TEST_F(UndoCommandTest, addCommandShouldThrow) {
    const auto mockCmd = new MockCommand{};
    EXPECT_THROW(cmd.addCommand(mockCmd), Command::FailedToAddCommandException);
    delete mockCmd;
}

TEST_F(UndoCommandTest, getCommandShouldThrow) {
    EXPECT_THROW(cmd.getCommands(), Command::FailedToGetCommandException);
}
