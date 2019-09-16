/*
    Archive of Reversing.ID
    Algorithm (Mathematics/Bits)
*/

// ======================================================================================

/** Swap bit **/

// Tukar bit antara posisi k1 dan k2

static inline 
size_t swap(size_t bits, size_t k1, size_t k2)
{
    size_t x = ((bits >> k1) ^ (bits >> k2)) & 1;
    bits ^= (x << k2);
    bits ^= (x << k1);

    return bits;
}


// Jika kedua bit memiliki nilai berbeda, routine berikut bisa diterapkan

static inline
size_t swap(size_t bits, size_t k1, size_t k2)
{
    return (a ^ ((1UL << k1) ^ (1UL << k2)));
}