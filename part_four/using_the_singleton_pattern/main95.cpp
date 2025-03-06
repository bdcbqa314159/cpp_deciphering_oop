#include <iostream>
#include <list>

using std::cout, std::endl, std::string, std::list;

class Singleton;
class SingletonDestroyer;
class Person;
class President;

class SingletonDestroyer
{
private:
    Singleton *theSingleton = nullptr;

public:
    SingletonDestroyer(Singleton *s = nullptr) { theSingleton = s; }
    SingletonDestroyer(const SingletonDestroyer &) = delete;
    SingletonDestroyer &operator=(const SingletonDestroyer &) = delete;
    ~SingletonDestroyer();
    void setSingleton(Singleton *s) { theSingleton = s; }
    Singleton *getSingleton() const { return theSingleton; }
};

class Singleton
{
protected:
    static Singleton *theInstance;
    static SingletonDestroyer destroyer;

    Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    friend class SingletonDestroyer;
    virtual ~Singleton() { cout << "destructor" << endl; }
};

Singleton *Singleton::theInstance = nullptr;
SingletonDestroyer Singleton::destroyer;

SingletonDestroyer::~SingletonDestroyer()
{
    if (theSingleton == nullptr)
        cout << "SingletonDestroyer destructor: Singleton has been already destroyed" << endl;
    else
    {
        cout << "SingletonDestroyer destructor: Singleton is being destroyed" << endl;
        delete theSingleton;
    }
}

class Person
{
private:
    string firstName;
    string lastName;
    char middleInitial = '\0'; // in-class initialization -- value to be used in default constructor
    string title;              // Mr., Ms., Mrs., Miss, Dr., etc.
    string greeting;

protected:
    void modifyTitle(const string &); // Make this operation available to derived classes
public:
    Person() = default;                                           // default constructor
    Person(const string &, const string &, char, const string &); // alternate constructor
    // Remember, it is not necessary to prototype the default copy constructor
    // Person(const Person &) = default;  // copy constructor
    Person &operator=(const Person &);                       // overloaded assignment operator
    virtual ~Person();                                       // virtual destructor
    const string &getFirstName() const { return firstName; } // firstName returned as reference to const string
    const string &getLastName() const { return lastName; }   // so is lastName (via implicit cast)
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }
    void setGreeting(const string &);
    virtual const string &speak() { return greeting; } // note return type of const string & (we're no longer returning a literal)
    virtual void print() const;
};

Person::Person(const string &fn, const string &ln, char mi, const string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t), greeting("Hello")

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
        greeting = p.greeting;
    }
    return *this;
}

Person::~Person()
{
    cout << "Person destructor" << endl;
}

void Person::modifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::setGreeting(const string &newGreeting)
{
    greeting = newGreeting;
}

void Person::print() const
{
    cout << title << " " << firstName << " " << lastName << endl;
}

class President : public Person, public Singleton
{
private:
    President(const string &, const string &, char, const string &);

public:
    ~President() override;
    President(const President &) = delete;
    President &operator=(const President &) = delete;
    static President *instance(const string &, const string &, char, const string &);
};

President::President(const string &fn, const string &ln, char mi, const string &t) : Person(fn, ln, mi, t), Singleton()
{
}

President::~President()
{
    destroyer.setSingleton(nullptr);
    cout << "President destructor" << endl;
}

President *President::instance(const string &fn, const string &ln, char mi, const string &t)
{
    if (theInstance == nullptr)
    {
        theInstance = new President(fn, ln, mi, t);
        destroyer.setSingleton(theInstance);
        cout << "Creating the Singleton" << endl;
    }
    else
        cout << "Singleton previously created. Returning existing singleton" << endl;
    return dynamic_cast<President *>(theInstance);
}

int main()
{
    President *p1 = President::instance("John", "Adams", 'Q', "President");
    President *p2 = President::instance("William", "Harrison", 'H', "President");

    if (p1 == p2)
        cout << "Same instance (only one Singleton)" << endl;

    p1->print();

    return 0;
}