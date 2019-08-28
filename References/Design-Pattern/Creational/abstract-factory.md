# Programming Reference

Abstract Factory (Creational pattern)

## Tujuan

* menawarkan interface untuk menciptakan sekelompok objek yang berhubungan atau memiliki keterkaitan dependensi tanpa memberikan detail kelas konkret.
* sebuah hirarki yang mengenkapsulasi berbagai kemungkinan produk dan konstruksi sekelompok produk.

## Struktur 

Abstract Factory mendefinisikan sebuah Factory Method untuk setiap produk. Setiap Factory Method mengenkapsulasi pembentukan dan konstruksi objek yang konkret dan spesifik.

Class yang terlibat:

* AbstractProduct: kelas dasar yang mendefinisikan sekelompok produk bertipe sejenis.
* Product: produk yang termasuk dalam kategori jenis yang sama.
* AbstractFactory: interface untuk operasi yang menciptakan factory (untuk keluarga objek tertentu).
* Factory: kelas yang menciptakan bertanggung jawab menciptakan objek-objek.

## Penggunaan

Desain ini digunakan ketika:

* system harus bersikap independen terhadap bagaimana produk dapat tercipta, dikomposisi, dan direpresentasikan.
* system harus dapat dikonfigurasi untuk satu dari sekian keluarga / kelompok produk.
* sekelompok produk yang saling berkaitan didesain untuk dapat bekerja bersama.

## Catatan

## Karakteristik

* hasil akhir merupakan sebuah factory yang dapat membentuk beberapa produk dalam kelompok tertentu.