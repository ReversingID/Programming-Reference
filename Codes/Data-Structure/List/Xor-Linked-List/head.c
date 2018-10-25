/*
    Xor Linked-List 
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
    Sebuah doubly linked list dengan hanya satu field untuk menyimpan informasi next
    dan previous node dalam bentuk XOR.

    ...   A       B       C       D       E   ...
             <-> A^C <-> B^D <-> C^E <-> 
    
    link(B) = addr(A) ^ addr(C) 

    Variasi:
        - Addition linked list
        - Subtraction linked list
*/

/* ******************************** TYPE DEFINITIONS ******************************** */
/* 
    Tipe data value node 

    Tidak ada batasan terhadap tipe data yang dapat digunakan. Namun untuk menyederhanakan
    persoalan, tipe integer digunakan sebagai contoh.
*/
typedef int T;

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
    T value;
    struct node_t * address;
} node_t;

/*
    Data structure definition
*/
typedef struct 
{
    uint32_t        length;
    struct node_t * head;
} xorlist_t;

/* ******************************** PROTOTIPE FUNGSI ******************************** */
int32_t  xorlist_init    (xorlist_t * collection);

int32_t  xorlist_prepend (xorlist_t * collection, T value);
int32_t  xorlist_append  (xorlist_t * collection, T value);
int32_t  xorlist_insert  (xorlist_t * collection, uint32_t index, T value);

int32_t  xorlist_delete_front (xorlist_t * collection);
int32_t  xorlist_delete_rear  (xorlist_t * collection);
int32_t  xorlist_delete_at    (xorlist_t * collection, uint32_t index);
int32_t  xorlist_delete       (xorlist_t * collection, T value, uint32_t count);

int32_t  xorlist_update (xorlist_t * collection, uint32_t index, T value);

int32_t  xorlist_merge (xorlist_t * collection, xorlist_t * source);

int32_t  xorlist_clear (xorlist_t * collection);

int32_t  xorlist_clone (xorlist_t * collection, xorlist_t * source);

void     xorlist_traverse (xorlist_t * collection, callback_t callback, T * acc);

/* ******************************* INTERNAL FUNCTIONS ******************************* */
/*
    Buat node baru.
*/
node_t * newnode(T value)
{
    node_t * node = (node_t*) malloc(sizeof(node_t));
    if (node != NULL)
    {
        memcpy(&node->value, &value, sizeof(T));
        node->address = NULL;
    }
    return node;
}

/*
    Operasi XOR untuk mendapatkan alamat node
    Operasi ini memenuhi persamaan:

    NULL == leftnode ^ address ^ rightnode
*/
node_t * node_xor(node_t * leftnode, node_t * address, node_t * rightnode)
{
    return (node_t*)(
        (uintptr_t) leftnode ^ (uintptr_t) address ^ (uintptr_t) rightnode
    );
}

/*
    Menautkan atau memecah tautan di antara dua buah node.
*/
void node_link(node_t * leftnode, node_t * rightnode)
{
    /* node penerus dari "leftnode" adalah "rightnode" */
    leftnode->address = node_xor(NULL, leftnode->address, rightnode);

    /* node pendahulu dari "rightnode" adalah "leftnode" */
    rightnode->address = node_xor(leftnode, rightnode->address, NULL);
}

/*
    Mencari node dengan index tertentu.
*/
node_t * xorlist_find(xorlist_t * collection, uint32_t index, node_t** res_prevnode)
{
    node_t *save, *iternode, *prevnode;
    
    prevnode = NULL;
    iternode = collection->head;

    while (prevnode != iternode->address && index--)
    {
        save = iternode;
        iternode = node_xor(prevnode, iternode->address, NULL);
        prevnode = save;
    }
    
    if (res_prevnode)
        *res_prevnode = prevnode;

    return iternode;
}


