/*
    Shape
    Archive of Reversing.ID
    Design Pattern (Creational/Prototype)

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
#include <iostream>
#include <memory>
#include <unordered_map>

/* *********************************** DECLARATION *********************************** */

class Shape 
{
    int         _x, _y;
    uint32_t    _color;     // 32-bit depth color
public:
    virtual ~Shape() { }

    Shape() { }
    
    Shape(int x, int y) : _x{x}, _y{y}
    { }

    virtual void print() = 0;

    virtual auto clone() -> std::unique_ptr<Shape> = 0;
};

// ======================================================================================

class Rectangle : public Shape
{
    int         _width, _height;
public:
    Rectangle(int width, int height) : _width{width}, _height{height}
    { }

    void print() override 
    {
        std::cout << "Rectangle " << std::endl
                  << "   Width: " << _width << std::endl
                  << "   Height: " << _height << std::endl;
    }

    auto clone() -> std::unique_ptr<Shape> override
    {
        return std::make_unique<Rectangle>(*this);
    }
};

// ======================================================================================

class Circle : public Shape
{
    int         _radius;
public:
    Circle(int radius) : _radius{radius} 
    { }

    void print() override 
    {
        std::cout << "Circle " << std::endl
                  << "   Radius: " << _radius << std::endl;
    }

    auto clone() -> std::unique_ptr<Shape> override
    {
        return std::make_unique<Circle>(*this);
    }
};

// ======================================================================================

enum ShapeType { RECTANGLE, CIRCLE };

/**
 * ShapeFactory
 * 
 * sebuah factory yang berperan sebagai registry untuk menyimpan prototype dan melakukan
 * penciptaan objek baru (clone).
 * 
 * Tugas factory hanya membantu untuk menciptakan objek yang sesuai karena penciptaan objek
 * diimplementasikan dengan Prototype.
 */
class ShapeFactory
{
    std::unordered_map<ShapeType, std::unique_ptr<Shape>, std::hash<int>> _records;

public:
    ShapeFactory()
    {
        _records[RECTANGLE] = std::make_unique<Rectangle>(10, 20);
        _records[CIRCLE]    = std::make_unique<Circle>(10);
    }

    auto create(ShapeType type) -> std::unique_ptr<Shape>
    {
        return _records[type]->clone();
    }
};


/* *********************************** USAGE *********************************** */

int main()
{
    ShapeFactory factory;

    auto record = factory.create(RECTANGLE);
    record->print();

    record = factory.create(CIRCLE);
    record->print();

    return 0;
}