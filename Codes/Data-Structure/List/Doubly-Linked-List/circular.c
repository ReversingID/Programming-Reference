/*
    Doubly Linked-List (Circular)
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o circular.asm circular.c

        (msvc)
        $ cl /c /Facircular.asm circular.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus dan
    field lain yang menunjuk ke alamat node pendahulu. 
    
    Senarai membentuk pola circular dimana node terakhir akan menunjuk node pertama
    sebagai penerus dan node pertama akan menunjuk node terakhir sebagai pendahulu.

    Kasus umum
    ...   A  <->  B  <->  C  <->  D  <->  E  <->  A
          ^
          ^
        HEAD
    
    Kasus kosong
    ...   <NULL>
            ^
            ^
           HEAD
    
    Kasus 1 element
    ... A  <-  A  ->  A
               ^
               ^
              HEAD

    
    HEAD adalah pointer yang menunjuk ke node di awal list.


    Asumsi:
    Struktur data tidak generic.
    Tidak ada alokasi VALUE ketika pembuatan node baru, data yang disimpan akan disalin
    secara langsung.
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
    struct node_t * _prev;
} node_t;

/*
    Data structure definition
*/
typedef struct 
{
    uint32_t _length;
    node_t * _head;
} doubly_t;


/* ******************************** PROTOTIPE FUNGSI ******************************** */
int32_t  doubly_init (doubly_t * collection);

int32_t  doubly_prepend (doubly_t * collection, T value);
int32_t  doubly_append  (doubly_t * collection, T value);
int32_t  doubly_insert  (doubly_t * collection, uint32_t index, T value);

int32_t  doubly_delete_front (doubly_t * collection);
int32_t  doubly_delete_rear  (doubly_t * collection);
int32_t  doubly_delete_at    (doubly_t * collection, uint32_t index);
int32_t  doubly_delete       (doubly_t * collection, T value, uint32_t count);

int32_t  doubly_update (doubly_t * collection, uint32_t index, T value);

int32_t  doubly_merge (doubly_t * collection, doubly_t * source);

int32_t  doubly_clear (doubly_t * collection);

int32_t  doubly_length (doubly_t * collection);

int32_t  doubly_clone (doubly_t * collection, doubly_t * source);

void     doubly_traverse (doubly_t * collection, callback_t callback, T * acc);


/* ******************************* INTERNAL FUNCTIONS ******************************* */
/*
    Buat node baru.
*/
node_t * node_new(T value)
{
    node_t * node = (node_t*) malloc(sizeof(node_t));
    if (node != NULL)
    {
        node->_value = value;
        node->_next  = node;
        node->_prev  = node;
    }

    return node;
}

/*
    Menautkan dua node sehingga tautan di antara keduanya menunjuk
    satu sama lain.
*/
void node_link(node_t * leftnode, node_t * rightnode)
{
    /* node penerus dari "leftnode" adalah "rightnode" */
    leftnode->_next = rightnode;

    /* node pendahulu dari "rightnode" adalah "leftnode" */
    rightnode->_prev = leftnode;
}

/*
    Mencari node dengan index tertentu.
    Pencarian dapat dilakukan dari dua arah: maju, mundur.

    Hanya menghasilkan pointer ke node yang sesuai.
*/
node_t * doubly_find_idx(doubly_t * collection, uint32_t index)
{
    node_t * iternode;
    uint32_t iter;

    /* Operasi pencarian hanya bisa dilakukan pada collection yang memiliki konten */
    if (collection->_length == 0)
        return NULL;

    /*
    Apabila index berada di rentang (0..length/2] maka pencarian dilakukan 
    secara maju (forward). 
    */
    iternode = collection->_head;
    if (index < collection->_length / 2)
    {
        iter = index;

        /* iterasi list, cari node ke-(index-1). */
        while (iter--)
            iternode = iternode->_next;
    }
    /*
    Namun apabila index berada di rentang (length/2..length] maka pencarian 
    dilakukan secara mundur (backward)
    */
    else 
    {
        iter = collection->_length - index;
        
        while (iter--)
            iternode = iternode->_prev;
    }

    return iternode;
}


