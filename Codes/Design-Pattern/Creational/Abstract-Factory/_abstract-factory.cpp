/*
    Abstract Factory
    Archive of Reversing.ID
    Design Pattern (Creational)

Definition:
    Menawarkan interface untuk menciptakan sekelompok objek yang memiliki keterkaitan
    tanpa menspesifikasi objek yang akan diinstansiasi. AbstractFactory merupakan sebuah
    enkapsulasi dari beberapa factory yang memiliki tema sejenis.

Compile:
    [gcc]
    $ g++ abstract-factory.cpp -o abstract-factory

    [msvc]
    $ cl abstract-factory.cpp

Run:
    $ abstract-factory
*/
#include <iostream>

/**
 * Definisi (Gang of Four):
 *    Provide an interface for creating families of related or dependant objects without
 *    specifying their concrete classes.
 * 
 * Skenario:
 *    * Kelas abstract AbstractFactory dapat membuat sebuah objek AbstractProduct
 *    * Kelas ProductA dan ProductB merupakan turunan dari AbstractProduct dengan karakteristik
 *      tertentu.
 *    * Kelas Factory merupakan turunan dari AbstractFactory. 
 *    * Factory dapat menciptakan objek ProductA dan ProductB, masing-masing menggunakan
 *      sebuah factory method yang terpisah. 
 */
/* *********************************** DECLARATION *********************************** */
/**
 * AbstractProduct (abstract)
 * 
 * Kelas dasar dari seluruh product yang akan dihasilkan.
 * Kelas dasar dapat pula berupa sebuah kelas konkret.
 */
class AbstractProduct
{
public:
    /**
     * Virtual destructor.
     */
    virtual ~AbstractProduct() { }

    /**
     * Contoh operasi kelas yang akan diimplementasikan oleh setiap kelas turunan
     */
    virtual void operation() = 0;
};

// ======================================================================================

/**
 * ProductA (concrete)
 */
class ProductA : public AbstractProduct
{
public:
     ProductA() { }
    ~ProductA() { }

    void operation()
    {
        std::cout << "Product A operation" << std::endl;
    }
};

// ======================================================================================

/**
 * ProductB (concrete)
 */
class ProductB : public AbstractProduct
{
public:
     ProductB() { }
    ~ProductB() { }

    void operation()
    {
        std::cout << "Product B operation" << std::endl;
    }
};

// ======================================================================================

/**
 * AbstractFactory (abstract)
 * 
 * Interface dari kelas yang akan menghasilkan product.
 */
class AbstractFactory 
{
public:
    virtual ~AbstractFactory() { }
    
    virtual AbstractProduct * build_ProductA() = 0;
    virtual AbstractProduct * build_ProductB() = 0;
};

// ======================================================================================

/**
 * ConcreteFactory (concrete)
 * 
 * Kelas yang akan menghasilkan produk-produk melalui pemanggilan fungsi tertentu.
 * Masing-masing fungsi mengabstraksi proses pembuatan sebuah kelas sehingga pengguna
 * dapat memeroleh kelas tanpa harus melakukan pembuatan secara manual.
 */
class ConcreteFactory : public AbstractFactory
{
public:
    AbstractProduct * build_ProductA()
    {
        return new ProductA();
    }

    AbstractProduct * build_ProductB()
    {
        return new ProductB();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Instansiasi objek factory untuk membangun produk
    AbstractFactory * factory = new ConcreteFactory();

    // Bangun tiap produk menggunakan factory
    AbstractProduct * A = factory->build_ProductA(); 
    AbstractProduct * B = factory->build_ProductB();

    // Tes tiap operasi.
    A->operation();
    B->operation();

    delete factory;
    delete A;
    delete B;

    return 0;
}