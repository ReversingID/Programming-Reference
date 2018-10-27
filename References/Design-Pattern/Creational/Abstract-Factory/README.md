# Programming Reference

Abstract Factory (Creational pattern)

## Tujuan

* Menawarkan interface untuk menciptakan sekelompok objek yang berhubungan atau memiliki keterkaitan dependensi tanpa memberikan detail kelas konkret.
* Sebuah hirarki yang mengenkapsulasi berbagai kemungkinan produk dan konstruksi sekelompok produk.

## Struktur 

Abstract Factory mendefinisikan sebuah Factory Method untuk setiap produk. Setiap Factory Method mengenkapsulasi pembentukan dan konstruksi objek yang konkret dan spesifik.

Class yang terlibat:

* AbstractProduct: kelas dasar yang mendefinisikan sekelompok produk bertipe sejenis.
* Product: produk yang termasuk dalam kategori jenis yang sama.
* Factory: kelas yang menciptakan bertanggung jawab menciptakan objek-objek.

## Penggunaan

Desain ini digunakan ketika:

* Penciptaan objek harus independen terhadap sistem yang menggunakan mereka.
* Pustaka digunakan / dipublikasi tanpa memberikan detail implementasi.
* Kelas konkret harus decouple dari client.