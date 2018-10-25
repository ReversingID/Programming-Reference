/*
    Singly Linked-List (Head + Tail)
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o head-tail.asm head-tail.c

        (msvc)
        $ cl /c /Fahead-tail.asm head-tail.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus.

    Kasus umum
    ...   A  ->  B  ->  C  ->  D  ->  E 
          ^                           ^
          ^                           ^
        HEAD                        TAIL
    
    Kasus kosong
    ...   <NULL>      <NULL>
            ^           ^   
            ^           ^   
          HEAD        TAIL  


    HEAD adalah pointer yang menunjuk ke node di awal list.
    TAIL adalah pointer yang menunjuk ke node di akhir list.

    Senarai dengan variasi ini seringkali digunakan apabila dibutuhkan banyak operasi
    yang melibatkan elemen terakhir. Fungsi dari TAIL adalah untuk menghindari traversal 
    untuk mencapai elemen terakhir sehingga node terakhir dicatat sebagai alamat khusus.
*/

/* ******************************** TYPE DEFINITIONS ******************************** */
/* 
    Tipe data value node 

    Tidak ada batasan terhadap tipe data yang dapat digunakan. Namun untuk menyederhanakan
    persoalan, tipe integer digunakan sebagai contoh.
*/
typedef int32_t T;

/* 
    Prototipe dari function pointer yang digunakan untuk memanipulasi elemen dalam
    collection.

    Parameter:
        - [T*] val: value dari node yang sedang diiterasi
        - [T*] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
*/
typedef int32_t (*callback_t)(T * val, T * acc);

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
    collection->_tail   = NULL;
    
    return 1;
}

/*
    Penambahan (prepend)
    Menambahkan elemen baru di awal list (mengubah head).

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_prepend(singly_t * collection, T value)
{
    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node_t * node = node_new(value);
    if (node == NULL)
        return 0;

    /* 
    Jika belum ada node sebelumnya maka tail harus diposisikan 
    menunjuk node baru 
    */
    if (collection->_length == 0)
        collection->_tail = node;
    /* jika tidak, maka hubungkan node dengan head */
    else 
        node->_next = collection->_head;

    /* jadikan node sebagai node pertama di list */
    collection->_head = node;

    collection->_length ++;

    return 1;
}

/*
    Penambahan (append)
    Menambahkan elemen baru di akhir list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_append(singly_t * collection, T value)
{
    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node_t * node = node_new(value);
    if (node == NULL)
        return 0;
    
    /* jika list kosong maka jadikan node sebagai node pertama */
    if (collection->_length == 0)
        collection->_head   = node;
    /* jika tidak maka ...  */
    else 
        /* Tautkan node sebagai node terakhir dengan tail menunjuk kepadanya */
        collection->_tail->_next = node;

    collection->_tail = node;
    collection->_length ++;

    return 1;
}

/*
    Penyisipan (insert)
    Menambahkan elemen baru di tengah list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [uint32_t] index: lokasi index dimana nilai akan disisipkan.
        - [T] value: nilai yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_insert(singly_t * collection, uint32_t index, T value)
{
    node_t  *node, *iternode;

    /* jika list kosong atau index bernilai 0 maka lakukan prepend() */
    if (collection->_length == 0 || index == 0)
        return singly_prepend(collection, value);
    
    /* jika index bernilai lebih daripada panjang list maka lakukan append() */
    if (index >= collection->_length)
        return singly_append(collection, value);

    /* jika tidak, maka iterasi dari awal list untuk dapatkan posisi penyisipan */

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new(value);
    if (node == NULL)
        return 0;

    /* iterasi list, cari node ke-(index-1) */
    iternode = collection->_head;
    while (--index)
        iternode = iternode->_next;

    /* dan letakkan node setelah node tersebut */
    node->_next      = iternode->_next;
    iternode->_next  = node;
        
    collection->_length ++;

    return 1;
}

/*
    Penghapusan (delete)
    Hapus sebuah node di awal list

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t singly_delete_front(singly_t * collection)
{
    node_t * head;

    /* jika list kosong maka kondisi list tidak berubah */
    if (collection->_length == 0)
        return 0;
    
    head = collection->_head;

    /* ubah agar head menunjuk ke node berikutnya dan turunkan counter panjang list */
    collection->_head = head->_next;
    
    /* dealokasi node */
    free(head);
    collection->_length --;

    return 1;
}

