/*
    Queue (implemented with Linked_List) 
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o list-head-tail.asm list-head-tail.c

        (msvc)
        $ cl /c /Falist-head-tail.asm list-head-tail.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Sebuah Abstract Data Type (ADT) yang memberikan layanan akses manajemen
    kumpulan objek (element) secara terurut berdasarkan kedatangan. Terdapat 
    dua operasi dasar:
        - enqueue() - menambah element ke queue
        - dequeue() - mengambil dan menghapus element
    
    Queue disebut juga sebagai struktur yang bersifat FIFO (First-In First-Out).
    Objek yang pertama kali ditambahkan akan menjadi objek yang akan dikeluarkan 
    pertama kali.

    Queue (antrean) adalah kumpulan objek yang tersusun secara terurut.
    Sebuah antrean memiliki dua ujung yaitu ujung depan dan ujung belakang.
    Objek akan ditambahkan ke ujung belakang antrean (BACK), sementara pengambilan 
    dilakukan dari ujugn depan (FRONT).
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
typedef struct singly_t
{
    uint32_t _length;
    node_t * _head;
    node_t * _tail;
} queue_t;


/* ******************************** PROTOTIPE FUNGSI ******************************** */
int32_t  queue_init (queue_t * queue, size_t N);

int32_t  queue_enqueue (queue_t * queue, T value);

int32_t  queue_dequeue (queue_t * queue, T * value);

int32_t  queue_peek (queue_t * queue, T * value);

int32_t  queue_size (queue_t * queue);


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
        - [queue_t] queue: objek yang akan dibentuk dan diinisiasi.
        - [size_t] N: ukuran dari queue yang akan dibentuk.
    Return: 
        - [int32_t] status konstruksi (0 = gagal, 1 = berhasil)
*/
int32_t queue_init (queue_t * queue, size_t N)
{
    queue->_length = 0;
    queue->_head   = NULL;
    queue->_tail   = NULL;
    
    return 1;
}

/*
    Penambahan (Enqueue)
    Menambahkan objek dengan meletakkan objek ke antrean. 

    Parameter:
        - [queue_t] queue: objek yang telah dikonstruksi.
        - [T] value: nilai / objek yang akan ditambahkan.
    Return: 
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t queue_enqueue(queue_t * queue, T value)
{
    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node_t * node = node_new(value);
    if (node == NULL)
        return 0;
    
    /* jika list kosong maka jadikan node sebagai node pertama */
    if (queue->_length == 0)
        queue->_head   = node;
    /* jika tidak maka ...  */
    else 
        /* Tautkan node sebagai node terakhir dengan tail menunjuk kepadanya */
        queue->_tail->_next = node;

    queue->_tail = node;
    queue->_length ++;

    return 1;
}

/*
    Pengambilan (Dequeue)
    Menghapus objek dengan mengambil objek yang berada di depan antrean. 

    Parameter:
        - [queue_t] queue: objek yang telah dikonstruksi.
        - [T] value: menampung objek yang diambil.
    Return: 
        - [int32_t] status pengambilan (0 = gagal, 1 = berhasil)
*/
int32_t queue_dequeue(queue_t * queue, T * value)
{
    node_t * head;

    /* jika list kosong maka kondisi list tidak berubah */
    if (queue_empty(queue))
        return 0;
    
    head = queue->_head;

    /* ubah agar head menunjuk ke node berikutnya dan turunkan counter panjang list */
    queue->_head = head->_next;
    
    /* dealokasi node */
    free(head);
    queue->_length --;

    return 1;
}

/*
    Mengamati Element (Peek)
    Melihat objek yang ada di puncak queue 

    Parameter:
        - [queue_t] queue: objek yang telah dikonstruksi.
        - [T] value: menampung objek yang diamati.
    Return: 
        - [int32_t] status pengamatan (0 = gagal, 1 = berhasil)
*/
int32_t queue_peek(queue_t * queue, T * value)
{
    if (queue_empty(queue))
        return 0;

    /* Menyalin data */
    memcpy(value, queue->_head, sizeof(T));

    return 1;
}

/*
    Ukuran (size)
    Mendapatkan informasi ukuran queue saat ini.

    Parameter:
        - [queue_t] queue: objek yang telah dikonstruksi.
    Return: 
        - [int32_t] status pengambilan (0 = gagal, 1 = berhasil)
*/
int32_t queue_size(queue_t * queue)
{
    /* ukuran queue diindikasikan oleh posisi TOP */
    return queue->_length;
}

/*
    Is Empty?
    Mendapatkan informasi apakah queue dalam keadaan kosong.

    Parameter:
        - [queue_t] queue: objek yang telah dikonstruksi.
    Return: 
        - [int32_t] status empty dari queue (1 = kosong, 0 = tidak kosong)
*/
int32_t  queue_empty(queue_t * queue)
{
    return (0 == queue->_length);
}