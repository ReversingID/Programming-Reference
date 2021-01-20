/*
    Singly Linked-List (Head only)
    Archive of Reversing.ID
    Data Structure

Assemble:
    (gcc)
    $ gcc -m32 -S -masm=intel -o head.asm head.c

    (msvc)
    $ cl /c /Fahead.asm head.c

    (clang)
    $ clang -m32 -S -masm=intel -o head.asm head.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus.

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
    
    
    HEAD adalah pointer yang menunjuk ke node di awal list.
    
    Senarai dengan variasi ini merupakan bentuk paling dasar dan sederhana.

    Umumnya senarai ini mewakili banyak persoalan nyata, misalnya mewakili list of windows,
    list of item pada suatu menu, list of object pada editor gambar, dsb. Pada kasus-kasus
    tersebut, elemen list merupakan objek dengan tipe yang sama.


Asumsi:
    Struktur data tidak generic.
    Tidak ada alokasi VALUE ketika pembuatan node baru, data yang disimpan akan disalin
    secara langsung.
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
typedef int32_t (*callback_t) (T * val,T * acc);

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
/* penciptaan objek single linked-list */
int32_t  singly_init    (singly_t * collection);
int32_t  singly_destroy (singly_t * collection);
/* penambahan elemen/node */
int32_t  singly_prepend (singly_t * collection, T value);
int32_t  singly_append  (singly_t * collection, T value);
int32_t  singly_insert  (singly_t * collection, uint32_t index, T value);
/* penghapusan elemen/node */
int32_t  singly_delete_front (singly_t * collection);
int32_t  singly_delete_rear  (singly_t * collection);
int32_t  singly_delete_at    (singly_t * collection, uint32_t index);
int32_t  singly_delete       (singly_t * collection, T value, uint32_t count);
/* perubahan data pada elemen tertentu */
int32_t  singly_update (singly_t * collection, uint32_t index, T value);
/* perubahan struktur */
int32_t  singly_merge  (singly_t * collection, singly_t * source);
int32_t  singly_clone  (singly_t * collection, singly_t * source);
int32_t  singly_clear  (singly_t * collection);

int32_t  singly_length (singly_t * collection);

void     singly_traverse (singly_t * collection, callback_t callback, T * acc);


/* ******************************* INTERNAL FUNCTIONS ******************************* */
/*
    Buat node baru.
*/
node_t * node_new (T value)
{
    node_t * node = (node_t*) malloc (sizeof (node_t));
    if (node != NULL)
    {
        node->_value = value;
        node->_next = NULL;
    }

    return node;
}

/*
    Mencari node berdasarkan index.
    Index dihitung dari awal node dengan 0 merujuk kepada node pertama.
*/
node_t * node_find_by_idx (node_t * startnode, uint32_t index, node_t ** res_prevnode)
{
    node_t *iternode, *prevnode;

    prevnode = NULL;
    iternode = startnode;

    /* iterasi list, cari node ke- (index - 1) atau selama list masih ada */
    while (iternode && index--)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    *res_prevnode = prevnode;
    
    return iternode;
}

