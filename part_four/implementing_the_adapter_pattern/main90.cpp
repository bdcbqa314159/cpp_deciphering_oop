#include <iostream>
#include <list>

using std::cout, std::endl, std::string, std::to_string, std::list;

constexpr int MAX = 3;

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

class Humanoid : private Person
{
protected:
    void setTitle(const string &t) { modifyTitle(t); }

public:
    Humanoid() = default;
    Humanoid(const string &, const string &, const string &, const string &);

    const string &getSecondaryName() const { return getFirstName(); }
    const string &getPrimaryName() const { return getLastName(); }
    const string &getTitle() const { return Person::getTitle(); }
    void setSalutation(const string &m) { setGreeting(m); }
    virtual void getInfo() const { print(); }
    virtual const string &converse() = 0;
};

Humanoid::Humanoid(const string &n2, const string &n1, const string &planetNation, const string &greeting) : Person(n2, n1, ' ', planetNation)
{
    setGreeting(greeting);
}

const string &Humanoid::converse()
{
    return speak();
}

class Orkan : public Humanoid
{
public:
    Orkan() = default;
    Orkan(const string &n2, const string &n1, const string &t) : Humanoid(n2, n1, t, "Nanu nanu") {}

    const string &converse() override;
};

const string &Orkan::converse()
{
    return Humanoid::converse();
}

class Romulan : public Humanoid
{
public:
    Romulan() = default;
    Romulan(const string &n2, const string &n1, const string &t) : Humanoid(n2, n1, t, "jolan'tru") {}

    const string &converse() override;
};

const string &Romulan::converse()
{
    return Humanoid::converse();
}

class Earthling : public Humanoid
{
public:
    Earthling() = default;
    Earthling(const string &n2, const string &n1, const string &t) : Humanoid(n2, n1, t, "Hello") {}

    const string &converse() override;
};

const string &Earthling::converse()
{
    return Humanoid::converse();
}

int main()
{
    list<Humanoid *> allies;
    Orkan *o1 = new Orkan("Mork", "McConnell", "Orkan");
    Romulan *r1 = new Romulan("Donatra", "Jarok", "Romulan");
    Earthling *e1 = new Earthling("Eve", "Xu", "Earthling");

    allies.push_back(o1);
    allies.push_back(r1);
    allies.push_back(e1);

    for (auto *entity : allies)
    {
        entity->getInfo();
        cout << entity->converse() << endl;
    }

    e1->setSalutation("Bonjour");
    e1->getInfo();
    cout << e1->converse() << endl;

    delete o1;
    delete r1;
    delete e1;

    return 0;
}