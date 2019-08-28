/*
    Transportation Company
    Archive of Reversing.ID
    Design Pattern (Creational/Factory Method)
    
    Modern C++

Compile:
    [clang]
    $ clang++ transport-company.cpp -o factory-method
    
    [gcc]
    $ g++ transport-company.cpp -o transport-company

    [msvc]
    $ cl transport-company.cpp

Run:
    $ transport-company
*/
#include <memory>
#include <iostream>

/**
 * Case:
 * 
 * Sebuah perusahaan logistic pada mulanya menangani transportasi dengan trucks.
 * Ekspansi dilakukan dengan penambahan transportasi laut.
 */


/* *********************************** DECLARATION *********************************** */

class Transport
{
public:
    virtual ~Transport() { }

    /* Contoh operasi kelas yang akan diimplementasikan oleh setiap kelas turunan */
    virtual void deliver() = 0;
};

// ======================================================================================

class Truck : public Transport
{
public:
     Truck() { }
    ~Truck() { }

    void deliver()
    {
        std::cout << "Delivered by land, in a box" << std::endl;
    }
};

// ======================================================================================

class Ship : public Transport
{
public:
     Ship() { }
    ~Ship() { }

    void deliver()
    {
        std::cout << "Delivered by sea, in a container" << std::endl;
    }
};

// ======================================================================================

class Logistics 
{
public:
    virtual ~Logistics() { }
    virtual std::unique_ptr<Transport> createTransport() = 0;

    void    planDelivery();
};

// ======================================================================================

class RoadLogistic : public Logistics
{
public:
     RoadLogistic() { }
    ~RoadLogistic() { }

    auto createTransport() -> std::unique_ptr<Transport>
    {
        return std::make_unique<Truck>();
    }
};

// ======================================================================================

/**
 * ShipLogistics (concrete)
 * 
 * Kelas yang akan menghasilkan produk melalui pemanggilan fungsi tertentu.
 * Fungsi mengabstraksi proses pembuatan sebuah kelas sehingga pengguna
 * dapat memeroleh kelas tanpa harus melakukan pembuatan secara manual.
 * 
 * Kelas ini akan menghasilkan Ship
 */
class ShipLogistic : public Logistics
{
public:
     ShipLogistic() { }
    ~ShipLogistic() { }

    auto createTransport() -> std::unique_ptr<Transport>
    {
        return std::make_unique<Ship>();
    }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    std::unique_ptr<Logistics> logistic{nullptr};
    
    logistic   = std::make_unique<RoadLogistic>();
    auto truck = logistic->createTransport();
    truck->deliver();

    logistic   = std::make_unique<ShipLogistic>();
    auto ship  = logistic->createTransport();
    ship->deliver();

    return 0;
}