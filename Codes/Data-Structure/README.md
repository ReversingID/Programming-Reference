# Data Structure and Algorithm Reference

## Istilah Dasar

* **Algoritma** adalah urutan langkah-langkah terstruktur untuk memecahkan suatu masalah.
* **Struktur data** adalah mekanisme organisir kumpulan data ke dalam struktur tertentu sehingga pengaksesan dapat dilakukan secara efisien.
* **Data** (dalam ilmu komputer) adalah informasi yang direpresentasikan dalam bilangan maupun teks sebagai dasar dalam proses pengolahan.
* **Abstract Data Type** (ADT) adalah sebuah model yang merepresentasikan data serta operasi yang didefinisikan terhadapnya.
* **Container** adalah sebuah ADT yang berupa kumpulan objek-objek lain.


## Abstract Data Type

**Abstract Data Type** (ADT) adalah definisi TYPE dan sekumpulan PRIMITIF (operasi dasar) terhadap TYPE tersebut. Selain itu, dalam sebuah ADT yang lengkap disertakan pula definisi invarian dari TYPE dan aksioma yang berlaku.

Definisi type dari sebuah ADT dapat mengandung sebuah definisi ADT lain.

Type diterjemahkan menjadi type terdefinisi dalam bahasa yang bersangkutan, misal menjadi _record_ dalam bahasa Ada/Pascal atau _struct_ dalam bahasa C.

Primitif, dalam konteks prosedural, diterjemahkan menjadi fungsi atau prosedur. Primitif dikelompokkan menjadi:

* Konstruktor / kreator, pembentuk nilai type. Semua objek (variabel) bertipe tersebut harus dibentuk menggunakan konstruktor. Biasanya namanya diawali _Make_ / _Create_.
* Selektor, untuk mengakses komponen _type_. Biasanya diawali dengan _Get_.
* Modifier, prosedur untuk mengubah nilai komponen. Biasanya namanya diawali _Set_.
* Validator komponen type, yang dipakai untuk menguji apakah type dapat dibentuk sesuai dengan batasan.
* Destruktor / Dealokator, yaitu untuk "menghancurkan" nilai objek (sekaligus memori penyimpanannya).
* Operator, untuk mendefinisikan suatu hubungan dengan variabel lain dengan tipe sama (relasional, aritmetik).
* Konversi dari type tersebut ke type dasar dan sebaliknya.

## Koleksi Objek

Terkadang terdapat kebutuhan untuk mengelola sekumpulan (koleksi) objek. Setiap elemen dalam suatu koleksi objek harus bertipe sama (mungkin tipe dasar atau suatu ADT yang pernah didefinisikan).

Elemen sebuah koleksi diorganisir sesuai dengan aturan. Setiap elemen dapat memiliki keterurutan. Sebuah Koleksi yang setiap elemen dapat diakses berdasarkan urutan disebut sebagai _Struktur Data Linier_. Sebaliknya, apabila tidak terdapat keterurutan maka ia disebut sebagai _Struktur Data Nonlinier_.

## Definisi Fungsional

Sebuah struktur data / koleksi merupakan sebuah ADT. Dengan demikian terdapat operasi-opeasi yang dilakukan terhadap tipe. Secara umum, operasi fungsional terdiri dari:

* Penciptaan / pembuatan (konstruktor).
* Penambahan (add, insert).
* penghapusan (delete).
* Perubahan (update).
* Penggabungan.
* Operasi lain-lain.