/* ***************************** PRIMITIVE & OPERATIONS ***************************** */
/*
    Konstruktor (pembentuk objek)
    Inisiasi objek menjadi objek yang valid.

    Parameter:
        - [doubly_t] collection: objek yang akan dibentuk dan diinisiasi.
    Return: 
        - [int32_t] status konstruksi (0 = gagal, 1 = berhasil)
*/
int32_t doubly_init(doubly_t * collection)
{
    collection->_length = 0;
    collection->_head   = NULL;

    return 1;
}

/*
    Penambahan (prepend)
    Menambahkan elemen baru di awal list (mengubah head dan "tail").

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_prepend(doubly_t * collection, T value)
{
    /* 
    operasi prepend() atau menambahkan node di urutan terdepan merupakan 
    operasi yang ekivalen dengan operasi insert() pada posisi 0
    */
    return doubly_insert(collection, 0, value);
}

/*
    Penambahan (append)
    Menambahkan elemen baru di akhir list.

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_append(doubly_t * collection, T value)
{
    /* 
    Operasi append() atau menambahkan node di urutan terakhir merupakan
    operasi yang ekivalen dengan operasi insert() pada posisi Length
    */
    return doubly_insert(collection, collection->_length, value);
}

/*
    Penyisipan (insert)
    Menambahkan elemen baru di tengah list.

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
        - [uint32_t] index: lokasi index dimana nilai akan disisipkan.
        - [T] value: nilai yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_insert(doubly_t * collection, uint32_t index, T value)
{
    node_t   *iternode, *node;
    uint32_t iter;

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new(value);
    if (node == NULL)
        return 0;

    /*
    Jika senarai kosong, definisikan kondisi circular pada node saat ini.
    */
    if (collection->_length == 0)
        collection->_head = node;

    /*
    Jika tidak, iterasi senarai dan cari posisi tepat untuk meletakkan node.
    */
    else 
    {
        /* rentang index yang diperbolehkan adalah (0..length) */
        if (collection->_length < index)
            index = collection->_length;

        /* cari node pada posisi index */
        iternode = doubly_find_idx(collection, index);
        
        /* dan letakkan node sebelum node tersebut */
        node_link(iternode->_prev, node);
        node_link(node, iternode);

        /* sesuaikan head apabila terjadi perubahan */
        if (index == 0)
            collection->_head = node;
    }

    collection->_length ++;

    return 1;
}

/*
    Penghapusan (delete)
    Hapus sebuah node di awal list

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_delete_front(doubly_t * collection)
{
    /* 
    operasi penghapusan node di urutan terdepan merupakan 
    operasi yang ekivalen dengan operasi penghapusan pada posisi 0
    */
    return doubly_delete_at(collection, 0);
}

/*
    Penghapusan (delete)
    Hapus sebuah node di akhir list

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_delete_rear(doubly_t * collection)
{
    /* 
    operasi penghapusan node di urutan terakhir merupakan 
    operasi yang ekivalen dengan operasi penghapusan pada posisi "Length - 1"
    */
    return doubly_delete_at(collection, collection->_length - 1);
}

/*
    Penghapusan (delete)
    Hapus sebuah node yang ada di index tertentu

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
        - [uint32_t] index: posisi node yang akan dihapus
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_delete_at(doubly_t * collection, uint32_t index)
{
    node_t   *prev, *iternode, *node;
    uint32_t  iter;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;

    /* Jika hanya ada satu node di senarai, segera hapus */
    else if (collection->_length == 1)
    {
        iternode = collection->_head;
        collection->_head = NULL;
    }

    /* Jika terdapat lebih dari satu node, lakukan pencarian terhadap node yang tepat */
    else    
    {
        /* cari node pada posisi index */
        iternode = doubly_find_idx(collection, index);
            
        /* perbaiki tautan yang ada di node tetangga */
        node_link(iternode->_prev, iternode->_next);

        /* sesuaikan head apabila terjadi perubahan */
        if (index == 0)
            collection->_head = iternode->_next;
    }

    /* dealokasi node */
    free(iternode);
    collection->_length --;

    return 1;
}

