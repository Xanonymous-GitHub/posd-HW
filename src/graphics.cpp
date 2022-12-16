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

#include <iostream>
#include <memory>
#include <stdexcept>

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
    const std::shared_ptr<SDL> renderer = std::make_shared<SDLRenderer>(30);
    const std::shared_ptr<Canvas> canvas = std::make_shared<SDLAdapter>(1024, 768, renderer);

    ShapePrinter printer{canvas};

    for (auto &&it : shapes) {
        const auto sit = it->createIterator(IteratorFactory::getInstance("DFS"));

        if (sit->isDone()) {
            // could be a Leaf shape
            it->accept(&printer);
        } else {
            // is a CompoundShape
            for (; !sit->isDone(); sit->next()) {
                sit->currentItem()->accept(&printer);
            }
        }

        delete sit;
        it->force_cleanup_shapes();
    }

    canvas->display();
}
