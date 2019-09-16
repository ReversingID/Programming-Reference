/*
    Colinear Points
    Archive of Reversing.ID
    Algorithm (Mathematics/Geometry)
    
Compile:
    [clang]
    $ clang++ colinear-points.cpp -o colinear-points

    [gcc]
    $ g++ colinear-points.cpp -o colinear-points

    [msvc]
    $ cl colinear-points.cpp

Run:
    $ colinear-points
*/
#include <cmath>

/*
    Periksa apakah tiga titik merupakan colinear (berada dalam satu garis)
*/

// ======================================================================================

struct point_t 
{
    double x;
    double y;
};

// ======================================================================================

/** Menggunakan rumus yang diturunkan dari Shoelace Formula **/

bool algorithm(point_t p1, point_t p2, point_t p3)
{
    // hitung area segitiga.
    int a = 
        p1.x * (p2.y - p3.y) +
        p2.x * (p3.y - p1.y) + 
        p3.x * (p1.y - p2.y);
    
    return (a == 0);
}

// ======================================================================================

/** Menghitung kemiringan **/

/* 
kemiringan (slope) semua garis haruslah sama

    (y3 - y2)(x2 - x1) = (y2 - y1)(x3 - x2)

*/

bool algorithm(point_t p1, point_t p2, point_t p3)
{
    // hitung area segitiga.
    int lh = (p3.y - p2.y) * (p2.x - p1.x);
    int rh = (p2.y - p1.y) * (p3.x - p2.x);
    
    return (lh == rh);
}