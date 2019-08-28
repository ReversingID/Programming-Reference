# Programming Reference

Builder (Creational pattern)

Mengonstruksi objek yang kompleks secara bertahap.

## Tujuan

* Memisahkan konstruksi sebuah objek yang kompleks dari representasinya sehingga proses konstruksi yang sama dapat menciptakan representasi yang berbeda.
* Mendekomposisi proses menjadi serangkaian aksi-aksi kecil.

## Struktur

Builder mendefinisikan satu atau lebih method yang mewakili fase pembentukan sebuah produk. Fase-fase ini kemudian akan di-invoke oleh sebuah Directory. Semua proses pembentukan akan ditangani oleh Director.

Class yang terlibat:

* Director: kelas yang melakukan pembangunan produk. Proses pembuatan produk yang terdiri dari fase-fase berbeda diabstraksi menjadi satu method yang seragam.
* Builder: kelas yang bertanggung jawab membentuk komponen-komponen dari produk.
* Produk: kelas yang diinstansiasi oleh Builder.

## Penggunaan

Desain ini digunakan ketika:

## Catatan

* Terkadang creational patterns bersifat komplementer: Builder dapat menggunakan satu atau lebih pattern lain untuk mengimplementasikan komponen yang akan dibangun.
* Builder berfokus kepada konstruksi objek yang kompleks secara langkah demi langkah. AbstractFactory menekankan sekelompok objek produk (bisa produk sederhana maupun kompleks). Builder mengembalikan produk pada langkah akhir, sementara AbstractFactory langsung memberikan product yang diminta.
* Builder seringkali membangun sebuah Composite.

## Karakteristik

- Pola Builder mengorganisir konstruksi objek menjadi beberapa langkah. 
- Pembuatan objek dilakukan dengan mengeksekusi beberapa method untuk melakukan konstumisasi terhadap objek yang akan dihasilkan di akhir.

## References

- [Refactoring.Guru](https://refactoring.guru/design-patterns/builder)
- [SourceMaking](https://sourcemaking.com/design_patterns/builder)