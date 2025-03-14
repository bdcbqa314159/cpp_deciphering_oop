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

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }

    virtual ~Person();
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

    void earnPHD();

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const { return studentId; }

    void setCurrentCourse(const string &newCourse) { currentCourse = newCourse; }

    ~Student() override;
    void print() const override;
    void isA() const override;

    static int getNumOfStudents();
};

int Student::numOfStudents = 0;

int main()
{
    Person *people[MAX] = {}; // init. with nullptrs
    people[0] = new Person("Joy", "Lin", "Ms.", 'M');
    people[1] = new Student("Renee", "Alexander",
                            "Dr.", 'Z', 3.95, "C++", "21-MIT");
    people[2] = new Student("Gabby", "Doone",
                            "Ms.", 'A', 3.95, "C++", "18-GWU");
    // In Chp. 8, we'll upgrade to a range for loop
    for (int i = 0; i < MAX; i++)
    {                     // at compile time, modified to:
        people[i]->isA(); // *(people[i]->vptr[2])()
        people[i]
            ->print();
        people[i]->greeting("Hello");
        delete people[i];
    }

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

void Student::print() const
{
    cout << getTitle() << " " << getFirstName() << " " << getMiddleInitial() << ". " << getLastName() << "\n";
    cout << "with id: " << studentId << " and gpa: " << setprecision(2) << gpa << "\n";
    cout << "course: " << currentCourse << "\n";
}

void Student::isA() const
{
    cout << "Student" << endl;
}
