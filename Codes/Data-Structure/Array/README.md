# Programming Reference

Array implementation and reversing

## Overview

Array adalah struktur data sederhana untuk menyimpan elemen data yang homogen di lokasi yang kontigu. Ukuran array harus didefinisikan terlebih dahulu sebelum penyimpanan data dapat dilakukan.

* Accessing Time: O(1)
* Search Time: O(n) untuk pencarian sekuensial, O(log n) untuk binary search jika array dalam keadaan terurut.
* Insertion Time: O(n) 
* Deletion Time: O(n)

## Reversing Notes

#### Code

Sebagai kumpulan elemen kontigu, akses elemen Array dilakukan berdasarkan dua informasi: `base address` dan `offset`. Base address adalah alamat dimana penyimpanan Array dimulai. Sementara offset adalah jarak dari base address dimana elemen dapat ditemukan.

Array dapat dideklarasikan secara global maupun lokal (dalam fungsi). Ketika dideklarasikan secara global, Array akan dialokasikan di section data yang dapat diakses (baca/tulis). Base address akan bernilai sebuah alamat statis. Sementara ketika dideklarasikan secara lokal, Array akan dialokasikan di Stack. Base address akan relatif terhadap `Stack Pointer` dan hanya berlaku pada scope fungsi saja.

Nilai offset bergantung kepada index dan ukuran elemen. Index adalah urutan sebuah elemen di dalam deretan Array. Elemen pertama diidentifikasi dengan index 0. Karena Array adalah struktur data yang homogen, maka jarak antar elemen proporsional dengan ukuran elemen itu sendiri.

Sehingga untuk mendapatkan alamat dari suatu elemen, maka perhitungan berikut dapat digunakan.

```
address = base + index * size
```