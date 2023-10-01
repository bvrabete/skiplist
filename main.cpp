#include <iostream>

#include "skiplist.hpp"

int main(void)
{
    const int MAX_LEVEL = 5;
    const std::vector<long> data = {13, 63, 22, 4, 75, 22};

    SkipList<long> skiplist(static_cast<int>(MAX_LEVEL));

    for (int i = 0; i < data.size(); i++)
    {
        skiplist.AddElement(data[i]);

        skiplist.Print();
    }

    skiplist.RemoveElement(data[0]);

    skiplist.RemoveElement(27);

    skiplist.Print();

    return 0;
}