/*
    Penghapusan (delete)
    Hapus sebuah node di akhir list

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t singly_delete_rear(singly_t * collection)
{
    node_t *prevnode, *iternode;

    /* jika list kosong maka kondisi list tidak berubah */
    if (collection->_length == 0)
        return 0;
    
    /* jika list hanya berisi 1 node maka segera hapus node tersebut */
    if (collection->_length == 1)
    {
        iternode = collection->_head;

        collection->_head = NULL;
        collection->_tail = NULL;
    }
    else 
    {
        /* iterasi hingga menemukan node tail */
        prevnode = NULL;
        iternode = collection->_head;
        while (iternode->_next)
        {
            prevnode = iternode;
            iternode = iternode->_next;
        }

        /* tetapkan "prevnode" sebagai tail dan lakukan penyesuaian */
        prevnode->_next   = NULL;
        collection->_tail = prevnode;        
    }
    
    /* dealokasi node */
    free(iternode);
    collection->_length --;

    return 1;
}

/*
    Penghapusan (delete)
    Hapus sebuah node yang ada di index tertentu

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [uint32_t] index: posisi node yang akan dihapus
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t singly_delete_at(singly_t * collection, uint32_t index)
{
    node_t   *prevnode, *iternode, *node;
    uint32_t  iter = index;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;

    /* jika penghapusan dilakukan terhadap node awal .. */
    if (index == 0)
        return singly_delete_front(collection);
    /* jika penghapusan dilakukan terhadap node terakhir ... */
    else if (index == collection->_length - 1)
        return singly_delete_rear(collection);

    /* iterasi list, cari node ke-index atau selama list masih ada */
    prevnode = collection->_head;
    iternode = prevnode->_next;

    for (iter = 1; iternode && iter < index; iter++)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    /* perbaiki tautan yang ada di node tetangga */
    prevnode->_next = iternode->_next;
    
    /* dealokasi node */
    free(iternode);
    collection->_length --;

    return 1;
}

/*
    Penghapusan (delete)
    Menghapus sebanyak `count` kemunculan nilai `value` di list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan dihapus dari collection.
        - [uint32_t] count: banyaknya salinan node yang akan dihapus
                    0 jika ingin hapus semua kemunculan nilai.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t singly_delete(singly_t * collection, T value, uint32_t count)
{
    node_t   *prevnode, *iternode, *nextnode;
    uint32_t length;

    /* jika list kosong maka kondisi list tidak berubah */
    if (collection->_length == 0)
        return 0;
    
    /* 
    jika count bernilai 0, hapus semua kemunculan nilai.
    Kita bisa anggap semua node adalah sama sehingga kemungkinan menghapus
    semua nilai adalah sebanyak panjang dari list tersebut 
    */ 
    if (count == 0)
        count  = collection->_length;
    
    prevnode   = NULL;
    length     = collection->_length;
    iternode   = collection->_head;

    /* iterasi list selama masih ada node dan counter masih ada */
    while (count && iternode)
    {
        /* simpan alamat node penerus */
        nextnode = iternode->_next;

        /* jika node memiliki nilai yang dicari ... */
        if (iternode->_value == value)
        {
            /* sesuaikan tautan pada "prevnode" agar menunjuk ke node penerus "iternode" */
            if (prevnode)
                prevnode->_next = nextnode;
            /* bila node yang dihapus merupakan head, maka pindahkan head ke posisi berikutnya */
            else
                collection->_head = nextnode;
            
            /* hapus "iternode" */
            free(iternode);
            
            /* kurangi counter dan jumlah node */
            count --;
            length --;
        }
        /* jika tidak, maka ubah nilai "prevnode" agar dapat mengikuti "iternode" */
        else 
            prevnode = iternode;

        /* pindahkan pointer "iternode" menunjuk ke node berikutnya */
        iternode = nextnode;
    }
    
    collection->_length = length;

    return 1;
}

/*
    Perubahan (update)

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [T] value: nilai baru yang akan diisikan.
        - [uint32_t] index: index dari elemen yang akan dimodifikasi
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_update(singly_t * collection, uint32_t index, T value)
{
    node_t * iternode;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;
    else 
    {
        /* jika index adalah 0, maka ubah nilai di node terdepan */
        iternode = collection->_head;

        /* jika tidak, iterasi list dan cari node ke-index atau selama list masih ada */
        while (iternode->_next && index--)
            iternode = iternode->_next;

        /* ubah nilainya */
        iternode->_value = value;
    }

    return 1;
}

