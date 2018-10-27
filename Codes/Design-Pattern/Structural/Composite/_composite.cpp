/*
    Composite
    Archive of Reversing.ID
    Design Pattern (Structural)

Definition:
    Mendeskripsikan sekelompok objek yang diperlakukan selayaknya sebuah instance dari 
    sebuah objek. Tujuannya adalah untuk membentuk komposisi objek menjadi struktur tree
    sehingga merepresentasikan hirarki part-whole.

Compile:
    [gcc]
    $ g++ composite.cpp -o composite

    [msvc]
    $ cl composite.cpp

Run:
    $ composite
*/
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
    /**
     * Virtual destructor.
     */
    virtual ~Component() { }
    
    virtual void operation () { }
    virtual void add (const Component & com) { }
    virtual void remove (const Component & com) { }
    virtual Component * getChild (int index) 
    {
        return 0;
    }
};

// ======================================================================================

/**
 * Composite (concrete)
 * 
 * Composite merupakan turunan Component yang diakses sebagai kumpulan beberapa Component.
 */
class Composite : public Component 
{
    std::vector<Component*> _coms;

public:
    void operation ()
    {
        for (auto com : _coms)
            com->operation();
    }

    void add (Component * com) 
    {
        _coms.push_back(com);
    }

    void remove (Component * com)
    {
        
    }

    Component * getChild (int index) 
    {
        return _coms[index];
    }
};

// ======================================================================================

/**
 * Leaf (concrete)
 * 
 * 
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
    Leaf * leaf1 = new Leaf(1);
    Leaf * leaf2 = new Leaf(2);

    std::cout << "Instansiasi leaf" << std::endl;
    leaf1->operation();
    leaf2->operation();
    std::cout << std::endl;


    // Membangun objek komposit yang terdiri dari leaf1 dan leaf2
    Composite * com = new Composite();
    com->add(leaf1);
    com->add(leaf2);

    std::cout << "Melakukan operasi terhadap keseluruhan objek" << std::endl;
    com->operation();
    std::cout << std::endl;


    // Mendapatkan objek individual dan melakukan operasi terhadapnya
    Component * leaf = com->getChild(0);

    std::cout << "Melakukan operasi terhadap Leaf1" << std::endl;
    leaf->operation();
    std::cout << std::endl;

    delete leaf1;
    delete leaf2;
    delete com;

    return 0;
}