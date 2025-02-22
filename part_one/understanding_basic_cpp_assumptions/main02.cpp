#include <iostream>
#include <iomanip>

int main()
{
    char name[20]; // overflow risk here.
    float gpa{};

    std::cout << "Please enter a name and a gpa...\n";
    std::cout << ">>> ";
    std::cin >> std::setw(20) >> name >> gpa;

    std::cout << "Hello " << name << std::flush;
    std::cout << ". GPA is " << gpa << "\n";

    return 0;
}