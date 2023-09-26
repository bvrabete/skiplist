#include "skiplist.hpp"

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
            if (it->data <= data)
            {
                // Element found. Insert after it
                return it;
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
    if (Find(data) == nullptr)
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
SkipListNode<T> *SkipList<T>::Find(T data)
{
    // The level 0 holds all the list elements in the skiplist. Find the element in the skip
    // list means fiding the element in the first level
    return head[0].level.find(data);
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
    if (Find(data) != nullptr)
    {
        // Element already exists in the list. Nothing to insert
        return false;
    }

    SkipListNode<T> *newNode = new SkipListNode<T>(data);
    if (newNode == nullptr)
    {
        // Failed to allocate memory for the new node
        throw std::bad_alloc();
    }

    SkipListNode<T> *position = FindNewElementPosition(data);
    InsertAfterNode(newNode, position);

    return true;
}
