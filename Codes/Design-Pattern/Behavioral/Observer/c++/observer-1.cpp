/*
    Observer
    Archive of Reversing.ID
    Design Pattern (Behavioral)

Compile:
    [clang]
    $ clang++ observer.cpp -o observer
    
    [gcc]
    $ g++ observer.cpp -o observer

    [msvc]
    $ cl observer.cpp

Run:
    $ observer
*/
#include <memory>
#include <list>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

class Publisher;
class Subscriber;

// ======================================================================================

/**
 * Subscriber (abstract)
 * 
 * Disebut pula Observer.
 * Berlangganan kepada publisher dan menanti notifikasi apabila terjadi perubahan.
 */
class Subscriber
{
protected:
    std::string _state;

public:
    virtual ~Subscriber() { }

    virtual void update(Publisher * publisher) = 0;
};

// ======================================================================================

/**
 * Publisher (abstract)
 * 
 * Disebut pula Subject.
 * Memberi notifikasi kepada semua objek yang berlangganan apabila terdapat update.
 */
class Publisher
{
    std::list<Subscriber *>  _subscribers;

protected:
    Publisher()
    { }

public:
    virtual ~Publisher() { }

    virtual void        setState(const std::string & state) = 0;
    virtual std::string getState() = 0;
    
    virtual void attach(Subscriber * subscriber)
    {
        _subscribers.push_back(subscriber);
    }

    virtual void detach(Subscriber * subscriber)
    {
        if (subscriber != nullptr)
            _subscribers.remove(subscriber);
    }

    virtual void notify()
    {
        for (auto subscriber: _subscribers)
            subscriber->update(this);
    }
};

// ======================================================================================

/**
 * ConcretePublisher (concrete)
 */
class ConcretePublisher: public Publisher
{
    std::string _state;

public:
    ConcretePublisher()
    { }

    std::string getState() override 
    {
        return _state;
    }

    void setState(const std::string & state) override 
    {
        _state = state;
    }
};

// ======================================================================================

/**
 * ConcreteSubscriber (concrete)
 */
class ConcreteSubscriber: public Subscriber
{
    Publisher *     _publisher;

public:
    ConcreteSubscriber(Publisher * publisher) : _publisher{publisher}
    { 
        _publisher->attach(this);
    }

    void update(Publisher * publisher) override
    {
        _state = publisher->getState();
    }

    std::string getState()
    {
        return _state;
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto publisher  = std::make_shared<ConcretePublisher>();
    auto sub1       = std::make_shared<ConcreteSubscriber>(publisher.get());
    auto sub2       = std::make_shared<ConcreteSubscriber>(publisher.get());

    publisher->setState("Old-State");
    publisher->notify();
    std::cout << "Subscriber-1: " << sub1->getState() << std::endl;
    std::cout << "Subscriber-2: " << sub2->getState() << std::endl;

    publisher->setState("New-State");
    publisher->notify();
    std::cout << "Subscriber-1: " << sub1->getState() << std::endl;
    std::cout << "Subscriber-2: " << sub2->getState() << std::endl;

    return 0;
}