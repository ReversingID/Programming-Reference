/*
    Min or Max Value
    Archive of Reversing.ID
    Algorithm (Brute-Force)
    
Compile:
    [clang]
    $ clang++ min-max.cpp -o min-max

    [gcc]
    $ g++ min-max.cpp -o min-max

    [msvc]
    $ cl min-max.cpp

Run:
    $ min-max
*/

/*
Masalah:
    Diberikan senarai beranggotakan N buah bilangan bulat. Cari elemen terkecil dan
    terbesar di dalam elemen tersebut.
*/

// ======================================================================================

template <typename T>
void algorithm(T arr[], size_t size, T & min, T & max)
{
    T _min, _max;

    _min = _max = arr[0];

    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] < _min)
            _min = arr[i];
        
        if (arr[i] > _max)
            _max = arr[i];
    }

    min = _min;
    max = _max;
}