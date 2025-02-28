#include <iostream>

using std::cout, std::endl, std::string, std::to_string;

class LifeForm
{

private:
    int lifeExpectancy{};

public:
    LifeForm() = default;
    LifeForm(int life) : lifeExpectancy(life) {}
    LifeForm(const LifeForm &) = default;

    virtual ~LifeForm() = default;
    [[nodiscard]] int getLifeExpectancy() const { return lifeExpectancy; }

    virtual void print() const = 0;
    virtual string isA() const = 0;
    virtual string speak() const = 0;
};

class Horse : public virtual LifeForm
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

class Person : public virtual LifeForm
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
    Person(const Person &) = default;

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
    static constexpr int CENTAUR_LIFE = 1000;

public:
    Centaur() : LifeForm(CENTAUR_LIFE) {}
    Centaur(const string &, const string &, char = ' ', const string & = "Mythological Centaur");
    Centaur(const Centaur &c) : Person(c), Horse(c), LifeForm(CENTAUR_LIFE) {}

    void print() const override;
    string isA() const override;
    string speak() const override;
};

int main()
{
    Centaur beast("Wild", "Man");
    cout << beast.speak() << endl;
    cout << "I am a " << beast.isA() << ". ";
    beast.print();
    cout << "I will live: ";
    cout << beast.getLifeExpectancy();
    cout << " years" << endl;

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

Centaur::Centaur(const string &fn, const string &ln, char mi, const string &title) : Person(fn, ln, mi, title), Horse(fn), LifeForm(CENTAUR_LIFE) {}

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
