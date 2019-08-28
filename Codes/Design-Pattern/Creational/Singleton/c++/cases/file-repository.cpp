/*
    FileRepository
    Archive of Reversing.ID
    Design Pattern (Creational/Singleton)
    
Compile:
    [gcc]
    $ g++ file-repository.cpp -o file-repository

    [msvc]
    $ cl file-repository.cpp

Run:
    $ file-repository
*/
#include <memory>
#include <string>
#include <deque>
#include <iostream>

/* *********************************** DECLARATION *********************************** */

class FileRepository
{
    std::deque<std::string> _files;
    
    FileRepository() = default;

    FileRepository(FileRepository const&) = delete;
    FileRepository(FileRepository&&) = delete;
    FileRepository& operator=(FileRepository const &) = delete;
    FileRepository& operator=(FileRepository &&) = delete;

public:
    /* public method agar operasi delete dapat dilakukan */
    virtual ~FileRepository() = default;

    static FileRepository& getInstance()
    {
        // Instance didefinisikan sebagai static
        static auto _instance = std::unique_ptr<FileRepository>{nullptr};

        std::cout << _instance.get() << std::endl;
        if (!_instance)
            _instance.reset(new FileRepository);

        return *_instance.get();
    }

    void addFile(std::string fname)
    {
        _files.push_back(std::move(fname));
    }

    void clearFiles()
    {
        _files.clear();
    }

    void showFiles() 
    {
        std::cout << "Content of Repository" << std::endl;
        for (const auto& file : _files)
            std::cout << "  File = " << file << std::endl;
    }
};

/* *********************************** USAGE *********************************** */

void subroutine()
{
    auto& repo = FileRepository::getInstance();
    repo.showFiles();
}

int main(int argc, char* argv[])
{
    auto& repo = FileRepository::getInstance();
    repo.showFiles();

    // Lakukan operasi di Singleton
    repo.addFile("reversing.id-projects.dat");
    repo.addFile("invoices.pdf");
    repo.addFile("adrt.docx");
    repo.showFiles();

    // Panggil di dalam subroutine
    subroutine();

    auto& repo2 = FileRepository::getInstance();
    repo2.showFiles();

    return 0;
}