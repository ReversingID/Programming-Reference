# Programming Reference

Divide and Conquer.

## Definisi

Menyelesaikan masalah dengan membagi masalah menjadi bagian kecil.

## Struktur

Terdiri dari tiga langkah:

* divide: memecah permasalahan menjadi beberapa subproblem yang memiliki kemiripan dengan masalah semula namun berukuran lebih kecil.
* conquer: menyelesaikan subproblem secara independen (rekursif / iteratif).
* combine: menggabungkan solusi tiap subproblem sehingga terbentuk solusi masalah semula.

## Penggunaan

Strategi ini digunakan apabila:

* subproblem tidak dievaluasi berkali-kali. Jika perlu evaluasi berkali-kali, gunakan Dynamic Programming.

## Catatan

* Divide and Conquer serta [Dynamic Programming](dynamic-programming.md) membagi problem menjadi subproblem dan menyelesaikannya.
* apabila subproblem yang dihasilkan hanya satu, maka disebut Decrease and Conquer.

## Karakteristik

* umumnya problem dibagi menjadi dua bagian relatif sama besar.
* terdapat batas ambang (treshold) ukuran masukan sehingga subproblem tidak perlu dipecah lagi.