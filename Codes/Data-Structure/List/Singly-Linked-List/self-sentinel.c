/*
    Singly Linked-List (Self Pointing Node as Dummy on Last)
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o self-sentinel.asm self-sentinel.c

        (msvc)
        $ cl /c /Faself-sentinel.asm self-sentinel.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus.

    Sebuah elemen fiktif (dummy) sengaja dialokasikan untuk mempermudah operasi namun
    bukan termasuk sebagai bagian dari senarai. Node fiktif ini kemudian menggunakan 
    alamat diri sendiri sebagai node penerus.

    Kasus umum
    ...   A  ->  B  ->  C  ->  D  ->  DUMMY -- +
          ^                             ^      |
          ^                             + ---- +
          ^
        HEAD

    Kasus kosong
    ... DUMMY -- +
        ^   ^    |
        ^   + -- +
        ^
      HEAD


    HEAD adalah pointer yang menunjuk ke node di awal list.

    Seringkali representasi ini dipilih jika tidak dikehendaki hasil NULL pada akhir
    traversal. Dengan representasi ini, maka traversal "terhenti" pada elemen terakhir.
    Operasi terhadap elemen terakhi tidak memerlukan memorisasi elemen sebelumnya, misalnya
    jika ingin melakukan pnemabahan menjadi elemen terakhir.


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
int32_t  singly_init    (singly_t * collection);
int32_t  singly_destroy (singly_t * collection);

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
        node->_value = value;
        node->_next = node;
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
    collection->_head   = node_new(0);

    if (collection->_head)
        return 1;

    return 0;
}

/*
    Destruktor (penghancur objek)
    destruktsi objek yang valid untuk membebaskan objek dari memori

    Parameter:
        - [singly_t] collection: objek yang akan didestruksi.
    Return: 
        - [int32_t] status konstruksi (0 = gagal, 1 = berhasil)
*/
int32_t singly_destroy(singly_t * collection)
{
    if (collection->_length > 0 && collection->_head)
        singly_clear(collection);
    
    // Bersihkan sentinel
    free(collection->_head);
    
    collection->_length = 0;
    collection->_head   = NULL;

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
    /* 
    operasi prepend() atau menambahkan node di urutan terdepan merupakan 
    operasi yang ekivalen dengan operasi insert() pada posisi 0
    */
    return singly_insert(collection, 0, value);
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
    /* 
    Operasi append() atau menambahkan node di urutan terakhir merupakan
    operasi yang ekivalen dengan operasi insert() pada posisi Length
    */
    return singly_insert(collection, collection->_length, value);
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
    node_t   *prevnode, *node, *iternode;
    uint32_t iter;

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new(value);
    if (node == NULL)
        return 0;

    prevnode = NULL;
    iternode = collection->_head;

    /* iterasi list, cari node ke-(index-1) atau selama list masih ada */
    for (iter = index; iternode->_next != iternode && iter; iter--)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

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
int32_t singly_delete_front(singly_t * collection)
{
    /* 
    operasi penghapusan node di urutan terdepan merupakan 
    operasi yang ekivalen dengan operasi penghapusan pada posisi 0
    */
    return singly_delete_at(collection, 0);
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
    /* 
    operasi penghapusan node di urutan terakhir merupakan 
    operasi yang ekivalen dengan operasi penghapusan pada posisi "Length - 1"
    */
    return singly_delete_at(collection, collection->_length - 1);
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
    node_t   *prevnode, *iternode, *nextnode;
    uint32_t  iter;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;

    prevnode = NULL;
    iternode = collection->_head;

    /* iterasi list, cari node ke-index atau selama list masih ada */
    for (iter = index; iternode->_next != iternode && iter; iter--)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    /* simpan alamat node penerus */
    nextnode = iternode->_next;
    
    /* jika penghapusan terjadi di head, maka ubah head agar menunjuk node berikutnya */
    if (index == 0)
        collection->_head = nextnode;
    
    /* lewati (skip) "thisnode" */
    else
        prevnode->_next = nextnode;
    
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
        - [uint32_t] count: banyaknya salinan node yang akan dihapus, 
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
    while (count && iternode->_next != iternode)
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
        while (iternode->_next != iternode && index--)
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
    node_t   *prevnode, *iternode, *dummy;
    uint32_t length;

    /* jika source kosong, tidak ada yang perlu dilakukan */
    if (source->_length == 0)
        return 0;

    prevnode = NULL;
    iternode = collection->_head;

    /* telusuri hingga tail dari "collection" */
    while (iternode->_next != iternode)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    /* simpan node dummy untuk sementara */
    dummy = iternode;

    /* sambungkan node terakhir (non elemen fiktif) ke node pertama di source */
    if (prevnode)
        prevnode->_next = source->_head;
    else 
        collection->_head = source->_head;
    
    /* telusuri hingga elemen fiktif dari "source" */
    iternode = source->_head;
    while (iternode->_next != iternode)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    /* jadikan elemen fiktif sebagai elemen terakhir */
    prevnode->_next = dummy;
    
    collection->_length += source->_length;
    
    /* kosongkan source */
    source->_length = 0;
    source->_head = iternode;

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
        while (iternode->_next != iternode)
        {
            nextnode = iternode->_next;
            free(iternode);
            iternode = nextnode;
        }
        collection->_length = 0;
        collection->_head = iternode;
    }

    return 1;
}

/*
    Mendapatkan banyaknya node yang ada di dalam list.

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] jumlah node dalam list
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
    node_t   *iterdst = NULL, *itersrc = NULL, *node, *dummy;
    uint32_t length = 0;

    /*
    Apabila objek telah menyimpan beberapa node, maka list
    harus dibersihkan terlebih dahulu.
    */
    singly_clear(collection);

    /* iterasi seluruh node di dalam list */
    dummy   = collection->_head;
    itersrc = source->_head;
    if (itersrc->_next != itersrc)
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
            while (itersrc->_next != itersrc)
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

            /* sesuaikan agar node terakhir merupakan elemen fiktif */
            iterdst->_next = dummy;
        }
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
        - [T] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
    Return:
        - None
*/
void singly_traverse(singly_t * collection, callback_t callback, T * acc)
{
    node_t *iternode;

    /* Jika list kosong atau callback tak terdefinisi, maka iterasi tidak dilakukan */
    if (collection->_length == 0 || callback == NULL)
        return;

    /* jika tidak, iterasi list */
    iternode = collection->_head;
    while (iternode->_next != iternode)
    {
        /* jalankan callback di setiap node */
        (*callback)(&iternode->_value, acc);

        /* maju ke node berikutnya */
        iternode = iternode->_next;
    }
}