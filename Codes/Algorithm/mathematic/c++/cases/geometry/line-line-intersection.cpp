/*
    Line-Line Intersection Area
    Archive of Reversing.ID
    Algorithm (Mathematics/Geometry)
    
Compile:
    [clang]
    $ clang++ line-line-intersection.cpp -o line-line-intersection

    [gcc]
    $ g++ line-line-intersection.cpp -o line-line-intersection

    [msvc]
    $ cl line-line-intersection.cpp

Run:
    $ line-line-intersection
*/
#include <cmath>
#include <algorithm>

/*
    Perpotongan (intersection) dari dua buah garis
*/

// ======================================================================================

struct point_t
{
    double x;
    double y;
};

struct line_t 
{
    point_t p1;
    point_t p2;
}

// diberikan tiga titik colinear p, q, r; periksa jika q berada di segmen pr
bool on_segment(point_t p, point_t q, point_t r)
{
    return  q.x <= std::max(p.x, r.x) &&
            q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) &&
            q.y >= std::min(p.y, r.y);
}

/* 
    cari orientasi dari triplet (p, q, r)
    hasil:
        0  -> p, q, dan r colinear
        1  -> clockwise
        -1 -> counter-clockwise
*/
int orientation(point_t p, point_t q, point_t r)
{
    int val =   (q.y - p.y) * (r.x - q.x) -
                (q.x - p.x) * (r.y - q.y);
    
    if (val > 0)
        return 1;
    else if (val < 0)
        return -1;
    else 
        return 0;
}

// ======================================================================================

/** Perkiraan berdasarkan orientasi **/

bool algorithm(line_t line1, line_t line2)
{
    point_t p1 = line1.p1, q1 = line1.p2,
            p2 = line2.p1, q2 = line2.p2;
    
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // kasus umum
    if (o1 != o2 && o2 != o4)
        return true;
    
    // -- kasus spesial --
    // p1, q1 dan p2 colinear dan p2 berada di segmen p1q1 
    if (o1 == 0 && on_segment(p1, p2, q1)) return true; 
  
    // p1, q1 dan q2 colinear dan q2 berada di segmen p1q1 
    if (o2 == 0 && on_segment(p1, q2, q1)) return true; 
  
    // p2, q2 dan p1 colinear dan p1 berada di segmen p2q2 
    if (o3 == 0 && on_segment(p2, p1, q2)) return true; 
  
    // p2, q2 dan q1 colinear dan q1 berada di segmen p2q2 
    if (o4 == 0 && on_segment(p2, q1, q2)) return true; 
  
    // tidak memenuhi kasus apapun
    return false;
}