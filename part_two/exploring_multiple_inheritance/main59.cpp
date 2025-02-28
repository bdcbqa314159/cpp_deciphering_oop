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
    Person(const Person &) = delete;
    virtual ~Person();

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }
};

class BillableEntity
{
private:
    float invoiceAmt{};

public:
    BillableEntity() = default;
    BillableEntity(float amt) : invoiceAmt(amt) {}
    BillableEntity(const BillableEntity &) = delete;
    virtual ~BillableEntity();
    void pay(float amt) { invoiceAmt -= amt; }
    float getBalance() const { return invoiceAmt; }
    void balance() const;
};

class Student : public Person, public BillableEntity
{
private:
    float gpa{};
    string currentCourse;
    const string studentId;
    static int numOfStudents;

public:
    Student();
    Student(const string &, const string &, const string &, char, float, const string &, const string &, float);
    Student(const Student &) = delete;

    ~Student() override;

    void print() const;
    void earnPHD();

    float getGpa() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const string &getStudentId() const { return studentId; }

    void setCurrentCourse(const string &newCourse) { currentCourse = newCourse; }

    static int getNumOfStudents();
};

int Student::numOfStudents = 0;

int main()
{
    float tuition1 = 1000.00, tuition2 = 2000.00;
    Student s1("Gabby", "Doone", "Ms.", 'A', 3.9, "C++",
               "178GWU", tuition1);
    Student s2("Zack", "Moon", "Dr.", 'R', 3.9, "C++",
               "272MIT", tuition2);
    // public mbrs. of Person, BillableEntity, Student are
    // accessible from any scope, including main()
    s1.print();
    s2.print();
    cout << s1.getFirstName() << " paid $500.00" << endl;
    s1.pay(500.00);
    cout << s2.getFirstName() << " paid $750.00" << endl;
    s2.pay(750.00);
    cout << s1.getFirstName() << ": ";
    s1.balance();
    cout << s2.getFirstName() << ": ";
    s2.balance();

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

BillableEntity::~BillableEntity()
{
    cout << "BillableEntity destructor" << endl;
}

void BillableEntity::balance() const
{
    if (invoiceAmt >= 0.)
        cout << "owed amount: $ " << invoiceAmt << endl;
    else
        cout << "credit: $ " << 0. - invoiceAmt << endl;
}

inline int Student::getNumOfStudents()
{
    return numOfStudents;
}

Student::Student() : studentId(to_string(numOfStudents + 100) + "Id")
{
    numOfStudents++;
}

Student::Student(const string &fn, const string &ln, const string &t, char mi, float avg, const string &course, const string &id, float amt) : Person(fn, ln, t, mi), gpa(avg), BillableEntity(amt), currentCourse(course), studentId(id)
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
    cout << "with balance: $ " << getBalance() << "\n";
}
