/*
    Singleton
    Archive of Reversing.ID
    Design Pattern (Creational)

    Modern C++

    Membuat instance di heap yang akan dikelola oleh unique_ptr<> 
    
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

    Singleton(const Singleton &) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton &) = delete;
    Singleton& operator=(Singleton &&) = delete;

public:
    ~Singleton() = default;

    static Singleton& getInstance()
    {
        // Instance didefinisikan sebagai static
        static auto _instance = std::unique_ptr<Singleton>{nullptr};

        if (!_instance)
            _instance.reset(new Singleton);

        return *_instance.get();
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