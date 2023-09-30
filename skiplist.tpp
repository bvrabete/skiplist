
#if !defined(__SKIP_LIST_CPP__)
#define __SKIP_LIST_CPP__

#include <stdexcept>
#include <string>
#include <iomanip>

#include "skiplist.hpp"

template <typename T>
SkipList<T>::SkipList(int max_level)
{
    if (max_level < 2)
    {

        // Head is empty
        // Throw an exception
        throw std::runtime_error(std::string("Incorrect head level size"));
    }

    // Initialise the head
    for (int i = 0; i < max_level; i++)
    {
        head.push_back(SkipListLevel<T>());
    }

    // Initialise the random number generator
    std::srand(static_cast<int>(std::time(nullptr)));

    list_max_level = max_level;
}

template <typename T>
SkipList<T>::~SkipList()
{
    // Delete the node data using the pointers from the first level

    for (auto it = head[0].level.begin(); it != head[0].level.end(); ++it)
    {
        delete (*it);
    }

    // Remove all elements from each level
    for (auto head_it = head.begin(); head_it != head.end(); ++head_it)
    {
        head_it->level.clear();
    }

    head.clear();
}

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
    SkipListNode<T> *newNode = new SkipListNode<T>(data);

    if (node == nullptr)
    {
        // Empty list
        // Add data to each level on the first position

        for (auto head_it = head.begin(); head_it != head.end(); ++head_it)
        {
            (*head_it).level.push_front(newNode);

            newNode->vertical_navigation.push_back((*head_it).level.begin());
        }

        return true;
    }

    auto it = head[0].level.insert(std::next(node->vertical_navigation[0]), newNode);
    newNode->vertical_navigation.push_back(it);

    for (int i = 1; i < list_max_level; i++)
    {
        if (!CoinFlip(node))
        {
            // Stop adding levels
            break;
        }

        // newNode->vertical_navigation.push_back(head[i].level.begin());
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
    int level_id = head.size() - 1;
    if (level_id < 0)
    {
        // Head is empty
        // Throw an exception
        throw std::runtime_error(std::string("Incorrect head level size"));
    }

    SkipListNode<T> *insertAfter = nullptr;

    // Start searching from the last level

    auto start = head.back().level.begin();

    for (auto head_it = head.rbegin(); head_it != head.rend(); ++head_it)
    {
        // for each level
        insertAfter = nullptr;

        if (head_it->level.size() > 0)
        {
            auto it = std::lower_bound(start, head_it->level.end(), data, compare<T>);

            if (it != head_it->level.end())
            {
                insertAfter = *it;
            }
            else
            {
                insertAfter = head_it->level.back();
            }
        }

        if (!insertAfter)
        {
            // the new element is smaller than all the other elements in the list

            // Stop here and add it to the beginning of the list
            break;
        }

        if (level_id > 0)
        {
            start = insertAfter->vertical_navigation[level_id - 1]; // or next element from here?
        }

        level_id--;
    }

    // if element is nullptr, then the list is empty or the new element needs to be added as
    // the first element in the list
    return insertAfter;
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

    // Binary search using custom comparison function
    auto it = std::lower_bound(head[0].level.begin(), head[0].level.end(), data, compare<T>);
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
    if (position)
    {
        std::cout << "Inserting " << data << " after " << position->data << std::endl;
    }
    else
    {
        std::cout << "Inserting " << data << " at the beginning" << std::endl;
    }

    return AddElementAfterNode(data, position);
}

template <typename T>
void SkipList<T>::Print()
{
    std::cout << std::endl;
    std::cout << "List content begin" << std::endl;

    for (int i = list_max_level - 1; i >= 0; i--)
    {
        std::cout << "Level " << std::setw(3) << std::setfill('0') << i << ": ";

        for (auto it = head[i].level.begin(); it != head[i].level.end(); ++it)
        {
            std::cout << (*it)->data << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "List content end" << std::endl;
    std::cout << std::endl;
}

#endif //! defined(__SKIP_LIST_CPP__)