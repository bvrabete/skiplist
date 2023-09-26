#include <forward_list>
#include <list>
#include <vector>

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
    std::forward_list<SkipListNode<T> *> level; // List of pointers to nodes in this level
};

template <typename T>
class SkipList
{
protected:
    std::vector<SkipListLevel<T>> head;

public:
    SkipList(unsigned int max_level)
    {
        for (unsigned int i = 0; i < max_level; i++)
        {
            this->head.push_back(SkipListLevel<T>());
        }
    }

    bool AddNode(T data);
};
