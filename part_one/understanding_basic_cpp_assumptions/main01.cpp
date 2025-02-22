#include <iostream>

int main()
{
    char name[20]; // overflow risk here.
    int age{};

    std::cout << "Please enter a name and an age...\n";
    std::cout << ">>> ";
    std::cin >> name >> age;

    std::cout << "Hello " << name << "\n";
    std::cout << "you have " << age << " years.\n";

    return 0;
}