/*
    Penghapusan (delete)
    Menghapus sebanyak `count` kemunculan nilai `value` di list.

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan dihapus dari collection.
        - [uint32_t] count: banyaknya salinan node yang akan dihapus
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_delete(doubly_t * collection, T value, uint32_t count)
{
    node_t   *iternode, *nextnode, *tailnode;
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
    
    length     = collection->_length;
    iternode   = collection->_head;
    tailnode   = iternode->_prev;

    /* Jika node yang dicari ada di awal, hapus node yang berurutan di awal */
    if (iternode->_value == value)
    {
        /* iterasi list dan hapus node yang sesuai di awal */
        while (count && iternode != tailnode && iternode->_value == value)
        {
            /* simpan alamat node penerus */
            nextnode = iternode->_next;

            node_link(iternode->_prev, iternode->_next);

            /* hapus "iternode" yang berarti kurangi counter dan jumlah node */
            free(iternode);
            count --;
            length --;

            iternode = nextnode;
        }

        /* pindahkan HEAD ke posisi yang sesuai */
        collection->_head = iternode;
    }

    iternode = iternode->_next;
    
    /* iterasi segment di tengah list */
    while (count && iternode != tailnode)
    {
        nextnode = iternode->_next;

        /* jika node memiliki nilai yang dicari ... */
        if (iternode->_value == value)
        {
            node_link(iternode->_prev, iternode->_next);

            /* hapus iternode */
            free(iternode);

            /* kurangi counter */
            count --;
            length --;
        }

        iternode = nextnode;
    }
    
    /*
    Ada dua kondisi berakhirnya loop:
        - tidak ada lagi yang perlu dihapus (count mencapai 0)
        - mencapai ujung list
    
    Periksa node jika kondisi kedua tercapai.
    */
    if (count && tailnode->_value == value)
    {
        if (length > 1)
            node_link(tailnode->_prev, tailnode->_next);

        free(tailnode);

        count --;
        length --;
    }

    /* perbaharui posisi head */
    if (length == 0)
        collection->_head = NULL;        

    collection->_length = length;

    return 1;
}

/*
    Perubahan (update)

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
        - [T] value: nilai baru yang akan diisikan.
        - [uint32_t] index: index dari elemen yang akan dimodifikasi
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_update(doubly_t * collection, uint32_t index, T value)
{
    node_t * iternode;

    /* 
    - Jika list kosong, maka kondisi list tak berubah.
    - Jika index di luar rentang, pencarian menjadi tidak valid dan kondisi list tak berubah.
    */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;
    else 
    {
        /* cari node pada posisi index */
        iternode = doubly_find_idx(collection, index);

        /* ubah nilainya */
        iternode->_value = value;

        return 1;
    }
}

/*
    Penggabungan (merge)
    Menggabungkan dua buah list.

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi,
                list yang akan menerima isi dari source.
        - [doubly_t] source: objek yang telah dikonstruksi, 
                list yang akan ditambahkan ke collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_merge(doubly_t * collection, doubly_t * source)
{
    /* jika list collection kosong maka ... */
    if (collection->_length == 0)
        /* cukup pindahkan referensi head di source ke collection */
        collection->_head = source->_head;
    /* jika tidak maka ... */
    else 
    {
        node_t * head_n = collection->_head;
        node_t * tail_n = head_n->_prev;
        node_t * head_s = source->_head;
        node_t * tail_s = head_s->_prev;

        /* sesuaikan tautan yang ada agar kedua senarai saling menyambung */
        node_link(tail_n, head_s);
        node_link(tail_s, head_n);
    }

    collection->_length += source->_length;
    
    /* kosongkan source */
    source->_length = 0;
    source->_head = NULL;

    return 1;
}

