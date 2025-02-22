#include <iostream>

class Student
{
public:
    std::string name;
    float semesterGrades[5];
    float gpa;
};

int main()
{
    Student s1;
    s1.name = "George Katz";
    s1.semesterGrades[0] = 3.;
    s1.semesterGrades[1] = 4.;

    s1.gpa = 3.5;

    std::cout << "the student:\n";
    std::cout << s1.name << "\nhas a gpa of " << s1.gpa << "\n";

    return 0;
}