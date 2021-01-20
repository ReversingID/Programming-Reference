/*
    Singly Linked-List (Dummy Node as First Node)
    Archive of Reversing.ID
    Data Structure

Assemble:
    (gcc)
    $ gcc -m32 -S -masm=intel -o sentinel-first.asm sentinel-first.c

    (msvc)
    $ cl /c /Fasentinel-first.asm sentinel-first.c

    (clang)
    $ clang -m32 -S -masm=intel -o sentinel-first.asm sentinel-first.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus.

    Sebuah elemen fiktif (sentinel) sengaja dialokasikan untuk mempermudah operasi namun
    bukan termasuk sebagai bagian dari senarai. Node fiktif ini digunakan agar penanganan
    terhadap kasus senarai kosong tidak berbeda dengan penangan kasus senarai umum.

    Kasus umum
    ... DUMMY  ->  A  ->  B  ->  C  ->  D  ->  E  ->  <NULL>
          ^
          ^
        HEAD

    Kasus kosong
    ... DUMMY  ->  <NULL>
          ^
          ^
        HEAD
    

    HEAD adalah pointer yang menunjuk ke node di awal list.
    
    Dengan adanya elemen fiktir sebagai elemen pertama, penyisipan nilai melalui append () 
    pada kasus senarai kosong akan menjadi sama pada senarai biasa. Pengaksesan elemen 
    pertama tidak akan pernah menghasilkan NULL melainkan selalu terdefinisi.


    Asumsi:
    Struktur data tidak generic.
    Tidak ada alokasi VALUE ketika pembuatan node baru, data yang disimpan akan disalin
    secara langsung.
    HEAD adalah sentinel
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
    node_t * sentinel;

    sentinel = node_new (0);

    collection->_length = 0;
    collection->_head   = sentinel;

    if (sentinel)
        return 1;

    return 0;
}

/*
    Destruktor (penghancur objek)
    Destruksi objek yang valid untuk membebaskan objek dari memori

    Parameter:
        - [singly_t] collection: objek yang akan didestruksi.
    Return: 
        - [int32_t] status konstruksi (0 = gagal, 1 = berhasil)
*/
int32_t singly_destroy (singly_t * collection)
{
    /* bersihkan node terlebih dahulu, kemudian bersihkan sentinel */
    if (singly_clear (collection))
    {
        // Bersihkan sentinel yang menjadi node pertama
        free (collection->_head);
        collection->_head   = NULL;

        return 1;
    }

    return 0;
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
    node_t * prevnode, *node;
    
    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new (value);
    if (node == NULL)
        return 0;
    
    prevnode = collection->_head;

    /* iterasi list, cari node ke- (index-1) atau selama list masih ada */
    while (prevnode->_next && index--)
        prevnode = prevnode->_next;
    
    /* Tautkan node setelah "prevnode" sebagai node penerus */
    node->_next = prevnode->_next;

    /* Tautkan node ini sebagai node penerus "prevnode" */
    prevnode->_next = node;

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
    node_t   *prevnode, *iternode;
    uint32_t  iter;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;

    prevnode = collection->_head;
    iternode = prevnode->_next;

    /* iterasi list, cari node ke-index atau selama list masih ada */
    for (iter = index; iternode && iter; iter--)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }
    
    /* lewati (skip) "thisnode" */
    prevnode->_next = iternode->_next;
    
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
    prevnode   = collection->_head;
    iternode   = prevnode->_next;

    /* iterasi list selama masih ada node dan counter masih ada */
    while (count && iternode)
    {
        /* simpan alamat node penerus */
        nextnode = iternode->_next;

        /* jika node memiliki nilai yang dicari ... */
        if (iternode->_value == value)
        {
            /* sesuaikan tautan pada prevnode agar menunjuk ke node penerus "iternode" */
            prevnode->_next = nextnode;
            
            /* hapus "iternode" */
            free (iternode);
            
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
        - [int32_t] status perubahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_update (singly_t * collection, uint32_t index, T value)
{
    node_t * iternode;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;
    else 
    {
        /* jika index adalah 0, maka ubah nilai di node terdepan */
        iternode = collection->_head->_next;

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
        - [int32_t] status penggabungan (0 = gagal, 1 = berhasil)
*/
int32_t singly_merge (singly_t * collection, singly_t * source)
{
    node_t   *iternode;

    /* jika list collection kosong maka ... */
    if (collection->_length == 0)
        /* cukup pindahkan referensi head di source ke collection */
        collection->_head->_next = source->_head->_next;
    /* jika tidak maka ... */
    else 
    {
        iternode = collection->_head;

        /* iterasi hingga akhir list collection */
        while (iternode->_next)
            iternode = iternode->_next;
        
        iternode->_next = source->_head->_next;
    }
    
    collection->_length += source->_length;
    
    /* kosongkan source */
    source->_length = 0;
    source->_head->_next = NULL;

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
    itersrc = source->_head->_next;
    if (itersrc)
    {
        /* alokasi node sebagai calon head */
        node = node_new (itersrc->_value);
        
        /* jika alokasi berhasil maka ... */
        if (node)
        {
            /* jadikan node tersebut sebagai head */
            collection->_head->_next = node;
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

    if (collection->_head)
    {
        /* Iterasi seluruh list */
        iternode = collection->_head->_next;
        while (iternode)
        {
            nextnode = iternode->_next;
            free (iternode);
            iternode = nextnode;
        }
        collection->_head->_next = NULL;
    }

    collection->_length = 0;

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

    iternode = collection->_head->_next;

    /* jika tidak, iterasi list */
    while (iternode)
    {
        /* jalankan callback di setiap node */
       (*callback) (&iternode->_value, acc);

        /* maju ke node berikutnya */
        iternode = iternode->_next;
    }
}