/*
    Multiton
    Archive of Reversing.ID
    Design Pattern (Creational)

Definition:
    
Compile:
    [gcc]
    $ g++ multiton-managed.cpp -o multiton-managed

    [msvc]
    $ cl multiton-managed.cpp

Run:
    $ multiton-managed
*/
#include <iostream>
#include <map>

/**
 * Definisi (Gang of Four):
 * 
 * Skenario:
 * 
 */
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
    static std::map<std::string, Managed *> _Instance;

protected:
     Multiton() { }
    ~Multiton() { }

public:
    // Hapus semua instance multiton
    static void clear()
    {
        for (auto & it : _Instance)
            delete it.second;
        
        _Instance.clear();
    }

    // Hapus instance multiton ini
    static void destroy(const std::string key)
    {
        auto it = _Instance.find(key);

        if (it != _Instance.end())
        {
            delete it->second;
            _Instance.erase(it);
        } 
    }

    // Dapatkan instance multiton
    static Managed * getInstance(std::string key)
    {
        auto it = _Instance.find(key);

        if (it != _Instance.end())
            return it->second;

        Managed * item = new Managed();
        _Instance[key] = item;
        return item;
    }
};

// Instansiasi komponen statis
std::map<std::string, Managed *> Multiton::_Instance;

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Key tidak ditemukan sehingga instance baru akan diciptakan
    Managed * p1 = Multiton::getInstance("ReversingID");
    std::cout << p1 << std::endl;

    // Key ditemukan sehingga instance yang sudah ada akan diberikan
    Managed * p2 = Multiton::getInstance("ReversingID");
    std::cout << p2 << std::endl;

    // Key tidak ditemukan sehingga instance baru akan diciptakan
    Managed * p3 = Multiton::getInstance("Reversing"); 
    std::cout << p3 << std::endl;

    return 0;
}