#include <iostream>

using std::cout, std::endl, std::string, std::to_string;

class Person
{
private:
    string firstName;
    string lastName;
    char middleInitial = '\0';
    string title;
    string greeting;

protected:
    void modifyTitle(const string &);

public:
    Person() = default;
    Person(const string &, const string &, char, const string &);
    virtual ~Person() = default;

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }
    void setGreeting(const string &g) { greeting = g; }

    virtual void print() const;
    virtual const string &speak() const { return greeting; }
};

Person objectRead;

Person::Person(const string &fn, const string &ln, char mi, const string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t), greeting("Hello")

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
// External database access function

void db_open(const string &dbName)
{
    // Assume implementation exists
    cout << "Opening database: " << dbName << endl;
}

void db_close(const string &dbName)
{
    // Assume implementation exists
    cout << "Closing database: " << dbName << endl;
}

Person &db_read(const string &dbName, const string &key)
{
    // Assume implementation exists
    cout << "Reading from: " << dbName << " using key: " << key << endl;

    return objectRead;
}

const string &db_write(const string &dbName, Person &data)
{
    // Assume implementation exists
    const string &key = data.getLastName();
    cout << "Writing: " << key << " to: " << dbName << endl;
    return key;
}

class CitizenDataBase
{
private:
    string name;

public:
    CitizenDataBase(const string &);
    CitizenDataBase(const CitizenDataBase &) = delete;
    CitizenDataBase &operator=(const CitizenDataBase &) = delete;
    virtual ~CitizenDataBase();
    inline Person &Read(const string &);
    inline const string &Write(Person &);
};

CitizenDataBase::CitizenDataBase(const string &n) : name(n)
{
    db_open(name);
}

CitizenDataBase::~CitizenDataBase()
{
    db_close(name);
}

Person &CitizenDataBase::Read(const string &key)
{
    return db_read(name, key);
}

const string &CitizenDataBase::Write(Person &data)
{
    return db_write(name, data);
}

int main()
{
    string key;
    string name("PersonData");

    Person p1("Curt", "Jeffreys", 'M', "Mr.");
    Person p2("Frank", "Burns", 'W', "Mr.");
    Person p3;

    CitizenDataBase People(name); // create a Database
    key = People.Write(p1);
    p3 = People.Read(key);

    return 0;
}