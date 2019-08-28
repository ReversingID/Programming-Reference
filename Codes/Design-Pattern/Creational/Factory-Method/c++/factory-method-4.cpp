/*
    Factory Method
    Archive of Reversing.ID
    Design Pattern (Creational)

    Registry based.


Compile:
    [clang]
    $ clang++ factory-method.cpp -o factory-method
    
    [gcc]
    $ g++ factory-method.cpp -o factory-method

    [msvc]
    $ cl factory-method.cpp

Run:
    $ factory-method
*/
#include <memory>
#include <map>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * Product (abstract)
 * 
 * Kelas dasar dari seluruh product yang akan dihasilkan.
 * Kelas dasar dapat pula berupa sebuah kelas konkret.
 */
class Product
{
public:
    virtual ~Product() { }

    /* Contoh operasi kelas yang akan diimplementasikan oleh setiap kelas turunan */
    virtual int operation() = 0;
};

// ======================================================================================

/**
 * ProductA (concrete)
 * 
 * Varian dari Product
 */
class ProductA : public Product
{
public:
     ProductA() { }
    ~ProductA() { }

    int operation()
    {
        return 135;
    }
};

// ======================================================================================

/**
 * ProductB (concrete)
 * 
 * Varian dari Product
 */
class ProductB : public Product
{
public:
     ProductB() { }
    ~ProductB() { }

    int operation()
    {
        return 182;
    }
};

// ======================================================================================

/**
 * Creator
 * 
 * Menggunakan static method sebagai factory untuk menciptakan beberapa barang.
 */
class Creator 
{
    using CreatorMap = std::map<std::string, Creator*>;

    static auto getRegister() -> CreatorMap&
    {
        static CreatorMap _register{};
        return _register;
    } 

public:
    virtual ~Creator() = default;

    static void registerFactory(const std::string& name, Creator* factory)
    {
        auto& reg = Creator::getRegister();
        reg[name] = factory;
    }

    static void showClasses() 
    {
        std::cout << " Registered classes" << std::endl;
        std::cout << " ==================" << std::endl;
        for (const auto& pair: Creator::getRegister())
            std::cout << "  > " << pair.first << std::endl;
    }

    static Product * makeRaw(const std::string& name)
    {
        auto creator = Creator::getRegister();
        auto it = creator.find(name);
        if (it != creator.end())
            return it->second->build();
        
        return nullptr;        
    }

    static auto makePtr(const std::string& name)
    {
        return std::unique_ptr<Product>(Creator::makeRaw(name));
    }

    virtual Product * build() const = 0;
};

// ======================================================================================

/**
 * Concrete Creator
 * 
 * Menggunakan template untuk membangun factory terhadap product.
 */
template <typename DerivedClass>
class ConcreteCreator : public Creator 
{
public:
    ConcreteCreator(const std::string& name)
    {
        Creator::registerFactory(name, this);
    }

    Product * build() const
    {
        return new DerivedClass;
    } 
};


/* *********************************** USAGE *********************************** */

/* 
Register Base class 

Penggunaan anonymous namespace untuk membuat definisi bersifat private terhadap file ini.    
*/
namespace 
{
    ConcreteCreator<ProductA>   productA("A");
    ConcreteCreator<ProductB>   productB("B");
};

int main(int argc, char* argv[])
{
    Creator::showClasses();

    std::unique_ptr<Product> prod1 = Creator::makePtr("A");
    std::cout << prod1->operation() << std::endl;

    std::unique_ptr<Product> prod2 = Creator::makePtr("B");
    std::cout << prod2->operation() << std::endl;

    return 0;
}