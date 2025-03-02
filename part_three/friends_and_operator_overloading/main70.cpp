#include <iostream>
#include <iomanip>

using std::cout, std::endl, std::setprecision, std::string, std::to_string;

class Student;

class Id
{
private:
    string idNumber;
    Student *student = nullptr;
    const string &getId() const { return idNumber; }

public:
    Id() = default;
    Id(const string &);
    void setStudent(Student *);
    friend class Student;
};

Id::Id(const string &id) : idNumber(id) {}

class Person
{
private:
    string firstName;
    string lastName;
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

Person::Person(const string &fn, const string &ln, char mi, const string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t) {}

void Person::modifyTitle(const string &newTitle)
{
    title = newTitle; // assignment between strings ensures a deep assignment
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
    static int numStudents;
    Id *studentId = nullptr;

public:
    Student();
    Student(const string &, const string &, char, const string &, float, const string &, const string &);
    Student(const Student &);
    ~Student() override;
    void earnPhD();
    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    void setCurrentCourse(const string &);

    void print() const override;
    void isA() const override;

    static int getNumberStudents() { return numStudents; }
    const string &getStudentId() const;
    friend void Id::setStudent(Student *);
};

int Student::numStudents = 0;

inline void Student::setCurrentCourse(const string &c)
{
    currentCourse = c;
}

Student::Student() : studentId(new Id(to_string(numStudents + 110) + "Id"))
{
    studentId->setStudent(this);
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course,
                 const string &id) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(new Id(id))
{
    studentId->setStudent(this);
    numStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(new Id(s.getStudentId()))
{
    studentId->setStudent(this);
    numStudents++;
}

Student::~Student()
{
    numStudents--;
    delete studentId;
}

void Student::earnPhD()
{
    modifyTitle("Dr.");
}

void Student::print() const
{
    cout << getTitle() << " " << getFirstName() << " ";
    cout << getMiddleInitial() << ". " << getLastName();
    cout << " with id: " << studentId->getId() << " GPA: "; // note GetId() is private, but we're in
    cout << setprecision(3) << " " << gpa;                  // the scope of a friend class
    cout << " Course: " << currentCourse << endl;
}

void Student::isA() const
{
    cout << "Student" << endl;
}

const string &Student::getStudentId() const
{

    return studentId->getId();
}

void Id::setStudent(Student *s)
{
    student = s;
    cout << "Set back link for " << student->getFirstName() << " with gpa: " << student->gpa << endl;
}

int main()
{
    Student s1("Cyrus", "Bond", 'I', "Mr.", 3.65, "C++", "6996CU");
    Student s2("Anne", "Brennan", 'M', "Ms.", 3.95, "C++", "909EU");

    cout << s1.getFirstName() << " " << s1.getLastName() << " has id #: ";
    cout << s1.getStudentId() << endl;

    cout << s2.getFirstName() << " " << s2.getLastName() << " has id #: ";
    cout << s2.getStudentId() << endl;

    return 0;
}