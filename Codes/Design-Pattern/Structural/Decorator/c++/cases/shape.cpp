/*
    Shape
    Archive of Reversing.ID
    Design Pattern (Creational/Decorator)

Compile:
    [clang]
    $ clang++ shape.cpp -o shape

    [gcc]
    $ g++ shape.cpp -o shape

    [msvc]
    $ cl shape.cpp

Run:
    $ shape
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

class Shape 
{
public:
    virtual ~Shape() = default;

    virtual auto draw() -> void = 0;
    virtual auto description() -> std::string = 0;
};

// ======================================================================================

class Square: public Shape 
{
public:
    virtual auto draw() -> void
    {
        std::cout << " => Draw square" << std::endl;
    }

    virtual auto description() -> std::string
    {
        return "Square";
    }
};

class Triangle: public Shape 
{
public:
    virtual auto draw() -> void
    {
        std::cout << " => Draw triangle" << std::endl;
    }

    virtual auto description() -> std::string
    {
        return "Triangle";
    }
};

// ======================================================================================

/**
 * ColorDecorator (concrete)
 * 
 * Menambahkan atribut warna.
 */
class ColorDecorator: public Shape
{
    std::shared_ptr<Shape> _shape;
    std::string     _color;

public:
    ColorDecorator(std::shared_ptr<Shape> shape) : _shape{shape}
    { 
        _color = "blue";
    }

    auto draw() -> void
    {
        std::cout << " => [ColorDecorator] draw object with color " << _color << std::endl;
        _shape->draw();
    }

    auto description() -> std::string
    {
        return _shape->description() + " : color = " + _color;
    }

    auto setColor(std::string color) -> decltype(*this)&
    {
        _color = color;
        return *this;
    }
};

// ======================================================================================


/**
 * PositionDecorator (concrete)
 * 
 * Memberikan atribut posisi
 */
class PositionDecorator: public Shape
{
    std::shared_ptr<Shape> _shape;
    double      _x, _y;

public:
    PositionDecorator(std::shared_ptr<Shape> shape) : _shape{shape}
    { }

    auto draw() -> void
    {
        std::cout   << " => [PositionDecorator] draw object at x = " << _x 
                    << " ; y = " << _y << std::endl;
        _shape->draw();
    }

    auto description() -> std::string
    {
        return _shape->description() + " : position x = " + std::to_string(_x) + " ; y = " + std::to_string(_y);
    }

    auto setPosition(double x, double y) -> decltype(*this)&
    {
        _x = x;
        _y = y;
        return *this;
    }
};


/* *********************************** USAGE *********************************** */

int main()
{
    auto shape1 = std::make_shared<ColorDecorator>(std::make_shared<Square>());
    shape1->setColor("yellow");
    shape1->draw();

    auto shape2 = std::shared_ptr<Shape>{nullptr};
    auto shape3 = 
        [&shape2] {
            auto shape = std::make_shared<Triangle>();
            shape2     = shape;
            auto shapeColored = std::make_shared<ColorDecorator>(shape);
            shapeColored->setColor("white");
            auto shapePos = std::make_shared<PositionDecorator>(shapeColored);
            return shapePos;
        }();
    shape3->setPosition(100, 20);
    shape3->draw();


    return 0;
}