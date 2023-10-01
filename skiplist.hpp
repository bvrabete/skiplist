#if !defined(__SKIP_LIST_HPP__)
#define __SKIP_LIST_HPP__

#include <forward_list>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

template <typename T>
class SkipListNode;

// Custom comparison function
template <typename T>
bool custom_compare(const SkipListNode<T> *node, const T &value)
{
    return node->data < value;
};

template <typename T>
class SkipListLevel
{
public:
    using SkipListLevelType = typename std::list<SkipListNode<T> *>;
    SkipListLevelType level; // List of pointers to nodes in this level
};

template <typename T>
class SkipListNode
{
public:
    T data;
    using SkipListLevelIterator = typename SkipListLevel<T>::SkipListLevelType::iterator;
    std::vector<SkipListLevelIterator> vertical_navigation; // List of pointers to nodes in the next level
    SkipListNode(T _data) : data(_data){};
    ~SkipListNode() { vertical_navigation.clear(); }
};

template <typename T>
class SkipList
{

public:
    using SkipListHeadType = typename std::vector<SkipListLevel<T>>;
    using SkipListHeadReverseIterator = typename SkipListHeadType::reverse_iterator;
    using SkipListLevelIterator = typename SkipListNode<T>::SkipListLevelIterator;

protected:
    SkipListHeadType head;
    int list_max_level;

    bool CoinFlip(SkipListNode<T> *) const;
    bool AddElementAfterPosition(T data, SkipListLevelIterator position);
    SkipListLevelIterator FindNewElementPosition(T data);

public:
    bool AddElement(T data);
    bool RemoveElement(T data);
    SkipListLevelIterator Find(T data);

    void Print();

    SkipList(int max_level);
    ~SkipList();
};

#include "skiplist.tpp"

#endif //! defined(__SKIP_LIST_HPP__)