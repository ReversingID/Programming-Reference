/*
    Cycle Sort
    Archive of Reversing.ID
    Algorithm (Sorting)
    
Compile:
    [clang]
    $ clang++ cycle-sort.cpp -o cycle-sort

    [gcc]
    $ g++ cycle-sort.cpp -o cycle-sort

    [msvc]
    $ cl cycle-sort.cpp

Run:
    $ cycle-sort
*/


/*
    Implementasi Cycle Sort
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

/** Iterative Solution **/

template <typename T>
void algorithm(T arr[], size_t size)
{
    // telusuri elemen array dan letakkan ke posisi yang tepat
    for (size_t cycle_start = 0; cycle_start <= size - 2; cycle_start++)
    {
        // inisialisasi item sebagai titik awal
        T item = arr[cycle_start];

        /*
        temukan posisi untuk meletakkan item. 
        hitung semua elemen di sisi kanan yang bernilai lebih kecil.
        */
        size_t pos = cycle_start;
        for (size_t i = cycle_start + 1; i < size; i++)
            if (arr[i] < item)
                pos++;
        
        // jika item sudah berada di posisi yang tepat
        if (pos == cycle_start)
            continue;
        
        // abaikan semua elemen terduplikat
        while (item == arr[pos])
            pos ++;
        
        // letakkan item ke posisi yang tepat
        if (pos != cycle_start)
            swap(item, arr[pos]);

        // rotasi cycle yang tersisa
        while (pos !=cycle_start)
        {
            pos = cycle_start;

            // cari posisi untuk meletakkan elemen
            for (size_t i = cycle_start + 1; i < size; i++)
                if (arr[i] < item)
                    pos++;
            
            // abaikan semua elemen terduplikat
            while (item == arr[pos])
                pos ++;
            
            // letakkan item ke lokasi yang tepat
            if (item != arr[pos])
                swap(item, arr[pos]);
        }
    }
}