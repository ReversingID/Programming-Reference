/*
    Object Pool
    Archive of Reversing.ID
    Design Pattern (Creational)

    
Compile:
    [clang]
    $ clang++ object-pool.cpp -o object-pool
    
    [gcc]
    $ g++ object-pool.cpp -o object-pool

    [msvc]
    $ cl object-pool.cpp

Run:
    $ object-pool
*/
#include <iostream>
#include <list>

/**
 * Skenario:
 * 
 */
/* *********************************** DECLARATION *********************************** */
/**
 * Resource (concrete)
 * 
 * Tipe kelas yang akan dikelola oleh Object Pool.
 */
class Resource 
{
public:
    Resource() { }

    // Mengembalikan state resource ke keadaan default
    // sehingga dapat dipergunakan kembali.
    void reset()
    { }
};

// ======================================================================================

/**
 * ObjectPool (concrete)
 */
class ObjectPool
{
    // Kumpulan objek yang tersedia / siap digunakan
    std::list<Resource*>  _available;

    // catatan: sebuah list dapat pula digunakan untuk mencatat resource yang
    // sedang digunakan, namun di contoh ini kita memilih untuk tidak melakukannya.

public:
    // Pool dapat diciptakan di awal dengan jumlah yang ditentukan, atau dapat dikembangkan
    // setiap kali objek dibutuhkan.

    ObjectPool( )
    { }
     
    ObjectPool(int n)
    {
        for (int i = 0; i < n; i++)
            _available.push_front(new Resource());
    }

    virtual ~ObjectPool()
    {
        for (auto & it : _available)
            delete it;
        
        _available.clear();
    }

    Resource * getResource()
    {
        Resource * item = nullptr;

        // Alternatif opsi:
        // Membuat resource baru ketika resource tidak tersedia
        if (_available.empty())
            item = new Resource();
        // Mengambil item yang ada di paling depan
        else 
        {
            item = _available.front();
            _available.pop_front();
        }

        return item;
    }    

    bool returnResource(Resource * resource)
    {
        // Reset kondisi resource
        resource->reset();

        // Masukkan kembali ke pool
        _available.push_back(resource);
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])

{
    // Menciptakan sebuah pool 
    ObjectPool pool(10);

    std::list<Resource*> collector;

    // Mengambil seluruh resource
    for (int i = 0; i < 11; i++)
    {
        Resource * res = pool.getResource();

        std::cout << "Resource: " << res << std::endl;
        collector.push_front(res);
    }

    return 0;
}