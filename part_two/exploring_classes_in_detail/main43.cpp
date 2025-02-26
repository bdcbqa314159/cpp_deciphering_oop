#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl, std::string;

class University
{
private:
    char *name = nullptr;
    int numStudents{};

public:
    University() = default;
    University(const char *, int);
    University(const University &);
    ~University();

    void print();
};

int main()
{
    University u1("Temple University", 39500);
    University *u2 = new University("Boston U", 32500);
    u1.print();
    u2->print();
    delete u2;
    return 0;
}

University::University(const char *name, int numStudents)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->numStudents = numStudents;
}

University::University(const University &university)
{
    name = new char[strlen(university.name) + 1];
    strcpy(name, university.name);
    numStudents = university.numStudents;
}

University::~University()
{
    delete[] name;
    cout << "destructor called for " << this << "\n";
}

void University::print()
{
    cout << "university: " << name << "\n";
    cout << "enrollement: " << numStudents << "\n";
}