/*
    Quick Sort
    Archive of Reversing.ID
    Algorithm (Divide and Conquer)
    
Compile:
    [clang]
    $ clang++ quick-sort.cpp -o quick-sort

    [gcc]
    $ g++ quick-sort.cpp -o quick-sort

    [msvc]
    $ cl quick-sort.cpp

Run:
    $ quick-sort
*/
#include <cstdlib>

/*
    Implementasi Quick Sort.

    Mengambil sebuah elemen sebagai pivot dan mempartisi array berdasarkan pivot.
    Terdapat beberapa versi pengambilan pivot dalam quick sort
        - selalu mengambil elemen pertama
        - selalu mengambil elemen terakhir
        - mengambil elemen secara random
        - mengambil median
*/

// ======================================================================================

template <typename T>
void swap(T & a, T & b)
{
    T t = b;
    b = a;
    a = t;
}

// ======================================================================================

/** Partition - Random Pivot **/

template <typename T>
ssize_t partition(T arr[], ssize_t low, ssize_t high)
{
    ssize_t p = rand() % (high - low) + low;
    T       t = arr[p];

    /*
    pivot dipindah ke index low terlebih dahulu.
    pertukarkan elemen yang menyalahi urutan.
    tempatkan elemen pivot ke lokasi baru. 
    */
    swap(arr[low], arr[p]);

    ssize_t i = low;
    ssize_t j = i + 1;

    while (j <= high)
    {
        while (arr[j] > t && j <= high)   j++;

        if (j <= high)
        {
            i ++;
            swap(arr[i], arr[j]);
            j ++;
        }
    }

    swap(arr[i], arr[low]);

    return i;
}

// ======================================================================================

/** Partition - Last Item Pivot **/

template <typename T>
ssize_t partition(T arr[], ssize_t low, ssize_t high)
{
    T t = arr[high];

    ssize_t i = (low - 1);      // index dari elemen yang bernilai lebih kecil
    ssize_t j = low;

    while (j < high)
    {
        // jika elemen sekarang lebih kecil dibandingkan pivot
        if (arr[j] < t)
            swap(arr[++i], arr[j]);
        j++;
    }

    swap(arr[i + 1], arr[high]);

    return (i + 1);
}

// ======================================================================================

/** Partition - Middle Item Pivot **/

template <typename T>
ssize_t partition(T arr[], ssize_t low, ssize_t high)
{
    ssize_t p = (low + high) / 2;
    T      t = arr[p];

    /*
    ruas kiri bernilai kurang dari pivot
    ruas kanan bernilai lebih dari pivot
    apabila ada elemen yang menyalahi aturan, pindahkan ke ruas sebaliknya.
    */
    while (low < high)
    {
        while (arr[low] < t)    low++;

        while (arr[high] > t)   high--;

        if (low < high && arr[low] != arr[high])
            swap(arr[low], arr[high]);
        else
            return high;
    }

    return high;
}


// ======================================================================================

/** Recursive Solution **/ 

template <typename T>
void algorithm(T arr[], ssize_t low, ssize_t high)
{
    if (high > low)
    {
        ssize_t pi = partition(arr, low, high);

        algorithm(arr, low,  pi - 1);
        algorithm(arr, pi + 1, high);
    }
}


// ======================================================================================

/** Iterative Solution **/ 

// emulasi cara kerja rekursif dengan internal stack
template <typename T>
void algorithm(T arr[], ssize_t low, ssize_t high)
{
    // buat stack
    ssize_t stack [high - low + 1];

    // inisialisasi top
    ssize_t top = -1;

    // push initial value low dan high ke stack
    stack[++top] = low;
    stack[++top] = high;

    // operasi tak berhenti selama stack belum kosong
    while (top >= 0)
    {
        // pop high dan low
        high = stack[top--];
        low  = stack[top--];

        // partisi array dan dapatkan pivot
        ssize_t p = partition(arr, low, high);

        // jika ada elemen di sisi kiri pivot, push ke stack
        if (p - 1 > low)
        {
            stack[++top] = low;
            stack[++top] = p - 1;
        }

        // jika ada elemen di sisi kanan pivot, push ke stack
        if (p + 1 < high)
        {
            stack[++top] = p + 1;
            stack[++top] = high;
        }
    }
}

template <typename T>
void algorithm(T arr[], size_t N)
{
    algorithm(arr, 0, N - 1);
}