#include <iostream>

using std::cout, std::endl;

int main()
{
    int x = 10;
    int *p = new int;
    *p = 20;

    int &refInt1 = x;
    int &refInt2 = *p;

    cout << x << " " << *p << endl;
    cout << refInt1 << " " << refInt2 << endl;

    refInt1++;
    refInt2++;

    cout << x << " " << *p << endl;
    cout << refInt1 << " " << refInt2 << endl;

    delete p;

    return 0;
}