/*
    Vehicle Record
    Archive of Reversing.ID
    Design Pattern (Creational/Prototype)

    Implementasi dengan Registry

Compile:
    [clang]
    $ clang++ vehicle-record.cpp -o vehicle-record
    
    [gcc]
    $ g++ vehicle-record.cpp -o vehicle-record

    [msvc]
    $ cl vehicle-record.cpp

Run:
    $ vehicle-record
*/
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

/* *********************************** DECLARATION *********************************** */

/**
 * Record (abstract)
 * 
 * Interface yang mendefinisikan prototype.
 */
class Record 
{
public:
    virtual ~Record() { }
    virtual void print() = 0;
    virtual std::unique_ptr<Record> clone() = 0;
};

// ======================================================================================

class CarRecord : public Record 
{
    std::string _name;
    int         _id;
public:
    CarRecord(std::string name, int id) : _name{name}, _id{id}
    { }

    void print() override 
    {
        std::cout << "Car record" << std::endl
                  << "   Name   : " << _name << std::endl
                  << "   Number : " << _id << std::endl;
    }

    auto clone() -> std::unique_ptr<Record> override
    {
        return std::make_unique<CarRecord>(*this);
    }
};

// ======================================================================================

class BikeRecord : public Record 
{
    std::string _name;
    int         _id;
public:
    BikeRecord(std::string name, int id) : _name{name}, _id{id}
    { }

    void print() override 
    {
        std::cout << "Bike record" << std::endl
                  << "   Name   : " << _name << std::endl
                  << "   Number : " << _id << std::endl;
    }

    auto clone() -> std::unique_ptr<Record> override
    {
        return std::make_unique<BikeRecord>(*this);
    }
};

// ======================================================================================

enum RecordType { CAR, BIKE };

/**
 * RecordFactory
 * 
 * sebuah factory yang berperan sebagai registry untuk menyimpan prototype dan melakukan
 * penciptaan objek baru (clone).
 * 
 * Tugas factory hanya membantu untuk menciptakan objek yang sesuai karena penciptaan objek
 * diimplementasikan dengan Prototype.
 */
class RecordFactory
{
    std::unordered_map<RecordType, std::unique_ptr<Record>, std::hash<int>> _records;

public:
    RecordFactory()
    {
        _records[CAR]    = std::make_unique<CarRecord>("Toyota", 5005);
        _records[BIKE]   = std::make_unique<BikeRecord>("Whimsical", 2525);
    }

    auto create(RecordType type) -> std::unique_ptr<Record>
    {
        return _records[type]->clone();
    }
};


/* *********************************** USAGE *********************************** */

int main()
{
    RecordFactory factory;

    auto record = factory.create(CAR);
    record->print();

    record = factory.create(BIKE);
    record->print();

    return 0;
}