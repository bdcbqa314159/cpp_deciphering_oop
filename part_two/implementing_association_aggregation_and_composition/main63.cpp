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

class Student;
class University
{
private:
    string name;
    static constexpr int MAX = 25;
    Student *studentBody[MAX] = {};
    int currentNumStudents{};

public:
    University();
    University(const string &);
    University(const University &);
    ~University();

    void enrollStudent(Student *);
    const string &getName() const { return name; }
    void printStudents() const;
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
    University *univ = nullptr;

public:
    Student();
    Student(const string &, const string &, char, const string &, float, const string &, const string &, University *);
    Student(const Student &);

    ~Student() override;

    void earnPHD();

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const;
    const string &getUniversity() const;

    void setCurrentCourse(const string &newCourse) { currentCourse = newCourse; }

    void print() const override;
    void isA() const override;

    static int getNumOfStudents();
};

int Student::numOfStudents = 0;

int main()
{
    University u1("The George Washington University");
    Student s1("Gabby", "Doone", 'A', "Miss", 3.85, "C++", "4225GWU", &u1);
    Student s2("Giselle", "LeBrun", 'A', "Ms.", 3.45,
               "C++", "1227GWU", &u1);
    Student s3("Eve", "Kendall", 'B', "Ms.", 3.71, "C++",
               "5542GWU", &u1);
    cout << s1.getFirstName() << " " << s1.getLastName();
    cout << " attends " << s1.getUniversity() << endl;
    cout << s2.getFirstName() << " " << s2.getLastName();
    cout << " attends " << s2.getUniversity() << endl;
    cout << s3.getFirstName() << " " << s3.getLastName();
    cout << " attends " << s3.getUniversity() << endl;
    u1.printStudents();

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

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course, const string &id, University *univ) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id)
{
    this->univ = univ;
    univ->enrollStudent(this);
    numOfStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
    this->univ = s.univ;
    univ->enrollStudent(this);
    numOfStudents++;
}

Student::~Student()
{
    numOfStudents--;
    univ = nullptr;
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

const string &Student::getUniversity() const
{
    return univ->getName();
}

University::University() {}

University::University(const string &n) : name(n) {}

University::~University()
{
    for (int i = 0; i < MAX; ++i)
        studentBody[i] = nullptr;
}

void University::enrollStudent(Student *s)
{
    studentBody[currentNumStudents++] = s;
}

void University::printStudents() const
{
    cout << name << " has the following students: \n";
    for (int i = 0; i < currentNumStudents; ++i)
    {
        cout << "\t" << studentBody[i]->getFirstName();
        cout << " " << studentBody[i]->getLastName() << endl;
    }
}