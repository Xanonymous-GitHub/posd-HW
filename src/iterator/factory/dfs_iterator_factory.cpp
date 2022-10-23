#include "./dfs_iterator_factory.h"
#include "../dfs_compound_iterator.h"

Iterator * DFSIteratorFactory::createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const {
    return new DFSCompoundIterator<std::list<Shape *>::const_iterator>{begin, end};
}