/*
    Mencari node berdasarkan value.
*/
node_t * node_find_by_val (node_t * startnode, T value, node_t ** res_prevnode)
{
    node_t *prevnode, *iternode, *nextnode;

    prevnode = NULL;
    iternode = startnode;

    while (iternode && iternode->_value != value)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    *res_prevnode = prevnode;

    return iternode; 
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
int32_t singly_init (singly_t * collection)
{
    collection->_length = 0;
    collection->_head   = NULL;
    
    return 1;
}

/*
    Destruktor (penghancur objek)
    destruksi objek yang valid untuk membebaskan objek dari memori

    Parameter:
        - [singly_t] collection: objek yang akan didestruksi.
    Return: 
        - [int32_t] status destruksi (0 = gagal, 1 = berhasil)
*/
int32_t singly_destroy (singly_t * collection)
{
    /* tidak ada elemen tambahan sehingga destroy() = clear() */
    return singly_clear (collection);
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
int32_t singly_prepend (singly_t * collection, T value)
{
    /* 
    operasi prepend () atau menambahkan node di urutan terdepan merupakan 
    operasi yang ekivalen dengan operasi insert () pada posisi 0
    */
    return singly_insert (collection, 0, value);
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
int32_t singly_append (singly_t * collection, T value)
{
    /* 
    Operasi append () atau menambahkan node di urutan terakhir merupakan
    operasi yang ekivalen dengan operasi insert () pada posisi Length
    */
    return singly_insert (collection, collection->_length, value);
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
int32_t singly_insert (singly_t * collection, uint32_t index, T value)
{
    node_t   *prevnode, *node, *iternode;
    uint32_t iter;

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new (value);
    if (node == NULL)
        return 0;
    
    iternode = node_find_by_idx (collection->_head, index, &prevnode);

    /* tautkan node pendahulu (prevnode) ke node saat ini */
    if (prevnode)
        prevnode->_next = node;
    
    /* tautkan node saat ini ke node penerus */
    node->_next = iternode;

    /* jika index adalah 0, maka jadikan node sebagai head */
    if (index == 0 || collection->_length == 0)
        collection->_head = node;

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
int32_t singly_delete_front (singly_t * collection)
{
    /* 
    operasi penghapusan node di urutan terdepan merupakan 
    operasi yang ekivalen dengan operasi penghapusan pada posisi 0
    */
    return singly_delete_at (collection, 0);
}

/*
    Penghapusan (delete)
    Hapus sebuah node di akhir list

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t singly_delete_rear (singly_t * collection)
{
    /* 
    operasi penghapusan node di urutan terakhir merupakan 
    operasi yang ekivalen dengan operasi penghapusan pada posisi "Length - 1"
    */
    return singly_delete_at (collection, collection->_length - 1);
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
int32_t singly_delete_at (singly_t * collection, uint32_t index)
{
    node_t   *prevnode, *iternode, *nextnode;
    uint32_t  iter;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;
    
    iternode = node_find_by_idx (collection->_head, index, &prevnode);

    /* simpan alamat node penerus */
    nextnode = iternode->_next;
    
    /* lewati (skip) "thisnode" */
    if (prevnode)
        prevnode->_next = nextnode;
    
    /* jika penghapusan terjadi di head, maka ubah head agar menunjuk node berikutnya */
    if (index == 0)
        collection->_head = nextnode;
    
    /* dealokasi node */
    free (iternode);
    collection->_length --;

    return 1;
}

/*
    Penghapusan (delete)
    Menghapus sebanyak `count` kemunculan nilai `value` di list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan dihapus dari collection.
        - [uint32_t] count: banyaknya salinan node yang akan dihapus, 
                    0 jika ingin hapus semua kemunculan nilai.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t singly_delete (singly_t * collection, T value, uint32_t count)
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
    
    length     = collection->_length;

     /* iterasi list selama masih ada node dan counter masih ada */
    iternode = node_find_by_val (collection->_head, value, &prevnode);
    while (count && iternode)
    {
        /* simpan alamat node penerus */
        nextnode = iternode->_next;

        /* sesuaikan tautan pada prevnode agar menunjuk ke node penerus "iternode" */
        if (prevnode)
            prevnode->_next = nextnode;
        /* bila node yang dihapus merupakan head, maka pindahkan head ke posisi berikutnya */
        else 
            collection->_head = nextnode;

        /* hapus "iternode" */
        free (iternode);
        
        /* kurangi counter dan jumlah node */
        count --;
        length --;

        iternode = node_find_by_val (nextnode, value, &prevnode);
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
        - [int32_t] status perubahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_update (singly_t * collection, uint32_t index, T value)
{
    node_t  *prevnode, *iternode;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;
    else 
    {
        /* cari lokasi node yang akan diubah */
        iternode = node_find_by_idx (collection->_head, index, &prevnode);
        
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
        - [int32_t] status penggabungan (0 = gagal, 1 = berhasil)
*/
int32_t singly_merge (singly_t * collection, singly_t * source)
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

        /* iterasi hingga akhir list collection */
        while (iternode->_next)
            iternode = iternode->_next;
        
        iternode->_next = source->_head;
    }
    
    collection->_length += source->_length;
    
    /* kosongkan source */
    source->_length = 0;
    source->_head = NULL;

    return 1;
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
int32_t singly_clone (singly_t * collection, singly_t * source)
{
    node_t   *iterdst = NULL, *itersrc = NULL, *node;
    uint32_t length = 0;

    /*
    Apabila objek telah menyimpan beberapa node, maka list
    harus dibersihkan terlebih dahulu.
    */
    singly_clear (collection);

    /* iterasi seluruh node di dalam list */
    itersrc = source->_head;
    if (itersrc)
    {
        /* alokasi node sebagai calon head */
        node = node_new (itersrc->_value);
        
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
                node = node_new (itersrc->_value);
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
    }

    collection->_length = length;

    return 1;
}

/*
    Pembersihan (clear)
    Mengosongkan (menghapus) seluruh node dari list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] status pembersihan (0 = gagal, 1 = berhasil)
*/
int32_t singly_clear (singly_t * collection)
{
    node_t *iternode, *nextnode;

    if (collection->_length)
    {
        /* Iterasi seluruh list */
        iternode = collection->_head;
        while (iternode)
        {
            nextnode = iternode->_next;
            free (iternode);
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
        - [singly_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] jumlah node dalam list
*/
int32_t singly_length (singly_t * collection)
{
    return collection->_length;
}

/*
    Penelusuran (traverse)

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [callback_t] callback: pointer ke fungsi yang akan dipanggil terhadap
                    setiap nilai dalam collection.
        - [T] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
    Return:
        - None
*/
void singly_traverse (singly_t * collection, callback_t callback, T * acc)
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
        (*callback) (&iternode->_value, acc);

        /* maju ke node berikutnya */
        iternode = iternode->_next;
    }
}