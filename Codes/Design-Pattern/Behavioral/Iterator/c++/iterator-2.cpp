/*
    Iterator
    Archive of Reversing.ID
    Design Pattern (Behavioral)

    Iterator dideklarasikan di dalam Collection.

Compile:
    [clang]
    $ clang++ iterator.cpp -o iterator
    
    [gcc]
    $ g++ iterator.cpp -o iterator

    [msvc]
    $ cl iterator.cpp

Run:
    $ iterator
*/
#include <memory>
#include <iostream>


/* *********************************** DECLARATION *********************************** */

/**
 * ConcreteCollection (concrete)
 */
class Collection
{
    int _items[64];

public:
    // collection ini akan mengisi _items ketika objek dibentuk
    Collection()
    {
        for (int i = 0; i < 64; i++)
            _items[i] = i;
    }

    int getItem(int idx) 
    {
        if (idx < size())
            return _items[idx];
        else
            return 0;
    }
    int size() 
    {
        return 64;
    }

    /**
     * Iterator
     */
    
    class Iterator
    {
        std::shared_ptr<Collection> _collection;
        int     _idx;

    public:
        Iterator(std::shared_ptr<Collection> collection, int idx = 0) : _collection{collection}, _idx{idx}
        { }

        // Menunjuk elemen pertama dalam collection.
        void first()
        {
            _idx = 0;
        }

        // Menunjuk elemen berikutnya dalam collection
        void next() 
        {
            if (_idx < _collection->size())
                _idx ++;
        }

        // Periksa apakah iterasi sudah mencapai akhir
        bool done() 
        {
            return (_idx == _collection->size());
        }

        // mendapatkan elemen yang sedang ditunjuk saat ini.
        int  current()
        {
            return _collection->getItem(_idx);
        }
    };
};

// ======================================================================================


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto coll = std::make_shared<Collection>();
    auto it   = std::make_shared<Collection::Iterator>(coll, 0);
    
    for (; !it->done(); it->next())
        std::cout << it->current() << std::endl;

    return 0;
}