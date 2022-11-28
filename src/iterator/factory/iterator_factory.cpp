#include "./iterator_factory.h"

#include <cstring>
#include <list>
#include <unordered_map>

#include "../../shape.h"
#include "../iterator.h"
#include "../null_iterator.h"
#include "./bfs_iterator_factory.h"
#include "./dfs_iterator_factory.h"
#include "./list_iterator_factory.h"

std::unordered_map<std::string, std::unique_ptr<IteratorFactory>> IteratorFactory::instances_{};

Iterator *IteratorFactory::createIterator() const {
    return new NullIterator{};
}

Iterator *IteratorFactory::createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const {
    return new NullIterator{};
}

IteratorFactory *IteratorFactory::getInstance(const std::string &requested_instance_name) {
    if (HasExistingInstanceOf_(requested_instance_name)) {
        return instances_[requested_instance_name].get();
    }

    if (requested_instance_name == "DFS") {
        instances_[requested_instance_name] = std::make_unique<DFSIteratorFactory>();
    } else if (requested_instance_name == "BFS") {
        instances_[requested_instance_name] = std::make_unique<BFSIteratorFactory>();
    } else if (requested_instance_name == "List") {
        instances_[requested_instance_name] = std::make_unique<ListIteratorFactory>();
    } else {
        throw IteratorFactoryException{"Unknown iterator type"};
    }

    return instances_[requested_instance_name].get();
}

bool IteratorFactory::HasExistingInstanceOf_(const std::string &requested_instance_name) {
    return instances_.find(requested_instance_name) != instances_.cend();
}
