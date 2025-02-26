#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl, std::string;

class Student
{
private:
    string firstName, lastName;
    char middleInitial{'\0'};
    float gpa{};
    string currentCourse;
    const int studentId = 0;

public:
    Student() = default;
    Student(const string &, const string &, char, float, const string &, int);
    Student(const Student &);
    ~Student() = default;
    void print() const;

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    char getMiddleInitial() const { return middleInitial; }
    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }

    void setCurrentCourse(const string &);
};

int main()
{
    Student s1("Zack", "Moon", 'R', 3.75, "C++", 1378);
    cout << s1.getFirstName() << " " << s1.getLastName();
    cout << " Enrolled in " << s1.getCurrentCourse();
    cout << endl;
    s1.setCurrentCourse("Advanced C++ Programming");
    cout << s1.getFirstName() << " " << s1.getLastName();
    cout << " New course: " << s1.getCurrentCourse();
    cout << endl;
    const Student s2("Gabby", "Doone", 'A', 4.0,
                     "C++", 2239);
    s2.print();

    return 0;
}

Student::Student(const string &fn, const string &ln, char mi, float aGpa, const string &course, int id) : firstName(fn), lastName(ln), middleInitial(mi), gpa(aGpa), currentCourse(course), studentId(id) {}

Student::Student(const Student &other) : firstName(other.firstName), lastName(other.lastName), middleInitial(other.middleInitial), gpa(other.gpa), currentCourse(other.currentCourse), studentId(other.studentId) {}

inline void Student::setCurrentCourse(const string &course)
{
    currentCourse = course;
}

void Student::print() const
{
    cout << firstName << " " << middleInitial << ". " << lastName << "\n";
    cout << "gpa: " << gpa << "\n";
    cout << "enrolled in: " << currentCourse << "\nstudent id: " << studentId << "\n";
}
