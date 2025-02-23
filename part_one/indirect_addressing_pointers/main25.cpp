#include <iostream>

using std::cout, std::cin, std::endl, std::flush;

void tryToAddOne(int);
void addOne(int *);

int main()
{

    int x = 1;
    int *y = nullptr;

    y = new int{4};
    cout << x << " " << *y << endl;

    tryToAddOne(x);
    tryToAddOne(*y);

    cout << x << " " << *y << endl;

    addOne(&x);
    addOne(y);

    cout << x << " " << *y << endl;

    return 0;
}

void tryToAddOne(int x)
{
    x++;
    cout << "tryToAddOne: " << x << "\n";
}

void addOne(int *x)
{
    (*x)++;
    cout << "addOne: " << *x << "\n";
}