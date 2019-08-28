/*
    Singleton
    Archive of Reversing.ID
    Design Pattern (Creational)

    Membuat instance di heap tanpa pengelolaan.
    
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

/* *********************************** DECLARATION *********************************** */

/**
 * Singleton (concrete)
 */
class Singleton
{
    // Instance didefinisikan sebagai static
    static Singleton * _instance;

public:
    static Singleton * getInstance()
    {
        if (nullptr == _instance)
            _instance = new Singleton();
        
        return _instance;
    }
};

// Instansiasi komponen statis
Singleton* Singleton::_instance = nullptr;

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Instansiasi awal akan menciptakan objek baru
    Singleton * inst1 = Singleton::getInstance(); 

    // Instansiasi selanjutnya akan mengambil instance
    // yang telah diciptakan sebelumnya.
    Singleton * inst2 = Singleton::getInstance();    

    return 0;
}