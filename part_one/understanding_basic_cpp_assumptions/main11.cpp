#include <iostream>

using std::cout, std::endl;

namespace DataTypes
{
    int total;

    class LinkList
    {
    };

    class Stack
    {
    };
};

namespace AbstractDataTypes
{
    class Stack
    {
    };
    class Queue
    {
    };
};

namespace AbstractDataTypes
{
    int total;

    class Tree
    {
    };
};

int main()
{
    using namespace AbstractDataTypes;
    using DataTypes::LinkList;

    LinkList list;
    Stack stack;

    total = 5;

    DataTypes::total = 45;
    cout << "total: " << total << endl;
    cout << "DataTypes::total: " << DataTypes::total << endl;

    return 0;
}