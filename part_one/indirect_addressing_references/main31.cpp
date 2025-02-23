#include <iostream>

using std::cout, std::endl, std::flush;

void addOne(int &);
void addOne(int *);
void display(int &);

int main()
{
    int x = 10;
    int *y = nullptr;

    y = new int;
    *y = 15;

    display(x);
    display(*y);

    addOne(x);
    addOne(*y);
    display(x);
    display(*y);

    addOne(&x);
    addOne(y);
    display(x);
    display(*y);

    cout << endl;

    delete y;
    return 0;
}

void addOne(int &arg)
{
    arg++;
}

void addOne(int *arg)
{
    (*arg)++;
}

void display(int &arg)
{
    cout << arg << " " << flush;
}