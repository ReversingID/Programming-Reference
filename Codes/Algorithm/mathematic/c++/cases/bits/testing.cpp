/*
    Archive of Reversing.ID
    Algorithm (Mathematics/Bits)
*/

// ======================================================================================

/*
    false jika bits[1] bernilai 0
    true jika sebaliknya
*/
static inline
bool test(size_t bits, size_t idx)
{
    return ((bits & (1UL << idx)) != 0);
}