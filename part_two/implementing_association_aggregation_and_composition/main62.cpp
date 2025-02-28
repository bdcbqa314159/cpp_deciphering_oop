#include <iostream>
#include <iomanip>

using std::cout, std::endl, std::setprecision, std::string, std::to_string;

class Id final
{
private:
    string idNumber;

public:
    Id() = default;
    Id(const string &id) : idNumber(id) {}
    const string &getId() const { return idNumber; }
};

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
    Person(const Person &) = default;
    virtual ~Person() = default;

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }

    virtual void print() const;
    virtual void isA() const;
    virtual void greeting(const string &) const;
};

class Student : public Person
{
private:
    float gpa{};
    string currentCourse;
    static int numOfStudents;
    Id studentId;

public:
    Student();
    Student(const string &, const string &, char, const string &, float, const string &, const string &);
    Student(const Student &);

    ~Student() override;

    void earnPHD();

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const;

    void setCurrentCourse(const string &newCourse) { currentCourse = newCourse; }

    void print() const override;
    void isA() const override;

    static int getNumOfStudents();
};

int Student::numOfStudents = 0;

int main()
{
    Student s1("Cyrus", "Bond", 'I', "Mr.", 3.65, "C++",
               "6996CU");
    Student s2("Anne", "Brennan", 'M', "Ms.", 3.95, "C++",
               "909EU");
    cout << s1.getFirstName() << " " << s1.getLastName();
    cout << " has id #: " << s1.getStudentId() << endl;
    cout << s2.getFirstName() << " " << s2.getLastName();
    cout << " has id #: " << s2.getStudentId() << endl;

    return 0;
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

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

inline int Student::getNumOfStudents()
{
    return numOfStudents;
}

Student::Student() : studentId(to_string(numOfStudents + 100) + "Id")
{
    numOfStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course, const string &id) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id)
{
    numOfStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
    numOfStudents++;
}

Student::~Student()
{
    numOfStudents--;
    cout << "destructor: " << getFirstName() << " " << getLastName() << "\n";
}

void Student::earnPHD()
{
    modifyTitle("Dr.");
}

void Student::print() const
{
    cout << getTitle() << " " << getFirstName() << " " << getMiddleInitial() << ". " << getLastName() << "\n";
    cout << "with id: " << studentId.getId() << " and gpa: " << setprecision(2) << gpa << "\n";
    cout << "course: " << currentCourse << "\n";
}

void Student::isA() const
{
    cout << "Student" << endl;
}

const string &Student::getStudentId() const
{
    return studentId.getId();
}
