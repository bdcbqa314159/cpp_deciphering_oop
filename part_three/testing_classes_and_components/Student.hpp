#pragma once
#include "Person.hpp"
using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::move;
class Student : public Person
{
private:
    float gpa{};
    string currentCourse;
    const char *studentId = nullptr;
    static int numStudents;

public:
    Student();
    Student(const string &, const string &, char, const char *, float, const string &, const char *);

    Student(const Student &);
    Student(Student &&);

    ~Student() override;

    void earnPHD();
    float getGPA() const { return gpa; }
    const string &getCurrentCourse() const { return currentCourse; }
    const char *getStudentId() const { return studentId; }
    void setCurrentCourse(const string &);

    void print() const override;
    void isA() const override;

    Student &operator=(const Student &);
    Student &operator=(Student &&);
    static int getNumberStudents() { return numStudents; }
};