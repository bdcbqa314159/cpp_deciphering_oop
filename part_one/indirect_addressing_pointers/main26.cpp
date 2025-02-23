#include <iostream>
#include <iomanip>

using std::cout, std::cin, std::endl, std::flush, std::setw;

constexpr int MAX = 20;
[[nodiscard]] char *createName();

int main()
{
    char *name = nullptr;
    name = createName();

    cout << "name: " << name << "\n";
    delete[] name;

    return 0;
}

[[nodiscard]] char *createName()
{
    char *temp = new char[MAX];
    cout << "Enter name\n>>> " << flush;
    cin >> setw(MAX) >> temp;
    return temp;
}