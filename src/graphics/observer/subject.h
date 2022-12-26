#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "observer.h"

class Subject {
   private:
    std::vector<Observer *> _observer_$views;

   public:
    virtual ~Subject() = default;

    void attach(Observer *observer) {
        if (observer == nullptr) {
            throw ObserverNullException{"can not attach null observer"};
        }

        _observer_$views.push_back(observer);
    }

    void detach(Observer *observer) {
        if (observer == nullptr) {
            throw ObserverNullException{"can not detach null observer"};
        }

        _observer_$views.erase(std::remove(_observer_$views.begin(), _observer_$views.end(), observer), _observer_$views.cend());
    }

    void notify() const {
        for (auto &&it : _observer_$views) {
            if (it == nullptr) {
                throw ObserverNullException{"can not notify a null observer"};
            }

            it->update();
        }
    }

    std::vector<Observer *> getObservers() {
        return _observer_$views;
    }

    class ObserverNullException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};
