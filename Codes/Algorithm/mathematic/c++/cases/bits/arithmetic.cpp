/*
    Archive of Reversing.ID
    Algorithm (Mathematics/Bits)
*/

// ======================================================================================

/*
    
*/

static inline 
ulong floor_average(ulong x, ulong y)
// Return floor( (x+y)/2 )
// Result is correct even if (x+y) wouldn't fit into a ulong
// Use:      x+y == ((x&y)<<1) + (x^y)
// that is:  sum ==  carries   + sum_without_carries
{
    return  (x & y) + ((x ^ y) >> 1);
    // return  y + ((x-y)>>1);  // works if x>=y
}