/*
    Singly Linked-List (Dummy Node as First and Last Node)
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o dummy-both.asm dummy-both.c

        (msvc)
        $ cl /c /Fadummy-both.asm dummy-both.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus.

    Sebuah elemen fiktif (dummy) sengaja dialokasikan untuk mempermudah operasi namun
    bukan termasuk sebagai bagian dari senarai. Node fiktif ini digunakan agar penanganan
    terhadap kasus senarai kosong tidak berbeda dengan penangan kasus senarai umum.

    Kasus umum
    ... DUMMY  ->  A  ->  B  ->  C  ->  D  ->  DUMMY  ->  <NULL>
          ^                                      ^
          ^                                      ^
        HEAD                                   TAIL

    Kasus kosong
    ...   DUMMY  ->  DUMMY  ->  <NULL>
            ^          ^
            ^          ^
          HEAD       TAIL
    

    HEAD adalah pointer yang menunjuk ke node di awal list.
    TAIL adalah pointer yang menunjuk ke node fiktif.

    Senarai ini dipilih jika operasi penambahan dan penghapusan sebagai elemen pertama
    dan terakhir ingin dihindari. Dengan representasi semacam ini, semua operasi penambahan
    maupun penghapusan akan menjadi operasi di tengah.
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
{
    node_t *dummy_head, *dummy_tail;

    dummy_head = node_new(0);
    dummy_tail = node_new(0);

    collection->_length = 0;
    collection->_head   = dummy_head;
    collection->_tail   = dummy_tail;

    if (dummy_head && dummy_tail)
    {
        dummy_head->_next = dummy_tail;
        return 1;
    }

    if (dummy_head)
        free(dummy_head);
    if (dummy_tail)
        free(dummy_tail);

    return 0;
}