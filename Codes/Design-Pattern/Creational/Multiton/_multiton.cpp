/*
    Multiton
    Archive of Reversing.ID
    Design Pattern (Creational)

Definition:
    
Compile:
    [gcc]
    $ g++ multiton.cpp -o multiton

    [msvc]
    $ cl multiton.cpp

Run:
    $ multiton
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
 * Nultiton (concrete)
 * 
 * Sekumpulan instance global dari sebuah class yang didapatkan dengan sebuah key. 
 * Objek yang diciptakan adalah objek Multiton itu sendiri.
 */
class Multiton
{
    static std::map<std::string, Multiton *> _Instance;

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
    static Multiton * getInstance(std::string key)
    {
        auto it = _Instance.find(key);

        if (it != _Instance.end())
            return it->second;

        Multiton * item = new Multiton();
        _Instance[key] = item;
        return item;
    }
};

// Instansiasi komponen statis
std::map<std::string, Multiton *> Multiton::_Instance;

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Key tidak ditemukan sehingga instance baru akan diciptakan
    Multiton * p1 = Multiton::getInstance("ReversingID");

    // Key ditemukan sehingga instance yang sudah ada akan diberikan
    Multiton * p2 = Multiton::getInstance("ReversingID");

    // Key tidak ditemukan sehingga instance baru akan diciptakan
    Multiton * p3 = Multiton::getInstance("Reversing"); 

    return 0;
}