#include <iostream>

using std::cout, std::cin, std::endl, std::flush;

struct collection
{
    int x{};
    float y{};
};

int main()
{
    int numOfElements{};
    int *intArray = nullptr;
    collection *collectionArray = nullptr;

    cout << "how many elements would you like\n>>> " << flush;
    cin >> numOfElements;

    intArray = new int[numOfElements];
    collectionArray = new collection[numOfElements];

    for (size_t i = 0; i < numOfElements; ++i)
    {
        intArray[i] = i;
        collectionArray[i].x = i;
        collectionArray[i].y = i + 0.5;
    }

    cout << "array with int: \n";
    for (size_t i = 0; i < numOfElements; ++i)
        cout << *(intArray + i) << " ";
    cout << "\n";

    cout << "array with collections: \n";
    for (size_t i = 0; i < numOfElements; ++i)
    {
        cout << (*(collectionArray + i)).x << " " << (*(collectionArray + i)).y << "\n";
    }

    cout << "\n";

    delete[] intArray;
    delete[] collectionArray;

    return 0;
}