/* ***************************** PRIMITIVE & OPERATIONS ***************************** */
/*
    Konstruktor (pembentuk objek)
    Inisiasi objek menjadi objek yang valid.

    Parameter:
        - [xorlist_t] collection: objek yang akan dibentuk dan diinisiasi.
    Return: 
        - [int] status konstruksi (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_init(xorlist_t * collection)
{
    collection->length = 0;
    collection->head   = NULL;
    return 1;
}

/*
    Penambahan (prepend)
    Menambahkan elemen baru di awal list (mengubah head).

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan ditambahkan ke dalam collection.
    Return:
        - [int] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_prepend(xorlist_t * collection, T value)
{
    /* 
    operasi prepend() atau menambahkan node di urutan terdepan merupakan 
    operasi yang ekivalen dengan operasi insert() pada posisi 0
    */
    return xorlist_insert(collection, 0, value);
}

/*
    Penambahan (append)
    Menambahkan elemen baru di akhir list.

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan ditambahkan ke dalam collection.
    Return:
        - [int] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_append(xorlist_t * collection, T value)
{
    /* 
    Operasi append() atau menambahkan node di urutan terakhir merupakan
    operasi yang ekivalen dengan operasi insert() pada posisi Length
    */
    return xorlist_insert(collection, collection->length, value);
}
/*
    Penyisipan (insert)
    Menambahkan elemen baru di tengah list.

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
        - [uint32_t] index: lokasi index dimana nilai akan disisipkan.
        - [T] value: nilai yang akan ditambahkan ke dalam collection.
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_insert(xorlist_t * collection, uint32_t index, T value)
{
    node_t   *prevnode, *iternode, *save, *node;
    uint32_t iter = index;

    /* buat node baru. Jika gagal, maka kondisi list tak berubah */
    node = newnode(value);
    if (node == NULL)
        return 0;

    /*
    Jika senarai kosong, jadikan node ini sebagai "head".
    */
    if (collection->length == 0)
        collection->head = node;
    
    /*
    Jika tidak, iterasi senarai dan cari posisi tepat untuk meletakkan node.
    */
    else
    {
        /* cari node pada posisi index */
        iternode = xorlist_find(collection, index, &prevnode);

        /* Jika index menunjukkan posisi akhir */
        if (index >= collection->length)
            node_link(iternode, node);
        else 
        {
             /* tautkan "prevnode" sebagai node pendahulu dari node saat ini */
            if (prevnode)
            {
                /* pecahkan tautan antara "prevnode" dan "iternode" */
                node_link(prevnode, iternode);

                /* tautkan "prevnode" sebagai node pendahulu */
                node_link(prevnode, node);
            }
            /* tautkan "iternode" sebagai node penerus */
            node_link(node, iternode);
        }

        /* jika index adalah 0, maka jadikan node sebagai head */
        if (index == 0)
            collection->head = node;        
    } 

    collection->length ++;
    return 1;
}

/*
    Penghapusan (delete)
    Hapus sebuah node di awal list

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_delete_front(xorlist_t * collection)
{
    /* 
    operasi penghapusan node di urutan terdepan merupakan 
    operasi yang ekivalen dengan operasi penghapusan pada posisi 0
    */
    return xorlist_delete_at(collection, 0);
}

/*
    Penghapusan (delete)
    Hapus sebuah node di akhir list

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_delete_rear(xorlist_t * collection)
{
    /* 
    operasi penghapusan node di urutan terakhir merupakan 
    operasi yang ekivalen dengan operasi penghapusan pada posisi "Length - 1"
    */
    return xorlist_delete_at(collection, collection->length - 1);
}

/*
    Penghapusan (delete)
    Hapus sebuah node yang ada di index tertentu

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
        - [uint32_t] index: posisi node yang akan dihapus
    Return:
        - [int32_t] status penghapusan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_delete_at(xorlist_t * collection, uint32_t index)
{
    node_t   *prevnode, *iternode, *save, *nextnode, *node;
    uint32_t  iter = index;

    /* Jika list kosong atau index melebihi panjang list, maka kondisi list tak berubah */
    if (collection->length == 0 || index >= collection->length)
        return 0;

    /* Jika hanya ada satu node di senarai, segera hapus */
    else if (collection->length == 1)
    {
        iternode = collection->head;
        collection->head = NULL;
    }
    
    /* Jika terdapat lebih dari satu node, lakukan pencarian terhadap node yang tepat */
    else    
    {
        /* cari node pada posisi index */
        iternode = xorlist_find(collection, index, &prevnode);

        /* alamat dari node penerus iternode */
        nextnode = node_xor(prevnode, iternode->address, NULL); 

        /* pecahkan tautan antara "prevnode" dan "iternode" */
        if (prevnode)
            node_link(prevnode, iternode);
        
        /* pecahkan tautan antara "prevnode" dan "iternode" */
        if (nextnode)
            node_link(iternode, nextnode);
        
        /* tautkan antara "prevnode" dan "nextnode" */
        if (prevnode && nextnode)
            node_link(prevnode, nextnode);
        
        /* jika penghapusan terjadi di head, maka ubah head agar menunjuk node berikutnya */
        if (index == 0)
            collection->head = nextnode;
    }
    
    /* dealokasi node */
    free(iternode);
    collection->length --;
    return 1;
}

