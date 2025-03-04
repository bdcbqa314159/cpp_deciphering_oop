#include <iostream>
#include <iomanip>
#include <map>

using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::map, std::iterator, std::pair;

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
struct comparison // This struct represents a ‘functor’
{                 // that is, a ‘function object’
    bool operator()(const string &key1, const string &key2) const
    {
        int ans = key1.compare(key2);
        if (ans >= 0)
            return true; // return true if greater than or =
        else
            return false; // return false if they are equal or less than
    }
    // comparison() { }   // we can use default constructor and destructor
    // ~comparison() { }
};

int main()
{
    Student s1("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU");
    Student s2("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU");
    Student s3("Jill", "Long", 'R', "Dr.", 3.7, "C++", "234PSU");

    map<string, Student, comparison> studentBody;

    pair<string, Student> studentPair1(s1.getStudentId(), s1);
    pair<string, Student> studentPair2(s2.getStudentId(), s2);
    pair<string, Student> studentPair3(s3.getStudentId(), s3);

    studentBody.insert(studentPair1);
    studentBody.insert(studentPair2);
    studentBody.insert(studentPair3);

    map<string, Student, comparison>::iterator mapIter;
    mapIter = studentBody.begin();
    while (mapIter != studentBody.end())
    {
        pair<string, Student> temp = *mapIter;
        Student &tempS = temp.second;
        cout << temp.first << " " << temp.second.getFirstName();
        cout << " " << tempS.getLastName() << endl;
        ++mapIter;
    }

    for (auto &[id, student] : studentBody)
        cout << id << " " << student.getFirstName() << " " << student.getLastName() << endl;

    return 0;
}