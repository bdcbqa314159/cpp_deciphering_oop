#include <iostream>

int minimum(int a, int b);

int main()
{
    int x{}, y{};
    std::cout << "Enter two integers: \n >> ";
    std::cin >> x >> y;
    std::cout << "The minimum is " << minimum(x, y) << "\n";

    return 0;
}

int minimum(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}