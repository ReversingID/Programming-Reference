/*
    Archive of Reversing.ID
    Algorithm (Mathematics/number-theory)
*/

// ======================================================================================

/** Greatest Common Divisior (GCD) dan Lowest Common Multiple (LCM) **/


// Mencari GCD dengan algoritma euclid

static inline
size_t gcd(size_t num_1, size_t num_2)
{
    if (num_2 == 0)
    {
        return num_1;
    }
    return gcd(num_2, num_1 % num_2);
}


// Mencari LCM

static inline
size_t lcm(size_t num_1, size_t num_2)
{
    /* 
        Simpan bilangan terbesar di max_value
        Tambahkan 1 hingga max_value habis dibagi bilangan pertama dengan bilangan kedua
    */
    size_t max_value = (num_1 > num_2) ? num_1 : num_2;

    while(true)
    {
        if((max_value % num_1 == 0) && (max_value % num_2 == 0))
        {
            return max_value;
        }
        max_value++;
    }
}

/*
    Hubungan antara GCD dan LCM

    LCM * GCD = num_1 * num_2
*/

static inline
size_t relation(size_t num_1, size_t num_2, size_t value)
{
    /*
        Jika value berisi GCD, akan mengembalikan nilai LCM
        Jika value berisi LCM, akan mengembalikan nilai GCD
    */

    size_t result = (num_1 * num_2) / value;
    return result;
}