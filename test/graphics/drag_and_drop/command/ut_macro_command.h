#include "../../../../src/graphics/drag_and_drop/command/macro_command.h"
#include <typeinfo>

class MacroCommandTest : public ::testing::Test {
protected:
    MacroCommand macroCmd{};
};

TEST_F(MacroCommandTest, shouldCorrectlyAddCommands) {
    const auto mockCmd1 = new MockCommand{};
    const auto mockCmd2 = new MockCommand{};
    macroCmd.addCommand(mockCmd1);
    macroCmd.addCommand(mockCmd2);

    const auto storedCmds = macroCmd.getCommands();
    ASSERT_FALSE(storedCmds.empty());
    EXPECT_EQ(storedCmds.size(), 2);

    const auto lastAddedCmd = storedCmds.at(0);
    ASSERT_TRUE(lastAddedCmd != nullptr);
    EXPECT_TRUE(lastAddedCmd == mockCmd1);

    const auto firstAddedCmd = storedCmds.at(1);
    ASSERT_TRUE(firstAddedCmd != nullptr);
    EXPECT_TRUE(firstAddedCmd == mockCmd2);
}

TEST_F(MacroCommandTest, shouldCallExecuteOnEachAddedCmd) {
    const auto mockCmd1 = new MockCommand{};
    const auto mockCmd2 = new MockCommand{};
    macroCmd.addCommand(mockCmd1);
    macroCmd.addCommand(mockCmd2);

    macroCmd.execute();

    EXPECT_TRUE(mockCmd1->isExecuteCalled());
    EXPECT_TRUE(mockCmd2->isExecuteCalled());
}

TEST_F(MacroCommandTest, shouldCallUndoOnEachAddedCmd) {
    const auto mockCmd1 = new MockCommand{};
    const auto mockCmd2 = new MockCommand{};
    macroCmd.addCommand(mockCmd1);
    macroCmd.addCommand(mockCmd2);

    macroCmd.undo();

    EXPECT_TRUE(mockCmd1->isUndoCalled());
    EXPECT_TRUE(mockCmd2->isUndoCalled());
}
