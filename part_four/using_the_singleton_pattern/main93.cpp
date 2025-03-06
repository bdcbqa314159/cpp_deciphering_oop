#include <iostream>

using std::cout, std::endl;

class Singleton
{
private:
    static Singleton *theInstance;
    Singleton();

public:
    static Singleton *instance();
    virtual ~Singleton();
};

Singleton *Singleton::theInstance = nullptr;

Singleton::Singleton()
{
    cout << "constructor" << endl;
}

Singleton::~Singleton()
{
    cout << "destructor" << endl;

    if (theInstance != nullptr)
    {
        Singleton *temp = theInstance;
        theInstance = nullptr;
        delete temp;
    }
}

Singleton *Singleton::instance()
{
    if (theInstance == nullptr)
        theInstance = new Singleton();
    return theInstance;
}

int main()
{
    Singleton *s1 = Singleton::instance();
    Singleton *s2 = Singleton::instance();

    cout << s1 << " " << s2 << endl;

    return 0;
}