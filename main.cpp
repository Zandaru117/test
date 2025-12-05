#include <iostream>
#include "MyVector.hpp"
#include "MyLinkingList.hpp"
#include "MyForwardList.hpp"

void test(auto& cont, const char* name)
{
    std::cout << "=== " << name << " ===\n";

    for (int i = 0; i < 10; ++i) cont.push_back(i);

    for (auto it = cont.begin(); it != cont.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "Size: " << cont.size() << "\n";

    cont.erase(6); cont.erase(4); cont.erase(2);

    for (auto x : cont) std::cout << x << " ";
    std::cout << "\n";

    cont.insert(0, 10);
    for (auto x : cont) std::cout << x << " ";
    std::cout << "\n";

    size_t mid = cont.size() / 2;
    cont.insert(mid, 20);
    for (auto x : cont) std::cout << x << " ";
    std::cout << "\n";

    cont.push_back(30);
    for (auto x : cont) std::cout << x << " ";
    std::cout << "\n\n";
}

int main()
{
    vector<int> vec;
    list<int> lst;
    Flist<int> flst;

    test(vec, "Vector");
    test(lst, "Doubly Linked List");
    test(flst, "Singly Forward List");

    return 0;
}
