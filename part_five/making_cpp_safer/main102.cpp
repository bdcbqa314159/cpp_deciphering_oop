#include <iostream>
#include <memory>
#include "Person.hpp"

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

// Note: could also include: using std::make_shared; if you don't want to qualify use below with std::

int main()
{
    shared_ptr<Person> pers1 = std::make_shared<Person>("Gabby", "Doone", 'A', "Miss");
    // Above line is equivalanet to:
    // shared_ptr<Person> pers1(new Person("Gabby", "Doone", 'A', "Miss"));

    pers1->print(); // or alternatively use: (*pers1).Print();

    weak_ptr<Person> wpers1(pers1); // Downgrade pers1 to a weak pointer
    // wpers1->Print(); // note: weak pointer can not access the resource, must use a shared pointer to do so

    cout << "# references: " << pers1.use_count() << endl;
    cout << "# references: " << wpers1.use_count() << endl;

    shared_ptr<Person> pers2 = wpers1.lock(); // create a shared pointer to the resource
    // shared_ptr<Person> pers2(wpers1.lock());  // same as line above - alternate initialization
    pers2->print();

    pers2->modifyTitle("Dr.");
    pers2->print();

    cout << "# references: " << pers1.use_count() << endl;
    cout << "# references: " << wpers1.use_count() << endl;
    cout << "# references: " << pers2.use_count() << endl;
    return 0;
}