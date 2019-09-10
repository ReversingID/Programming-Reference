/*
    Job Sequencing - Loss Minimization
    Archive of Reversing.ID
    Algorithm (Greedy)
    
Compile:
    [clang]
    $ clang++ job-sequencing-loss-minimization.cpp -o job-sequencing-loss-minimization

    [gcc]
    $ g++ job-sequencing-loss-minimization.cpp -o job-sequencing-loss-minimization

    [msvc]
    $ cl job-sequencing-loss-minimization.cpp

Run:
    $ job-sequencing-loss-minimization
*/

/*
Masalah:
    Diberikan senarai job dimana setiap job memiliki waktu pengerjaan serta kerugian
    yang didapat setiap hari jika job tertunda.
    Tentukan urutan komposisi job dan urutan yang tepat untuk meminimalisir kerugian.

Pertimbangan:
    terdapat dua extreme case:
    - semua job memiliki waktu yang sama untuk diproses (T[i] = k untuk semua i). 
    - semua job memiliki kerugian yang sama ketika ditunda.

    dengan demikian, pengurutan dapat dilakukan dengan perbandingan nilai C dimana 
    C = (loss produk[i]) * (waktu tunda)

Langkah:
    - urutkan job berdasarkan potensi kerugian terbesar (jika tertunda).
*/
#include <vector>
#include <utility>

// ======================================================================================

struct job_t
{
    int job_id;
    int time;
    int loss;
};

bool compare(job_t a, job_t b)
{
    return ((a.loss * b.time) > (b.loss * a.time));
}

// ======================================================================================

/** Iterative Solution **/

auto algorithm(job_t arr[], int size)
{
    // jadwal job yang dipilih
    std::vector<int>  jobids;

    // urutkan semua job terurut menurun berdasarkan profit
    std::sort(arr, arr + size, compare);
    
    for (size_t i = 0; i < size; i++)
        jobids.push_back(arr[i].job_id);

    return jobids;
}