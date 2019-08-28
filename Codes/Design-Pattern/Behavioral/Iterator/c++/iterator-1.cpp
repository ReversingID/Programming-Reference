/*
    Iterator
    Archive of Reversing.ID
    Design Pattern (Behavioral)

    Iterator dan Collection saling lepas.

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
 * Collection (abstract)
 */
class Collection
{
public:
    virtual ~Collection() { }

    virtual int getItem(int idx) = 0;
    virtual int size() = 0;
};

// ======================================================================================

/**
 * ConcreteCollection (concrete)
 */
class ConcreteCollection: public Collection
{
    int _items[64];

public:
    // collection ini akan mengisi _items ketika objek dibentuk
    ConcreteCollection()
    {
        for (int i = 0; i < 64; i++)
            _items[i] = i;
    }

    int getItem(int idx) override 
    {
        if (idx < size())
            return _items[idx];
        else
            return 0;
    }
    int size() override 
    {
        return 64;
    }
};

// ======================================================================================

/**
 * Iterator (abstract)
 */
class Iterator
{
public:
    virtual ~Iterator() { }

    virtual void first() = 0;
    virtual void next()  = 0;
    virtual bool done()  = 0;
    virtual int  current() = 0;
};

// ======================================================================================

/**
 * ConcreteIterator (concrete)
 */
class ConcreteIterator: public Iterator
{
    std::shared_ptr<Collection> _collection;
    int     _idx;

public:
    ConcreteIterator(std::shared_ptr<Collection> collection, int idx = 0) : _collection{collection}, _idx{idx}
    { }

    // Menunjuk elemen pertama dalam collection.
    void first() override
    {
        _idx = 0;
    }

    // Menunjuk elemen berikutnya dalam collection
    void next()  override
    {
        if (_idx < _collection->size())
            _idx ++;
    }

    // Periksa apakah iterasi sudah mencapai akhir
    bool done()  override
    {
        return (_idx == _collection->size());
    }

    // mendapatkan elemen yang sedang ditunjuk saat ini.
    int  current() override
    {
        return _collection->getItem(_idx);
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    auto coll = std::make_shared<ConcreteCollection>();
    auto it   = std::make_shared<ConcreteIterator>(coll, 0);
    
    for (; !it->done(); it->next())
        std::cout << it->current() << std::endl;

    return 0;
}