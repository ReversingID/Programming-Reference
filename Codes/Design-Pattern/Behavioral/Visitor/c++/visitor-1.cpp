/*
    Template Method
    Archive of Reversing.ID
    Design Pattern (Behavioral)

Compile:
    [clang]
    $ clang++ template.cpp -o template
    
    [gcc]
    $ g++ template.cpp -o template

    [msvc]
    $ cl template.cpp

Run:
    $ template
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

class Visitor;
class ConcreteElementA;
class ConcreteElementB;

// ======================================================================================

/**
 * Element (abstract)
 * 
 * Mendefinisikan accept() yang menerima visitor sebagai argumen.
 */
class Element 
{
public:
    virtual ~Element() { }

    virtual void accept(std::shared_ptr<Visitor> visitor) = 0;
};

// ======================================================================================

/**
 * Visitor (abstract)
 * 
 * Mendeklarasikan operasi visit untuk setiap class ConcreteElement di struktur objek.
 */
class Visitor 
{
public:
    virtual ~Visitor() { }

    virtual void visit(ConcreteElementA * e) = 0;
    virtual void visit(ConcreteElementB * e) = 0;
};

// ======================================================================================

/**
 * Variasi dari ConcreteElement.
 * 
 * Mengimplementasikan operasi accept() yang menerima Visitor sebagai argumen.
 */

class ConcreteElementA: public Element 
{
public:
    void accept(std::shared_ptr<Visitor> visitor)
    {
        visitor->visit(this);
        std::cout << "[ConcreteElement-A] :: visited ..." << std::endl;
    }
};

class ConcreteElementB: public Element 
{
public:
    void accept(std::shared_ptr<Visitor> visitor)
    {
        visitor->visit(this);
        std::cout << "[ConcreteElement-A] :: visited ..." << std::endl;
    }
};

// ======================================================================================

/**
 * Variasi concrete visitor 
 * 
 * Mengimplementasikan setiap operasi yang dideklarasikan oleh Visitor.
 * Tiap class mengimplementasikan algoritma berbeda sesuai dengan kasus yang dihadapi.
 */

class ConcreteVisitorX: public Visitor 
{
public:
    virtual ~ConcreteVisitorX() { }

    void visit(ConcreteElementA * e) override
    {
        std::cout << "[ConcreteVisitor-X] i will visit ConcreteElementA" << std::endl;
    }
    void visit(ConcreteElementB * e) override
    {
        std::cout << "[ConcreteVisitor-X] i will visit ConcreteElementB" << std::endl;
    }
};

class ConcreteVisitorY: public Visitor 
{
public:
    virtual ~ConcreteVisitorY() { }

    void visit(ConcreteElementA * e) override
    {
        std::cout << "[ConcreteVisitor-X] i will visit ConcreteElementA" << std::endl;
    }
    void visit(ConcreteElementB * e) override
    {
        std::cout << "[ConcreteVisitor-X] i will visit ConcreteElementB" << std::endl;
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto visitor = std::shared_ptr<Visitor>{std::make_shared<ConcreteVisitorX>()};
    auto element = std::shared_ptr<Element>{std::make_shared<ConcreteElementA>()};

    element->accept(visitor);

    return 0;
}