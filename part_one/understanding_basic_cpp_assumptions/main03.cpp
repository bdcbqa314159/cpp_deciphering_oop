#include <iostream>

int main()
{

    int x = 0;

    std::cout << "Enter an integer...\n>>> ";
    std::cin >> x;

    if (x == 0)
        std::cout << "the integer is 0\n";
    else if (x < 0)
        std::cout << "the integer is negative\n";
    else
    {
        std::cout << "the integer is positive.\n";
        std::cout << "and 10 * " << x << " = " << 10 * x << "\n";
    }

    return 0;
}