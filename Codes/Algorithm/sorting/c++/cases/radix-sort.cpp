/*
    Radix Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ radix-sort.cpp -o radix-sort

    [gcc]
    $ g++ radix-sort.cpp -o radix-sort

    [msvc]
    $ cl radix-sort.cpp

Run:
    $ radix-sort
*/

/*
    Implementasi Counting Sort.

    Mirip dengan Counting Sort.
    Melakukan pengurutan digit demi digit dimulai dari Least Significant Digit ke 
    Most Significant Digit.

    Kelemahan:
    Hanya dapat melakukan pengurutan terhadap elemen bertipe bilangan bulat dengan rentang 
    nilai terbatas.
*/

// ======================================================================================

// dapatkan elemen maximum di array
int max(int arr[], ssize_t size)
{
    int mx = arr[0];
    for (ssize_t i = 1; i < size; i++)
        if (arr[i] > mx)
            mx = arr[i];
    
    return mx;
}

// melakukan counting sort arr[] berdasarkan digit yang direpresentasikan oleh exp
void counting(int arr[], ssize_t size, int exp)
{
    int counter[10] = {0};
    int output[size];   // penampungan sementara
    ssize_t i;

    // simpan jumlah kemunculan
    for (i = 0; i < size; i++)
        counter[ (arr[i]/exp)%10 ]++;
    
    // ganti counter[i] sehingga counter[i] mengandung posisi dari digit di output[]
    for (i = 1; i < 10; i++)
        counter[i] += counter[i - 1];

    // bangun output
    for (i = size - 1; i >= 0; i--)
    {
        output[ counter[(arr[i]/exp) % 10] - 1] = arr[i];
        counter[(arr[i]/exp) % 10] --;
    }

    // salin kembali output ke arr
    for (i = 0; i < size; i++)
        arr[i] = output[i];
}

// ======================================================================================

void algorithm(int arr[], ssize_t size)
{
    // cari nilai maksimum untuk dapat memperkirakan digit
    int m = max(arr, size);

    /*
    Lakukan counting sort untuk setiap digit.
    Alih-alih memberikan nilai secara langsung, exp digunakan.
    */
    for (ssize_t exp = 1; m/exp > 0; exp *= 10)
        counting(arr, size, exp);
}