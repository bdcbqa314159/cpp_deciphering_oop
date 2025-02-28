#include <iostream>

using std::cout, std::endl, std::string, std::to_string;

class LifeForm
{

private:
    int lifeExpectancy{};

public:
    LifeForm() = default;
    LifeForm(int life) : lifeExpectancy(life) {}

    virtual ~LifeForm() = default;
    [[nodiscard]] int getLifeExpectancy() const { return lifeExpectancy; }

    virtual void print() const = 0;
    virtual string isA() const = 0;
    virtual string speak() const = 0;
};

class Horse : public LifeForm
{
private:
    string name;
    static constexpr int HORSE_LIFE = 35;

public:
    Horse() : LifeForm(HORSE_LIFE) {}
    Horse(const string &n);
    const string &getName() const { return name; }
    void print() const override;
    string isA() const override;
    string speak() const override;
};

class Person : public LifeForm
{

private:
    string firstName, lastName;
    char middleInitial = '\0';
    string title;

    static constexpr int PERSON_LIFE = 80;

protected:
    void modifyTitle(const string &);

public:
    Person();
    Person(const string &, const string &, char, const string &);

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }

    void print() const override;
    string isA() const override;
    string speak() const override;
};

class Centaur : public Person, public Horse
{
private:
public:
    Centaur() = default;
    Centaur(const string &, const string &, char = ' ', const string & = "Mythological Centaur");
    Centaur(const Centaur &c) : Person(c), Horse(c) {}

    void print() const override;
    string isA() const override;
    string speak() const override;
};

int main()
{
    Centaur beast("Wild", "Man");
    cout << beast.speak() << " I'm a " << beast.isA() << endl;

    // Ambiguous member function invocation below!  Two paths exist to
    // LifeForm::GetLifeExpectancy().  One via Horse and one via Person.
    // Also, two copies of the LifeForm object exist--one initialized the
    // way Horse dictated, one initialized the way Person dictated.  Which
    // of these two LifeForms are you asking to be the 'this' pointer?
    // cout << beast.GetLifeExpectancy();

    cout << "It is unclear how many years I will live: ";
    cout << beast.Person::getLifeExpectancy();
    cout << " or ";
    cout << beast.Horse::getLifeExpectancy() << endl;

    return 0;
}

Horse::Horse(const string &n) : LifeForm(HORSE_LIFE), name(n) {}

void Horse::print() const
{
    cout << name << endl;
}

string Horse::isA() const
{
    return "Horse";
}

string Horse::speak() const
{
    return "Neigh";
}

Person::Person() : LifeForm(PERSON_LIFE)
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : LifeForm(PERSON_LIFE), firstName(fn), lastName(ln), middleInitial(mi), title(t)
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

string Person::isA() const
{
    return "Person";
}

string Person::speak() const
{
    return "Hello!";
}

Centaur::Centaur(const string &fn, const string &ln, char mi, const string &title) : Person(fn, ln, mi, title), Horse(fn) {}

void Centaur::print() const
{
    cout << "my name is " << getFirstName();
    cout << ". I am as " << getTitle() << endl;
}

string Centaur::isA() const
{
    return "Centaur";
}

string Centaur::speak() const
{
    return "Neigh! and Hello!";
}
