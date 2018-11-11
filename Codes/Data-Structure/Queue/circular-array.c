/*
    Queue (implemented with Circular Array) 
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o circular-array.asm circular-array.c

        (msvc)
        $ cl /c /Facircular-array.asm circular-array.c
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
    Data structure definition
*/
typedef struct singly_t
{
    T * _nodes;

    uint32_t _length;
    uint32_t _capacity;

    uint32_t _head;
    uint32_t _tail;
} queue_t;


/* ******************************** PROTOTIPE FUNGSI ******************************** */
int32_t  queue_init (queue_t * queue, size_t N);

int32_t  queue_enqueue (queue_t * queue, T * value);
int32_t  queue_dequeue (queue_t * queue, T * value);

int32_t  queue_peek (queue_t * queue, T * value);

int32_t  queue_size (queue_t * queue);

int32_t  queue_empty(queue_t * queue);
int32_t  queue_full (queue_t * queue);


/* ******************************* INTERNAL FUNCTIONS ******************************* */
/*
Digunakan untuk melakukan penyalinan elemen secara generik.
Implementasikan ini jika T merupakan elemen yang kompleks.
*/
void element_copy(T * dst, T * src)
{
    *dst = *src;
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
    queue->_capacity = N;
    queue->_length = 0;

    queue->_head   = 0;
    queue->_tail   = 0;

    /* Alokasi array sebagai Queue */
    queue->_nodes = (T*) malloc(sizeof(N * sizeof(T)));
    if (queue->_nodes)
        return 1;
    
    return 0;
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
int32_t queue_enqueue(queue_t * queue, T * value)
{
    /* Jika Queue penuh maka operasi tidak dapat dilakukan */
    if (queue_full(queue))
        return 0;
    
    /* penambahan selalu dilakukan dari belakang */
    element_copy(&queue->_nodes[queue->_tail], value);
    queue->_length++;

    /* pemosisian TAIL agar menunjuk ke elemen berikutnya */
    queue->_tail = (queue->_tail + 1) % queue->_capacity;

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
    /* jika list kosong maka kondisi list tidak berubah */
    if (queue_empty(queue))
        return 0;
    
    /* pengambilan selalu dilakukan dari depan */
    element_copy(value, &queue->_nodes[queue->_head]);
    queue->_length --;
    
    /* pemosisian HEAD agar menunjuk ke elemen berikutnya */
    queue->_head = (queue->_head + 1) % queue->_capacity;

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
    element_copy(value, &queue->_nodes[queue->_head]);

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

/*
    Is Empty?
    Mendapatkan informasi apakah queue dalam keadaan penuh.

    Parameter:
        - [queue_t] queue: objek yang telah dikonstruksi.
    Return: 
        - [int32_t] status empty dari queue (1 = penuh, 0 = tidak penuh)
*/
int32_t  queue_full(queue_t * queue)
{
    return (queue->_capacity == queue->_length);
}