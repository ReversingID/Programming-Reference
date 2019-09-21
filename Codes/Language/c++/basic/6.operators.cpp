/*
    Operators
    Archive of Reversing.ID
    Programming Language (C++)

    Operator dan contoh penggunaannya.
*/

int main(int argc, char* argv[])
{
    // -- deklarasi variabel
    // bilangan bulat (integer)
    int   i_var = 135;
    int   i_var2 = 9;
    int   i_result;

    // boolean
    bool  b_result;

    // -- Operasi Aritmetika --
    i_result = i_var + i_var2;      // tambah
    i_result = i_var - i_var2;      // kurang
    i_result = i_var * i_var2;      // kali
    i_result = i_var / i_var2;      // bagi
    i_result = i_var % i_var2;      // modulus

    // -- Operasi Relasional --
    b_result = i_var == i_var2;     // sama dengan
    b_result = i_var != i_var2;     // tidak sama dengan
    b_result = i_var > i_var2;      // lebih dari
    b_result = i_var < i_var2;      // kurang dari
    b_result = i_var >= i_var2;     // lebih dari atau sama dengan
    b_result = i_var <= i_var2;     // kurang dari atau sama dengan

    // -- Operasi Logika --
    b_result = true && false;       // dan (and)
    b_result = true || false;       // atau (or)
    b_result = ! true;              // bukan (not)

    // -- Operasi Bitwise --
    i_result = i_var & i_var2;      // dan (and)
    i_result = i_var | i_var2;      // atau (or)
    i_result = i_var ^ i_var2;      // exclusive-or (xor)
    i_result = ~ i_var;             // bukan (not)
    i_result = i_var << 3;          // shift left
    i_result = i_var >> 2;          // shift right

    // -- Operasi Assignment --
    i_result = 100;                 // assignment nilai
    i_result += i_var;              // i_result = iresult + i_var
    i_result -= i_var2;             // i_result = iresult - i_var2
    i_result *= 2;                  // i_result = iresult * 2
    i_result /= 3;                  // i_result = iresult / 3
    i_result %= 256;                // i_result = iresult % 256
    i_result <<= 2;                 // i_result = iresult << 2
    i_result >>= 3;                 // i_result = iresult >> 3
    i_result &= 0xFFFFFFFF;         // i_result = iresult & 0xFFFFFFFF
    i_result |= 0x55555555;         // i_result = iresult | 0x55555555
    i_result ^= 0x11111111;         // i_result = iresult ^ 0x11111111


    return 0;
}