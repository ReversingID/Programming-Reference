/*
    Multiton
    Archive of Reversing.ID
    Design Pattern (Creational)
    
Compile:
    [clang]
    $ clang++ multiton.cpp -o multiton
    
    [gcc]
    $ g++ multiton.cpp -o multiton

    [msvc]
    $ cl multiton.cpp

Run:
    $ multiton
*/
#include <map>


/* *********************************** DECLARATION *********************************** */
/**
 * Multiton (concrete)
 * 
 * Sekumpulan instance global dari sebuah class yang didapatkan dengan sebuah key. 
 * Objek yang diciptakan adalah objek Multiton itu sendiri.
 */
class Multiton
{
    static std::map<std::string, Multiton *> _instance;

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
    static Multiton * getInstance(std::string key)
    {
        auto it = _instance.find(key);

        if (it != _instance.end())
            return it->second;

        Multiton * item = new Multiton();
        _instance[key] = item;
        return item;
    }
};

// Instansiasi komponen statis
std::map<std::string, Multiton *> Multiton::_instance;

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Key tidak ditemukan sehingga instance baru akan diciptakan
    Multiton * p1 = Multiton::getInstance("ReversingID");

    // Key ditemukan sehingga instance yang sudah ada akan diberikan
    Multiton * p2 = Multiton::getInstance("ReversingID");

    // Key tidak ditemukan sehingga instance baru akan diciptakan
    Multiton * p3 = Multiton::getInstance("Reversing"); 

    // Periksa alamat tiap instance multiton
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;


    // Tidak perlu delete p1/p2/p3 karena dikelola oleh Multiton

    return 0;
}