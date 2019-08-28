/*
    Singleton
    Archive of Reversing.ID
    Design Pattern (Creational)

    Modern C++

    Singleton template

Compile:
    [clang]
    $ clang++ singleton.cpp -o singleton
    
    [gcc]
    $ g++ singleton.cpp -o singleton

    [msvc]
    $ cl singleton.cpp

Run:
    $ singleton
*/
#include <memory>
#include <mutex>

/* *********************************** DECLARATION *********************************** */
/**
 * Singleton (template)
 * 
 */
template <typename Type>
class Singleton
{
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;

    static Type* _instance;

protected:
     Singleton() = default;
    ~Singleton() = default;

public:
    template <typename... Args>
    static Type& getInstance(Args... args)
    {
        if (!_instance)
            _instance = new Type(std::forward<Args>(args)...);
        
        return *_instance;
    }
};

template <typename Type> Type* Singleton<Type>::_instance = nullptr;

// ======================================================================================

/**
 * Service (concrete)
 * 
 * object yang dibungkus sebagai singleton.
 */
class Service
{
    int _data;
public:
    Service(int a, int b)
    {
        _data = a * b;
    }

    int provideService() 
    {
        return _data;
    }
};

typedef Singleton<Service> ServiceSingleton;

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Pemanggilan Service dengan parameter
    ServiceSingleton::getInstance(9, 15).provideService();

    return 0;
}