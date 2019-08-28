/*
    Point
    Archive of Reversing.ID
    Design Pattern (Creational/Named Factory)
    
Compile:
    [clang]
    $ clang++ point.cpp -o point
    
    [gcc]
    $ g++ point.cpp -o point

    [msvc]
    $ cl point.cpp

Run:
    $ point
*/
#include <iostream>
#include <cmath>

/* *********************************** DECLARATION *********************************** */

/**
 * Point (concrete)
 * 
 * Representasi titik dalam 2 dimensi (X-Y)
 */
struct Point
{
    Point(double x, double y) : x{x}, y{y}
    { }

    double x, y;

    static Point cartesian(double x, double y)
    {
        return Point{x, y};
    }

    static Point polar(double r, double theta)
    {
        return Point{ r*cos(theta), r*sin(theta) };
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    Point p0{1, 5};
    Point p1 = Point::cartesian(10, 20);
    Point p2 = Point::polar(10, 45);

    return 0;
}