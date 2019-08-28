/*
    Composite
    Archive of Reversing.ID
    Design Pattern (Structural)

Compile:
    [clang]
    $ clang++ composite.cpp -o composite

    [gcc]
    $ g++ composite.cpp -o composite

    [msvc]
    $ cl composite.cpp

Run:
    $ composite
*/
#include <memory>
#include <iostream>
#include <vector>


/* *********************************** DECLARATION *********************************** */

/**
 * Component (abstract)
 * 
 * Komponen-komponen yang akan dikomposisikan ke dalam Composite.
 */
class Component
{
public:
    /* Virtual destructor */
    virtual ~Component() { }
    
    virtual void operation () { }
};

// ======================================================================================

/**
 * Composite (concrete)
 * 
 * Composite merupakan turunan Component yang diakses sebagai kontainer bagi kumpulan 
 * Component.
 */
class Composite : public Component 
{
    using ComponentPtr = std::unique_ptr<Component>;

    std::vector<ComponentPtr> _coms;

public:
    void operation () override
    {
        for (auto& com : _coms)
            com->operation();
    }

    void add (Component * com)
    {
        _coms.push_back(std::unique_ptr<Component>(com));
    }

    void remove (int index)
    {
        _coms.erase(_coms.begin() + index);
    }

    auto getChild (int index) -> std::unique_ptr<Component>&
    {
        return _coms[index];
    }
};

// ======================================================================================

/**
 * Leaf (concrete)
 * 
 * Implementasi akhir dari sebuah componen yang melakukan operasi.
 */
class Leaf : public Component 
{
    int _id;

public:
    Leaf (int id)
    {
        _id = id;
    }

    void operation()
    {
        std::cout << "Leaf(" << _id << ")::operation ... " << std::endl;
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Instansiasi komponen secara individual
    auto leaf1 = new Leaf(1);
    auto leaf2 = new Leaf(2);

    std::cout << "Instansiasi leaf" << std::endl;
    leaf1->operation();
    leaf2->operation();
    std::cout << std::endl;


    // Membangun objek komposit yang terdiri dari leaf1 dan leaf2
    auto com = std::make_unique<Composite>();
    com->add(leaf1);
    com->add(leaf2);

    std::cout << "Melakukan operasi terhadap keseluruhan objek" << std::endl;
    com->operation();
    std::cout << std::endl;


    // Mendapatkan objek individual dan melakukan operasi terhadapnya
    auto& leaf = com->getChild(0);

    std::cout << "Melakukan operasi terhadap Leaf1" << std::endl;
    leaf->operation();
    std::cout << std::endl;

    return 0;
}