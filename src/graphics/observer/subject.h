#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "observer.h"

class Subject {
   private:
    std::vector<Observer *> _observers;

   public:
    virtual ~Subject() = default;

    void attach(Observer *observer) {
        if (observer == nullptr) {
            throw ObserverNullException{"can not attach null observer"};
        }

        _observers.push_back(observer);
    }

    void detach(Observer *observer) {
        if (observer == nullptr) {
            throw ObserverNullException{"can not detach null observer"};
        }

        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.cend());
    }

    void notify() const {
        for (auto &&it : _observers) {
            if (it == nullptr) {
                throw ObserverNullException{"can not notify a null observer"};
            }

            it->update();
        }
    }

    std::vector<Observer *> getObservers() {
        return _observers;
    }

    class ObserverNullException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};
