/*
    Factory Method
    Archive of Reversing.ID
    Design Pattern (Creational)

Definition:
    Mendefinisikan sebuah interface untuk menciptakan sebuah objek tanpa menspesifikasi
    objek yang akan diinstansiasi. Penciptaan objek dilakukan dengan memanggil sebuah method
    (disebut factory method) sebuah kelas (bisa interface, turunan, dsb) alih-alih menggunakan
    konstruktor.

Compile:
    [gcc]
    $ g++ factory-method.cpp -o factory-method

    [msvc]
    $ cl factory-method.cpp

Run:
    $ factory-method
*/
#include <iostream>

/**
 * Definisi (Gang of Four):
 *    Define an interface for creating an object, but let subclasses decide which class to
 *    instantiate.
 * 
 * Skenario:
 *    * Kelas abstract AbstractFactory dapat membuat sebuah objek AbstractProduct
 *    * Kelas Product merupakan turunan dari AbstractProduct.
 *    * Kelas Factory merupakan turunan dari AbstractFactory. 
 *    * Tidak ada spesifikasi bahwa factory akan menghasilkan objek bertipe apa, namun
 *      Factory dapat menspesifikkan bahwa ia akan menghasilkan objek bertipe Product
 *      yang diturunkan dari AbstractProduct. 
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
     * Virtual destructor
     */
    virtual ~AbstractProduct() { }

    /**
     * Contoh operasi kelas yang akan diimplementasikan oleh setiap kelas turunan
     */
    virtual void operation() = 0;
};

// ======================================================================================

/**
 * ConcreteProduct (concrete)
 * 
 * Varian dari AbstractProduct
 */
class ConcreteProduct : public AbstractProduct
{
public:
     ConcreteProduct() { }
    ~ConcreteProduct() { }

    void operation()
    {
        std::cout << "Product A operation" << std::endl;
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
    virtual AbstractProduct * build() = 0;
};

// ======================================================================================

/**
 * ConcreteFactory (concrete)
 * 
 * Kelas yang akan menghasilkan produk melalui pemanggilan fungsi tertentu.
 * Fungsi mengabstraksi proses pembuatan sebuah kelas sehingga pengguna
 * dapat memeroleh kelas tanpa harus melakukan pembuatan secara manual.
 */
class ConcreteFactory : public AbstractFactory
{
public:
     ConcreteFactory() { }
    ~ConcreteFactory() { }

    /* build() merupakan factory method yang di-override oleh ConcreteFactory */
    AbstractProduct * build()
    {
        return new ConcreteProduct();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Instansiasi objek factory untuk membangun produk
    AbstractFactory * factory = new ConcreteFactory();

    // Bangun produk (ConcreteProduct) melalui AbstractFactory.
    // Karena A merupakan ConcreteFacoty yang ditunjuk oleh super class,
    // maka pemanggilan build() akan memanggil fungsi build() yang telah di-override.
    AbstractProduct * A = factory->build();

    // Tes operasi dari produk.
    A->operation();

    delete factory;
    delete A;

    return 0;
}