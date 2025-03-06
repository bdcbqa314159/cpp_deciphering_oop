#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>

using std::cout, std::endl, std::setprecision, std::string, std::to_string;

constexpr int MAX = 3;

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
    virtual string isA() const;
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

string Person::isA() const
{
    return "Person";
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
    const string studentId;
    static int numStudents;

public:
    Student();
    Student(const string &, const string &, char, const string &, float, const string &, const string &);
    Student(const Student &);
    ~Student() override;

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const { return studentId; }
    void setCurrentCourse(const string &);
    void print() const override;
    string isA() const override { return "Student"; }

    virtual void graduate() = 0;

    static int getNumberStudents() { return numStudents; }
};

int Student::numStudents = 0;

Student::Student() : studentId(to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

inline void Student::setCurrentCourse(const string &c)
{
    currentCourse = c;
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

void Student::print() const
{
    cout << getTitle() << " " << getFirstName() << " ";
    cout << getMiddleInitial() << ". " << getLastName();
    cout << " with id: " << studentId << " GPA: ";
    cout << setprecision(3) << " " << gpa;
    cout << endl;
}

class GradStudent : public Student
{
private:
    string degree;

public:
    GradStudent() = default;
    GradStudent(const string &, const string &, const string &, char, const string &, float, const string &, const string &);

    void earnPhD();
    string isA() const override { return "GradStudent"; }
    void graduate() override;
};

GradStudent::GradStudent(const string &deg, const string &fn, const string &ln, char mi,
                         const string &t, float avg, const string &course, const string &id) : Student(fn, ln, mi, t, avg, course, id), degree(deg)
{
}

void GradStudent::earnPhD()
{
    if (!degree.compare("PhD"))
        modifyTitle("Dr.");
}

void GradStudent::graduate()
{
    earnPhD();
    cout << "GradStudent::Graduate()" << endl;
}

class UnderGradStudent : public Student
{
private:
    string degree; // BS, BA, etc
public:
    UnderGradStudent() = default;
    UnderGradStudent(const string &, const string &, const string &, char, const string &,
                     float, const string &, const string &);

    string isA() const override { return "UnderGradStudent"; }
    void graduate() override;
};

UnderGradStudent::UnderGradStudent(const string &deg, const string &fn, const string &ln, char mi,
                                   const string &t, float avg, const string &course, const string &id) : Student(fn, ln, mi, t, avg, course, id), degree(deg)
{
}

void UnderGradStudent::graduate()
{
    cout << "UnderGradStudent::Graduate()" << endl;
}

class NonDegreeStudent : public Student
{
private:
public:
    NonDegreeStudent() = default;
    NonDegreeStudent(const string &, const string &, char, const string &, float, const string &, const string &);

    string isA() const override { return "NonDegreeStudent"; }
    void graduate() override;
};

NonDegreeStudent::NonDegreeStudent(const string &fn, const string &ln, char mi,
                                   const string &t, float avg, const string &course, const string &id) : Student(fn, ln, mi, t, avg, course, id)
{
}

void NonDegreeStudent::graduate()
{
    cout << "NonDegreeStudent::Graduate()" << endl;
}

class StudentFactory
{
public:
    Student *MatriculateStudent(const string &degree, const string &fn, const string &ln, char mi,
                                const string &t, float avg, const string &course, const string &id)
    {
        if (!degree.compare("PhD") || !degree.compare("MS") || !degree.compare("MA"))
            return new GradStudent(degree, fn, ln, mi, t, avg, course, id);
        else if (!degree.compare("BS") || !degree.compare("BA"))
            return new UnderGradStudent(degree, fn, ln, mi, t, avg, course, id);
        else if (!degree.compare("None"))
            return new NonDegreeStudent(fn, ln, mi, t, avg, course, id);
        else
            return nullptr;
    }
};

int main()
{
    Student *scholars[MAX] = {};

    StudentFactory *UofD = new StudentFactory();

    scholars[0] = UofD->MatriculateStudent("PhD", "Sara", "Kato", 'B', "Ms.", 3.9, "C++", "272PSU");
    scholars[1] = UofD->MatriculateStudent("BS", "Ana", "Sato", 'U', "Ms.", 3.8, "C++", "178PSU");
    scholars[2] = UofD->MatriculateStudent("None", "Elle", "LeBrun", 'R', "Miss", 3.5, "C++", "111BU");

    for (auto *oneStudent : scholars)
    {
        if (oneStudent)
        {
            oneStudent->graduate();
            oneStudent->print();
        }
    }

    for (auto *oneStudent : scholars)
        delete oneStudent;

    return 0;
}