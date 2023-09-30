#include <iostream>

#include "skiplist.hpp"

int main(void)
{
    const int MAX_LEVEL = 5;
    const std::vector<long> data = {13, 22, 63, 4, 75};

    SkipList<long> skiplist(static_cast<int>(MAX_LEVEL));

    for (int i = 0; i < data.size(); i++)
    {
        if (!skiplist.AddElement(data[i]))
        {
            return i + 1;
        }
    }

    skiplist.RemoveElement(data[0]);

    return 0;
}
