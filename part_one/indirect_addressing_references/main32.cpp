#include <iostream>

using std::cout, std::endl;

int &createId();

int main()
{
    int &id1 = createId();
    int &id2 = createId();

    cout << "Id1: " << id1 << " " << "Id2: " << id2 << "\n";
    delete &id1;
    delete &id2;

    return 0;
}

int &createId()
{
    static int count_id = 100;
    int *memory = new int;

    *memory = count_id++;
    return *memory;
}