#include <iostream>
#include <iomanip>
using std::cout, std::cin, std::endl, std::string, std::to_string, std::setprecision;

class Person
{
private:
    string firstName, lastName, title;
    char middleInitial = '\0';

protected:
    void modifyTitle(const string &);

public:
    Person() = default;
    Person(const string &, const string &, const string &, char);
    Person(const Person &) = default;
    ~Person() = default;

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }
};

class Student : public Person
{
private:
    float gpa{};
    string currentCourse;
    const string studentId;
    static int numStudents;

public:
    Student();
    Student(const string &, const string &, const string &, char, float, const string &, const string &);
    Student(const Student &);
    ~Student();

    void print() const;
    void earnPHD();

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const { return studentId; }

    void setCurrentCourse(const string &);
    static int getNumberStudents();
};

int Student::numStudents = 0;

int main()
{
    Student s1("Jo", "Li", "Ms.", 'U', 3.8, "C++", "178PSU");

    s1.print();
    s1.setCurrentCourse("Doctoral Thesis");
    s1.earnPHD();
    s1.print();
    cout << "Total number of students: " << Student::getNumberStudents() << endl;

    return 0;
}

Person::Person(const string &fn, const string &ln, const string &title, char mi) : firstName(fn), lastName(ln), title(title), middleInitial(mi) {}

void Person::modifyTitle(const string &newTitle)
{
    title = newTitle;
}

inline void Student::setCurrentCourse(const string &course)
{
    currentCourse = course;
}

inline int Student::getNumberStudents()
{
    return numStudents;
}

Student::Student() : studentId(to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

Student::Student(const string &fn, const string &ln, const string &t, char mi, float avg, const string &course, const string &id) : Person(fn, ln, t, mi), gpa(avg), currentCourse(course), studentId(id)
{
    numStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
    numStudents++;
}

Student::~Student()
{
    numStudents--;
}

void Student::print() const
{
    cout << getFirstName() << " " << getMiddleInitial() << ". " << getLastName() << endl;
    cout << "id: " << getStudentId() << " with gpa: " << setprecision(2) << getGpa() << endl;
    cout << " course: " << currentCourse << endl;
}

void Student::earnPHD()
{
    modifyTitle("Dr.");
}
