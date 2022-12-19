#pragma once

#include "../../../iterator/factory/iterator_factory.h"
#include "../../../iterator/iterator.h"
#include "../../../shape.h"
#include "../../../visitor/shape_printer.h"
#include "../../canvas.h"
#include "command.h"
#include <memory>
#include <vector>

class RefreshCommand : public Command {
private:
    Canvas *_canvas = nullptr;
    const std::unique_ptr<ShapePrinter> _printer;
    std::vector<Shape *> _shapes;

public:
    RefreshCommand(
        Canvas *const canvas,
        const std::vector<Shape *> &shapes) : _canvas{canvas},
                                              _shapes{shapes},
                                              _printer{std::make_unique<ShapePrinter>(canvas)} {}

    void execute() override {
        for (auto &&it : _shapes) {
            const auto sit = it->createIterator(IteratorFactory::getInstance("DFS"));

            it->accept(_printer.get());

            for (; !sit->isDone(); sit->next()) {
                sit->currentItem()->accept(_printer.get());
            }

            delete sit;
        }
    }

    void undo() override {
    }
};
