#pragma once

#include <vector>

#include "./observer/subject.h"

class Drawing : public Subject {
   private:
    std::vector<Shape *> shapes_;

   public:
    Drawing(const std::vector<Shape *> &shapes) : shapes_{shapes} {}

    ~Drawing() {
        for (auto &&it : shapes_) {
            if (it != nullptr) {
                delete it;
            }
        }

        shapes_.clear();
    };

    /**
     * Only release $views
     */
    std::vector<Shape *> shapes() {
        return shapes_;
    }
};
