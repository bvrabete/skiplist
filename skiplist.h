#if !defined(__SKIP_LIST_HPP__)
#define __SKIP_LIST_HPP__

#include <forward_list>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

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
    using SkipListLevelType = typename std::forward_list<SkipListNode<T>*>;
    SkipListLevelType level; // List of pointers to nodes in this level
};

template <typename T>
class SkipList
{

public:
    using SkipListLevelIterator = typename SkipListLevel<T>::SkipListLevelType::iterator;
    using SkipListHeadType = typename std::vector<SkipListLevel<T>>;
    using SkipListHeadReverseIterator = typename SkipListHeadType::reverse_iterator;
protected:
    SkipListHeadType head;

    bool CoinFlip(SkipListNode<T> *) const;
    bool AddElementAfterNode(T data, SkipListNode<T> *node);
    SkipListNode<T> *FindNewElementPosition(T data);

public:

    bool AddElement(T data);
    bool RemoveElement(T data);
    bool Find(T data);

    SkipList(int max_level)
    {
        for (int i = 0; i < max_level; i++)
        {
            head.push_back(SkipListLevel<T>());
        }

        // Initialise the random number generator
        std::srand(static_cast<int>(std::time(nullptr)));
    }
};

template <typename T>
bool SkipList<T>::AddElementAfterNode(T data, SkipListNode<T> *node)
{
    if (node == nullptr)
    {
        // Element needs to be added to the first column of the skiplist
        return true;
    }

    return true;
}

template <typename T>
SkipListNode<T> *SkipList<T>::FindNewElementPosition(T data)
{
    // Element not in the list. Find the element position

    for (SkipListHeadReverseIterator head_it = head.rbegin(); head_it != head.rend(); ++head_it)
    {
        // Search for the element in the current level
        for (SkipListLevelIterator it = head_it->level.begin(); it != head_it->level.end(); ++it)
        {
            if (*it.data <= data)
            {
                // Element found. Insert after it
                return it->;
            }
        }
    }

    return nullptr;
}

/**
 * Remove an element from the SkipList.
 *
 * @param data the element to be removed
 *
 * @return true if the element was successfully removed, false otherwise
 *
 * @throws None
 */
template <typename T>
bool SkipList<T>::RemoveElement(T data)
{
    if (Find(data) )
    {
        // Element not in the list. Nothing to remove
        return true;
    }

    // Remove the element from each level of the skiplist it is in
    return false;
}

/**
 * Finds the node with the specified data in the SkipList.
 *
 * @param data the data to search for in the SkipList
 *
 * @return a pointer to the SkipListNode containing the data, or nullptr if the data is not found
 *
 * @throws None
 */
template <typename T>
 bool SkipList<T>::Find(T data)
{
    // The level 0 holds all the list elements in the skiplist. Find the element in the skip
    // list means fiding the element in the first level

    // Custom comparison function
    auto compare = [](const SkipListNode<T> &node, const T &value)
    {
        return node.data < value;
    };

    // Binary search using custom comparison function
    return std::binary_search(head[0].level.begin(), head[0].level.end(), data, compare);
    
}

/**
 * Generates a random boolean value based on a coin flip.
 *
 * @param node a pointer to a SkipListNode object
 *
 * @return a boolean value representing the outcome of the coin flip
 *
 * @throws None
 */
template <typename T>
bool SkipList<T>::CoinFlip(SkipListNode<T> *) const
{
    return static_cast<bool>(std::rand() % 2);
}

template <typename T>
bool SkipList<T>::AddElement(T data)
{
    if (Find(data))
    {
        // Element already exists in the list. Nothing to insert
        return false;
    }

    SkipListNode<T> *position = FindNewElementPosition(data);
    AddElementAfterNode(data, position);

    return true;
}

#endif //! defined(__SKIP_LIST_HPP__)