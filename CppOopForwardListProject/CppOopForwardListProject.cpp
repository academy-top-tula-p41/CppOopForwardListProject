#include <iostream>
#include "ForwardList.h"

int main()
{
    ForwardList<int> list;
    list.PushFront(100);
    list.PushFront(200);
    list.PushFront(300);

    for (auto iterator = list.GetIterator(); !iterator.IsEnd(); iterator.Next())
        std::cout << iterator.Current() << "\n";

}
