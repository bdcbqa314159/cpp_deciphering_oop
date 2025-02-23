#include <iostream>

using std::cout, std::endl;

int main()
{
    void *unspecified = nullptr;
    int *x = nullptr;

    unspecified = new int;
    *(static_cast<int *>(unspecified)) = 89;

    x = static_cast<int *>(unspecified);
    cout << *x << " " << *(static_cast<int *>(unspecified)) << endl;

    delete static_cast<int *>(unspecified);

    return 0;
}