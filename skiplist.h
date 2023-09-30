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

template <typename T>
class SkipListLevel
{
public:
    using SkipListLevelType = typename std::forward_list<SkipListNode<T> *>;
    SkipListLevelType level; // List of pointers to nodes in this level
};

template <typename T>
class SkipListNode
{
public:
    T data;
    using SkipListLevelIterator = typename SkipListLevel<T>::SkipListLevelType::iterator;
    std::vector<SkipListLevelIterator> vertical_navigation; // List of pointers to nodes in the next level
    SkipListNode(int max_level) { vertical_navigation.resize(max_level); }
};

template <typename T>
class SkipList
{

public:
    using SkipListHeadType = typename std::vector<SkipListLevel<T>>;
    using SkipListHeadReverseIterator = typename SkipListHeadType::reverse_iterator;

protected:
    SkipListHeadType head;
    // bool isEmpty();

    bool CoinFlip(SkipListNode<T> *) const;
    bool AddElementAfterNode(T data, SkipListNode<T> *node);
    SkipListNode<T> *FindNewElementPosition(T data);

public:
    bool AddElement(T data);
    bool RemoveElement(T data);
    bool Find(T data);

    int list_max_level;

    SkipList(int max_level);
};

#include "skiplist.cpp"

#endif //! defined(__SKIP_LIST_HPP__)