/*
    Penghapusan (delete)
    Menghapus sebanyak `count` kemunculan nilai `value` di list.

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
        - [T] value: elemen yang akan dihapus dari collection.
        - [uint32_t] count: banyaknya salinan node yang akan dihapus
    Return:
        - [int] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_delete(xorlist_t * collection, T value, uint32_t count)
{
    node_t   *prevnode, *iternode, *save, *nextnode;
    uint32_t length;

    /* jika list kosong maka kondisi list tidak berubah */
    if (collection->length == 0)
        return 0;

    /* 
    jika count bernilai 0, hapus semua kemunculan nilai.
    Kita bisa anggap semua node adalah sama sehingga kemungkinan menghapus
    semua nilai adalah sebanyak panjang dari list tersebut 
    */ 
    if (count == 0)
        count  = collection->length;
    
    prevnode   = NULL;
    length     = collection->length;
    iternode   = collection->head;

    /* iterasi list selama masih ada node dan counter masih ada */
    while (count && iternode)
    {
        /* dapatkan node penerus dari "iternode" */
        nextnode = node_xor(prevnode, iternode->address, NULL);

        /* jika node memiliki nilai yang dicari ... */
        if (iternode->value == value)
        {            
            /* pecahkan tautan antara "prevnode" dan "iternode" */
            if (prevnode)
                node_link(prevnode, iternode);
            /* bila node yang dihapus merupakan head, maka pindahkan head ke posisi berikutnya */
            else
                collection->head = nextnode;
            
            /* pecahkan tautan antara "prevnode" dan "iternode" */
            if (nextnode)
                node_link(iternode, nextnode);
            
            /* tautkan antara "prevnode" dan "nextnode" */
            if (prevnode && nextnode)
                node_link(prevnode, nextnode);
            
            /* hapus iternode */
            free(iternode);
            
            /* kurangi counter dan jumlah node */
            count --;
            length --;
        }
        else 
            prevnode = iternode;

        /* pindahkan pointer "iternode" menunjuk ke node berikutnya */
        iternode = nextnode;
    }

    collection->length = length;
    return 1;
}

/*
    Perubahan (update)

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
        - [T] value: nilai baru yang akan diisikan.
        - [uint32_t] index: index dari elemen yang akan dimodifikasi
    Return:
        - [int] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_update(xorlist_t * collection, uint32_t index, T value)
{
    node_t *iternode;

    /* Jika list kosong, maka kondisi list tak berubah */
    if (collection->length == 0)
        return 0;
    else 
    {
        /* cari node pada posisi index */
        iternode = xorlist_find(collection, index, NULL);

        /* ubah nilainya */
        iternode->value = value;
    }
    return 1;
}

/*
    Penggabungan (merge)

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi,
                list yang akan menerima isi dari source.
        - [xorlist_t] source: objek yang telah dikonstruksi, 
                list yang akan ditambahkan ke collection.
    Return:
        - [int] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_merge(xorlist_t * collection, xorlist_t * source)
{
    node_t *iternode;

    /* Jika "source" merupakan senarai kosong, maka tidak ada yang bisa dilakukan */
    if (source->head == NULL)
        return 0;

    /* jika senarai "collection" kosong maka ... */
    if (collection->length == 0)
        /* cukup pindahkan referensi head di source ke collection */
        collection->head = source->head;

    /* jika tidak maka ... */
    else 
    {
        /* Cari node terakhir */
        iternode = xorlist_find(collection, collection->length - 1, NULL);

        /* tautkan antara "tail" dari collection dan "head" dari source */
        node_link(iternode, source->head);
    }
    
    /* kosongkan source */
    collection->length += source->length;
    source->length = 0;
    source->head = NULL;
    return 1;
}

