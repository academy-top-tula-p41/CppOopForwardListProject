#include <iostream>
#include "ForwardList.h"

int main()
{
    ForwardList<int> list;
    list.PushFront(100);
    list.PushFront(200);
    list.PushFront(300);
    list.PushFront(400);
    list.PushFront(500);

    for (auto iterator = list.GetIterator(); !iterator.IsEnd(); iterator.Next())
        std::cout << iterator.Current() << "\n";
    std::cout << "\n";

    auto iterator = list.Find(200);
    if (!iterator.IsEnd())
        iterator = list.Insert(iterator, 1000);
    
    for (auto it = list.GetIterator(); !it.IsEnd(); it.Next())
        std::cout << it.Current() << "\n";
    std::cout << "\n";

    iterator = list.GetIterator();
    
    iterator = iterator + 2;
    std::cout << iterator.Current() << "\n";

    int value = list.Erase(iterator);
    std::cout << "Erase value: " << value << "\n\n";

    for (auto it = list.GetIterator(); !it.IsEnd(); it.Next())
        std::cout << it.Current() << "\n";
    std::cout << "\n";

}
