#include <iostream>

using std::cout, std::endl, std::string;

class Singleton
{
private:
    string data;
    Singleton(string d);

public:
    static Singleton &instance(string);
    const string &getData() const { return data; }
    virtual ~Singleton();
};

Singleton::Singleton(string d) : data(d)
{
    cout << "constructor" << endl;
}

Singleton::~Singleton()
{
    cout << "destructor" << endl;
}

Singleton &Singleton::instance(string d)
{
    static Singleton theInstance(d);
    return theInstance;
}

int main()
{
    Singleton &s1 = Singleton::instance("Unique data"); // first call, creates theInstance
    Singleton &s2 = Singleton::instance("More data");   // returns existing theInstance

    cout << s1.getData() << "\n"
         << s2.getData() << endl;

    return 0;
}