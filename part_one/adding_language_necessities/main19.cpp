#include <iostream>

using std::cout, std::endl;

int my_maximum(int, int);
float my_maximum(float, float);

int main()
{
    char a = 'A', b = 'B';
    int m = 10, n = 6;
    float x = 9.1, y = 31.2;

    cout << "max is " << my_maximum(a, b) << endl;
    cout << "max is " << my_maximum(m, n) << endl;
    cout << "max is " << my_maximum(x, y) << endl;

    /*
    The following creates an ambiguous situation:
    cout << "max is " << my_maximum(a, y) << endl;
    */

    cout << "max is " << my_maximum(static_cast<float>(a), y) << endl;

    return 0;
}

int my_maximum(int a, int b)
{
    return (a < b) ? b : a;
}

float my_maximum(float a, float b)
{
    return (a < b) ? b : a;
}