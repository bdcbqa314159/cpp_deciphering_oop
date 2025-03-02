#include <iostream>
#include <iomanip>

using std::cout, std::endl;

template <class Type1, class Type2>
Type2 chooseFirst(Type1, Type2);

template <class Type1, class Type2>
Type2 chooseFirst(Type1 x, Type2 y)
{
    if (x < y)
        return static_cast<Type2>(x);
    else
        return y;
}

int main()
{
    int value1 = 4, value2 = 7;
    float value3 = 5.67f;
    cout << "First: " << chooseFirst(value1, value3) << endl;
    cout << "First: " << chooseFirst(value2, value1) << endl;
}