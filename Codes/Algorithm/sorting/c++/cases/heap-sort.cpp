/*
    Heap Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ heap-sort.cpp -o heap-sort

    [gcc]
    $ g++ heap-sort.cpp -o heap-sort

    [msvc]
    $ cl heap-sort.cpp

Run:
    $ heap-sort
*/


/*
    Implementasi Heap Sort.

    Binary Heap adalah Complete Binary Tree dengan item tersimpan berdasarkan urutan khusus.
    Nilai di node parent lebih besar (atau lebih kecil) daripada nilai di kedua node children.

    Heap Sort berusaha mentransformasikan array menjadi representasi Binary Heap.

Langkah:
    - bangun max heap pada rentang array tertentu
    - tukar root max-heap dengan elemen terakhir array
    - kembali ke langkah pertama hingga ukuran heap lebih dari 1
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

/** Recursive Solution **/

// membentuk array dengan property heap.
template <typename T>
void heapify(T arr[], size_t size, size_t idx)
{
    size_t largest = idx;
    size_t left    = 2 * idx + 1;
    size_t right   = 2 * idx + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;
    
    if (right < size && arr[right] > arr[largest])
        largest = right;
    
    if (largest != idx)
    {
        swap(arr[idx], arr[largest]);
        heapify(arr, size, largest);
    }
}

template <typename T>
void algorithm(T arr[], size_t size)
{
    ssize_t i;
    
    // build heap
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
    
    // mengambil elemen paling besar
    for (i = size - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}