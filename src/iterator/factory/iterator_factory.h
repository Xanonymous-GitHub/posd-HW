#pragma once

#include <list>
#include <string>
#include <unordered_map>

class Iterator;
class Shape;

class IteratorFactory {
public:
    virtual Iterator *createIterator() const;

    virtual Iterator *createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const;

    static IteratorFactory *getInstance(const std::string &requested_instance_name);

    IteratorFactory(const IteratorFactory &) = delete;

    IteratorFactory &operator=(const IteratorFactory &) = delete;

    virtual ~IteratorFactory() = default;

    class IteratorFactoryException : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
    };

protected:
    IteratorFactory() = default;
    static std::unordered_map<std::string, std::unique_ptr<IteratorFactory>> instances_;

private:
    static bool HasExistingInstanceOf_(const std::string &requested_instance_name);
};
