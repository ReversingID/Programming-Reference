/*
    Singleton
    Archive of Reversing.ID
    Design Pattern (Creational)

    Modern C++

    Menggunakan sebuah instance yang didefinisikan sebagai static dan menjadikannya
    sebagai instance rujukan.
    
Compile:
    [clang]
    $ clang++ singleton.cpp -o singleton
    
    [gcc]
    $ g++ singleton.cpp -o singleton

    [msvc]
    $ cl singleton.cpp

Run:
    $ singleton
*/
#include <memory>


/* *********************************** DECLARATION *********************************** */

/**
 * Singleton (concrete)
 */
class Singleton
{
     Singleton() = default;
    ~Singleton() = default;

    Singleton(const Singleton &) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton &) = delete;
    Singleton& operator=(Singleton &&) = delete;

public:
    static Singleton& getInstance()
    {
        static Singleton instance;
        return instance;
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    /* Instansiasi awal akan menciptakan objek baru (Singleton&) */ 
    auto& inst1 = Singleton::getInstance();

    /*
    Instansiasi selanjutnya akan mengambil instance
    yang telah diciptakan sebelumnya.
    */
    auto& inst2 = Singleton::getInstance();

    return 0;
}