/*
    Archive of Reversing.ID
    Algorithm (Mathematics/Bits)
*/

// ======================================================================================

/** Copy bit **/

// Copy dari posisi [isrc] ke posisi [idst]

static inline 
size_t copy(size_t bits, size_t isrc, size_t idst)
{
    size_t x = ((bits >> isrc) ^ (bits >> idst)) & 1;   // bernilai 1 jika bits berbeda
    return bits ^ (x << idst);                          // ubah jika bits berbeda
}


// Copy dengan posisi dikodekan sebagai mask

static inline
size_t copy(size_t bits, size_t msrc, size_t mdst)
{
    size_t x = mdst;
    if (msrc & bits) x = 0;
    x ^= mdst;
    bits &= ~mdst;
    return (bits |= x);
}