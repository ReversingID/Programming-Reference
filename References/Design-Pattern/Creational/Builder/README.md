# Programming Reference

Builder (Creational pattern)

## Tujuan

* Memisahkan konstruksi sebuah objek yang kompleks dari representasinya sehingga proses konstruksi yang sama dapat menciptakan representasi yang berbeda.
* Mendekomposisi proses menjadi serangkaian aksi-aksi kecil.

## Struktur

Builder mendefinisikan satu atau lebih method yang mewakili fase pembentukan sebuah produk. Fase-fase ini kemudian akan di-invoke oleh sebuah Directory. Semua proses pembentukan akan ditangani oleh Director.

Class yang terlibat:

* Director: kelas yang melakukan pembangunan produk. Proses pembuatan produk yang terdiri dari fase-fase berbeda diabstraksi menjadi satu method yang seragam.
* Builder: kelas yang bertanggung jawab membangun produk.
* Produk: kelas yang diinstansiasi oleh Builder.

## Catatan

* Terkadang creational patterns bersifat komplementer: Builder dapat menggunakan satu atau lebih pattern lain untuk mengimplementasikan komponen yang akan dibangun.
* Builder berfokus kepada konstruksi objek yang kompleks secara langkah demi langkah. AbstractFactory menekankan sekelompok objek produk (bisa produk sederhana maupun kompleks). Builder mengembalikan produk pada langkah akhir, sementara AbstractFactory langsung memberikan product yang diminta.
* Builder seringkali membangun sebuah Composite.