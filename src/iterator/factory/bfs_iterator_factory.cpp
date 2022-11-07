#include "./bfs_iterator_factory.h"
#include "../bfs_compound_iterator.h"

Iterator *BFSIteratorFactory::createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const {
    return new BFSCompoundIterator<std::list<Shape *>::const_iterator>{begin, end};
}
