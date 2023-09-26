#if !defined(__SKIP_LIST_HPP__)
#define __SKIP_LIST_HPP__

#include <forward_list>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>

template <typename T>
class SkipListNode
{
public:
    T data;
    std::list<SkipListNode<T> *> vertical_navigation; // List of pointers to nodes in the next level
};

template <typename T>
class SkipListLevel
{
public:
    using _SkipListLevelIterator = typename std::forward_list<SkipListNode<T> *>::iterator;
    std::forward_list<SkipListNode<T> *> level; // List of pointers to nodes in this level
};

template <typename T>
class SkipList
{
protected:
    std::vector<SkipListLevel<T>> head;

    bool CoinFlip(SkipListNode<T> *) const;
    bool AddElementAfterNode(T data, SkipListNode<T> *node);
    SkipListNode<T> *FindNewElementPosition(T data);

public:
    using SkipListHeadReverseIterator = typename std::vector<SkipListLevel<T>>::reverse_iterator;
    using SkipListLevelIterator = typename SkipListLevel<T>::_SkipListLevelIterator;

    bool AddElement(T data);
    bool RemoveElement(T data);
    SkipListNode<T> *Find(T data);

    SkipList(int max_level);
};

#endif //! defined(__SKIP_LIST_HPP__)