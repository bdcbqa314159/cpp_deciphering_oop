#include <iostream>
#include <iomanip>
#include <cstring>
#include "Person.hpp"
#include "Student.hpp"

using std::cout;
using std::endl;

constexpr int MAX = 3;

int main()
{
    // Test all means for instantiation, including copy constructor
    Student s0; // Default construction

    // instantiate two Students
    Student s1("Jo", "Li", 'H', "Ms.", 3.7, "C++", "UD1234");
    Student s2("Sam", "Lo", 'A', "Mr.", 3.5, "C++", "UD2245");

    // These initializations implicitly invoke copy constructor
    Student s3(s1);
    Student s4 = s2;

    // Test the assignment operator
    Student s5("Ren", "Ze", 'A', "Dr.", 3.8, "C++", "BU5563");
    Student s6;
    s6 = s5; // this is an assignment, not initialization

    // Test each public method. A sample is shown here. Be sure to test ALL methods.
    s1.print();
    s3.print();
    s2.print();
    s4.print();

    // Generalize derived instances as base types -- do methods work as expected?
    Person *people[MAX]{};                                                      // will be initialized to nullptrs
    people[0] = new Person("Juliet", "Martinez", 'M', "Ms.");                   // base instance for comparison
    people[1] = new Student("Zack", "Moon", 'R', "Dr.", 3.8, "C++", "UMD1234"); // derived instances
    people[2] = new Student("Gabby", "Doone", 'A', "Dr.", 3.9, "C++", "GWU4321");

    // Compare range for loop to older style, further below
    for (auto *item : people) // note item is a Person (auto can determine this); can also use: for (auto item : people)
    {
        item->isA();
        cout << "  ";
        item->print();
    }

    for (auto *item : people)
        delete item;

    return 0;
}