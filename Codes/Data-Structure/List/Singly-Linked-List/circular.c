/*
    Singly Linked-List (Circular)
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o dummy-first.asm dummy-first.c

        (msvc)
        $ cl /c /Fadummy-first.asm dummy-first.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus.

    Kasus umum
          + --------------------------+
          v                           |
    ...   A  ->  B  ->  C  ->  D  ->  E
          ^ 
          ^
        HEAD

    Kasus kosong
    ...   <NULL>
            ^
            ^
           HEAD
    
    Kasus 1 element
          + -- +
          v    |
    ...   A -- +
          ^ 
          ^
        HEAD

    
    HEAD adalah pointer yang menunjuk ke node di awal list.

    Senarai dengan representasi ini sebenarnya tidak memiliki elemen yang disebut sebagai
    HEAD. Representasi ini dipakai jika dilakukan proses terus menerus terhadap anggota
    senarai (misalnya dalam Round Robin Service pada sistem operasi).

    Secara visualisasi, senarai ini menggambarkan seakan-akan terdapat sebuah "loop".

    Penambahan dan penghapusan pada node pertama akan berakibat harus dilakukan traversal
    untuk mengubah Next dari node terakhir.
*/


/* ******************************** TYPE DEFINITIONS ******************************** */
/* 
    Tipe data dari value 

    Tidak ada batasan terhadap tipe data yang dapat digunakan. Namun untuk menyederhanakan
    persoalan, tipe integer digunakan sebagai contoh.
*/
typedef int32_t T;

/* 
    Prototipe dari function pointer yang digunakan untuk memanipulasi elemen dalam
    collection.

    Parameter:
        - [T] val: value dari node yang sedang diiterasi
        - [T] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
*/
typedef int32_t (*callback_t)(T * val,T * acc);

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
typedef struct singly_t
{
    uint32_t _length;
    node_t * _head;
} singly_t;

/* ******************************** PROTOTIPE FUNGSI ******************************** */
int32_t  singly_init (singly_t * collection);

int32_t  singly_prepend (singly_t * collection, T value);
int32_t  singly_append  (singly_t * collection, T value);
int32_t  singly_insert  (singly_t * collection, uint32_t index, T value);

int32_t  singly_delete_front (singly_t * collection);
int32_t  singly_delete_rear  (singly_t * collection);
int32_t  singly_delete_at    (singly_t * collection, uint32_t index);
int32_t  singly_delete       (singly_t * collection, T value, uint32_t count);

int32_t  singly_update (singly_t * collection, uint32_t index, T value);

int32_t  singly_merge (singly_t * collection, singly_t * source);

int32_t  singly_clear (singly_t * collection);

int32_t  singly_length (singly_t * collection);

int32_t  singly_clone (singly_t * collection, singly_t * source);

void     singly_traverse (singly_t * collection, callback_t callback, T * acc);


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
        - [singly_t] collection: objek yang akan dibentuk dan diinisiasi.
    Return: 
        - [int32_t] status konstruksi (0 = gagal, 1 = berhasil)
*/
int32_t singly_init(singly_t * collection)
{
    collection->_length = 0;
    collection->_head   = NULL;
    
    return 1;
}