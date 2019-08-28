/*
    Factory Method
    Archive of Reversing.ID
    Design Pattern (Creational)

    Menggunakan sebuah method untuk menciptakan objek.

Compile:
    [clang]
    $ clang++ factory-method.cpp -o factory-method
    
    [gcc]
    $ g++ factory-method.cpp -o factory-method

    [msvc]
    $ cl factory-method.cpp

Run:
    $ factory-method
*/


/* *********************************** DECLARATION *********************************** */

/**
 * Product (abstract)
 * 
 * Kelas dasar dari seluruh product yang akan dihasilkan.
 * Kelas dasar dapat pula berupa sebuah kelas konkret.
 */
class Product
{
public:
    virtual ~Product() { }

    /* Contoh operasi kelas yang akan diimplementasikan oleh setiap kelas turunan */
    virtual int operation() = 0;
};

// ======================================================================================

/**
 * ProductA (concrete)
 * 
 * Varian dari Product
 */
class ProductA : public Product
{
public:
     ProductA() { }
    ~ProductA() { }

    int operation()
    {
        return 135;
    }
};

// ======================================================================================

/**
 * ProductB (concrete)
 * 
 * Varian dari Product
 */
class ProductB : public Product
{
public:
     ProductB() { }
    ~ProductB() { }

    int operation()
    {
        return 182;
    }
};

// ======================================================================================

/**
 * Creator (abstract)
 * 
 * Interface dari kelas yang akan menghasilkan product
 */
class Creator 
{
public:
    virtual ~Creator() { }
    virtual Product * build() = 0;
};

// ======================================================================================

/**
 * ProductA_Creator (concrete)
 * 
 * Kelas yang akan menghasilkan produk melalui pemanggilan fungsi tertentu.
 * Fungsi mengabstraksi proses pembuatan sebuah kelas sehingga pengguna
 * dapat memeroleh kelas tanpa harus melakukan pembuatan secara manual.
 * 
 * Kelas ini akan menghasilkan ProductA
 */
class ProductA_Creator : public Creator
{
public:
     ProductA_Creator() { }
    ~ProductA_Creator() { }

    /* buildProduct() akan menghasilkan objek ProductA */
    Product * build()
    {
        return new ProductA();
    }
};

// ======================================================================================

/**
 * ProductB_Creator (concrete)
 * 
 * Kelas yang akan menghasilkan produk melalui pemanggilan fungsi tertentu.
 * Fungsi mengabstraksi proses pembuatan sebuah kelas sehingga pengguna
 * dapat memeroleh kelas tanpa harus melakukan pembuatan secara manual.
 * 
 * Kelas ini akan menghasilkan ProductB
 */
class ProductB_Creator : public Creator
{
public:
     ProductB_Creator() { }
    ~ProductB_Creator() { }

    /* buildProduct() akan menghasilkan objek ProductB */
    Product * build()
    {
        return new ProductB();
    }
};


/* *********************************** USAGE *********************************** */
#include <iostream>

int main(int argc, char* argv[])
{
    Creator * creator = nullptr;

    /* Tes produk A */
    creator = new ProductA_Creator();
    Product * prod1 = creator->build();
    std::cout << prod1->operation() << std::endl;
    delete prod1;
    delete creator;

    /* Tes produk B */
    creator = new ProductB_Creator();
    Product * prod2 = creator->build();
    std::cout << prod2->operation() << std::endl;
    delete prod2;
    delete creator;

    return 0;
}