#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>

using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::list;

constexpr int MAXCOURSES = 5, MAXSTUDENTS = 5;

enum State
{
    Initial = 0,
    Success = 1,
    Failure = 2
};
enum StudentState
{
    AddSuccess = State::Success,
    AddFailure = State::Failure
};

enum CourseState
{
    OpenForEnrollment = State::Success,
    NewSpaceAvailable = State::Success,
    Full = State::Failure
};

// class Subject;
// class Student;

class Observer
{
private:
    int observerState = State::Initial;

protected:
    Observer() = default;
    Observer(int s) : observerState(s) {}
    void setState(int s) { observerState = s; }

public:
    int getState() const { return observerState; }
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Subject
{
private:
    list<class Observer *> observers;
    int numObservers = 0;
    int subjectState = State::Initial;
    list<Observer *>::iterator newIter;

protected:
    Subject() = default;
    Subject(int s) : subjectState(s) {}
    void setState(int s) { subjectState = s; }

public:
    int getState() const { return subjectState; }
    int getNumObservers() const { return numObservers; }
    virtual ~Subject() = default;
    virtual void attach(Observer *);
    virtual void release(Observer *);
    virtual void notify();
};

void Subject::attach(Observer *ob)
{
    observers.push_back(ob);
    numObservers++;
}

void Subject::release(Observer *ob)
{
    bool found = false;

    for (auto iter = observers.begin(); iter != observers.end() && !found; ++iter)
    {
        if (*iter == ob)
        {
            newIter = observers.erase(iter);
            found = true;
            numObservers--;
        }
    }
}

void Subject::notify()
{
    for (auto iter = observers.begin(); iter != observers.end(); ++iter)
    {
        Observer *observer = *iter;
        observer->update();
        if (observer->getState() == State::Success)
        {
            iter = newIter;
            numObservers--;
        }
    }

    if (!observers.empty())
    {
        Observer *last = *newIter;
        last->update();
    }
}

class Student;
class Course : public Subject
{
private:
    string title;
    int number{};
    Student *students[MAXSTUDENTS] = {};
    int totalStudents{};

public:
    Course(const string &title, int num) : number(num)
    {
        this->title = title;
    }

    ~Course() override {}
    int getCourseNum() const { return number; }
    const string &getTitle() const { return title; }
    bool addStudent(Student *);
    void open()
    {
        setState(CourseState::OpenForEnrollment);
        notify();
    }

    void printStudents() const;
};

bool Course::addStudent(Student *s)
{
    if (totalStudents < MAXSTUDENTS)
    {
        students[totalStudents++] = s;
        return true;
    }

    else
        return false;
}

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

class Student : public Person, public Observer
{
private:
    float gpa = 0.0;
    const string studentId;
    int currentNumCourses = 0;
    Course *courses[MAXCOURSES] = {};
    Course *waitingListedCourse = nullptr;
    static int numStudents;

public:
    Student();
    Student(const string &, const string &, char, const string &, float, const string &, Course *);
    Student(const string &, const string &, char, const string &, float, const string &);
    Student(const Student &) = delete;
    ~Student() override;
    void earnPhD();

    float getGpa() const { return gpa; }
    const string &getStudentId() const { return studentId; }

    void print() const override;
    void isA() const override;
    void update() override;

    virtual void graduate();
    bool addCourse(Course *);
    void printCourses() const;

    static int getNumberStudents() { return numStudents; }
};

int Student::numStudents = 0;

Student::Student() : studentId(to_string(numStudents + 100) + "Id")
{
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &id, Course *c) : Person(fn, ln, mi, t), gpa(avg), Observer(), studentId(id), currentNumCourses(0)
{
    waitingListedCourse = c;
    c->attach(this);
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &id) : Person(fn, ln, mi, t), Observer(), gpa(avg), studentId(id), currentNumCourses(0)
{
    waitingListedCourse = nullptr;
    numStudents++;
}

Student::~Student()
{
    numStudents--;
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
    cout << endl;
}

void Student::isA() const
{
    cout << "Student" << endl;
}

bool Student::addCourse(Course *c)
{
    if (currentNumCourses < MAXCOURSES)
    {
        courses[currentNumCourses++] = c;
        c->addStudent(this);
        return true;
    }

    else
    {
        c->attach(this);
        waitingListedCourse = c;
        return false;
    }
}

void Student::graduate()
{
    cout << "Student graduates finally\n";
}

void Student::update()
{
    if ((waitingListedCourse->getState() == CourseState::OpenForEnrollment) || (waitingListedCourse->getState() == CourseState::NewSpaceAvailable))
    {

        if (addCourse(waitingListedCourse))
        {
            cout << getFirstName() << " " << getLastName() << " removed from waitlist and added to " << waitingListedCourse->getTitle() << "\n";
            setState(StudentState::AddSuccess);
            waitingListedCourse->release(this);
            waitingListedCourse = 0;
        }
    }
}

void Student::printCourses() const
{
    cout << "Student: (" << getFirstName() << " " << getLastName() << ") enrolled in: \n";
    for (int i = 0; i < MAXCOURSES && courses[i] != nullptr; ++i)
        cout << "\t" << courses[i]->getTitle() << "\n";
}

void Course::printStudents() const
{
    cout << "Course: (" << getTitle() << ") has the following students: \n";
    for (int i = 0; i < MAXSTUDENTS && students[i] != nullptr; ++i)
        cout << "\t" << students[i]->getFirstName() << " " << students[i]->getLastName() << "\n";
}

int main()
{
    Course *c1 = new Course("C++", 230);
    Course *c2 = new Course("Advanced C++", 430);
    Course *c3 = new Course("C++ Design Patterns", 550);

    Student s1("Anne", "Chu", 'M', "Ms.", 3.9, "66TU", c1);
    Student s2("Joley", "Putt", 'I', "Ms.", 3.1, "585UD", c1);
    Student s3("Goeff", "Curt", 'K', "Mr.", 3.1, "667UD", c1);
    Student s4("Ling", "Mau", 'I', "Ms.", 3.1, "55TU", c1);
    Student s5("Jiang", "Wu", 'Q', "Dr.", 3.8, "88TU", c1);

    cout << "Registration is Open" << "\n";
    cout << "Waitlist Students to be added to Courses" << endl;
    c1->open();
    c2->open();
    c3->open();

    cout << "During open registration, Students now adding more courses" << endl;
    s1.addCourse(c2);
    s2.addCourse(c2);
    s4.addCourse(c2);
    s5.addCourse(c2);

    s1.addCourse(c3);
    s3.addCourse(c3);
    s5.addCourse(c3);

    cout << "Registration complete" << endl;
    c1->printStudents();
    c2->printStudents();
    c3->printStudents();

    s1.printCourses();
    s2.printCourses();
    s3.printCourses();
    s4.printCourses();
    s5.printCourses();

    delete c1;
    delete c2;
    delete c3;

    return 0;
}