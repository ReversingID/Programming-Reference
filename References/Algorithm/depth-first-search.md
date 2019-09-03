# Programming Reference

Depth-First Search (DFS)

## Definisi

Pencarian mendalam. Mengunjungi simpul-simpul pada graf dengan cara mengunjungi seluruh path dari suatu node hingga akhir sebelum akhirnya mengunjungi node tetangga.

## Struktur

Komponen algoritma:

- Visited Array (`V`)

    Sebuah larik beertipe boolean untuk menyimpan informasi simpul-simpul yang telah dikunjungi sehingga dapat ditelusuri bahwa tidak ada simpul yang dikunjungi lebih dari sekali.

Langkah umum:

- proses node `n` dan tandai bahwa `n` telah dikunjungi.
- untuk setiap node yang terhubung dengan `n`, periksa apakah node telah dikunjungi. Jika belum, lakukan `DFS()` ke node tersebut.

## Penggunaan

Strategi ini digunakan apabila:

## Catatan

## Karakteristik