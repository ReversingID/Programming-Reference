/*
    Mediator
    Archive of Reversing.ID
    Design Pattern (Behavioral)

    Semua Colleague merupakan class yang diturunkan dari
    satu interface sama.

Compile:
    [clang]
    $ clang++ mediator.cpp -o mediator
    
    [gcc]
    $ g++ mediator.cpp -o mediator

    [msvc]
    $ cl mediator.cpp

Run:
    $ mediator
*/
#include <memory>
#include <vector>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

class Mediator;
class Colleague;

using MediatorPtr  = std::weak_ptr<Mediator>;
using ColleaguePtr = std::shared_ptr<Colleague>;

// ======================================================================================

/**
 * Colleague (abstract)
 */
class Colleague
{
protected:
    MediatorPtr _mediator;
    int         _id;

public:
    Colleague(MediatorPtr mediator, int id) : _mediator{mediator}, _id{id}
    { }

    virtual ~Colleague() { }

    int getId()
    {
        return _id;
    }

    virtual void send(std::string msg) = 0;
    virtual void recv(std::string msg) = 0;
};

// ======================================================================================

/**
 * Mediator (abstract)
 */
class Mediator
{
public:
    virtual ~Mediator() { }

    virtual void add(ColleaguePtr c) = 0;
    virtual void distribute(Colleague * sender, std::string msg) = 0;
};

// ======================================================================================

/**
 * ConcreteColleague (concrete)
 */
class ConcreteColleague: public Colleague
{
public:
    ConcreteColleague(MediatorPtr mediator, int id) : Colleague(mediator, id)
    { }

    void send(std::string msg) override 
    {
        std::cout << "[ConcreteColleague] :: send [" << getId() << "]" << std::endl;
        std::cout << "   message = " << msg << std::endl;

        _mediator.lock()->distribute(this, msg);
    }
    void recv(std::string msg) override 
    {
        std::cout << "[ConcreteColleague] :: receive [" << getId() << "]" << std::endl;
        std::cout << "   message = " << msg << std::endl;
    }
};

// ======================================================================================

/**
 * ConcreteMediator (concrete)
 */
class ConcreteMediator: public Mediator
{
    std::vector<ColleaguePtr>   _colleagues;

public:

    void add(ColleaguePtr c) override
    {
        _colleagues.push_back(c);   
    }

    void distribute(Colleague * sender, std::string msg) override
    {
        for (auto& colleague: _colleagues)
            if (colleague->getId() != sender->getId())
                colleague->recv(msg);
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto mediator = std::make_shared<ConcreteMediator>();

    auto c1 = std::make_shared<ConcreteColleague>(mediator, 1);
    auto c2 = std::make_shared<ConcreteColleague>(mediator, 2);
    auto c3 = std::make_shared<ConcreteColleague>(mediator, 3);
    
    mediator->add(c1);
    mediator->add(c2);
    mediator->add(c3);

    c1->send("Reversing.ID");
    c3->send("Mediator Pattern!");

    return 0;
}