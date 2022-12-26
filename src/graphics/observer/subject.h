#pragma once

#include <vector>

#include "observer.h"

class Subject {
   private:
    std::vector<Observer *> _observers;

   public:
    virtual ~Subject() {}

    void attach(Observer *observer) {}

    void detach(Observer *observer) {}

    void notify() {}

    std::vector<Observer *> getObservers() {}
};
