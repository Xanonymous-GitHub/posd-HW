#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include <typeinfo>

class CommandHistoryTest : public ::testing::Test {
protected:
    CommandHistory history{};
};

TEST_F(CommandHistoryTest, shouldCorrectlyAddCommand) {
    const auto mockCmd = new MockCommand{};
    history.addCommand(mockCmd);

    const auto storedCmds = history.getHistory();
    ASSERT_FALSE(storedCmds.empty());

    const auto justAddedCmd = storedCmds.top();
    ASSERT_TRUE(justAddedCmd != nullptr);
    EXPECT_TRUE(justAddedCmd == mockCmd);
}

TEST_F(CommandHistoryTest, shouldCorrectlyUndoCommand) {
    const auto mockCmd = new MockCommand{};
    history.addCommand(mockCmd);
    history.undo();

    EXPECT_TRUE(mockCmd->isUndoCalled());
}

TEST_F(CommandHistoryTest, shouldCallBeginMacroCorrectly) {
    history.beginMacroCommand();

    const auto storedCmds = history.getHistory();
    ASSERT_FALSE(storedCmds.empty());

    const auto justAddedCmd = static_cast<MacroCommand *>(storedCmds.top());
    ASSERT_TRUE(justAddedCmd != nullptr);
    EXPECT_TRUE(typeid(justAddedCmd) == typeid(MacroCommand *));
}

TEST_F(CommandHistoryTest, shouldEndMacroCorrectly) {
    history.beginMacroCommand();
    history.endMacroCommand();

    const auto mockCmd = new MockCommand{};
    history.addCommand(mockCmd);

    const auto storedCmds = history.getHistory();
    ASSERT_FALSE(storedCmds.empty());
    EXPECT_EQ(storedCmds.size(), 2);

    const auto justAddedCmd = storedCmds.top();
    ASSERT_TRUE(justAddedCmd != nullptr);
    EXPECT_TRUE(justAddedCmd == mockCmd);
}
