#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl, std::string;

class Student
{
private:
    string firstName, lastName;
    char middleInitial{'\0'};
    float gpa{};
    char *currentCourse = nullptr;

public:
    Student() = default;
    Student(const string &, const string &, char, float, const char *);
    Student(const Student &);
    ~Student();
    void print();

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    char getMiddleInitial() const { return middleInitial; }
    float getGpa() const { return gpa; }
    const char *getCurrentCourse() const { return currentCourse; }

    void setCurrentCourse(const char *);
};

int main()
{
    Student s1("Jo", "Muritz", 'Z', 4.0, "C++");
    cout << s1.getFirstName() << " " << s1.getLastName();
    cout << " Enrolled in: " << s1.getCurrentCourse();
    cout << endl;
    s1.setCurrentCourse("Advanced C++ Programming");
    cout << s1.getFirstName() << " " << s1.getLastName();
    cout << " New course: " << s1.getCurrentCourse();
    cout << endl;

    return 0;
}

Student::Student(const string &fn, const string &ln, char mi, float gpa, const char *course)
{
    firstName = fn;
    lastName = ln;
    this->middleInitial = mi;
    this->gpa = gpa;
    currentCourse = new char[strlen(course) + 1];
    strcpy(currentCourse, course);
}

Student::Student(const Student &other)
{
    firstName = other.firstName;
    lastName = other.lastName;
    this->middleInitial = other.middleInitial;
    this->gpa = other.gpa;
    currentCourse = new char[strlen(other.currentCourse) + 1];
    strcpy(currentCourse, other.currentCourse);
}

Student::~Student()
{
    delete[] currentCourse;
}

inline void Student::setCurrentCourse(const char *course)
{
    delete[] currentCourse;
    currentCourse = new char[strlen(course) + 1];
    strcpy(currentCourse, course);
}

void Student::print()
{
    cout << firstName << " " << middleInitial << ". " << lastName << "\n";
    cout << "gpa: " << gpa << "\n";
    cout << "enrolled in: " << currentCourse << "\n";
}
