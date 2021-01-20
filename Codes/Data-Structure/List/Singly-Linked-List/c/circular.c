/*
    Singly Linked-List (Circular)
    Archive of Reversing.ID
    Data Structure

Assemble:
    (gcc)
    $ gcc -m32 -S -masm=intel -o circular.asm circular.c

    (msvc)
    $ cl /c /Facircular.asm circular.c

    (clang)
    $ clang -m32 -S -masm=intel -o circular.asm circular.c
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
typedef int32_t value_t;

/* 
    Prototipe dari function pointer yang digunakan untuk memanipulasi elemen dalam
    collection.

    Parameter:
        - [value_t] val: value dari node yang sedang diiterasi
        - [value_t] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
*/
typedef int32_t (*callback_t) (value_t * val,value_t * acc);

/*
    Node definition
*/
typedef struct node_t
{
    value_t         _value;
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
node_t * node_new (value_t value)
{
    node_t * node = (node_t*) malloc (sizeof (node_t));
    if (node != NULL)
    {
        node->_value = value;
        node->_next = node;

        /*
        Secara default node akan menunjuk diri sendiri sebagai node penerus.
        Ubah ini dalam operasi penambahan node.
        */
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
    collection->_length = 0;
    collection->_head   = NULL;         /* kasus kosong */

    return 1;
}

/*
    Destruktor (penghancur objek)
    Destruksi objek yang valid untuk membebaskan objek dari memori

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
        - [value_t] value: elemen yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_prepend (singly_t * collection, value_t value)
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
        - [value_t] value: elemen yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_append (singly_t * collection, value_t value)
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
        - [value_t] value: nilai yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_insert (singly_t * collection, uint32_t index, value_t value)
{
    node_t *node, *headnode, *iternode;
    
    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new (value);
    if (node == NULL)
        return 0;

    iternode = collection->_head;
    headnode = collection->_head;
    
    /* Jika list kosong, jadikan node sebagai node mula-mula */
    if (collection->_length == 0)
        collection->_head = node;
    
    /* Jika penambahan dilakukan di awal (index 0) */
    else if (index == 0)
    {
        /* jadikan node sebagai HEAD */
        node->_next = headnode;
        collection->_head = node;

        /* normalisasi ujung list agar menunjuk ke HEAD baru */
        while (iternode->_next != headnode)
            iternode = iternode->_next;
        
        iternode->_next = node;
    }

    /* Jika penambahan dilakukan di tengah hingga akhir */
    else 
    {
        /* iterasi list, cari ndoe ke- (index-1) atau selama list masih ada */
        while (iternode->_next != headnode && --index)
            iternode = iternode->_next;
        
        node->_next = iternode->_next;
        iternode->_next = node;
    }

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
    node_t   *prevnode, *iternode, *headnode;
    uint32_t  iter;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;

    iternode = collection->_head;
    headnode = collection->_head;

    /* Jika hanya ada satu node tersisa, kosongkan */
    if (collection->_length == 1)
        collection->_head = NULL;
    
    /* Jika penghapusan dilakukan di awal (index 0) maka ubah posisi HEAD */
    else if (index == 0)
    {
        /* jadikan node penerus sebagai HEAD baru */
        collection->_head = headnode->_next;

        /* normalisasi ujung list agar menunjuk ke HEAD baru */
        while (iternode->_next != headnode)
            iternode = iternode->_next;
        
        iternode->_next = collection->_head;

        /* kembali menunjuk ke HEAD lama */
        iternode = headnode;
    }

    /* Jika penghapusan dilakukan di tengah hingga akhir */
    else 
    {
        /* iterasi list, cari ndoe ke- (index-1) atau selama list masih ada */
        while (iternode->_next != headnode && index--)
        {
            prevnode = iternode;
            iternode = iternode->_next;
        }
        
        /* Jika node ini merupakan node akhir, maka jadikan node sebagai ujung yang baru */
        if (iternode->_next == headnode)
            prevnode->_next = headnode;

        /* Jika tidak, tautkan node berikutnya ke node pendahulu */
        else
            prevnode->_next = iternode->_next;
    }

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
        - [value_t] value: elemen yang akan dihapus dari collection.
        - [uint32_t] count: banyaknya salinan node yang akan dihapus, 
                    0 jika ingin hapus semua kemunculan nilai.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t singly_delete (singly_t * collection, value_t value, uint32_t count)
{
    node_t   *headnode, *prevnode, *iternode, *nextnode;
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
    headnode   = collection->_head;
    iternode   = collection->_head;

    /* Jika node yang dicari ada di awal, hapus node yang berurutan di awal */
    if (iternode->_value == value)
    {
        /* iterasi list dan hapus node yang sesuai di awal */
        while (count && iternode->_next != headnode && iternode->_value == value)
        {
            /* Kondisi saat ini prevnode masih NULL, kita masih ada di awal */
            nextnode = iternode->_next;

            /* hapus "iternode" yang berarti kurangi counter dan jumlah node */
            free (iternode);
            count --;
            length --;

            iternode = nextnode;
        }

        /* pindahkan HEAD ke posisi yang sesuai */
        collection->_head = iternode;
    }
    
    prevnode = iternode;
    iternode = iternode->_next;

    /* iterasi segment di tengah list */
    while (count && iternode->_next != headnode)
    {
        /* simpan alamat node penerus */
        nextnode = iternode->_next;

        /* jika node memiliki nilai yang dicari ... */
        if (iternode->_value == value)
        {
            /* sesuaikan tautan pada prevnode agar menunjuk ke node penerus "iternode" */
            prevnode->_next = nextnode;
            
            /* hapus "iternode" yang berarti kurangi counter dan jumlah node */
            free (iternode); 
            count --;
            length --;
        }
        /* jika tidak, maka ubah nilai "prevnode" agar dapat mengikuti "iternode" */
        else 
            prevnode = iternode;

        /* pindahkan pointer "iternode" menunjuk ke node berikutnya */
        iternode = nextnode;
    }
    
    /*
    Ada dua kondisi berakhirnya loop:
        - tidak ada lagi yang perlu dihapus (count mencapai 0)
        - mencapai ujung list
    
    Periksa node jika kondisi kedua tercapai.
    */
    if (count && iternode->_value == value)
    {
        /* Jika ini node terakhir */
        if (length == 1)
            collection->_head = NULL;
            
        /* hapus "iternode" */
        free (iternode);
        length --;

        /* normalisasi agar menunjuk ke HEAD */
        prevnode->_next = collection->_head;
    }

    /* normalisasi agar node terakhir menunjuk ke HEAD baru */
    else if (headnode != collection->_head)
    {
        while (iternode->_next != headnode)
            iternode = iternode->_next;
        
        iternode->_next = collection->_head;
    }
    
    collection->_length = length;

    return 1;
}

/*
    Perubahan (update)

    Parameter:
        - [singly_t] collection: objek yang telah dikonstruksi.
        - [value_t] value: nilai baru yang akan diisikan.
        - [uint32_t] index: index dari elemen yang akan dimodifikasi
    Return:
        - [int32_t] status perubahan (0 = gagal, 1 = berhasil)
*/
int32_t singly_update (singly_t * collection, uint32_t index, value_t value)
{
    node_t *iternode, *headnode;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->_length == 0 || index >= collection->_length)
        return 0;

    else 
    {
        /* jika index adalah 0, maka ubah nilai di node terdepan */
        iternode = collection->_head;
        headnode = collection->_head;

        /* jika tidak, iterasi list dan cari node ke-index atau selama list masih ada */
        while (iternode->_next != headnode && index--)
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
    node_t   *iternode, *headnode;

    /* jika list collection kosong maka ... */
    if (collection->_length == 0)
        /* cukup pindahkan referensi head di source ke collection */
        collection->_head = source->_head;
    /* jika tidak maka ... */
    else 
    {
        iternode = collection->_head;
        headnode = collection->_head;

        /* iterasi hingga akhir list collection */
        while (iternode->_next != headnode)
            iternode = iternode->_next;
        
        iternode->_next = source->_head;
        headnode = source->_head;
        iternode = headnode->_next;

        /* normalisasi agar node akhir menunjuk ke HEAD */
        while (iternode->_next != headnode)
            iternode = iternode->_next;
        
        iternode->_next = collection->_head;
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
    node_t   *iterdst = NULL, *itersrc = NULL, *headnode, *node;
    uint32_t length = 0;

    /*
    Apabila objek telah menyimpan beberapa node, maka list
    harus dibersihkan terlebih dahulu.
    */
    singly_clear (collection);

    /* iterasi seluruh node di dalam list */
    itersrc = source->_head;
    headnode = source->_head;

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
            while (itersrc->_next != headnode)
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

            /* buat dan tautkan node terakhir */
            node = node_new (itersrc->_value);
            if (node)
            {
                node->_next = collection->_head;
                iterdst->_next = node;
                length++;
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
    node_t *iternode, *headnode, *nextnode;

    /* Jika list kosong maka tidak ada yang perlu dilakukan */
    if (collection->_head == NULL)
        return 0;
    
    /* Iterasi seluruh list */
    iternode = collection->_head;
    headnode = collection->_head;
    
    while (iternode->_next != headnode)
    {
        nextnode = iternode->_next;
        free (iternode);
        iternode = nextnode;
    }

    /* hapus node terakhir */
    free (iternode);

    collection->_length = 0;
    collection->_head   = NULL;

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
        - [value_t] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
    Return:
        - None
*/
void singly_traverse (singly_t * collection, callback_t callback, value_t * acc)
{
    node_t *iternode, *headnode;

    /* Jika list kosong atau callback tak terdefinisi, maka iterasi tidak dilakukan */
    if (collection->_length == 0 || callback == NULL)
        return;
    
    iternode = collection->_head;
    headnode = collection->_head;

    /* iterasi seluruh list hingga mencapai node akhir */
    while (iternode->_next != headnode)
    {
        /* jalankan callback di setiap node */
        (*callback) (&iternode->_value, acc);

        /* maju ke node berikutnya */
        iternode = iternode->_next;
    }

    /* jalankan callback di node ujung */
    (*callback) (&iternode->_value, acc);
}