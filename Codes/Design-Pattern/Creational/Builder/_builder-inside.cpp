/*
    Builder
    Archive of Reversing.ID
    Design Pattern (Creational)

Definition:
    Menawarkan solusi yang fleksibel untuk menciptakan (create) objek.
    Tujuan Builder adalah untuk memisahkan antara konstruksi sebuah objek yang kompleks
    dengan representasinya.

Varian:
    Builder merupakan class anggota dari Product (inner class).
    Pembuatan product tanpa melibatkan sebuah director.

Compile:
    [gcc]
    $ g++ builder-inside.cpp -o builder-inside

    [msvc]
    $ cl builder-inside.cpp

Run:
    $ builder-inside
*/
#include <iostream>

/* *********************************** DECLARATION *********************************** */
/**
 * Beberapa parts yang membentuk sebuah product.
 * 
 * Setiap part / komponen dapat berupa objek yang saling independen dan memerlukan
 * perlakuan khusus ketika diciptakan.
 */
class PartA
{
public:
    int size;
};

class PartB 
{
public:
    int capacity;
};

class PartC 
{
public:
    int output;
};

// ======================================================================================

/**
 * Product (concrete)
 * 
 * Produk yang akan dihasilkan oleh builder.
 * Terdiri dari beberapa komponen yang kompleks dan perlu diciptakan dengan konfigurasi 
 * tertentu untuk membuat produk yang berbeda.
 */
class Product
{
    PartA * _A;
    PartB * _B;
    PartC * _C;

public:
    /**
     * Product Builder
     * 
     * Forward declaration untuk builder
     */
    class Builder;
    
    /**
     * Objek dikonstruksi dengan beberapa parts
     * Namun pembuatan masing-masing parts dilakukan oleh pihak lain.
     */
    Product(PartA* A, PartB * B, PartC * C) : _A(A), _B(B), _C(C)
    {

    }

    ~Product()
    {
        delete [] _A;
        delete [] _B;
        delete [] _C;
    }

    /**
     * Contoh operasi yang menggunakan parts
     */
    void specification()
    {
        std::cout << "A Size: " <<_A->size << std::endl;
        std::cout << "B Capacity: " << _B->capacity << std::endl;
        std::cout << "C Output: "   << _C->output   << std::endl;
    }
};

// ======================================================================================

/**
 * Product::Builder (concrete)
 * 
 * Kelas konkret yang bertanggung jawab menciptakan setiap parts dan produk yang 
 * membutuhkan part tersebut.
 * 
 * Kelas ini merupakan salah satu varian yang mungkin.
 */
class Product::Builder 
{
    PartA * _A; 
    PartB * _B; 
    PartC * _C;

public:
    Builder()
    {
        _A = new PartA();
        _B = new PartB();
        _C = new PartC();
    }

    ~Builder()
    {
        if (_A) delete _A;
        if (_B) delete _B;
        if (_C) delete _C;
    }

    Builder& setA(int val)
    {        
        _A->size = val;
        return *this;
    } 

    Builder& setB(int val)
    {
        _B->capacity = val;
        return *this;
    } 

    Builder& setC(int val)
    {
        _C->output = val;
        return *this;
    }

    Product build()
    {
        // Buat product baru
        Product product {_A, _B, _C};
        
        // reset
        _A = new PartA();
        _B = new PartB();
        _C = new PartC();

        return product;
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Penggunaan sederhana --------------------------------
    Product p1 = Product::Builder().setA(135).setB(10).setC(30).build();
    p1.specification();

    std::cout << std::endl;

    // Penggunaan tingkat lanjut ---------------------------
    Product::Builder b;
    Product p2 = b.build();     // Dapatkan product dengan nilai default
    p2.specification();

    std::cout << std::endl;

    b.setC(15);
    Product p3 = b.build();     // Dapatkan produk dengan nilai C di-set
    p3.specification();

    return 0;
}