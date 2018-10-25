/*
    Stack (implemented with linked list) 
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o linked-list.asm linked-list.c

        (msvc)
        $ cl /c /Falinked-list.asm linked-list.c
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

/*
    Stack diimplementasikan dengan linked list (senarai bertautan) sederhana 
    dengan akses terbatas hanya dapat dilakukan melalui HEAD.
    
    Kasus umum
    ...   A  ->  B  ->  C  ->  D  ->  E  ->  <NULL>
          ^
          ^
        HEAD
    
    Kasus kosong
    ...   <NULL>
            ^
            ^
           HEAD
    
    HEAD adalah pointer yang menunjuk ke node TOP.
*/

/* ******************************** TYPE DEFINITIONS ******************************** */
/* 
    Tipe data dari value 

    Tidak ada batasan terhadap tipe data yang dapat digunakan. Namun untuk menyederhanakan
    persoalan, tipe integer digunakan sebagai contoh.
*/
typedef int32_t T;

/*
    Node definition
*/
typedef struct node_t
{
    T      _value;
    struct node_t * _next;
} node_t;

/*
    Data structure definition
*/
typedef struct 
{
    uint32_t _length;
    node_t * _top;
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
/*
    Buat node baru.
*/
node_t * node_new(T value)
{
    node_t * node = (node_t*) malloc(sizeof(node_t));
    if (node != NULL)
    {
        memcpy(&node->_value, &value, sizeof(T));
        node->_next = NULL;
    }

    return node;
}


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
    /* inisialisasi nilai default */
    stack->_length  = 0;
    stack->_top     = NULL;

    return 0;
}

/*
    Push
    Menambahkan objek dengan meletakkan objek ke puncak tumpukan. 

    Parameter:
        - [stack_t] stack: tumpukan objek yang telah dikonstruksi.
        - [T] value: nilai / objek yang akan ditambahkan.
    Return: 
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t stack_push(stack_t * stack, T value)
{
    node_t * node;

    /* buat node baru. Jika gagal, maka kondisi stack tidak berubah */
    node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL)
        return 0;

    /* salin nilai ke node baru */
    memcpy(&node->_value, value, sizeof(T));

    node->_next = stack->_top;

    /* jadikan node sebagai TOP */    
    stack->_top = node;
    stack->_length ++;

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
    node_t * node;

    /*
    Memeriksa apakah tumpukan dalam keadaan kosong.
    Jika kosong, tidak ada yang dapat dikeluarkan.
    */
    if (stack->_top == NULL)
        return 0;

    node = stack->_top;
    
    /* jadikan node penerus sebagai TOP */
    stack->_top = node->_next;
    stack->_length --;
    
    /* Menyalin data */
    memcpy(value, &node->_value, sizeof(T));

    /* menghapus node di TOP */
    free(node);

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
    /* Memeriksa apakah tumpukan dalam keadaan kosong.
    Jika kosong, tidak ada yang dapat diperlihatkan.
    */
    if (stack->_top == NULL)
        return 0;

    /* Menyalin data */
    memcpy(value, &stack->_top->_value, sizeof(T));

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
    /* 
    penggunaan senarai mengakibatkan tidak ada batasan definitif terhadap kapasitas 
    */
    return 0;
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
    return stack->_length;
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
    return (NULL == stack->_top);
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
    /* 
    penggunaan senarai mengakibatkan tidak ada batasan definitif terhadap kapasitas 
    */
    return 0;
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
    /* 
    penggunaan senarai mengakibatkan tidak ada batasan definitif terhadap kapasitas 
    */
    return 1;
}