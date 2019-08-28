/*
    Factory Method
    Archive of Reversing.ID
    Design Pattern (Creational)

    Menggunakan function sebagai pengganti method untuk instansiasi.

    Kelemahan:
    Apabila terdapat tipe baru, maka perlu dilakukan perubahan terhadap method.

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
#include <memory>


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

enum class ProductType { PRODUCT_A, PRODUCT_B };

auto buildProduct(ProductType type) -> std::unique_ptr<Product>
{
    switch (type)
    {
        case ProductType::PRODUCT_A:
            return std::unique_ptr<Product>{new ProductA};
        case ProductType::PRODUCT_B:
            return std::unique_ptr<Product>{new ProductB};
        default:
            return nullptr;
    }
}


/* *********************************** USAGE *********************************** */
#include <iostream>

int main(int argc, char* argv[])
{
    /* Tes produk A */
    auto prod1 = buildProduct(ProductType::PRODUCT_A);
    std::cout << prod1->operation() << std::endl;

    /* Tes produk B */
    auto prod2 = buildProduct(ProductType::PRODUCT_B);
    std::cout << prod2->operation() << std::endl;

    return 0;
}