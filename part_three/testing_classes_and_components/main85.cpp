#include <iostream>
#include <iomanip>
#include <cstring>
#include <utility>

using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::move;

constexpr int MAX = 5;

class Person
{
private:
    string firstName, lastName;
    char middleInitial = '\0';
    char *title = nullptr;

protected:
    void modifyTitle(const string &);

public:
    Person() = default;
    Person(const string &, const string &, char, const char *);
    Person(const Person &);
    Person(Person &&);
    virtual ~Person();

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const char *getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }

    const string &setLastName(const string &);

    virtual void print() const;
    virtual void isA() const;
    virtual void greeting(const string &) const;

    Person &operator=(const Person &);
    Person &operator=(Person &&);
};

Person::Person(const string &fn, const string &ln, char mi, const char *t) : firstName(fn), lastName(ln), middleInitial(mi)
{
    title = new char[strlen(t) + 1];
    strcpy(title, t);
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial)
{
    cout << "Person copy constructor\n";
    title = new char[strlen(p.title) + 1];
    strcpy(title, p.title);
}

Person::Person(Person &&p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial), title(p.title)
{
    cout << "Person move copy constructor\n";
    p.firstName.clear();
    p.lastName.clear();
    p.middleInitial = '\0';
    p.title = nullptr;
}

Person::~Person()
{
    cout << "Person destructor\n";
    delete[] title;
}

void Person::modifyTitle(const string &newTitle)
{
    delete title;
    title = new char[strlen(newTitle.c_str()) + 1];
    strcpy(title, newTitle.c_str());
}

const string &Person::setLastName(const string &ln)
{
    lastName = ln;
    return lastName;
}

void Person::print() const
{
    if (title)
        cout << title << " ";
    if (!firstName.empty())
        cout << firstName << " ";
    else
        cout << "No first name ";
    if (middleInitial != '\0')
        cout << middleInitial << ". ";
    if (!lastName.empty())
        cout << lastName << " ";
    else
        cout << "No last name ";
}

void Person::isA() const
{
    cout << "Person\n";
}

void Person::greeting(const string &msg) const
{
    cout << msg << endl;
}

Person &Person::operator=(const Person &p)
{
    cout << "person assignement operator\n";

    if (this != &p)
    {
        delete[] title;
        firstName = p.firstName;
        lastName = p.lastName;
        middleInitial = p.middleInitial;
        title = new char[strlen(p.title) + 1];
        strcpy(title, p.title);
    }

    return *this;
}

Person &Person::operator=(Person &&p)
{
    cout << "person assignement operator\n";

    if (this != &p)
    {
        delete[] title;
        firstName = p.firstName;
        p.firstName.clear();
        lastName = p.lastName;
        p.lastName.clear();
        middleInitial = p.middleInitial;
        p.middleInitial = '\0';
        title = p.title;
        p.title = nullptr;
    }

    return *this;
}

class Student : public Person
{
private:
    float gpa{};
    string currentCourse;
    const char *studentId = nullptr;
    static int numStudents;

public:
    Student();
    Student(const string &, const string &, char, const char *, float, const string &, const char *);

    Student(const Student &);
    Student(Student &&);

    ~Student() override;

    void earnPHD();
    float getGPA() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const char *getStudentId() const { return studentId; }
    void setCurrentCourse(const string &);

    void print() const override;
    void isA() const override;

    Student &operator=(const Student &);
    Student &operator=(Student &&);
    static int getNumberStudents() { return numStudents; }
};

int Student::numStudents = 0;

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

int main()
{
    // Show default, copy, assignment operator, and virtual destructor.
    // Also show move copy and move assignment.

    // Simple cases of move, without inheritance
    Person p1("Alexa", "Gutierrez", 'R', "Ms.");
    p1.print();
    Person p2(std::move(p1)); // move copy constructor
    p1.print();
    p2.print();
    Person p3 = std::move(p2); // this is an initialization (not assignment) and calls move copy constructor
    p2.print();
    p3.print();

    Person p5("Xander", "LeBrun", 'R', "Dr.");
    p5.print();
    p5 = std::move(p3); // move assignment, in place of original instance
    p3.print();
    p5.print();

    // More complex cases, demonstrates uses of canonical form with inherited classes
    Student s0;                                                                           // default constructor
    Student s1("Jules", "Martinez", 'M', "Ms.", 3.2, "C++", "3562UD");                    // alternate constructor
    Person *p4 = new Student("George", "Valente", 'Q', "Mr.", 3.5, "Adv. C++", "1178UD"); // note: upcast to a base type

    cout << "Copy constructor" << endl;
    Student s2(s1); // copy constructor
    s1.print();
    s2.print();
    s1.setLastName("Martin");
    s2.setLastName("Martine");
    s1.print();
    s2.print();

    cout << "Move copy constructor" << endl;
    Student s3(std::move(s1)); // Move constructor
    s3.print();
    s1.print();
    s3.setLastName("Jonez");
    s1.setLastName("Jones");
    s3.print();
    s1.print();

    cout << "Overloaded assignment operator" << endl;
    s0 = s3; // overloaded assignment operator
    s0.print();
    s3.print();
    s0.setLastName("Smith");
    s3.setLastName("Smythe");
    s0.print();
    s3.print();

    cout << "Overloaded move assignment operator" << endl;
    s2 = std::move(s3);
    s2.print();
    s3.print();
    s2.setLastName("Green");
    s3.setLastName("Greene");
    s2.print();
    s3.print();

    cout << "Destructor sequences" << endl;
    delete p4; // This truly points to a Student, so we'll see virtual destruction sequence in action

    return 0;
}