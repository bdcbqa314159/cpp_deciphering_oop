#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl, std::string;

class Student
{
private:
    string firstName, lastName;
    char middleInitial{};
    float gpa{};
    char *currentCourse = nullptr;

public:
    void initialize();
    void initialize(string, string, char, float, const char *);
    void cleanUp();
    void print();
};

int main()
{
    Student s1;

    s1.initialize("Ming", "Li", 'I', 3.9, "C++");
    s1.print();

    s1.cleanUp();
    return 0;
}

void Student::initialize()
{
    firstName.clear();
    lastName.clear();
    middleInitial = '\0';
    gpa = 0.;
    currentCourse = nullptr;
}

void Student::initialize(string fn, string ln, char mi, float gpa, const char *course)
{
    firstName = fn;
    lastName = ln;
    this->middleInitial = mi;
    this->gpa = gpa;
    currentCourse = new char[strlen(course) + 1];
    strcpy(currentCourse, course);
}

void Student::cleanUp()
{
    delete[] currentCourse;
}

void Student::print()
{
    cout << firstName << " " << middleInitial << ". " << lastName << "\n";
    cout << "gpa: " << gpa << "\n";
    cout << "enrolled in: " << currentCourse << "\n";
}
