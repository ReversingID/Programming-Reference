/*
    Stack (implemented with Array) 
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o array.asm array.c

        (msvc)
        $ cl /c /Faarray.asm array.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Sebuah Abstract Data Type (ADT) yang memberikan layanan manajemen terhadap
    kumpulan objek (element) dengan dua operasi dasar:
        - push() - menambah element ke collection
        - pop()  - mengambil dan menghapus element terakhir yang ditambahkan.
    
    Stack disebut juga sebagai struktur yang bersifat LIFO (Last-In First-Out).
    Objek yang terakhir kali ditambahkan akan menjadi objek yang dikeluarkan 
    pertama kali.

    Stack divisualisasikan sebagai kumpulan objek yang bertumpuk di atas satu
    sama lain. Sebagaimana sebuah tumpukan, objek hanya bisa ditambahkan dan
    diambil dari posisi puncak (TOP) sebuah stack.
*/

/* ******************************** TYPE DEFINITIONS ******************************** */
/* 
    Tipe data dari value 

    Tidak ada batasan terhadap tipe data yang dapat digunakan. Namun untuk menyederhanakan
    persoalan, tipe integer digunakan sebagai contoh.
*/
typedef int32_t T;

/*
    Data structure definition
*/
typedef struct 
{
    uint32_t _capacity;
    uint32_t _top;
    T     *  _values;
} stack_t;

/* ******************************** PROTOTIPE FUNGSI ******************************** */
int32_t  stack_init (stack_t * stack, size_t N);

int32_t  stack_push (stack_t * stack, T value);

int32_t  stack_pop  (stack_t * stack, T * value);

int32_t  stack_peek (stack_t * stack, T * value);

int32_t  stack_capacity (stack_t * stack);

int32_t  stack_size (stack_t * stack);

int32_t  stack_empty (stack_t * stack);
int32_t  stack_full  (stack_t * stack);

int32_t  stack_grow (stack_t * stack);


/* ******************************* INTERNAL FUNCTIONS ******************************* */


/* ***************************** PRIMITIVE & OPERATIONS ***************************** */
/*
    Konstruktor (pembentuk objek)
    Inisiasi objek menjadi objek yang valid.

    Parameter:
        - [stack_t] stack: objek yang akan dibentuk dan diinisiasi.
        - [size_t] N: ukuran dari stack yang akan dibentuk.
    Return: 
        - [int32_t] status konstruksi (0 = gagal, 1 = berhasil)
*/
int32_t stack_init (stack_t * stack, size_t N)
{
    T * values;

    /* inisialisasi nilai default */
    stack->_top      = 0;
    stack->_capacity = 0;
    stack->_values   = NULL;

    /* Nilai yang valid sebagai ukuran stack adalah N > 0 */
    if (N)
    {
        /* Alokasikan buffer untuk menampung element di stack */
        values = (T*) malloc(sizeof(T) * N);
        if (values)
        {
            stack->_values   = values;
            stack->_capacity = N;

            return 1;
        }
    }

    return 0;
}

/*
    Push
    Menambahkan objek dengan meletakkan objek ke puncak tumpukan. 

    Parameter:
        - [stack_t] stack: objek yang telah dikonstruksi.
        - [T] value: nilai / objek yang akan ditambahkan.
    Return: 
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t stack_push(stack_t * stack, T value)
{
    /* 
    Mengecek apakah ukuran stack masih mencukupi.
    */
    if (stack_full(stack))
        return 0;

    /* Menyalin data */
    memcpy(&stack->_values[stack->_top], &value, sizeof(T));

    /* TOP menunjuk ke posisi berikutnya */
    stack->_top ++;

    return 1;
}

/*
    Pop
    Menghapus objek dengan mengambil objek yang berada di puncak tumpukan. 

    Parameter:
        - [stack_t] stack: objek yang telah dikonstruksi.
        - [T] value: menampung objek yang diambil.
    Return: 
        - [int32_t] status pengambilan (0 = gagal, 1 = berhasil)
*/
int32_t stack_pop(stack_t * stack, T * value)
{
    /*
    Mengecek apakah ukuran stack kosong
    */
    if (stack_empty(stack))
        return 0;
    
    /* TOP menunjuk ke posisi teratas tumpukan */
    stack->_top --;

    /* Menyalin data */
    memcpy(value, &stack->_values[stack->_top], sizeof(T));

    return 1;
}

/*
    Peek
    Melihat objek yang ada di puncak stack 

    Parameter:
        - [stack_t] stack: objek yang telah dikonstruksi.
        - [T] value: menampung objek yang diamati.
    Return: 
        - [int32_t] status pengamatan (0 = gagal, 1 = berhasil)
*/
int32_t stack_peek(stack_t * stack, T * value)
{
    if (stack_empty(stack))
        return 0;

    /* Menyalin data */
    memcpy(value, &stack->_values[stack->_top - 1], sizeof(T));

    return 1;
}

/*
    Capacity
    Mengambil informasi kapasitas maksimum tumpukan.

    Parameter:
        - [stack_t] stack: objek yang telah dikonstruksi.
    Return: 
        - [int32_t] kapasitas dari stack
*/
int32_t stack_capacity(stack_t * stack)
{
    return stack->_capacity;
}

/*
    Ukuran (size)
    Mendapatkan informasi ukuran stack saat ini.

    Parameter:
        - [stack_t] stack: objek yang telah dikonstruksi.
    Return: 
        - [int32_t] status pengambilan (0 = gagal, 1 = berhasil)
*/
int32_t stack_size(stack_t * stack)
{
    /* ukuran stack diindikasikan oleh posisi TOP */
    return stack->_top;
}

/*
    Is Empty?
    Mendapatkan informasi apakah stack dalam keadaan kosong.

    Parameter:
        - [stack_t] stack: objek yang telah dikonstruksi.
    Return: 
        - [int32_t] status empty dari stack (1 = kosong, 0 = tidak kosong)
*/
int32_t  stack_empty(stack_t * stack)
{
    return (0 == stack->_top);
}

/*
    Is Full?
    Mendapatkan informasi apakah stack dalam keadaan penuh.

    Parameter:
        - [stack_t] stack: objek yang telah dikonstruksi.
    Return: 
        - [int32_t] status full dari stack (1 = penuh, 0 = tidak penuh)
*/
int32_t stack_full(stack_t * stack)
{
    return (stack->_top == stack->_capacity);
}

/*
    Perbesar ruang penyimpanan (buffer) yang digunakan oleh stack

    Parameter:
        - [stack_t] stack: objek yang telah dikonstruksi.
    Return: 
        - [int32_t] status pembesaran ruang (0 = gagal, 1 = sukses)
*/
int32_t stack_grow(stack_t * stack)
{
    uint32_t capacity;
    T    *   new_values;
    
    capacity = 2 * stack->_capacity;
        
    new_values = (T*) realloc(stack->_values, capacity);
    if (new_values == NULL)
        return 0;
    
    /* Salin seluruh data di buffer lama */
    memcpy(new_values, stack->_values, sizeof(T) * stack->_capacity);

    /* Dealokasi buffer lama */
    free(stack->_values);

    /* buffer menunjuk ke lokasi baru */
    stack->_values = new_values;

    return 1;
}