/*
    Chain of Responsibility (Example)
    Archive of Reversing.ID
    Design Pattern (Behavioral)
    
Compile:
    [gcc]
    $ g++ logger.cpp -o logger

    [msvc]
    $ cl logger.cpp

Run:
    $ logger
*/
#include <iostream>

/**
 * Skenario:
 * 
 */
/* *********************************** DECLARATION *********************************** */
enum LogLevel
{
    None = 0,                 //        0
    Info = 1,                 //        1
    Debug = 2,                //       10
    Warning = 4,              //      100
    Error = 8,                //     1000
    FunctionalMessage = 16,   //    10000
    FunctionalError = 32,     //   100000
    All = 63                  //   111111
};

// ======================================================================================

/**
 * Logger (concrete)
 * 
 * Kelas dasar yang akan diturunkan menjadi berbagai handler.
 * Kelas ini juga akan menjadi entrypoint dalam handling.
 */
class Logger
{
    // Pointer yang menunjuk ke chain berikutnya.
    Logger * _next;

    int _mask;

protected:
    virtual void writeMessage(std::string message) = 0;

public:
    Logger(int mask)
    {
        _mask = mask;
        _next = nullptr;
    }

    void setNext(Logger * next)
    {
        if (_next)
            _next->setNext(next);
        else 
            _next = next;
    }

    // BaseHandle selalu mendelegasikan penanganan request ke handler berikutnya.
    virtual void message(std::string message, LogLevel severity)
    {
        if (severity & _mask)
            writeMessage(message);
        else if (_next != nullptr)
            _next->message(message, severity);
    }
};

// ======================================================================================

/**
 * ConsoleLogger (concrete)
 */
class ConsoleLogger : public Logger
{
protected:
    void writeMessage(std::string message)
    {
        std::cout << "C: " << message << std::endl;
    }
public:
    ConsoleLogger(int mask) : Logger(mask) { }
};

// ======================================================================================

/**
 * EmailLogger (concrete)
 */
class EmailLogger : public Logger
{
protected:
    void writeMessage(std::string message)
    {
        std::cout << "E: " << message << std::endl;
    }
public:
    EmailLogger(int mask) : Logger(mask) { }
};

// ======================================================================================

/**
 * FileLogger (concrete)
 */
class FileLogger : public Logger
{
protected:
    void writeMessage(std::string message)
    {
        std::cout << "F: " << message << std::endl;
    }
public:
    FileLogger(int mask) : Logger(mask) { }
};


/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    // Handle
    Logger * one   = new ConsoleLogger(Warning | Error);
    Logger * two   = new EmailLogger(FunctionalMessage | FunctionalError);
    Logger * three = new FileLogger(All);

    // kaitkan handler
    one->setNext(two);
    one->setNext(three);
    
    Logger * logger = one;

    // Tangani logging pesan
    logger->message("Warning", Warning);
    logger->message("Functional Error", FunctionalError);
    logger->message("Debug", Debug);

    return 0;
}