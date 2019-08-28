/*
    Purchase
    Archive of Reversing.ID
    Design Pattern (Behavioral/Chain of Responsibility)

Compile:
    [clang]
    $ clang++ purchase.cpp -o purchase

    [gcc]
    $ g++ purchase.cpp -o purchase

    [msvc]
    $ cl purchase.cpp

Run:
    $ purchase
*/
#include <memory>
#include <iostream>


// ===============================================================

/**
 * PurchaseRequest (concrete)
 * 
 * Tipe objek yang akan ditangani oleh handler.
 */
class PurchaseRequest
{
    double      _amount;
    std::string _purpose;

public:
    PurchaseRequest(double amount, std::string purpose)
    {
        _amount  = amount;
        _purpose = purpose;
    }
    double getAmount()
    {
        return _amount;
    }
    void setAmount(double amount)
    {
        _amount = amount;
    }
    std::string getPurpose()
    {
        return _purpose;
    }
    void setPurpose(std::string purpose)
    {
        _purpose = purpose;
    }
};

// ===============================================================

/**
 * PurchasePower (concrete)
 * 
 * base handler
 */
class PurchasePower
{
    std::shared_ptr<PurchasePower>  _succ;

protected:
    virtual double      isAllowable() = 0;
    virtual std::string getRole()     = 0;

    double  BASE = 500;

public:
    virtual ~PurchasePower() { }

    void setSuccessor(std::shared_ptr<PurchasePower> successor)
    {
        _succ = successor;
    }

    void process(PurchaseRequest & request)
    {
        if (request.getAmount() < isAllowable())
            std::cout << getRole() << " will approve IDR " << request.getAmount() << std::endl;
        else if (_succ != nullptr)
            _succ->process(request);
    }
};

// ===============================================================

/**
 * ManagerPPower (concrete)
 */
class ManagerPPower : public PurchasePower
{
protected:
    double      isAllowable()
    {
        return BASE * 10;
    }

    std::string getRole()
    {
        return "Manager";
    }
};

/**
 * DirectorPPower (concrete)
 */
class DirectorPPower : public PurchasePower
{
protected:
    double      isAllowable()
    {
        return BASE * 20;
    }

    std::string getRole()
    {
        return "Director";
    }
};

/**
 * VicePresidentPPower (concrete)
 */
class VicePresidentPPower : public PurchasePower
{
protected:
    double      isAllowable()
    {
        return BASE * 40;
    }

    std::string getRole()
    {
        return "Vice President";
    }
};

/**
 * PresidentPPower (concrete)
 */
class PresidentPPower : public PurchasePower
{
protected:
    double      isAllowable()
    {
        return BASE * 60;
    }

    std::string getRole()
    {
        return "President";
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char * argv[])
{
    double d;
    auto manager    = std::make_shared<ManagerPPower>();
    auto director   = std::make_shared<DirectorPPower>();
    auto vp         = std::make_shared<VicePresidentPPower>();
    auto president  = std::make_shared<PresidentPPower>();

    manager->setSuccessor(director);
    director->setSuccessor(vp);
    vp->setSuccessor(president);

    while (true)
    {
        std::cout << "Enter the amount to check who should approve your expenditure." << std::endl;
        std::cout << "> ";
        std::cin >> d;

        PurchaseRequest req(d, "General");
        manager->process(req);
    }
    return 0;
}