/*
    Penggabungan (merge)
    Menggabungkan dua buah list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi,
                list yang akan menerima isi dari source.
        - [singly_t] source: objek yang telah dikonstruksi, 
                list yang akan ditambahkan ke collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_merge(singly_t * collection, singly_t * source)
{
    /* jika list collection kosong maka ... */
    if (collection->_length == 0)
        /* cukup pindahkan referensi head di source ke collection */
        collection->_head = source->_head;
    /* jika tidak maka ... */
    else
        /* node setelah tail menunjuk ke head dari source */
        collection->_tail->_next = source->_head;
    
    /* update tail agar menunjuk akhir dari list */
    collection->_tail = source->_tail;
    
    collection->_length += source->_length;
    
    /* kosongkan source */
    source->_length = 0;
    source->_head = NULL;
    source->_tail = NULL;

    return 1;
}

/*
    Pembersihan (clear)
    Mengosongkan (menghapus) seluruh node dari list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_clear(singly_t * collection)
{
    node_t *iternode, *nextnode;

    if (collection->_length)
    {
        /* Iterasi seluruh list */
        iternode = collection->_head;
        while (iternode)
        {
            nextnode = iternode->_next;
            free(iternode);
            iternode = nextnode;
        }
        collection->_length = 0;
    }

    /* kosongkan list */
    collection->_head = NULL;
    collection->_tail = NULL;

    return 1;
}

/*
    Mendapatkan banyaknya node yang ada di dalam list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] jumlah node dalam list
    
    Sebagai alternatif, dapat pula dilakukan traversaldan melakukan pencacahan
    terhadap semua node.
*/
int32_t singly_length(singly_t * collection)
{
    return collection->_length;
}

/*
    Salin (clone)
    Membuat sebuah list baru dengan salinan seluruh node yang ada di list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi dan akan menerima
                     salinan node dari source.
        - [singly_t] source: objek yang telah dikonstruksi dan akan disalin ke 
                     collection
    Return:
        - [singly_t] list baru
*/
int32_t singly_clone(singly_t * collection, singly_t * source)
{
    node_t   *iterdst = NULL, *itersrc = NULL, *node;
    uint32_t length = 0;

    /*
    Apabila objek telah menyimpan beberapa node, maka list
    harus dibersihkan terlebih dahulu.
    */
    singly_clear(collection);

    /* iterasi seluruh node di dalam list */
    itersrc = source->_head;
    if (itersrc)
    {
        /* alokasi node sebagai calon head */
        node = node_new(itersrc->_value);

        /* jika alokasi berhasil maka ... */
        if (node)
        {
            /* jadikan node tersebut sebagai head */
            collection->_head = node;
            length ++;

            /* pindahkan itersrc ke node berikutnya */
            itersrc = itersrc->_next;

            /* mulai penambahan list */
            iterdst = node;

            /* iterasi list source dan lakukan clone untuk setiap node yang ada */
            while (itersrc)
            {
                node = node_new(itersrc->_value);
                if (node)
                {
                    /* menautkan node sebagai penerus */
                    iterdst->_next = node;

                    iterdst = node;
                    length ++;
                }
                itersrc = itersrc->_next;
            }
        }

        /* update tail agar menunjuk ke node akhir list */
        collection->_tail = iterdst;
    }

    collection->_length = length;
    
    return 1;
}

/*
    Penelusuran (traverse)

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [callback_t] callback: pointer ke fungsi yang akan dipanggil terhadap
                    setiap nilai dalam collection.
        - [T*] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
    Return:
        - None
*/
void singly_traverse(singly_t * collection, callback_t callback, T * acc)
{
    node_t *iternode;

    /* Jika list kosong atau callback tak terdefinisi, maka iterasi tidak dilakukan */
    if (collection->_length == 0 || callback == NULL)
        return;
    
    iternode = collection->_head;

    /* jika tidak, iterasi list */
    while (iternode)
    {
        /* jalankan callback di setiap node */
        (*callback)(&iternode->_value, acc);

        /* maju ke node berikutnya */
        iternode = iternode->_next;
    }
}
