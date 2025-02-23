#include <iostream>
using std::cout, std::cin, std::endl;

struct collection
{
    int x{};
    float y{};
};

void update(collection &);
void print(const collection &);

int main()
{
    collection collect1, *collect2 = nullptr;
    collect2 = new collection;

    update(collect1);
    update(*collect2);

    print(collect1);
    print(*collect2);

    delete collect2;

    return 0;
}

void update(collection &c)
{
    cout << "Enter <int> and <float> members. ";
    cin >> c.x >> c.y;
}

void print(const collection &c)
{
    cout << "status of the object:\n";
    cout << c.x << "\n"
         << c.y;
}