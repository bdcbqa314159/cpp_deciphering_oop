#include <iostream>

using std::cout, std::endl;

[[nodiscard]] int my_minimum(int, int);

void function_1(int);

void function_2(int);

int main()
{
    function_1(30);
    function_2(450);

    return 0;
}

[[nodiscard]] int my_minimum(int a, int b)
{
    return (a < b) ? a : b;
}

void function_2(int x)
{
    [[nodiscard]] int my_minimum(int, int arg = 90);
    cout << my_minimum(x) << endl;
}

void function_1(int x)
{
    [[nodiscard]] int my_minimum(int, int arg = 10000);
    cout << my_minimum(x) << endl;
}