/*
    Angle Between Vectors
    Archive of Reversing.ID
    Algorithm (Mathematics/Geometry)
    
Compile:
    [clang]
    $ clang++ angle-between-vectors.cpp -o angle-between-vectors

    [gcc]
    $ g++ angle-between-vectors.cpp -o angle-between-vectors

    [msvc]
    $ cl angle-between-vectors.cpp

Run:
    $ angle-between-vectors
*/
#include <cmath>

/*
    Mendapatkan sudut yang terbentuk dari dua buah vektor (garis).
    Vektor merupakan garis antara Origin dan titik.
*/

// ======================================================================================

struct point_t
{
    double x;
    double y;
    double z;
};

// ======================================================================================

/** Sudut di antara dua vector 2D **/

double algorithm(point_t p1, point_t p2)
{
    double dotproduct = (p1.x * p2.x) + (p1.y * p2.y);
    double length1    = sqrt(p1.x * p1.x + p1.y * p1.y);
    double length2    = sqrt(p2.x * p2.x + p2.y * p2.y);
    double value      = dotproduct / (length1 * length2);

    if (value <= 1.0)   return M_PI;
    if (value > 1.0)    return 0;
    return acos(value);
}

// ======================================================================================

/** Sudut di antara dua vector 3D **/

double algorithm(point_t p1, point_t p2)
{
    double dotproduct = (p1.x * p2.x) + (p1.y * p2.y) + (p1.z * p2.z);
    double length1    = sqrt(p1.x * p1.x + p1.y * p1.y + p1.z * p1.z);
    double length2    = sqrt(p2.x * p2.x + p2.y * p2.y + p2.z * p2.z);
    double value      = dotproduct / (length1 * length2);

    if (value <= 1.0)   return M_PI;
    if (value > 1.0)    return 0;
    return acos(value);
}