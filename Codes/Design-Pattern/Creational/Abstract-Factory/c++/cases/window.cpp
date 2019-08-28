/*
    Windows
    Archive of Reversing.ID
    Design Pattern (Creational/Abstract Factory)

Compile:
    [clang]
    $ clang++ window.cpp -o window
    
    [gcc]
    $ g++ window.cpp -o window

    [msvc]
    $ cl window.cpp

Run:
    $ window
*/
#include <memory>
#include <iostream>

/* *********************************** DECLARATION *********************************** */

class Window
{
protected:
    int _width;
    int _height;

    std::string _toolkit;
    std::string _type;

    Window(std::string toolkit, std::string type) : _toolkit{toolkit}, _type{type}
    { }

public:
    std::string getToolkit()
    {
        return _toolkit;
    }

    std::string getType()
    {
        return _type;
    }
};

// ======================================================================================
/**
 * Family of GTK
 */

struct GtkToolboxWindow : public Window 
{
    GtkToolboxWindow() : Window("Gtk", "ToolboxWindow")
    { }
};

struct GtkLayersWindow : public Window 
{
    GtkLayersWindow() : Window("Gtk", "LayersWindow")
    { }
};

struct GtkMainWindow : public Window 
{
    GtkMainWindow() : Window("Gtk", "MainWindow")
    { }
};

// ======================================================================================
/**
 * Family of Qt
 */

struct QtToolboxWindow : public Window 
{
    QtToolboxWindow() : Window("Qt", "ToolboxWindow")
    { }
};

struct QtLayersWindow : public Window 
{
    QtLayersWindow() : Window("Qt", "LayersWindow")
    { }
};

struct QtMainWindow : public Window 
{
    QtMainWindow() : Window("Qt", "MainWindow")
    { }
};



// ======================================================================================

/**
 * UiFactory (abstract factory)
 * 
 * Digunakan sebagai base dari factory lain.
 */
class UiFactory 
{
public:
    virtual std::unique_ptr<Window> getToolboxWindow()  = 0;
    virtual std::unique_ptr<Window> getLayersWindow()   = 0;
    virtual std::unique_ptr<Window> getMainWindow()     = 0;
};

// ======================================================================================

/**
 * GtkUiFactory (concrete)
 * 
 * Factory / creator untuk kelompok Gtk
 */
class GtkUiFactory : public UiFactory
{
public:
    std::unique_ptr<Window> getToolboxWindow() override
    {
        return std::make_unique<GtkToolboxWindow>();
    }

    std::unique_ptr<Window> getLayersWindow() override
    {
        return std::make_unique<GtkLayersWindow>();
    }

    std::unique_ptr<Window> getMainWindow() override
    {
        return std::make_unique<GtkMainWindow>();
    }
};

// ======================================================================================

/**
 * QtkUiFactory (concrete)
 * 
 * Factory / creator untuk kelompok Gtk
 */
class QtkUiFactory : public UiFactory
{
public:
    std::unique_ptr<Window> getToolboxWindow() override
    {
        return std::make_unique<QtToolboxWindow>();
    }

    std::unique_ptr<Window> getLayersWindow() override
    {
        return std::make_unique<QtLayersWindow>();
    }

    std::unique_ptr<Window> getMainWindow() override
    {
        return std::make_unique<QtMainWindow>();
    }
};



/* *********************************** USAGE *********************************** */

int main(int argc, char* argv[])
{
    std::unique_ptr<UiFactory> factory{nullptr};
    std::unique_ptr<Window>    toolw{nullptr};
    std::unique_ptr<Window>    layerw{nullptr};
    std::unique_ptr<Window>    mainw{nullptr};

    /* Instansiasi objek factory untuk membangun produk */
    factory = std::make_unique<GtkUiFactory>();
    toolw   = factory->getToolboxWindow();
    layerw  = factory->getLayersWindow();
    mainw   = factory->getMainWindow();

    
    return 0;
}