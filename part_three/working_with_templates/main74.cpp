#include <iostream>
#include <iomanip>

using std::cout, std::endl, std::to_string, std::out_of_range;

template <class Type>
class Array
{
private:
    int numElements = 0;
    Type *contents = nullptr;

public:
    Array(int size) : numElements(size), contents(new Type[size]) {}
    ~Array()
    {
        delete[] contents;
    }

    void print() const
    {
        for (int i = 0; i < numElements; ++i)
            cout << contents[i] << " ";
        cout << endl;
    }

    Type &operator[](int index)
    {
        if (index < numElements)
            return contents[i];
        else
            throw ::std::out_of_range(std::to_string(index));
    }
};

int main()
{
    Array<int> a1(3);
    try
    {
        a1[2] = 12;
        a1[1] = 70;
        a1[0] = 2;
        a1[100] = 10;
    }
    catch (const std::out_of_range &e)
    {
        cout << "Out of range: index " << e.what() << endl;
    }
    a1.print();
}