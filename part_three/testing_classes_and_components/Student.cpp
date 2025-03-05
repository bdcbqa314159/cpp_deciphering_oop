#include "Student.hpp"
#include <utility>

int Student::numStudents = 0;
using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::move;

inline void Student::setCurrentCourse(const string &c)
{
    currentCourse = c;
}

Student::Student()
{
    string tempstr = to_string(numStudents + 100) + "Id";
    char *temp = new char[tempstr.length() + 1];
    strcpy(temp, tempstr.c_str());
    studentId = temp;
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const char *t, float avg, const string &course, const char *id) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course)
{
    char *temp = new char[strlen(id) + 1];
    strcpy(temp, id);
    studentId = temp;
    numStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse)
{
    cout << "Student copy constructor\n";

    char *temp = new char[strlen(s.studentId) + 1];
    studentId = temp;
    numStudents++;
}

Student::Student(Student &&s) : Person(std::move(s)), // make sure we call base class Move copy constructor
                                gpa(s.gpa), currentCourse(s.currentCourse),
                                studentId(s.studentId) // take over source objects's resource
{
    cout << "Student move copy constructor\n";
    s.gpa = 0.;
    s.currentCourse.clear();
    s.studentId = nullptr;
    numStudents++;
}

Student::~Student()
{
    cout << "Student destructor\n";
    delete[] studentId;
    numStudents--;
}

void Student::earnPHD()
{
    modifyTitle("Dr.");
}

void Student::print() const
{

    if (getTitle())
        cout << getTitle() << " ";
    if (!getFirstName().empty())
        cout << getFirstName() << " ";
    else
        cout << "No first name" << " ";
    if (getMiddleInitial() != '\0')
        cout << getMiddleInitial() << ". ";
    if (!getLastName().empty())
        cout << getLastName();
    if (studentId)
        cout << " with id: " << studentId;
    if (gpa != 0.0)
        cout << " GPA: " << setprecision(3) << " " << gpa;
    if (!currentCourse.empty())
        cout << " Course: " << currentCourse << endl;
    else
        cout << " No current course" << endl;
}

void Student::isA() const
{
    cout << "Student" << endl;
}

// overloaded assignment operator
Student &Student::operator=(const Student &s)
{
    cout << "Student assignment operator" << endl;
    // make sure we're not assigning an object to itself
    if (this != &s)
    {
        Person::operator=(s); // call base class operator= for help

        // delete memory for existing destination data members that are pointers
        delete[] studentId;

        // for ptr data members, make a deep assignment -- reallocate memory then copy.
        // for non-ptr data members, an assignment is just fine
        gpa = s.gpa;
        currentCourse = s.currentCourse;
        // deep copy of pointer data member (use a temp since data is const and can't be directly copied into)
        char *temp = new char[strlen(s.studentId) + 1];
        strcpy(temp, s.studentId);
        studentId = temp;
    }
    return *this; // allow for cascaded assignments
}

// overloaded move assignment operator
Student &Student::operator=(Student &&s)
{
    cout << "Student Move assignment operator" << endl;
    // make sure we're not assigning an object to itself
    if (this != &s)
    {
        Person::operator=(std::move(s)); // call base class operator= for help

        // delete lhs original data members that are pointers
        delete[] studentId;

        // Take over rhs object's data members (at least those which are pointers)
        // Once data members are taken over by lhs, null out the rhs object's pointer to them
        // for non-pointer members, an assignment is fine
        gpa = s.gpa;
        s.gpa = 0.0;                     // zero out source objects data member value
        currentCourse = s.currentCourse; // take over memory from pointer data members
        s.currentCourse.clear();         // clear out original object's value
        // for ptr data members, destination data member will take over source data member's memory
        studentId = s.studentId; // this is a pointer assignment
        s.studentId = nullptr;   // null out source object's data member (so they won't share the memory)
    }
    return *this; // allow for cascaded assignments
}