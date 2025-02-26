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
    const char *studentId = nullptr;
    static int numStudents;

public:
    Student();
    Student(const string &, const string &, char, float, const string &, const char *id);
    Student(const Student &);
    ~Student();
    void print() const;

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    char getMiddleInitial() const { return middleInitial; }
    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const char *getStudentId() const { return studentId; }

    void setCurrentCourse(const string &);
    static int getNumberStudents();
};

int Student::numStudents = 0;

int main()
{
    Student s1("Nick", "Cole", 'S', 3.65, "C++", "112HAV");
    Student s2("Alex", "Tost", 'A', 3.78, "C++", "674HOP");
    cout << s1.getFirstName() << " " << s1.getLastName();
    cout << " Enrolled in " << s1.getCurrentCourse();
    cout << endl;
    cout << s2.getFirstName() << " " << s2.getLastName();
    cout << " Enrolled in " << s2.getCurrentCourse();
    cout << endl;

    cout << "There are " << Student::getNumberStudents();
    cout << " students" << endl;

    return 0;
}

inline int Student::getNumberStudents()
{
    return numStudents;
}

Student::Student()
{
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, float aGpa, const string &course, const char *id) : firstName(fn), lastName(ln), middleInitial(mi), gpa(aGpa), currentCourse(course), studentId(id)
{

    char *temp = new char[strlen(id) + 1];
    strcpy(temp, id);
    studentId = temp;

    numStudents++;
}

Student::Student(const Student &other) : firstName(other.firstName), lastName(other.lastName), middleInitial(other.middleInitial), gpa(other.gpa), currentCourse(other.currentCourse)
{
    delete studentId;
    char *temp = new char[strlen(other.studentId) + 1];
    strcpy(temp, other.studentId);
    studentId = temp;
    numStudents++;
}

inline void Student::setCurrentCourse(const string &course)
{
    currentCourse = course;
}

Student::~Student()
{
    delete[] studentId;
    numStudents--;
}

void Student::print() const
{
    cout << firstName << " " << middleInitial << ". " << lastName << "\n";
    cout << "gpa: " << gpa << "\n";
    cout << "enrolled in: " << currentCourse << "\nstudent id: " << studentId << "\n";
}
