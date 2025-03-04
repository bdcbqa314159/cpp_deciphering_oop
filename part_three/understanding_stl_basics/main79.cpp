#include <iostream>
#include <iomanip>
#include <deque>

using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::deque, std::iterator;

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
    Person &operator=(const Person &);
    virtual ~Person() = default;

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }

    virtual void print() const;
    virtual void isA() const;
    virtual void greeting(const string &) const;
};

Person::Person(const string &fn, const string &ln, char mi, const string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

Person &Person::operator=(const Person &p)
{

    if (this != &p)
    {

        firstName = p.firstName;
        lastName = p.lastName;
        middleInitial = p.middleInitial;
        title = p.title;
    }
    return *this;
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

class Student : public Person
{
private:
    float gpa = 0.0;
    string currentCourse;
    string studentId;
    static int numStudents;

public:
    Student();
    Student(const string &, const string &, char, const string &, float, const string &, const string &);
    Student(const Student &);
    Student &operator=(const Student &);
    ~Student() override;
    void earnPhD();

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const { return studentId; }
    void setCurrentCourse(const string &); // prototype only

    void print() const override;
    void isA() const override;

    static int getNumberStudents() { return numStudents; }
};

int Student::numStudents = 0;

inline void Student::setCurrentCourse(const string &c)
{
    currentCourse = c;
}

Student::Student() : studentId(to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course,
                 const string &id) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id)
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

Student &Student::operator=(const Student &s)
{
    if (this != &s)
    {
        Person::operator=(s);

        gpa = s.gpa;
        currentCourse = s.currentCourse;
        studentId = s.studentId;
    }
    return *this;
}

void Student::earnPhD()
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
    cout << "Student" << endl;
}

bool operator<(const Student &s1, const Student &s2)
{
    return s1.getGpa() < s2.getGpa();
}

bool operator==(const Student &s1, const Student &s2)
{
    return s1.getGpa() == s2.getGpa();
}

int main()
{
    deque<Student> studentBody;
    Student s1("Tim", "Lim", 'O', "Mr.", 3.2, "C++", "111UD");

    studentBody.push_back(Student("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU"));
    studentBody.push_back(Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU"));
    studentBody.push_front(Student("Giselle", "LeBrun", 'R', "Ms.", 3.4, "C++", "299TU"));

    studentBody.insert(std::next(studentBody.begin()), Student("Anne", "Brennan", 'B', "Ms.", 3.9, "C++", "299CU"));
    studentBody[0] = s1;

    while (!studentBody.empty())
    {
        studentBody.front().print();
        studentBody.pop_front();
    }

    return 0;
}