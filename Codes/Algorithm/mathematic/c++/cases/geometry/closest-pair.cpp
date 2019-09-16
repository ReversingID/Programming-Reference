/*
    Closest Pair
    Archive of Reversing.ID
    Algorithm (Mathematics/Geometry)
    
Compile:
    [clang]
    $ clang++ closest-pair.cpp -o closest-pair

    [gcc]
    $ g++ closest-pair.cpp -o closest-pair

    [msvc]
    $ cl closest-pair.cpp

Run:
    $ closest-pair
*/
#include <cmath>

/*
Masalah:
    Diberikan n buah titik. Tentukan dua buah titik yang memiliki jarak terdekat satu sama
    lain. 
*/

// ======================================================================================

struct point_t 
{
    double x;
    double y;
};

double distance(point_t p1, point_t p2)
{
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;

    return sqrt(x*x + y*y);
}

// ======================================================================================

/** pendekatan brute-force **/

void algorithm(point_t arr[], size_t N, size_t & idx1, size_t & idx2)
{
    double d, dmin = 0;
    size_t i, j;

    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            // periksa jarak kedua titik dalam 2D
            d = distance(arr[i], arr[j]);

            if (d < dmin || dmin == 0)
            {
                dmin = d;
                idx1 = i;
                idx2 = j;   
            }
        }
    }
}