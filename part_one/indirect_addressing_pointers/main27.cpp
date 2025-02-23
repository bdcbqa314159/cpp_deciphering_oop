#include <iostream>
#include <iomanip>
#include <cstring>

using std::cout, std::cin, std::endl, std::flush, std::setw;

char suffix = 'A';

const char *GenId(const char *);

int main()
{
    const char *newId1, *newId2;
    newId1 = GenId("Group");
    newId2 = GenId("Group");

    cout << "new ids: " << newId1 << " " << newId2 << "\n";

    delete[] newId1;
    delete[] newId2;

    return 0;
}

const char *GenId(const char *base)
{
    char *temp = new char[strlen(base) + 2];
    strcpy(temp, base);
    temp[strlen(base)] = suffix++;
    temp[strlen(base) + 1] = '\0';

    return temp;
}
