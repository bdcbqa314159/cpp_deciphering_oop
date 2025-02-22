#include <iostream>

int main()
{

    int i = 0;
    while (i < 10)
    {
        std::cout << i << "\n";
        ++i;
    }

    i = 0;
    do
    {
        std::cout << i << "\n";
        ++i;
    } while (i < 10);

    return 0;
}