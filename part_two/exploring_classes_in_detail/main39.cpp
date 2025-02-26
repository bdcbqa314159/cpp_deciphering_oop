#include <iostream>
using std::cout, std::endl, std::string;

class University
{
    string name;
    int numOfStudents{};

public:
    University() = default;
    University(const string &, int);
    void print();
    void cleanUp();
};

int main()
{
    University u1;
    University u2("University of Delaware", 23800);
    University u3{"Temple University", 20500};
    u1.print();
    u2.print();
    u3.print();
    u1.cleanUp();
    u2.cleanUp();
    u3.cleanUp();

    return 0;
}

University::University(const string &name, int numOfStudents)
{
    this->name = name;
    this->numOfStudents = numOfStudents;
}

void University::print()
{
    cout << "university: " << name << " with number of students: " << numOfStudents << endl;
}

void University::cleanUp()
{
    name.clear();
    numOfStudents = 0;
}