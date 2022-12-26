#pragma once

#include <vector>

#include "./observer/subject.h"

class Drawing : public Subject {
   private:
    std::vector<Shape *> shapes_;

   public:
    ~Drawing() {
        for (auto &&it : shapes_) {
            if (it != nullptr) {
                delete it;
            }
        }

        shapes_.clear();
    };
};
