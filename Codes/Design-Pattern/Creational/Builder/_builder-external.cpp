/*
    Builder
    Archive of Reversing.ID
    Design Pattern (Creational)

Definition:
    Menawarkan solusi yang fleksibel untuk menciptakan (create) objek.
    Tujuan Builder adalah untuk memisahkan antara konstruksi sebuah objek yang kompleks
    dengan representasinya.

Compile:
    [gcc]
    $ g++ builder.cpp -o builder

    [msvc]
    $ cl builder.cpp

Run:
    $ builder
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
        std::cout << "A Size     : " << _A->size << std::endl;
        std::cout << "B Capacity : " << _B->capacity << std::endl;
        std::cout << "C Output   : " << _C->output   << std::endl;
    }
};

// ======================================================================================

/**
 * AbstractBuilder (abstract)
 * 
 * Bertanggung jawab untuk membangun product dengan detail yang dibutuhkan
 */
class AbstractBuilder
{
protected:
    PartA * _A;
    PartB * _B;
    PartC * _C;

public:
    virtual PartA   * build_PartA() = 0; 
    virtual PartB   * build_PartB() = 0; 
    virtual PartC   * build_PartC() = 0;
    virtual Product * build() = 0;

    virtual ~AbstractBuilder() { }
};

// ======================================================================================

/**
 * BuilderGradeA (concrete)
 * 
 * Kelas konkret yang bertanggung jawab menciptakan setiap parts dan produk yang 
 * membutuhkan part tersebut.
 * 
 * Kelas ini merupakan salah satu varian yang mungkin.
 */
class BuilderGradeA : public AbstractBuilder
{
public:
    PartA * build_PartA()
    {        
        if (_A) 
            delete _A;

        _A = new PartA();
        _A->size = 135;

        return _A;
    } 

    PartB * build_PartB()
    {
        if (_B)
            delete _B;

        _B = new PartB();
        _B->capacity = 10;

        return _B;
    } 

    PartC * build_PartC()
    {
        if (_C)
            delete _C;

        _C = new PartC();
        _C->output = 30;

        return _C;
    }

    Product * build()
    {
        // Buat product baru
        Product * product = new Product(_A, _B, _C);
        
        // reset
        _A = nullptr;
        _B = nullptr;
        _C = nullptr;

        return product;
    }
};

// ======================================================================================

/**
 * Director (abstract)
 * 
 * Bertanggung jawab terhadap keseluruhan proses
 */
class Director 
{
    AbstractBuilder * _builder;

public:
    Director(AbstractBuilder* builder)
    {
        _builder = builder;
    }

    void set_builder(AbstractBuilder * builder)
    {
        _builder = builder;
    }

    Product * construct()
    {
        _builder->build_PartA();
        _builder->build_PartB();
        _builder->build_PartC();
        return _builder->build();
    } 
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    BuilderGradeA * builderA;
    Director      * director;
    Product       * product;

    // Instansiasi builderA
    builderA = new BuilderGradeA();

    // Instansiasi director
    director = new Director(builderA);

    // Konstruksi produk melalui directory
    product = director->construct();
    product->specification();

    delete product;    
    delete director;
    delete builderA;

    return 0;
}