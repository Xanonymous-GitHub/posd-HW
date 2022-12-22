#include "./point.h"
#include "./two_dimensional_vector.h"

#include "./shape.h"

#include "./circle.h"
#include "./rectangle.h"
#include "./triangle.h"

#include "./compound_shape.h"

#include "./bounding_box.h"
#include "./builder/shape_parser.h"
#include "./graphics/sdl/sdl_renderer.h"
#include "./graphics/sdl_adapter.h"
#include "./iterator/bfs_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "./iterator/list_compound_iterator.h"
#include "./iterator/null_iterator.h"
#include "./utils/file_reader.h"
#include "./visitor/collision_detector.h"
#include "./visitor/shape_printer.h"

#include "./graphics/drag_and_drop/command/command_history.h"
#include "./graphics/drag_and_drop/command/drop_command.h"
#include "./graphics/drag_and_drop/command/grab_command.h"
#include "./graphics/drag_and_drop/command/move_command.h"
#include "./graphics/drag_and_drop/command/refresh_command.h"
#include "./graphics/drag_and_drop/command/undo_command.h"
#include "./graphics/drag_and_drop/drag_and_drop.h"
#include "./graphics/event_listener.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#define DEBUGMSG(msg) std::cout << msg << std::endl;

class BadArgumentException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

int main(int argc, const char *args[]) {
    if (argc < 2) {
        std::cout << "Missing the path of input.txt" << std::endl;
        throw BadArgumentException{"Missing the path of input.txt"};
    }

    const FileReader reader{args[1]};
    const auto input = reader.read();

    ShapeParser parser{input};
    parser.parse();

    const auto shapes = parser.getResult();
    const auto eventListener = std::make_unique<EventListener>();
    const std::unique_ptr<SDL> renderer = std::make_unique<SDLRenderer>(30, eventListener.get());
    const std::unique_ptr<Canvas> canvas = std::make_unique<SDLAdapter>(1024, 768, renderer.get());

    const auto dragAndDrop = std::make_unique<DragAndDrop>(shapes);
    const auto commandHistory = std::make_unique<CommandHistory>();

    eventListener->on("Left_Mouse_Down", new GrabCommand(dragAndDrop.get(), commandHistory.get()));
    eventListener->on("Left_Mouse_Move", new MoveCommand(dragAndDrop.get(), commandHistory.get()));
    eventListener->on("Left_Mouse_Up", new DropCommand(dragAndDrop.get(), commandHistory.get()));
    eventListener->on("Right_Mouse_Down", new UndoCommand(dragAndDrop.get(), commandHistory.get()));
    eventListener->on("Refresh", new RefreshCommand(canvas.get(), shapes));

    const auto VALGRIND_MODE = std::getenv("VALGRIND_MODE");
    const auto shouldStartDisplay = VALGRIND_MODE == nullptr || std::string_view(VALGRIND_MODE) != "true";

    if (shouldStartDisplay) {
        canvas->display();
    }

    for (auto &&it : shapes) {
        delete it;
    }
}