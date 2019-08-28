/*
    Color
    Archive of Reversing.ID
    Design Pattern (Creational/Named Factory)
    
Compile:
    [clang]
    $ clang++ color.cpp -o color
    
    [gcc]
    $ g++ color.cpp -o color

    [msvc]
    $ cl color.cpp

Run:
    $ color
*/
#include <iostream>

/* *********************************** DECLARATION *********************************** */
/**
 * Color (concrete)
 * 
 * Objek Color dapat diciptakan dari RGB, maupun dari nilai hex.
 * Variasi objek Color tertentu juga dapat diciptakan secara langsung.
 */
using ubyte = uint8_t;

class Color
{
    ubyte _r, _g, _b;

public:
    /* Constructor tunggal untuk membentuk objek */
    Color(ubyte r, ubyte g, ubyte b) : _r(r), _g(g), _b(b) { }

    ubyte red() 
    {
        return _r;
    }
    
    ubyte green() 
    {
        return _g;
    }
    
    ubyte blue() 
    {
        return _b;
    }

    /* ----- Menciptakan variasi objek Color ----- */

    /* Color dari RGB */
    static Color fromRGB(ubyte red, ubyte green, ubyte blue)
    {
        return std::move(Color(red, green, blue));
    }

    /* Color dari nilai HEX (little endian) */
    static Color fromHex(int color)
    {
        int r = color & 0xFF;
        int g = (color >>  8) & 0xFF;
        int b = (color >> 16) & 0xFF;

        return std::move(Color(r, g, b));
    }

    /* variasi Color */
    static inline Color colorRED() 
    {
        return fromRGB(255, 0, 0);
    }

    static inline Color colorGREEN()
    {
        return fromRGB(0, 255, 0);
    }

    static inline Color colorBLUE()
    {
        return fromRGB(0, 0, 255);
    }
    
    friend std::ostream& operator << (std::ostream& os, const Color& c) 
    {
        os  << "Color( r = "
            << static_cast<int>(c._r)
            << ", g = " << static_cast<int>(c._g)
            << ", b = " << static_cast<int>(c._b)
            << " )";
        return os;
    }
};

/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    std::cout << "Red     => " << Color::colorRED()  << std::endl;
    std::cout << "Green   => " << Color::colorGREEN()<< std::endl;
    std::cout << "Blue    => " << Color::colorBLUE() << std::endl;
    std::cout << "Color1  => " << Color::fromRGB(128, 128, 128)  << std::endl;
    std::cout << "Color2  => " << Color::fromHex(0x00FFFF)       << std::endl;

    return 0;
}