/*
    Pembersihan (clear)
    Mengosongkan (menghapus) seluruh node dari list.

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] status penambahan (0 = gagal, 1 = berhasil)
*/
int32_t xorlist_clear(xorlist_t * collection)
{
    node_t *iternode, *prevnode, *nextnode;

    if (collection->length)
    {
        prevnode = NULL;

        /* Iterasi seluruh list */
        iternode = collection->head;
        while (iternode)
        {
            nextnode = node_xor(prevnode, iternode->address, NULL);
            prevnode = iternode;

            free(iternode);
            iternode = nextnode;
        }
        collection->length = 0;
    }

    collection->head = NULL;
    return 1;
}

/*
    Mendapatkan banyaknya node yang ada di dalam list.

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi
    Return:
        - [int32_t] jumlah node dalam list
*/
int32_t xorlist_length(xorlist_t * collection)
{
    return collection->length;
}

/*
    Salin (clone)
    Membuat sebuah list baru dengan salinan seluruh node yang ada di list.

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi dan akan menerima
                     salinan node dari source.
        - [xorlist_t] source: objek yang telah dikonstruksi dan akan disalin ke 
                     collection
    Return:
        - [xorlist_t] list baru
*/
int32_t xorlist_clone(xorlist_t * collection, xorlist_t * source)
{
    node_t   *iterdst = NULL, *itersrc = NULL, *node;
    node_t   *prevnode, *save;
    uint32_t length = 0;

    /*
    Apabila objek telah menyimpan beberapa node, maka list
    harus dibersihkan terlebih dahulu.
    */
    xorlist_clear(collection);

    /* iterasi seluruh node di dalam list */
    itersrc = source->head;
    if (itersrc)
    {
        prevnode = NULL;

        /* alokasi node sebagai calon head */
        node = newnode(itersrc->value);
        /* jika alokasi berhasil maka ... */
        if (node)
        {
            /* jadikan node tersebut sebagai head */
            collection->head = node;
            length ++;

            /* pindahkan itersrc ke node berikutnya */
            save     = itersrc;
            itersrc  = node_xor(prevnode, itersrc->address, NULL);
            prevnode = save;

            /* gunakan sebagai pivot dalam penambahan node */
            iterdst = node;

            /* Lakukan penyalinan dengan iterasi kembali ke seluruh node. */
            while (itersrc)
            {
                node = newnode(itersrc->value);
                if (node)
                {
                    /* tautkan antara "iterdst" dan node */
                    node_link(iterdst, node);

                    iterdst = node;
                    length ++;
                }
                
                /* maju ke node berikutnya di "source" */
                save     = itersrc;
                itersrc  = node_xor(prevnode, itersrc->address, NULL);
                prevnode = save;
            }
        }
    }

    collection->length = length;
    return 1;
}

/*
    Penelusuran (traverse)

    Parameter:
        - [xorlist_t] collection: objek yang telah dikonstruksi.
        - [callback_t] callback: pointer ke fungsi yang akan dipanggil terhadap
                    setiap nilai dalam collection.
        - [T*] acc: accumulator, nilai akhir hasil agregasi dari callback (jika diperlukan)
    Return:
        - None
*/
void xorlist_traverse(xorlist_t * collection, callback_t callback, T * acc)
{
    node_t *iternode, *prevnode, *save;

    /* Jika list kosong atau callback tak terdefinisi, maka iterasi tidak dilakukan */
    if (collection->length == 0 || callback == NULL)
        return;

    prevnode = NULL;
    iternode = collection->head;

    /* jika tidak, iterasi list */
    while (iternode)
    {
        /* jalankan callback di setiap node */
        (*callback)(&iternode->value, acc);

        /* maju ke node berikutnya */
        save = iternode;
        iternode  = node_xor(prevnode, iternode->address, NULL);
        prevnode = save;
    }
}