#include <iostream>
using std::cout, std::endl;

int main()
{
    int *ptr = nullptr;
    ptr = new int{20};

    int *&refPtr = ptr;

    cout << *ptr << " " << *refPtr << "\n";

    return 0;
}