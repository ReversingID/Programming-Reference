/*
    Abstract Factory
    Archive of Reversing.ID
    Design Pattern (Creational)

Compile:
    [clang]
    $ clang++ abstract-factory.cpp -o abstrac-factory

    [gcc]
    $ g++ abstract-factory.cpp -o abstract-factory

    [msvc]
    $ cl abstract-factory.cpp

Run:
    $ abstract-factory
*/
#include <memory>

/*
    Produk yang ada dapat dikelompokkan berdasarkan kategori tertentu.
    Sebuah factory digunakan untuk memproduksi produk-produk yang berkaitan atau 
    berada dalam satu keluarga.

    Sebuah produk dapat diturunkan dari sebuah base utama, atau bisa sama sekali
    tidak berkaitan dengan produk lain di luar keluarganya.
*/


/* *********************************** DECLARATION *********************************** */

/**
 * FamilyOne
 * 
 * Kelompok produk FamilyOne terdiri dari beberapa variasi: ProductAX, ProductAY.
 */
class FamilyOne 
{
public:
    virtual ~FamilyOne() {}
    virtual int info() = 0;
};

class ProductAX : public FamilyOne {
public:
    int info()
    {
        return 135;
    }
};

class ProductAY : public FamilyOne {
public:
    int info()
    {
        return 182;
    }
};

// ======================================================================================

/**
 * FamilyTwo
 * 
 * Kelompok produk FamilyTwo terdiri dari beberapa variasi: ProductBX, ProductBY.
 */
class FamilyTwo 
{
public:
    virtual ~FamilyTwo() {}
    virtual int characteristic() = 0;
};

class ProductBX : public FamilyTwo 
{
public:
    int characteristic()
    {
        return 235;
    }
};

class ProductBY : public FamilyTwo 
{
public:
    int characteristic()
    {
        return 282;
    }
};

// ======================================================================================

/**
 * Creator (abstract)
 * 
 * Interface dari kelas yang akan menghasilkan factory untuk memproduksi kelompok produk.
 */
class Creator 
{
public:
    virtual ~Creator() { }
    
    virtual auto build_ProductA() -> std::unique_ptr<FamilyOne> = 0;
    virtual auto build_ProductB() -> std::unique_ptr<FamilyTwo> = 0;
};

// ======================================================================================

/**
 * FamilyXCreator (concrete)
 * 
 * Creator untuk product yang tergabung dalam keluarga X.
 */
class FamilyXCreator : public Creator
{
public:
    auto build_ProductA() -> std::unique_ptr<FamilyOne>
    {
        return std::make_unique<ProductAX>();
    }

    auto build_ProductB() -> std::unique_ptr<FamilyTwo>
    {
        return std::make_unique<ProductBX>();
    }
};

// ======================================================================================

/**
 * FamilyYCreator (concrete)
 * 
 * Creator untuk product yang tergabung dalam keluarga Y.
 */
class FamilyYCreator : public Creator
{
public:
    auto build_ProductA() -> std::unique_ptr<FamilyOne>
    {
        return std::make_unique<ProductAY>();
    }

    auto build_ProductB() -> std::unique_ptr<FamilyTwo>
    {
        return std::make_unique<ProductBY>();
    }
};



/* *********************************** USAGE *********************************** */
#include <iostream>

int main(int argc, char* argv[])
{
    std::unique_ptr<Creator> creator{nullptr};

    // Instansiasi objek factory untuk membangun produk & bangun product.
    creator = std::make_unique<FamilyXCreator>();
    auto AX = creator->build_ProductA();
    auto BX = creator->build_ProductB();
    std::cout << "AX = " << AX->info() << std::endl;
    std::cout << "BX = " << BX->characteristic() << std::endl;

    creator = std::make_unique<FamilyYCreator>();
    auto AY = creator->build_ProductA();
    auto BY = creator->build_ProductB();
    std::cout << "AY = " << AY->info() << std::endl;
    std::cout << "BY = " << BY->characteristic() << std::endl;


    return 0;
}