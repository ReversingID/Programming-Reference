/*
    Doubly Linked-List (Head only)
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o head.asm head.c

        (msvc)
        $ cl /c /Fahead.asm head.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus dan
    field lain yang menunjuk ke alamat node pendahulu.

    Kasus umum
    ... <NULL>  <-  A  <->  B  <->  C  <->  D  <->  E  ->  <NULL>
                    ^
                    ^
                  HEAD
    
    Kasus kosong
    ...   <NULL>
            ^
            ^
           HEAD
    
    Kasus 1 element
    ... <NULL>  <-  A  ->  <NULL>
                    ^
                    ^
                  HEAD
    

    HEAD adalah pointer yang menunjuk ke node di awal senarai.

    Senarai dengan pointer ganda digunakan jika harus dilakukan banyak operasi terhadap
    elemen penerus (successor) dan pendahulu (predecessor). 
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
typedef int32_t (*callback_t)(T * val,T * acc);

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
        memcpy(&node->_value, &value, sizeof(T));
        node->_next = NULL;
        node->_prev = NULL;
    }

    return node;
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
    Menambahkan elemen baru di awal list (mengubah head).

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
    node_t   *prevnode, *iternode, *node;
    uint32_t iter = index;

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new(value);
    if (node == NULL)
        return 0;
    
    prevnode = NULL;

    /* iterasi list, cari node ke-(index-1) atau selama list masih ada */
    for (iternode = collection->_head; iternode && iter; iter--)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    /* tautkan node pendahulu dan node saat ini */
    if (prevnode)
    {
        prevnode->_next = node;
        node->_prev = prevnode;
    }

    /* tautkan node saat ini ke node penerus */
    node->_next = iternode;
    
    /* jika "iternode" merupakan node, tautkan node saat ini dan "iternode" */
    if (iternode)
        iternode->_prev = node;
    
    /* jika index adalah 0, maka jadikan node ini sebagai head */
    if (index == 0 || collection->_length == 0)
        collection->_head = node;
        
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
    node_t   *prevnode, *iternode, *nextnode;
    uint32_t  iter = index;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;
    
    prevnode = NULL;

    /* iterasi list, cari node ke-index atau selama list masih ada */
    for (iternode = collection->_head; iternode && iter; iter--)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    /* simpan alamat node penerus */
    nextnode = iternode->_next;

    /* perbaiki tautan yang ada di node tetangga */
    if (prevnode)
        prevnode->_next = nextnode;
    if (nextnode)
        nextnode->_prev = prevnode;
    
    /* jika penghapusan terjadi di head, maka ubah head agar menunjuk node berikutnya */
    if (index == 0)
        collection->_head = nextnode;
    
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
            /* sesuaikan tautan pada prevnode agar menunjuk ke node penerus "iternode" */
            if (prevnode)
                prevnode->_next = nextnode;
            /* bila node yang dihapus merupakan head, maka pindahkan head ke posisi berikutnya */
            else
                collection->_head = nextnode;

            /* sesuaikan tautan agar node penerus menunjuk ke "prevnode" */
            if (nextnode)
                nextnode->_prev = prevnode;
            
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
        - [doubly_t] collection: objek yang telah dikonstruksi.
        - [T] value: nilai baru yang akan diisikan.
        - [uint32_t] index: index dari elemen yang akan dimodifikasi
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_update(doubly_t * collection, uint32_t index, T value)
{
    node_t * iternode;

    /* Jika list kosong, maka kondisi list tak berubah */
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
        - [doubly_t] collection: objek yang telah dikonstruksi,
                list yang akan menerima isi dari source.
        - [doubly_t] source: objek yang telah dikonstruksi, 
                list yang akan ditambahkan ke collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t doubly_merge(doubly_t * collection, doubly_t * source)
{
    node_t   *iternode;
    uint32_t length;

    /* jika list collection kosong maka ... */
    if (collection->_length == 0)
        /* cukup pindahkan referensi head di source ke collection */
        collection->_head = source->_head;
    /* jika tidak maka ... */
    else 
    {
        iternode = collection->_head;
        length   = collection->_length;

        /* iterasi hingga akhir list collection */
        while (--length)
            iternode = iternode->_next;
        
        /* sesuaikan tautan yang ada agar kedua senarai saling menyambung */
        iternode->_next = source->_head;
        if (source->_head)
            source->_head->_prev = iternode;
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
    node_t   *iterdst = NULL, *itersrc = NULL, *node;
    uint32_t length = 0;

    /*
    Apabila objek telah menyimpan beberapa node, maka list
    harus dibersihkan terlebih dahulu.
    */
    doubly_clear(collection);

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

            /* gunakan sebagai pivot dalam penambahan node */
            iterdst = node;

            /* iterasi list source dan lakukan clone untuk setiap node yang ada */
            while (itersrc)
            {
                node = node_new(itersrc->_value);
                if (node)
                {
                    /* menautkan node sebagai penerus */
                    iterdst->_next = node;
                    node->_prev    = iterdst;

                    iterdst = node;
                    length ++;
                }
                itersrc = itersrc->_next;
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
        - [callback_t] callback: pointer ke fungsi yang akan dipanggil terhadap
                    setiap nilai dalam collection.
        - [T*] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
    Return:
        - None
*/
void doubly_traverse(doubly_t * collection, callback_t callback, T * acc)
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
