#pragma once

#include <memory>

#include "../visitor/shape_printer.h"

class RealCanvas : public Observer {
   private:
    Canvas *canvas_$view_ = nullptr;
    Drawing *drawing_$view_ = nullptr;
    const std::unique_ptr<ShapePrinter> _printer;

   public:
    RealCanvas(Canvas *const canvas,
               Drawing *const drawing) : canvas_$view_{canvas},
                                         drawing_$view_{drawing},
                                         _printer{std::make_unique<ShapePrinter>(canvas)} {
        drawing_$view_->attach(this);
    }

    void update() override {
        const auto shapes = drawing_$view_->shapes();
        for (auto &&it : shapes) {
            const auto sit = it->createIterator(IteratorFactory::getInstance("DFS"));

            it->accept(_printer.get());

            for (; !sit->isDone(); sit->next()) {
                sit->currentItem()->accept(_printer.get());
            }

            delete sit;
        }
    }
};
