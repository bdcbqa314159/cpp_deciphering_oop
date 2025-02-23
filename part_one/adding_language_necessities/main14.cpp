#include <iostream>

using std::cout, std::endl;

[[nodiscard]] int my_minimum(int arg1, int arg2); // the names here are ignored.

int main()
{
    int x = 10, y = 89;
    cout << my_minimum(x, y) << endl;

    return 0;
}

[[nodiscard]] int my_minimum(int a, int b)
{
    return (a < b) ? a : b;
}