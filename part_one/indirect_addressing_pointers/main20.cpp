#include <iostream>

using std::cout, std::endl;

struct collection
{
    int x{};
    float y{};
};

int main()
{
    collection *item = nullptr;

    item = new collection;

    item->x = 9;
    (*item).y = 10.9;

    cout << "item x element: " << (*item).x << "\nitem y element: " << item->y << "\n";

    delete item;
    cout << "testing...\n";
    item = nullptr;

    return 0;
}