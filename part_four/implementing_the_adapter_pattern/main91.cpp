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
    void modifyTitle(const string &);
    void setGreeting(const string &g) { greeting = g; }

    virtual void print() const;
    virtual const string &speak() const { return greeting; }
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

void Person::modifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::print() const
{
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". " << lastName << endl;
}

class Humanoid
{
private:
    Person *life = nullptr;

protected:
    void setTitle(const string &t) { life->modifyTitle(t); }

public:
    Humanoid() = default;
    Humanoid(const string &, const string &, const string &, const string &);
    Humanoid(const Humanoid &);
    Humanoid &operator=(const Humanoid &h);

    const string &getSecondaryName() const { return life->getFirstName(); }
    const string &getPrimaryName() const { return life->getLastName(); }
    const string &getTitle() const { return life->getTitle(); }
    void setSalutation(const string &m) { life->setGreeting(m); }
    virtual void getInfo() const { life->print(); }
    virtual const string &converse() = 0;
};

Humanoid::Humanoid(const string &n2, const string &n1, const string &planetNation, const string &greeting)
{
    life = new Person(n2, n1, ' ', planetNation);
    life->setGreeting(greeting);
}

Humanoid::Humanoid(const Humanoid &h)
{
    delete life;
    life = new Person(h.getSecondaryName(), h.getPrimaryName(), ' ', h.getTitle());
    life->setGreeting(h.life->speak());
}

Humanoid &Humanoid::operator=(const Humanoid &h)
{
    if (this != &h)
        life->Person::operator=(dynamic_cast<const Person &>(*h.life));
    return *this;
}

const string &Humanoid::converse()
{
    return life->speak();
}

class Orkan : public Humanoid
{
public:
    Orkan() = default;
    Orkan(const string &n2, const string &n1, const string &t) : Humanoid(n2, n1, t, "Nanu nanu") {}
    Orkan &operator=(const Orkan &h) { return dynamic_cast<Orkan &>(Humanoid::operator=(h)); }
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
    Romulan &operator=(const Romulan &h) { return dynamic_cast<Romulan &>(Humanoid::operator=(h)); }
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
    Earthling &operator=(const Earthling &h) { return dynamic_cast<Earthling &>(Humanoid::operator=(h)); }
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

    Orkan o2 = *o1;

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