/*
    Job Sequencing
    Archive of Reversing.ID
    Algorithm (Greedy)
    
Compile:
    [clang]
    $ clang++ job-sequencing.cpp -o job-sequencing

    [gcc]
    $ g++ job-sequencing.cpp -o job-sequencing

    [msvc]
    $ cl job-sequencing.cpp

Run:
    $ job-sequencing
*/

/*
Masalah:
    Diberikan senarai job dimana setiap job memiliki deadline dan profit jika job
    diselesaikan sebelum deadline. Setiap job membutuhkan waktu pemrosesan sebanyak 
    1 unit waktu. Hanya ada satu job yang dapat diproses dalam satu waktu.
    Tentukan urutan komposisi job dan urutan yang tepat untuk memaksimalkan profit.

Langkah:
    - urutkan job berdasarkan profit secara terurut menurun.
    - pilih job pertama dan simpan
    - lakukan hal berikut untuk job yang tersisa
        - jika job saat ini dapat dijalankan tanpa melewati deadline, tambahkan job ke
          result.
*/
#include <vector>
#include <utility>

// ======================================================================================

struct job_t
{
    int job_id;
    int deadline;
    int profit;
};

struct schedule_t 
{
    int job_id;
    int slot;
};

bool compare(job_t a, job_t b)
{
    return (a.profit > b.profit);
}

// ======================================================================================

/** Iterative Solution **/

auto algorithm(job_t arr[], int size)
{
    // jadwal job yang dipilih
    std::vector<schedule_t>  schedules;

    // slot waktu yang dialokasikan untuk mengerjakan job
    bool slot[size];

    // urutkan semua job terurut menurun berdasarkan profit
    std::sort(arr, arr + size, compare);

    // inisialisasi slot
    for (int i = 0; i < size; i++)
        slot[i] = false;
    
    for (int i = 0; i < size; i++)
    {
        // cari slot kosong untuk job ini, mulai dari batas akhir deadline
        for (int j = std::min(size, arr[i].deadline) - 1; j >= 0; j--)
        {
            if (! slot[j])
            {
                schedule_t schedule;
                
                schedule.job_id = arr[i].job_id;
                schedule.slot   = j + 1;
                schedules.push_back(schedule);
                
                slot[j] = true;                 // slot terpenuhi
                break;
            }
        }
    }

    return schedules;
}

// ======================================================================================

/** Iterative Solution -- Disjoint Set **/

// path compression
int _find(int parent[], int idx)
{
    // base case
    if (idx == parent[idx])
        return idx;
    
    // recursive-call dengan path-compression
    parent[idx] = _find(parent, parent[idx]);
    return parent[idx];
}

// merge dua himpunan, u sebagai parent dari v
void _union(int parent[], int u, int v)
{
    // update slot terbesar ke u
    parent[v] = u;
}

int findMaxDeadline(job_t arr[], int size)
{
    int ans = arr[0].deadline;

    for (int i = 1; i < size; i++)
        if (arr[i].deadline > ans)
            ans = arr[i].deadline;
    
    return ans;
}

auto algorithm(job_t arr[], int size)
{
    // jadwal job yang dipilih
    std::vector<schedule_t>  schedules;

    // urutkan semua job terurut menurun berdasarkan profit
    std::sort(arr, arr + size, compare);

    // cari deadline maksimum di antara semua job dan buat struktur data Disjoin Set
    int latest_deadline = findMaxDeadline(arr, size);

    // alokasi ruang dan buat setiap node merupakan parent dari diri sendiri
    int parent[size + 1];
    for (int i = 0; i <= size; i++)
        parent[i] = i;
    
    // telusuri semua job
    for (int i = 0; i < size; i++)
    {
        // cari slot kosong yang tersedia untuk job ini (berdasarkan deadline)
        int slot = _find(parent, arr[i].deadline);

        // jika slot kosong lebih besar dari 0, maka terdapat slot kosong
        if (slot > 0)
        {
            /*
            Slot ini telah diambil oleh job sehingga kita perlu update slot kosong.
            Pada operasi merge, parameter pertama merupakan parent dari parameter kedua
            Query berikutnya untuk slot kosong akan mengembalikan slot kosong tersedia di 
            (slot - 1)
            */
            _union(_find(parent, slot - 1), slot);

            schedule_t schedule;
            schedule.job_id = arr[i].job_id;
            schedule.slot   = slot;
            schedules.push_back(schedule);
        }
    }

    return schedules;    
}