/*
    Pembersihan (clear)
    Mengosongkan (menghapus) seluruh node dari list.

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_clear(doubly_t * collection)
{
    node_t   *iternode, *nextnode, *tailnode;
    uint32_t i;

    if (collection->_length)
    {
        iternode = collection->_head;
        tailnode = iternode->_prev;

        /* Iterasi seluruh node kecuali node terakhir */
        while (iternode != tailnode)
        {
           /* simpan node penerus */
            nextnode = iternode->_next;

            /* hapus node saat ini */
            free(iternode);

            /* maju ke node berikutnya */
            iternode = nextnode;
        }

        /* Hapus node terakhir */
        free(iternode);
    }

    collection->_length = 0;
    collection->_head = NULL;

    return 1;
}

/*
    Mendapatkan banyaknya node yang ada di dalam list.

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] jumlah node dalam list
*/
int32_t doubly_length(doubly_t * collection)
{
    return collection->_length;
}

/*
    Salin (clone)
    Membuat sebuah list baru dengan salinan seluruh node yang ada di list.

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi dan akan menerima
                     salinan node dari source.
        - [doubly_t] source: objek yang telah dikonstruksi dan akan disalin ke 
                     collection
    Return:
        - [doubly_t] list baru
*/
int32_t doubly_clone(doubly_t * collection, doubly_t * source)
{
    node_t   *iterdst = NULL, *itersrc = NULL, *node, *headnode;
    uint32_t length = 0;

    /*
    Apabila objek telah menyimpan beberapa node, maka list
    harus dibersihkan terlebih dahulu.
    */
    doubly_clear(collection);

    /* iterasi seluruh node di dalam list */
    itersrc = source->_head;
    headnode = source->_head;

    if (itersrc)
    {
        /* alokasi node sebagai calon head */
        node = node_new(itersrc->_value);
        if (node)
        {
            /* jadikan node tersebut sebagai head */
            collection->_head = node;
            length ++;

            /* pindahkan itersrc ke node berikutnya */
            itersrc = itersrc->_next;

            /* gunakan sebagai pivot dalam penambahan node */
            iterdst = node;

            /* iterasi list source dan lakukan clone untuk setiap node yang ada */
            while (itersrc->_next != headnode)
            {
                node = node_new(itersrc->_value);
                if (node)
                {
                    node_link(iterdst, node);

                    iterdst = iterdst->_next;
                    length ++;
                }
                itersrc = itersrc->_next;
            }

            /* buat dan tautkan node terakhir */
            node = node_new(itersrc->_value);
            if (node)
            {
                node_link(iterdst, node);
                node_link(node, collection->_head);
                length ++;
            }
        }
    }

    collection->_length = length;
    return 1;
}

/*
    Penelusuran (traverse)

    Parameter:
        - [doubly_t] collection: objek yang telah dikonstruksi.
    Return:
        - None
*/
void doubly_traverse(doubly_t * collection, callback_t callback, T * acc)
{
    node_t   *iternode, *headnode;

    /* Jika list kosong atau callback tak terdefinisi, maka iterasi tidak dilakukan */
    if (collection->_length == 0 || callback == NULL)
        return;
    
    iternode = collection->_head;
    headnode = collection->_head;

    /* iterasi seluruh list kecuali node akhir */
    while (iternode->_next != headnode)
    {
        /* jalankan callback di setiap node */
        (*callback)(&iternode->_value, acc);

        /* maju ke node berikutnya */
        iternode = iternode->_next;
    }

    /* jalankan callback di node akhir */
    (*callback)(&iternode->_value, acc);
}