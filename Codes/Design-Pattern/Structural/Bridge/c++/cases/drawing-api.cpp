/*
    Drawing API
    Archive of Reversing.ID
    Design Pattern (Creational/Bridge)

Compile:
    [clang]
    $ clang++ drawing-api.cpp -o drawing-api

    [gcc]
    $ g++ drawing-api.cpp -o drawing-api

    [msvc]
    $ cl drawing-api.cpp

Run:
    $ drawing-api
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * DrawingAPI (abstract)
 * 
 * Implementation.
 * Dalam kasus ini implementation tidak diturunkan dari Abstraction.
 */
class DrawingAPI
{
public:
    virtual ~DrawingAPI() { }

    virtual void draw(double x, double y, double radius) = 0;
};

// ======================================================================================

/**
 * NativeLayer (concrete)
 * 
 * ConcreteImplementation
 * Salah satu variasi yang akan mengimplementasikan operasi.
 */
class NativeLayer : public DrawingAPI
{
public:
    void draw(double x, double y, double radius)
    {
        std::cout << "Drawing-Native.circle at " << x << ":" << y << " " << radius << std::endl;
    }
};

/**
 * WebLayer (concrete)
 * 
 * ConcreteImplementation
 * Salah satu variasi yang akan mengimplementasikan operasi.
 */
class WebLayer : public DrawingAPI
{
public:
    void draw(double x, double y, double radius)
    {
        std::cout << "Drawing-Web.circle at " << x << ":" << y << " " << radius << std::endl;
    }
};

// ======================================================================================

/**
 * Shape (abstract)
 * 
 * Abstraction.
 * Dalam kasus ini Implementation tidak diturunkan dari Abstraction.
 */
class Shape
{
public:
    virtual ~Shape() { }

    virtual void draw() = 0;
    virtual void resizeByPercentage(double pct) = 0;
};

// ======================================================================================

/**
 * Circle (concrete)
 * 
 * RefinedAbstraction.
 * Class yang digunakan dalam operasi.
 */
class Circle : public Shape
{
    double _x, _y, _radius;
    std::unique_ptr<DrawingAPI> _api;

public:
    Circle(double x, double y, double radius, DrawingAPI * api)
        : _x{x}, _y{y}, _radius{radius}, _api{api}
    { }

    void draw()
    {
        _api->draw(_x, _y, _radius);
    }

    void resizeByPercentage(double pct)
    {
        _radius *= pct;
    }
};

/* *********************************** USAGE *********************************** */

int main()
{
    Circle circle1(1, 2, 3, new NativeLayer());
    Circle circle2(5, 7, 11, new WebLayer());

    circle1.resizeByPercentage(2.5);
    circle2.resizeByPercentage(2.5);

    circle1.draw();
    circle2.draw();

    return 0;
}