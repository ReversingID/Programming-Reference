/*
    Coin Change
    Archive of Reversing.ID
    Algorithm (Greedy)
    
Compile:
    [clang]
    $ clang++ coin-change.cpp -o coin-change

    [gcc]
    $ g++ coin-change.cpp -o coin-change

    [msvc]
    $ cl coin-change.cpp

Run:
    $ coin-change
*/
#include <vector>
#include <algorithm>

/*
Masalah:
    Terdapat sekumpulan uang koin dari berbagai satuan nilai (denomination). Tentukan 
    jumlah minimum koin yang diperlukan untuk menukar uang dengan nilai V. 

Langkah:
    - inisialisasi result sebagai himpunan kosong
    - cari denomination terbesar yang bernilai kurang dari V.
    - tambahkan denomination ke result dan kurangi V dengan denomination
    - jika V bernilai 0, proses berakhir.
      sebaliknya, ulangi tahap 2 dan 3 untuk nilai V yang baru.
*/

// ======================================================================================

auto algorithm(int denomination[], size_t size, int val)
{
    // menyimpan daftar denomination yang mungkin
    std::vector<int> result;

    // urutkan denomination (nilai mata uang) dari terbesar ke terkecil
    std::sort(denomination, denomination + size, std::greater<int>());

    // telusuri seluruh jenis denomination
    for (size_t i = 0; i < size; i++)
    {
        // jumlah koin suatu denomination bisa lebih dari satu
        while (val >= denomination[i])
        {
            val -= denomination[i];
            result.push_back(denomination[i]);
        }
    }

    return result;
}