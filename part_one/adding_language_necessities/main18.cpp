#include <iostream>

using std::cout, std::endl;

int my_max(double, double);

int main()
{
    int result{};
    int m = 6, n = 10;
    double x = 5.7, y = 9.89;

    result = my_max(m, n);

    cout << "result is " << result << "\n";
    cout << "max is " << my_max(x, y);

    return 0;
}

int my_max(double a, double b)
{
    return (a < b) ? b : a;
}