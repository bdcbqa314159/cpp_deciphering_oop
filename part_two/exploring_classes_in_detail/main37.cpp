#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl, std::string;

class Student
{
public:
    string firstName, lastName;
    char middleInitial{};
    float gpa{};
    char *currentCourse = nullptr;

    void initialize(string, string, char, float, const char *);
    void print();
};

int main()
{
    Student s1;
    Student *s2 = new Student;
    s1.initialize("Mary", "Jacobs", 'I', 3.9, "C++");
    s2->initialize("Sam", "Nelson", 'B', 3.2, "C++");
    s1.print();
    s2->print();
    delete[] s1.currentCourse;
    delete[] s2->currentCourse;
    delete s2;
    return 0;

    return 0;
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

void Student::print()
{
    cout << firstName << " " << middleInitial << ". " << lastName << "\n";
    cout << "gpa: " << gpa << "\n";
    cout << "enrolled in: " << currentCourse << "\n";
}
