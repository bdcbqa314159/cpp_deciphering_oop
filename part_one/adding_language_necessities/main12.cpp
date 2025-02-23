#include <iostream>
#include <iomanip>
#include <cstring>

using std::cout, std::cin, std::endl, std::setw;

const int MAX = 50;
constexpr int LARGEST = 50;

constexpr int my_minimum(int a, int b)
{
    return (a < b) ? a : b;
}

int main()
{
    int x{}, y{};
    constexpr int a = 10, b = 15;

    cout << "Enter two <int> type numbers >> ";
    cin >> x >> y;

    const int min = my_minimum(x, y);

    cout << "the minimum between " << x << " and " << y << " is: " << my_minimum(x, y) << "\n";

    constexpr int other_min = my_minimum(a, b);

    cout << "the minimum between " << a << " and " << b << " is: " << my_minimum(a, b) << "\n";

    char bigName[MAX] = {""};
    char largeName[LARGEST] = {""};

    cout << "Enter two names: \n>> ";
    cin >> setw(MAX) >> bigName >> setw(LARGEST) >> largeName;
    const int nameLen = strlen(bigName);

    cout << "length no.1: " << nameLen << "\n";
    cout << "length no.2: " << strlen(largeName) << "\n";

    return 0;
}