# Programming Reference

Breadth-First Search (BFS)

## Definisi

Pencarian melebar. Mengunjungi simpul-simpul pada graf dengan cara mengunjungi semua simpul tetangga / sibling terlebih sebelum mengunjungi simpul anak.

## Struktur

Komponen algoritma:

- Node Queue (Q)

    Sebuah antrean untuk menyimpan simpul yang telah dikunjungi. Simpul yang telah dikunjungi suatu saat diperlukan sebagai acuan untuk mengunjungi simpul-simpul yang bertetangga dengannya. Tiap simpul yang telah dikunjungi masuk ke dalam antrean hanya sekali.

- Visited Array (V)

    Sebuah larik beertipe boolean untuk menyimpan informasi simpul-simpul yang telah dikunjungi sehingga dapat ditelusuri bahwa tidak ada simpul yang dikunjungi lebih dari sekali.

Langkah umum:

- inisialisasi `Q` sebagai antrean kosong.
- masukkan simpul mula (start node) ke dalam antrean `Q`.
- ambil sebuah node `n` dari antrean `Q`
- untuk setiap node yang terhubung dengan `n`, periksa apakah node telah dikunjungi. Jika belum, masukkan node tersebut ke antrean `Q`.
- proses node `n` dan tandai bahwa `n` telah dikunjungi.
- jika antrean belum kosong, ulangi dari langkahstep 3.

## Penggunaan

Strategi ini digunakan apabila:

- 

## Catatan

## Karakteristik

- semua simpul pada aras (level) `d` akan dibangkitkan terlebih dahulu sebelum menelusuri simpul pada aras `d + 1`.