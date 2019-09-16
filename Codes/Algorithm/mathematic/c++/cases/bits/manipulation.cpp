/*
    Archive of Reversing.ID
    Algorithm (Mathematics/Bits)
*/

// ======================================================================================

/** Manipulasi bit (set, clear, toggle) secara individual **/

static inline
size_t set(size_t bits, size_t idx)
{
    return (bits | (1UL << idx));
}

static inline
size_t clear(size_t bits, size_t idx)
{
    return (bits & ~(1UL << idx));
}

static inline 
size_t toggle(size_t bits, size_t idx)
{
    return (bits ^ (1UL << idx));
}


// ======================================================================================

/** Manipulasi low-bit atau block word **/

/*
    Return word dengan hanya bit posisi paling rendah yang set.
    Return 0 jika tidak ada bit yang set.
*/
static inline 
size_t isolate_lowest_one(size_t x)
{
    // if (0 == x) return 0;
    // return ((x ^ (x - 1)) >> 1) + 1;

    // return (x & (x - 1)) ^ x;

    return x & -x;
}

/*
    Return word dengan hanya bit posisi paling rendah yang clear.
    Return 0 jika semua bit set.
*/
static inline 
size_t isolate_lowest_zero(size_t x)
{
//    return  (x ^ (x+1)) & ~x;
//    return  ((x ^ (x+1)) >> 1 ) + 1;
//    return (x+1) & ~x;

    x = ~x;
    return x & -x;
}

