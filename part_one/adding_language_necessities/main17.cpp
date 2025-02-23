#include <iostream>
#include <cmath>

using std::cout, std::endl;

constexpr float PI = 3.14159;

class Circle
{
public:
    float radius{}, area{};
};

class Rectangle
{
public:
    float length{}, width{}, area{};
};

void display(Circle);
void display(Rectangle);

int main()
{
    Circle myCircle;
    Rectangle myRect;
    Rectangle mySquare;
    myCircle.radius = 5.0;
    myCircle.area = PI * std::pow(myCircle.radius, 2.0);
    myRect.length = 2.0;
    myRect.width = 4.0;
    myRect.area = myRect.length * myRect.width;
    mySquare.length = 4.0;
    mySquare.width = 4.0;
    mySquare.area = mySquare.length * mySquare.width;
    display(myCircle); // invoke: void display(Circle)
    display(myRect);   // invoke: void display(Rectangle)
    display(mySquare);

    return 0;
};

void display(Circle c)
{
    cout << "circle with radius: " << c.radius << "\n";
    cout << "it has an area of " << c.area << "\n";
}

void display(Rectangle r)
{
    cout << "rectangle with length: " << r.length << " and witdh: " << r.width << "\n";
    cout << "it has an area of :" << r.area << "\n";
}