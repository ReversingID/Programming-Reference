/*
    Soto Maker
    Archive of Reversing.ID
    Design Pattern (Creational/Factory Method)

Compile:
    [clang]
    $ clang++ soto-maker.cpp -o soto-maker
    
    [gcc]
    $ g++ soto-maker.cpp -o soto-maker

    [msvc]
    $ cl soto-maker.cpp

Run:
    $ soto-maker
*/
#include <iostream>
#include <memory>


/* *********************************** DECLARATION *********************************** */

/**
 * Soto (abstract)
 * 
 * Kelas dasar dari seluruh product yang akan dihasilkan.
 * Kelas dasar dapat pula berupa sebuah kelas konkret.
 */
class Soto
{
public:
    virtual ~Soto() { }
    virtual void identify() = 0;
};

// ======================================================================================

/**
 * SotoLamongan (concrete)
 * 
 * Varian dari product
 */
class SotoLamongan : public Soto
{
public:
    void identify()
    {
        std::cout << "Soto Lamongan disajikan." << std::endl;
    }
};

// ======================================================================================

/**
 * SotoBetawi (concrete)
 * 
 * Varian dari product
 */
class SotoBetawi : public Soto
{
public:
    void identify()
    {
        std::cout << "Soto Betawi disajikan." << std::endl;
    }
};

// ======================================================================================

/**
 * SotoMakassar (concrete)
 * 
 * Varian dari product
 */
class SotoMakassar : public Soto
{
public:
    void identify()
    {
        std::cout << "Soto Makassar disajikan." << std::endl;
    }
};

// ======================================================================================

/**
 * ConcreteFactory (concrete)
 * 
 * Kelas yang akan menghasilkan produk melalui pemanggilan fungsi tertentu.
 * Fungsi mengabstraksi proses pembuatan sebuah kelas sehingga pengguna
 * dapat memeroleh kelas tanpa harus melakukan pembuatan secara manual.
 */
enum class SotoType { LAMONGAN, BETAWI, MAKASSAR };

class WarungSoto
{
public:
    
    static auto order(SotoType type) -> std::unique_ptr<Soto>
    {
        switch (type)
        {
            case SotoType::LAMONGAN: return std::make_unique<SotoLamongan>();
            case SotoType::BETAWI:   return std::make_unique<SotoBetawi>();
            case SotoType::MAKASSAR: return std::make_unique<SotoMakassar>();
        }
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Instansiasi beberapa produk soto
    auto soto1 = WarungSoto::order(SotoType::LAMONGAN);
    auto soto2 = WarungSoto::order(SotoType::BETAWI);
    auto soto3 = WarungSoto::order(SotoType::MAKASSAR);

    soto1->identify();
    soto2->identify();
    soto3->identify();

    return 0;
}