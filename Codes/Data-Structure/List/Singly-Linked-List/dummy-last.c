/*
    Singly Linked-List (Dummy Node as Last Node)
    Archive of Reversing.ID
    Data Structure

    Assemble:
        (gcc)
        $ gcc -m32 -S -masm=intel -o dummy-last.asm dummy-last.c

        (msvc)
        $ cl /c /Fadummy-last.asm dummy-last.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/*
    Serangkaian node dengan sebuah field yang menunjuk ke alamat node penerus.

    Sebuah elemen fiktif (dummy) sengaja dialokasikan untuk mempermudah operasi namun
    bukan termasuk sebagai bagian dari senarai. Node fiktif ini digunakan agar penanganan
    terhadap kasus senarai kosong tidak berbeda dengan penangan kasus senarai umum.

    Kasus umum
    ...   A  ->  B  ->  C  ->  D  ->  DUMMY  ->  <NULL>
          ^                             ^
          |                             |
        HEAD                          TAIL

    Kasus kosong
    ...   DUMMY  ->  <NULL>
            ^
        + - + - +
        |       |
       HEAD   TAIL
    

    HEAD adalah pointer yang menunjuk ke node di awal list.
    TAIL adalah pointer yang menunjuk ke node fiktif.
    
    Representasi ini seringkali digunakan jika dummy merupakan sentinel dan pencarian 
    diperlukan sebelum penambahan elemen. Dengan representasi ini, nilai yang dicari dapat 
    secara langsung disimpan untuk sementara pada dummy kemudian dilakukan searching. 
    Jika searching tidak berhasil dan elemen akan ditambahkan elemen baru
    
    Contoh pemakaian sentinel untuk kombinasi search dan insert ini sangat efisien terutama
    pada topological sort.
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
    node_t * dummy;

    dummy = node_new(0);

    collection->_length = 0;
    collection->_head   = dummy;
    collection->_tail   = dummy;

    if (dummy)
        return 1;

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
int32_t singly_prepend(singly_t * collection, T value)
{
    node_t * node; 

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new(value);
    if (node == NULL)
        return 0;
    
    /* tautkan "head" sebagai node penerus */
    node->_next = collection->_head;

    /* Jadikan node sebagai "head" baru */
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
    node_t *node, *tail; 

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new(0);
    if (node == NULL)
        return 0;
    
    tail = collection->_tail;

    /* ubah nilai di elemen fiktif */
    tail->_value = value;

    /* tambahkan elemen fiktif baru */
    tail->_next = node;
    collection->_tail = node;

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
    for (iter = index; iternode && iter; iter--)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    /* simpan alamat node penerus */
    nextnode = iternode->_next;
    
    /* lewati (skip) "thisnode" */
    if (prevnode)
        prevnode->_next = nextnode;
    
    /* jika penghapusan terjadi di head, maka ubah head agar menunjuk node berikutnya */
    if (index == 0)
        collection->_head = nextnode;
    
    /* dealokasi node */
    free(iternode);
    collection->_length --;

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
#include <stdio.h>
int32_t singly_insert(singly_t * collection, uint32_t index, T value)
{
    node_t   *prevnode, *node, *iternode;
    uint32_t iter;

    /* jika penyisipan terjadi di depan, gunakan prepend() */
    if (index == 0)
        return singly_prepend(collection, value);
    
    /* jika penyisipan terjadi di belakang, gunakan append() */
    else if (index >= collection->_length)
        return singly_append(collection, value);

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = node_new(value);
    if (node == NULL)
        return 0;
    
    iter = index;
    prevnode = collection->_head;
    iternode = prevnode->_next;

    /* iterasi list, cari node ke-(index-1) atau selama list masih ada */
    while (iternode && --iter)
    {
        prevnode = iternode;
        iternode = iternode->_next;
    }

    /* tautkan node pendahulu (prevnode) ke node saat ini */
    prevnode->_next = node;
    
    /* tautkan node saat ini ke node penerus */
    node->_next = iternode;

    collection->_length ++;

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

    iternode = collection->_head;

    /* jika tidak, iterasi list */
    while (iternode->_next)
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

    // /* Update node dengan index 4 */
    // singly_update(&coll1, 4, 25);
    // printf("Kondisi list-6 (update node ke-4):\n");
    // singly_traverse(&coll1, &printT, &acc);
    // printf("\n\n");

    // /* 
    // gabungkan coll1 dan coll2 
    // karena coll2 kosong, maka coll2 akan bernilai sama dengan coll1
    // */
    // singly_merge(&coll2, &coll1);
    // printf("Kondisi list-7 (coll1) len=%d:\n", singly_length(&coll1));
    // singly_traverse(&coll1, &printT, &acc);
    // printf("\n");
    // printf("Kondisi list-7 (coll2) len=%d:\n", singly_length(&coll2));
    // singly_traverse(&coll2, &printT, &acc);
    // printf("\n\n");

    // /* Hapus nilai 60 sebanyak 2 buah dari coll2 */
    // singly_delete(&coll2, 60, 2);
    // printf("Kondisi list-8 (menghapus node dengan nilai 60):\n");
    // singly_traverse(&coll2, &printT, &acc);
    // printf("\n\n");

    // /* Hapus node pertama */
    // singly_delete_front(&coll2);
    // printf("Kondisi list-9 (menghapus node awal):\n");
    // singly_traverse(&coll2, &printT, &acc);
    // printf("\n\n");

    // /* Hapus node terakhir */
    // singly_delete_rear(&coll2);
    // printf("Kondisi list-10 (menghapus node terakhir):\n");
    // singly_traverse(&coll2, &printT, &acc);
    // printf("\n\n");

    // /* Kloning coll2 dan merge */
    // singly_clone(&coll3, &coll2);
    // printf("Kondisi list-11 (list orisinil):\n");
    // singly_traverse(&coll2, &printT, &acc);
    // printf("\n");
    // printf("Kondisi list-11 (list hasil clone):\n");
    // singly_traverse(&coll3, &printT, &acc);
    // printf("\n");
    // singly_merge(&coll3, &coll2);
    // printf("Kondisi list-11 (hasil merge coll3 & coll2):\n");
    // singly_traverse(&coll3, &printT, &acc);
    // printf("\n\n");
    return 0;
}