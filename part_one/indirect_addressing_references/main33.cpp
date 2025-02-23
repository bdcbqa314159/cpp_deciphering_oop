#include <iostream>
using std::cout, std::endl;

int main()
{
    int x = 5;
    const int &refInt = x;

    cout << x << " " << refInt << "\n";
    // refInt++; <- illegal read only policy

    x = 90;
    cout << x << " " << refInt << "\n";

    return 0;
}