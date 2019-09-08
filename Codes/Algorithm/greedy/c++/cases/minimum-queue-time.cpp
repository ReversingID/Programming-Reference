/*
    Minimum Queue Time
    Archive of Reversing.ID
    Algorithm (Greedy)
    
Compile:
    [clang]
    $ clang++ minimum-queue-time.cpp -o minimum-queue-time

    [gcc]
    $ g++ minimum-queue-time.cpp -o minimum-queue-time

    [msvc]
    $ cl minimum-queue-time.cpp

Run:
    $ minimum-queue-time
*/
#include <vector>

/*
Masalah:
    Sebuah pemroses memiliki n pelanggan yang harus dilayani. Waktu pelayanan untuk setiap
    pelanggan sudah ditetapkan sebelumnya, yaitu pelanggan i membutuhkan waktu Ti,
    1 <= i <= m.
    Tentukan urutan yang tepat sehingga waktu tunggu keseluruhan di dalam sistem menjadi
    minimum.

    Meminimumkan waktu tunggu di dalam sistem ekivalen dengan meminimumkan waktu rata-rata.
*/

// ======================================================================================

struct job_t
{
    int job_id;
    int serve_time;
};

bool compare(job_t a, job_t b)
{
    return (a.serve_time < b.serve_time);
}

// ======================================================================================

/** Iterative Solution - array tak terurut **/

auto algorithm(job_t arr[], size_t size)
{
    // menampung jadwal (urutan antrean)
    std::vector<int> schedule;

    bool pick[size];
    int  idx;

    size_t i, count = 0;

    for (i = 0; i < size; i++)
        pick[i] = false;

    // untuk setiap iterasi, ambil job dengan waktu pelayanan terkecil
    while (count < size)
    {
        // pilih nilai awal sebagai pembanding
        for (i = 0; i < size; i++)
            if (! pick[i])
                idx = i;
        
        // cari nilai minimum
        for(; i < size; i++)
        {
            if (! pick[idx] && arr[i].serve_time < arr[idx].serve_time)
                idx = i;
        }

        // proses dan masukkan ke jadwal
        pick[idx] = true;
        schedule.push_back(arr[idx].job_id);
        count ++;
    }

    return schedule;
}

// ======================================================================================

/** Iterative Solution - array terurut **/

auto algorithm(job_t arr[], size_t size)
{
    std::vector<int> schedule;

    // urutkan berdasarkan waktu pelayanan
    std::sort(arr, arr + size, compare);
    
    // waktu tunggu I adalah 
    for (size_t i = 0; i < size; i++)
        schedule.push_back(arr[i].job_id);
    
    return schedule;
}