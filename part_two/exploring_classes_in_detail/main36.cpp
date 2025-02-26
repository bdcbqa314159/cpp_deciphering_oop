#include <iostream>
using std::cout, std::endl, std::string;

struct student
{
    string name;
    float gpa{};
    void initialize(string, float);
    void print();
};

class University
{
public:
    string name;
    int numOfStudents{};
    void initialize(string, int);
    void print();
};

int main()
{
    student s1;
    s1.initialize("Gabby Donne", 4.);
    s1.print();

    University u1;
    u1.initialize("GWU", 25340);
    u1.print();

    University *u2 = new University;
    u2->initialize("UMD", 40500);
    u2->print();

    delete u2;

    return 0;
}

void student::initialize(string name, float gpa)
{
    this->name = name;
    this->gpa = gpa;
}

void student::print()
{
    cout << "student: " << name << " with gpa: " << gpa << endl;
}

void University::initialize(string name, int numOfStudents)
{
    this->name = name;
    this->numOfStudents = numOfStudents;
}

void University::print()
{
    cout << "university: " << name << " with number of students: " << numOfStudents << endl;
}