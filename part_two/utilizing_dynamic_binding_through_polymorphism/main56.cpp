#include <iostream>
#include <iomanip>

using std::cout, std::endl, std::string, std::setprecision, std::to_string;

constexpr int MAX = 5;

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
    virtual ~Person();

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
    const string studentId;
    static int numOfStudents;

public:
    Student();
    Student(const string &, const string &, const string &, char, float, const string &, const string &);
    Student(const Student &);

    ~Student() override;

    void earnPHD();

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const { return studentId; }

    void setCurrentCourse(const string &newCourse) { currentCourse = newCourse; }

    void print(const string &) const;
    void isA() const override;

    static int getNumOfStudents();
};

int Student::numOfStudents = 0;

int main()
{
    Person *people[MAX] = {}; // init. with nullptrs
    people[0] = new Person("Jim", "Black",
                           "Mr.", 'M');
    people[1] = new Student("Kim", "Lin", "Dr.", 'Q',
                            3.55, "C++", "334UD");
    people[1]->print(); // ok, Person::Print() defined

    (dynamic_cast<Student *>(people[1]))->print("I have to study");
    // Student stored in its own type
    Student s1("Jafari", "Kanumba", "Dr.", 'B', 3.9,
               "C++", "845BU");

    // s1.Print(); // error, base class version hidden
    s1.print("I got an A!"); // works for type Student
    s1.Person::print();      // works using scope
                             // resolution to base class type

    return 0;
}

Person::Person(const string &fn, const string &ln, const string &t, char mi) : firstName(fn), lastName(ln), title(t), middleInitial(mi) {}

Person::~Person()
{
    cout << "destructor: " << firstName << " " << lastName << "\n";
}

void Person::modifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::print() const
{
    cout << firstName << " " << middleInitial << ". " << lastName << endl;
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

Student::Student(const string &fn, const string &ln, const string &t, char mi, float avg, const string &course, const string &id) : Person(fn, ln, t, mi), gpa(avg), currentCourse(course), studentId(id)
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

void Student::print(const string &msg) const
{
    cout << "message: " << msg << endl;
    // cout << getTitle() << " " << getFirstName() << " " << getMiddleInitial() << ". " << getLastName() << "\n";
    // cout << "with id: " << studentId << " and gpa: " << setprecision(2) << gpa << "\n";
    // cout << "course: " << currentCourse << "\n";
}

void Student::isA() const
{
    cout << "Student" << endl;
}
