/*
    Car Builder
    Archive of Reversing.ID
    Design Pattern (Creational/Builder)

Compile:
    [clang]
    $ clang++ car-builder.cpp -o car-builder
    
    [gcc]
    $ g++ car-builder.cpp -o car-builder

    [msvc]
    $ cl car-builder.cpp

Run:
    $ car-builder
*/
#include <iostream>

/* *********************************** DECLARATION *********************************** */

class Wheel 
{
public:
    int _size;
};

class Engine
{
public:
    int _horsepower;
};

class Body 
{
public:
    std::string _shape;
};

// ======================================================================================

/**
 * Car (concrete)
 * 
 * Produk akhir yang terdiri dari beberapa komponen.
 */
class Car
{
public:
    Wheel  * _wheels[4];
    Engine * _engine;
    Body   * _body;

    virtual ~Car()
    {
        for (Wheel* wh : _wheels)
            delete wh;
        delete _engine;
        delete _body;
    }

    void specification()
    {
        std::cout << "   Body: " << _body->_shape << std::endl;
        std::cout << "   Engine: " << _engine->_horsepower << std::endl;
        std::cout << "   Tire Size: " << _wheels[0]->_size << std::endl;
    }
};

// ======================================================================================

/**
 * Builder (abstract)
 * 
 * Membangun komponen per komponen mobil 
 */
class Builder
{
public:
    virtual Wheel  * getWheel()  = 0;
    virtual Engine * getEngine() = 0;
    virtual Body   * getBody()   = 0;
};

// ======================================================================================

class JeepBuilder : public Builder
{
public:
    Wheel * getWheel()
    {
        Wheel * wheel = new Wheel();
        wheel->_size = 22;
        return wheel;
    }

    Engine * getEngine()
    {
        Engine * engine = new Engine();
        engine->_horsepower = 400;
        return engine;
    }

    Body * getBody()
    {
        Body * body = new Body();
        body->_shape = "SUV";
        return body;
    }
};

// ======================================================================================

class NissanBuilder : public Builder
{
public:
    Wheel * getWheel()
    {
        Wheel * wheel = new Wheel();
        wheel->_size = 16;
        return wheel;
    }

    Engine * getEngine()
    {
        Engine * engine = new Engine();
        engine->_horsepower = 85;
        return engine;
    }

    Body * getBody()
    {
        Body * body = new Body();
        body->_shape = "hatchback";
        return body;
    }
};

// ======================================================================================

class Director
{
    Builder * _builder;

public:
    void setBuilder(Builder * builder)
    {
        _builder = builder;
    }

    Car * getCar()
    {
        Car * _car = new Car();

        _car->_body   = _builder->getBody();
        _car->_engine = _builder->getEngine();

        for (int i = 0; i < 4; i++)
            _car->_wheels[i] = _builder->getWheel();
        
        return _car;
    }
};


/* *********************************** USAGE *********************************** */

int main()
{
    Car * car;

    Director        director;

    JeepBuilder     jeepbuilder;
    NissanBuilder   nissanbuilder;

    /* Build a Jeep car */
    std::cout << "building Jeep Car" << std::endl;
    director.setBuilder(&jeepbuilder);
    car = director.getCar();
    car->specification();
    std::cout << std::endl;

    /* Build a Nissan car */
    std::cout << "building Nissan Car" << std::endl;
    director.setBuilder(&nissanbuilder);
    car = director.getCar();
    car->specification();
    std::cout << std::endl;

}