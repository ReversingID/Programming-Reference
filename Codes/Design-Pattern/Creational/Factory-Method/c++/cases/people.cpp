/*
    People
    Archive of Reversing.ID
    Design Pattern (Creational/Factory Method)
    
Compile:
    [clang]
    $ clang++ people.cpp -o people
    
    [gcc]
    $ g++ people.cpp -o people

    [msvc]
    $ cl people.cpp

Run:
    $ people
*/
#include <iostream>
#include <memory>


/* *********************************** DECLARATION *********************************** */
enum class PendudukType { PETANI,  PETERNAK,  PEDAGANG };

/**
 * Penduduk (abstract)
 */
class Penduduk 
{
public:
    virtual ~Penduduk() { }

    /* sign that greet the adventurer */
    virtual std::string sapa() = 0;
};

// ======================================================================================
/**
 * Petani (concrete)
 */
class Petani : public Penduduk 
{
public:
    virtual std::string sapa()
    {
        return "Petani di desa.";
    }
};

// ======================================================================================
/**
 * Peternak (concrete)
 */
class Peternak : public Penduduk
{
public:
    virtual std::string sapa()
    {
        return "Peternak sapi di desa.";
    }
};

// ======================================================================================
/**
 * Pedagang (concrete)
 */
class Pedagang : public Penduduk
{
public:
    virtual std::string sapa()
    {
        return "Pedagang batu akik di desa.";
    }
};

// ======================================================================================

class PendudukFactory
{
public:
    /* 
        Implementasi get() sebagai factory method untuk mengembalikan penduduk sesuai dengan
        tipe yang diinginkan.
    */
    static std::unique_ptr<Penduduk> get(PendudukType type)
    {
        switch (type)
        {
            case PendudukType::PETANI: 
                return getPetani();
            case PendudukType::PETERNAK: 
                return getPeternak();
            case PendudukType::PEDAGANG: 
                return getPedagang();
            default:
                return nullptr;
        }
    }

    /*
        Implementasi getX() sebagai factory method untuk mengembalikan penduduk melalui 
        pemanggilan secara individual.
    */
    static inline auto getPetani()      -> std::unique_ptr<Penduduk>
    {
        return std::make_unique<Petani>();
    }
    static inline auto getPeternak()    -> std::unique_ptr<Penduduk>
    {
        return std::make_unique<Peternak>();
    }
    static inline auto getPedagang()    -> std::unique_ptr<Penduduk>
    {
        return std::make_unique<Pedagang>();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Bangun tiap produk menggunakan factory
    auto petani   = PendudukFactory::get(PendudukType::PETANI);
    auto peternak = PendudukFactory::get(PendudukType::PETERNAK);
    auto pedagang = PendudukFactory::get(PendudukType::PEDAGANG);

    // Tes tiap operasi.
    std::cout << petani->sapa() << std::endl;
    std::cout << peternak->sapa() << std::endl;
    std::cout << pedagang->sapa() << std::endl;

    return 0;
}