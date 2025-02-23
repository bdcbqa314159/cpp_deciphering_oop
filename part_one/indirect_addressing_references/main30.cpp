#include <iostream>

using std::cout, std::endl, std::string;

class Student
{
public:
    string name;
    float gpa{};
};

int main()
{
    Student s1;
    Student &studentRef1 = s1;

    s1.name = "George";
    s1.gpa = 2.3;

    std::cout << s1.name << " " << s1.gpa << "\n";
    std::cout << studentRef1.name << " " << studentRef1.gpa << "\n";

    studentRef1.name = "Mark";
    studentRef1.gpa = 3.6;

    std::cout << s1.name << " " << s1.gpa << "\n";
    std::cout << studentRef1.name << " " << studentRef1.gpa << "\n";

    return 0;
}