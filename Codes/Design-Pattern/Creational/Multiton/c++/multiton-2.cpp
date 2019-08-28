/*
    Multiton
    Archive of Reversing.ID
    Design Pattern (Creational)
    
Compile:
    [clang]
    $ clang++ multiton.cpp -o multiton
    
    [gcc]
    $ g++ multiton-managed.cpp -o multiton-managed

    [msvc]
    $ cl multiton-managed.cpp

Run:
    $ multiton-managed
*/
#include <map>


/* *********************************** DECLARATION *********************************** */
/**
 * Managed (concrete)
 * 
 * Tipe kelas yang akan dikelola oleh multiton.
 */
class Managed 
{
public:
    Managed() { }
};

// ======================================================================================

/**
 * Multiton (concrete)
 * 
 * Sekumpulan instance global dari sebuah class yang didapatkan dengan sebuah key.
 * Objek yang diciptakan adalah objek bertipe lain yang dikelola oleh Multiton.
 */
class Multiton
{
    static std::map<std::string, Managed *> _instance;

protected:
     Multiton() { }
    ~Multiton() { }

public:
    // Hapus semua instance multiton
    static void clear()
    {
        for (auto & it : _instance)
            delete it.second;
        
        _instance.clear();
    }

    // Hapus instance multiton ini
    static void destroy(const std::string key)
    {
        auto it = _instance.find(key);

        if (it != _instance.end())
        {
            delete it->second;
            _instance.erase(it);
        } 
    }

    // Dapatkan instance multiton
    static Managed * getInstance(std::string key)
    {
        auto it = _instance.find(key);

        if (it != _instance.end())
            return it->second;

        Managed * item = new Managed();
        _instance[key] = item;
        return item;
    }
};

// Instansiasi komponen statis
std::map<std::string, Managed *> Multiton::_instance;

/* *********************************** USAGE *********************************** */
#include <iostream>

int main(int argc, char* argv[])
{
    // Key tidak ditemukan sehingga instance baru akan diciptakan
    Managed * p1 = Multiton::getInstance("ReversingID");

    // Key ditemukan sehingga instance yang sudah ada akan diberikan
    Managed * p2 = Multiton::getInstance("ReversingID");

    // Key tidak ditemukan sehingga instance baru akan diciptakan
    Managed * p3 = Multiton::getInstance("Reversing"); 

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;


    return 0;
}