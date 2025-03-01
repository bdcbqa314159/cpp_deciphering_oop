#include <iostream>
#include <iomanip>

using std::cout, std::endl, std::setprecision, std::to_string, std::string, std::set_terminate;

constexpr int MAX = 5;

void appSpecificTerminate()
{
    cout << "Uncaught exception. Program terminating" << endl;
    exit(1);
}

class Person
{
private:
    string firstName, lastName;
    char middleInitial = '\0';
    string title;

protected:
    void modifyTitle(const string &);

public:
    Person() = default;
    Person(const string &, const string &, char, const string &);
    virtual ~Person() = default;

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }

    char getMiddleInitial() const { return middleInitial; }

    virtual void print() const;
    virtual void isA() const;
    virtual void greeting(const string &) const;
};

Person::Person(const string &fn, const string &ln, char mi, const string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t) {}

void Person::modifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::print() const
{
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". " << lastName << endl;
}

void Person::isA() const
{
    cout << "Person" << endl;
}

void Person::greeting(const string &msg) const
{
    cout << msg << endl;
}

class Student : public Person
{
private:
    float gpa{};
    string currentCourse;
    const string studentId;
    static int numStudents;

public:
    Student();
    Student(const string &, const string &, char, const string &, float, const string &, const string &);
    Student(const Student &);

    ~Student() override;
    void earnPHD();

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const { return studentId; }

    void setCurrentCourse(const string &);

    void print() const override;
    void isA() const override;
    virtual void validate();
    static int getNumberStudents();
};

int Student::numStudents = 0;

inline void Student::setCurrentCourse(const string &c)
{
    currentCourse = c;
}

inline int Student::getNumberStudents()
{
    return numStudents;
}

Student::Student() : studentId(to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course, const string &id) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id)
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

void Student::earnPHD()
{
    modifyTitle("Dr.");
}

void Student::print() const
{
    cout << getTitle() << " " << getFirstName() << " ";
    cout << getMiddleInitial() << ". " << getLastName();
    cout << " with id: " << studentId << " GPA: ";
    cout << setprecision(3) << " " << gpa;
    cout << " Course: " << currentCourse << endl;
}

void Student::isA() const
{
    cout << "Student\n";
}

void Student::validate()
{
    throw string("Student does not meet prerequisites.");
}

int main()
{
    set_terminate(appSpecificTerminate);
    Student s1("Sara", "Lin", 'B', "Dr.", 3.9, "C++", "23PSU");

    try
    {
        s1.validate();
    }
    // catch (const string &err)
    // {
    //     cout << err << endl;

    //     exit(1);
    // }

    catch (float err)
    {
        cout << err << endl;
        exit(1);
    }

    cout << "Moving onward with remainder of code." << endl;

    return 0;
}