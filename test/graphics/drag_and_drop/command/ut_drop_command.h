#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/drop_command.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../mock_drag_and_drop.h"

TEST(DropCommandTest, executeShouldCallDropMethodWithCorrectMousePosition) {
    MockDragAndDrop mockDragAndDrop;
    CommandHistory history;
    MousePosition::getInstance()->setPos(85.23, 232.7);
    DropCommand dropCommand(&mockDragAndDrop, &history);
    dropCommand.execute();
    ASSERT_NEAR(85.23, mockDragAndDrop.getDropX(), 0.001);
    ASSERT_NEAR(232.7, mockDragAndDrop.getDropY(), 0.001);
}
