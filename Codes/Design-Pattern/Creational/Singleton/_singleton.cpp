/*
    Singleton
    Archive of Reversing.ID
    Design Pattern (Creational)

Definition:
    
Compile:
    [gcc]
    $ g++ singleton.cpp -o singleton

    [msvc]
    $ cl singleton.cpp

Run:
    $ singleton
*/
#include <iostream>

/**
 * Definisi (Gang of Four):
 * 
 * Skenario:
 * 
 */
/* *********************************** DECLARATION *********************************** */
/**
 * Singleton (concrete)
 */
class Singleton
{
    static Singleton * _Instance;

public:
    static Singleton * getInstance()
    {
        if (nullptr == _Instance)
        {
            _Instance = new Singleton();
        }
        return _Instance;
    }
};

// Instansiasi komponen statis
Singleton* Singleton::_Instance = nullptr;

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