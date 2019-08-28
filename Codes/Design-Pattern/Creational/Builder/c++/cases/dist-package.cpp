/*
    Distribution packages
    Archive of Reversing.ID
    Design Pattern (Creational/Builder)

Compile:
    [clang]
    $ clang++ dist-package.cpp -o dist-package
    
    [gcc]
    $ g++ dist-package.cpp -o dist-package

    [msvc]
    $ cl dist-package.cpp

Run:
    $ dist-package
*/
#include <iostream>
#include <stdio.h>
#include <string.h>

/* *********************************** DECLARATION *********************************** */
enum PersistenceType
{
    File, 
    Queue, 
    Pathway
};

struct PersistenceAttribute
{
    PersistenceType type;
    char value[30];
};

/**
 * DistrWorkPackage (concrete)
 * 
 * Produk yang akan dihasilkan oleh builder.
 * Terdiri dari beberapa komponen yang kompleks dan perlu diciptakan dengan konfigurasi 
 * tertentu untuk membuat produk yang berbeda.
 */
class DistrWorkPackage
{
    char _desc[200], _temp[80];

public:
    DistrWorkPackage(const char *type)
    {
        sprintf(_desc, "Distributed Work Package for: %s", type);
    }
    
    void setFile(const char *f, const char *v)
    {
        sprintf(_temp, "\n  File(%s): %s", f, v);
        strcat(_desc, _temp);
    }

    void setQueue(const char *q, const char *v)
    {
        sprintf(_temp, "\n  Queue(%s): %s", q, v);
        strcat(_desc, _temp);
    }

    void setPathway(const char *p, const char *v)
    {
        sprintf(_temp, "\n  Pathway(%s): %s", p, v);
        strcat(_desc, _temp);
    }

    const char *getState()
    {
        return _desc;
    }
};

// ======================================================================================

/**
 * Builder (abstract)
 * 
 * Interface dari kelas yang akan menghasilkan product.
 */
class Builder
{
public:
    virtual void configureFile(const char*)    = 0;
    virtual void configureQueue(const char*)   = 0;
    virtual void configurePathway(const char*) = 0;

    DistrWorkPackage *getResult()
    {
        return _result;
    }

protected:
    DistrWorkPackage *_result;
};

// ======================================================================================

/**
 * UnixBuilder (concrete)
 * 
 * Kelas yang akan menghasilkan produk melalui pemanggilan fungsi tertentu.
 */
class UnixBuilder: public Builder
{
public:
    UnixBuilder()
    {
        _result = new DistrWorkPackage("Unix");
    }

    /*
        Method yang mendeskripsikan beberapa bagian dalam pembuatan produk.
    */
    void configureFile(const char *name)
    {
        _result->setFile("flatFile", name);
    }
    void configureQueue(const char *queue)
    {
        _result->setQueue("FIFO", queue);
    }
    void configurePathway(const char *type)
    {
        _result->setPathway("thread", type);
    }
};

// ======================================================================================

/**
 * VmsBuilder (concrete)
 * 
 * Kelas yang akan menghasilkan produk melalui pemanggilan fungsi tertentu.
 */
class VmsBuilder: public Builder
{
public:
    VmsBuilder()
    {
        _result = new DistrWorkPackage("Vms");
    }

    /*
        Method yang mendeskripsikan beberapa bagian dalam pembuatan produk.
    */
    void configureFile(const char *name)
    {
        _result->setFile("ISAM", name);
    }
    void configureQueue(const char *queue)
    {
        _result->setQueue("priority", queue);
    }
    void configurePathway(const char *type)
    {
        _result->setPathway("LWP", type);
    }
};

// ======================================================================================

/**
 * Reader (concrete)
 * 
 * Bertanggung jawab terhadap keseluruhan proses
 */
class Reader
{
    Builder *_builder;

public:
    void setBuilder(Builder *b)
    {
        _builder = b;
    }

    void construct(PersistenceAttribute inputs[], int N)
    {
        for (int i = 0; i < N; i++)
        {
            if (inputs[i].type == File)
                _builder->configureFile(inputs[i].value);
            else if (inputs[i].type == Queue)
                _builder->configureQueue(inputs[i].value);
            else if (inputs[i].type == Pathway)
                _builder->configurePathway(inputs[i].value);
        }
    }
};


/* *********************************** USAGE *********************************** */

const int NUM_ENTRIES = 6;
PersistenceAttribute input[NUM_ENTRIES] = 
{
    {   File, "state.dat"   }
    , 
    {   File, "config.sys"  }
    , 
    {   Queue, "compute"    }
    , 
    {   Queue, "log"        }
    , 
    {   Pathway, "authentication"   }
    , 
    {   Pathway, "error processing" }
};


int main()
{
    UnixBuilder unixBuilder;
    VmsBuilder vmsBuilder;
    Reader reader;

    reader.setBuilder(&unixBuilder);
    reader.construct(input, NUM_ENTRIES);
    std::cout << unixBuilder.getResult()->getState() << std::endl;

    reader.setBuilder(&vmsBuilder);
    reader.construct(input, NUM_ENTRIES);
    std::cout << vmsBuilder.getResult()->getState() << std::endl;
}