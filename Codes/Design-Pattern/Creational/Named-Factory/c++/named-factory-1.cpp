/*
    Named Factory
    Archive of Reversing.ID
    Design Pattern (Creational)
    
Compile:
    [clang]
    $ clang++ named-factory.cpp -o named-factory
    
    [gcc]
    $ g++ named-factory.cpp -o named-factory

    [msvc]
    $ cl named-factory.cpp

Run:
    $ named-factory
*/
#include <utility>
#include <cstdint>

/* *********************************** DECLARATION *********************************** */
/**
 * NamedFactory (concrete)
 * 
 * Menciptakan objek dengan sebuah static method.
 * 
 * Named Factory dapat berupa sebuah factory dengan class abstract yang akan menghasilkan
 * objek lain.
 * 
 * Method dapat pula dikelompokkan menjadi satu ke dalam inner class yang bertindak sebagai
 * factory.
 */
class NamedFactory
{
    uint8_t _param1, _param2;

public:
    NamedFactory(uint8_t param1, uint8_t param2) : _param1(param1), _param2(param2) { }

    /* -- Membangun objek dari representasi berbeda -- */

    static NamedFactory fromA(uint8_t param1, uint8_t param2)
    {
        return std::move(NamedFactory(param1, param2));
    }

    static NamedFactory fromB(uint64_t param)
    {
        return std::move(NamedFactory(param & 0xFF, (param >> 8) & 0xFF));
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    NamedFactory nf1 = NamedFactory::fromA(135, 182);
    NamedFactory nf2 = NamedFactory::fromB(0xB687);

    return 0;
}