/*
    Flavius Number
    Archive of Reversing.ID
    Algorithm (Mathematics/Numbers)
    
Compile:
    [clang]
    $ clang++ flavius-number.cpp -o flavius-number

    [gcc]
    $ g++ flavius-number.cpp -o flavius-number

    [msvc]
    $ cl flavius-number.cpp

Run:
    $ flavius-number
*/

/*
    Flavius Number adalah barisan bilangan dengan yang dibentuk dengan aturan berikut:
        - diberikan bilangan bulat 1 hingga tak-terbatas dan bilangan N 
        - hapus bilangan pada urutan dengan kelipatan (i + 1) untuk setiap i iterasi 
          dari 1 hingga N.

    Apabila N terdapat pada baris yang dihasilkan, maka N merupakan Flavius Number.
*/

// ======================================================================================

/* 
    Iterative Solution
    Testing
    Periksa apakah bilangan merupakan Flavius Number
*/

bool algorithm(size_t N)
{
    /*
    lakukan perulangan dari 2 karena iterasi pertama akan menghapus elemen pada posisi
    kelipatan dua 
    */
    for (size_t i = 2; ; i++)
    {
        if (i > N)
            return true;
        if (N % i == 0)
            return false;
        
        // Hapus elemen yang telah dieliminasi pada iterasi ini
        N -= N / i;
    }
}