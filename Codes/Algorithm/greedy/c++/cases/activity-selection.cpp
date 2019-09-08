/*
    Activity Selection
    Archive of Reversing.ID
    Algorithm (Greedy)
    
Compile:
    [clang]
    $ clang++ activity-selection.cpp -o activity-selection

    [gcc]
    $ g++ activity-selection.cpp -o activity-selection

    [msvc]
    $ cl activity-selection.cpp

Run:
    $ activity-selection
*/

/*
Masalah:
    Terdapat n buah aktivitas dengan informasi waktu mulai dan berakhir. Tentukan jumlah
    aktivitas maksimum yang dapat dilakukan oleh seorang (asumsi hanya ada satu aktivitas
    dalam satu waktu).

Langkah:
    - urutkan aktivitas berdasarkan waktu akhir.
    - pilih aktivitas pertama dan simpan
    - lakukan hal berikut untuk aktivitas yang tersisa
        - pilih aktivitas dengan start time lebih besar atau sama dengan finish time
          aktivitas sebelumnya 
*/

// ======================================================================================

struct activity_t
{
    int act_id;
    int start;
    int finish;
};

// ======================================================================================

/** 
    Iterative Solution 
    dibentuk sebuah struct activity_t untuk mencatat start dan finish .

    asumsi array telah terurut berdasarkan finish time.
**/

auto algorithm(activity_t arr[], size_t size)
{
    std::vector<activity_t> result;

    // elemen pertama selalu terpilih
    result.push_back(arr[0]);
    for (size_t i = 0, j = 1; j < size; j++)
    {
        // mencari aktivitas yang dimulai setelah aktivitas sebelumnya usai
        if (arr[j].start >= arr[i].finish)
        {
            result.push_back(arr[j]);
            i = j;
        }
    }

    return result;
}

// ======================================================================================

/** 
    Iterative Solution 
    terdapat dua array sama panjang, satu menyatakan start, satu menyatakan finish time.

    asumsi kedua array telah terurut berdasarkan finish time.
**/

auto algorithm(int start[], int finish[],size_t size)
{
    std::vector<int> result;    // vector menyatakan id activity yang dipilih

    // elemen pertama selalu terpilih
    result.push_back(0);
    for (size_t i = 0, j = 1; j < size; j++)
    {
        if (start[j] >= finish[i])
        {
            result.push_back(j);
            i = j;
        }
    }

    return result;
}