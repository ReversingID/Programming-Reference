/*
    Singly Linked-List (Self Pointing Node)
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o self.asm self.c

        (msvc)
        $ cl /c /Faself.asm self.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus.

    Node yang menjadi node ujung (node terakhir) menunjuk ke diri sendiri 

    Kasus umum
    ...   A  ->  B  ->  C  ->  D  ->  E -- +
          ^                           ^    |
          ^                           + -- +
          ^
        HEAD
    
    Kasus kosong
    ...   <NULL>
            ^
            ^
           HEAD
    

    HEAD adalah pointer yang menunjuk ke node di awal list.

    Senarai dengan representasi ini dipilih jika tidak dikehendaki adanya suatu
    alamat link yang bernilai NULL pada akhir traversal. Dengan representasi ini
    maka traversal selalu terhenti pada elemen terakhir. Operasi terhadap element
    terakhir tidak memerlukan adanya memorisasi alamat node pendahulu.
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
#include <stdio.h>
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

    /* jika senarai kosong, jadikan node sebagai elemen pertama (head) */
    if (collection->_length == 0)
        collection->_head = node;

    /* jika tidak, temukan posisi yang sesuai untuk menyisipkan node */
    else 
    {
        printf(" > %d\n", index);
        /* iterasi list, cari node ke-(index-1) atau selama list masih ada */
        for (iter = index; iternode->_next != iternode && iter; iter--)
        {
            prevnode = iternode;
            iternode = iternode->_next;
            printf("  %d %p %p\n", iter, prevnode, iternode);
        }
        printf(" < %d %p %p\n", iter, node, iternode);


        /* tautkan node pendahulu (prevnode) ke node saat ini */
        if (prevnode)
            prevnode->_next = node;
        
        /* tautkan node saat ini ke node penerus */
        if (iternode  )
            node->_next = iternode;

        /* jika index adalah 0, maka jadikan node sebagai head */
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
    return 1;
    
    /* dealokasi node */
    // free(iternode);
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
    return 1;

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
    node_t   *iternode;
    uint32_t length;

    /* jika list collection kosong maka cukup pindahkan referensi head */
    if (collection->_length == 0)
        collection->_head = source->_head;
    /* jika tidak maka ... */
    else 
    {
        /* iterasi hingga akhir list collection */
        iternode = collection->_head;
        while (iternode->_next != iternode)
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

    return 1;

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
    uint32_t iter;

    /* Jika list kosong atau callback tak terdefinisi, maka iterasi tidak dilakukan */
    if (collection->_length == 0 || callback == NULL)
        return;

    /* jika tidak, iterasi list */
    iternode = collection->_head;
    for (iter = 0; iter < collection->_length; iter++)
    {
        /* jalankan callback di setiap node */
        (*callback)(&iternode->_value, acc);

        /* maju ke node berikutnya */
        iternode = iternode->_next;
    }
}

#include <stdio.h>

int32_t printT(T * val, T * acc)
{
    printf("%d %p\n", *val, val);
}

int main()
{
    singly_t coll1, coll2, coll3;
    T acc;
    
    /* inisialisasi collection */
    singly_init(&coll1);
    singly_init(&coll2);
    singly_init(&coll3);

    /* Tambah node di awal list */
    singly_prepend(&coll1, 10);
    printf("Kondisi list-1 (prepend):\n");
    singly_traverse(&coll1, &printT, &acc);
    printf("\n\n");

    /* Tambah node di akhir list */
    singly_append(&coll1, 20);
    singly_append(&coll1, 30);
    /* Tambah node di awal list */
    singly_prepend(&coll1, 40);
    printf("Kondisi list-2 (append-append-prepend):\n");
    singly_traverse(&coll1, &printT, &acc);
    printf("\n\n");

    /* Tambah node sebagai index 2 */
    singly_insert(&coll1, 2, 50);
    printf("Kondisi list-3 (insert di tengah):\n");
    singly_traverse(&coll1, &printT, &acc);
    printf("\n\n");

    /* Tambah node sebagai index 0 */
    singly_insert(&coll1, 0, 60);
    printf("Kondisi list-4 (insert di awal):\n");
    singly_traverse(&coll1, &printT, &acc);
    printf("\n\n");

    /* Tambah node sebagai index 12 */
    singly_insert(&coll1, 12, 70);
    printf("Kondisi list-5 (insert di index lebih besar daripada panjang list):\n");
    singly_traverse(&coll1, &printT, &acc);
    printf("\n\n");

    /* Update node dengan index 4 */
    singly_update(&coll1, 4, 25);
    printf("Kondisi list-6 (update node ke-4):\n");
    singly_traverse(&coll1, &printT, &acc);
    printf("\n\n");

    /* 
    gabungkan coll1 dan coll2 
    karena coll2 kosong, maka coll2 akan bernilai sama dengan coll1
    */
    singly_merge(&coll2, &coll1);
    printf("Kondisi list-7 (coll1) len=%d:\n", singly_length(&coll1));
    singly_traverse(&coll1, &printT, &acc);
    printf("\n");
    printf("Kondisi list-7 (coll2) len=%d:\n", singly_length(&coll2));
    singly_traverse(&coll2, &printT, &acc);
    printf("\n\n");

    /* Hapus nilai 60 sebanyak 2 buah dari coll2 */
    singly_delete(&coll2, 60, 2);
    printf("Kondisi list-8 (menghapus node dengan nilai 60):\n");
    singly_traverse(&coll2, &printT, &acc);
    printf("\n\n");

    /* Hapus node pertama */
    singly_delete_front(&coll2);
    printf("Kondisi list-9 (menghapus node awal):\n");
    singly_traverse(&coll2, &printT, &acc);
    printf("\n\n");

    /* Hapus node terakhir */
    singly_delete_rear(&coll2);
    printf("Kondisi list-10 (menghapus node terakhir):\n");
    singly_traverse(&coll2, &printT, &acc);
    printf("\n\n");

    /* Kloning coll2 dan merge */
    singly_clone(&coll3, &coll2);
    printf("Kondisi list-11 (list orisinil):\n");
    singly_traverse(&coll2, &printT, &acc);
    printf("\n");
    printf("Kondisi list-11 (list hasil clone):\n");
    singly_traverse(&coll3, &printT, &acc);
    printf("\n");
    singly_merge(&coll3, &coll2);
    printf("Kondisi list-11 (hasil merge coll3 & coll2):\n");
    singly_traverse(&coll3, &printT, &acc);
    printf("\n\n");
    return 0;
}