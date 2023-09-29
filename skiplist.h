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

    SkipList(int max_level)
    {
        for (int i = 0; i < max_level; i++)
        {
            head.push_back(SkipListLevel<T>());
        }

        // Initialise the random number generator
        std::srand(static_cast<int>(std::time(nullptr)));

        list_max_level = max_level;
    }
};

/**
 * Adds an element after a given node in the SkipList.
 *
 * @param data The data to be added.
 * @param node The node after which the element should be added. If `nullptr`, the element will be added to the first column of the skiplist.
 *
 * @return `true` if the element is successfully added.
 *
 * @throws None.
 */
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

/**
 * Find the position of a new element in the SkipList.
 *
 * @param data the data of the new element
 *
 * @return a pointer to the SkipListNode representing the position of the new element
 *
 * @throws None
 */
template <typename T>
SkipListNode<T> *SkipList<T>::FindNewElementPosition(T data)
{
    SkipListNode<T> *element = nullptr;

    int level_id = head.size() - 1;

    for (auto head_it = head.rbegin(); head_it != head.rend(); ++head_it)
    {
        auto start = head_it->level.begin();

        for (auto it = start; it != head_it->level.end(); ++it)
        {
            if ((*it)->data <= data)
            {
                element = *it;
                start = element->vertical_navigation[level_id];
                break;
            }
        }

        level_id--;
    }

    // if (element == nullptr)
    // {
    //     // Empty list
    //     // Add data to each level on the first position
    //     SkipListNode<T> *node = new SkipListNode<T>(list_max_level);

    //     for (auto head_it = head.rbegin(); head_it != head.rend(); ++head_it)
    //     {
    //         SkipListNode<T> *it = head_it->level.push_front(node);
    //         node->vertical_navigation[0] = it;
    //     }

    //     return node;
    // }

    // Element position found

    return element;
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
    if (Find(data))
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
    auto compare = [](const SkipListNode<T> *node, const T &value)
    {
        return node->data < value;
    };

    // Binary search using custom comparison function
    auto it = std::lower_bound(head[0].level.begin(), head[0].level.end(), data, compare);
    // Check if the element was found
    return it != head[0].level.end() && (*it)->data == data;
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

/**
 * Adds an element to the SkipList.
 *
 * @param data the data to be added to the SkipList
 *
 * @return true if the element was successfully added, false if the element already exists in the list
 *
 * @throws None
 */
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