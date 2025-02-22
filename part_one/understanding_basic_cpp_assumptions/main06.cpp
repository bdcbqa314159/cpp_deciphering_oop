#include <iostream>

int main()
{

    for (int i = 0; i < 10; ++i)
    {
        std::cout << i << "\n";
        for (int j = 0; j < 10; ++j)
            std::cout << j << "\n";
        std::cout << "\n";
    }

    return 0;
}