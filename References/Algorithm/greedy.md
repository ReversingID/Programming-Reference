# Programming Reference

Greedy

Mengambil sebanyak mungkin pilihan yang ada.

## Definisi

Membangun solusi sedikit demi sedikit dengan tiap bagian solusi dipilih berdasarkan benefit atau dapat memberikan keuntungan paling besar. Algoritma Greedy mengambil pilihan yang nampak memberikan keuntungan terbaik pada saat itu.

Pada algoritma Greedy, solusi global (global optimum) diharapkan dicapai dengan mengambil semua pilihan optimum lokal (local optimum).

Keputusan yang diambil pada suatu langkah tidak akan diubah pada langkah selanjutnya.

## Struktur

Komponen algoritma:

- Himpunan kandidat (C)

    Berisi elemen pembentuk solusi. Misal: himpunan job yang akan dikerjakan, simpul di dalam graf, dsb. Pada setiap langkah, satu buah kandidiat diambil dari  himpunannya.

- Himpunan solusi (S)

    Berisi kandidat-kandidat yang terpilih sebagai solusi persoalan.

- Fungsi seleksi (selection)

    Fungsi yang memilih kandidat paling memungkinkan mencapai solusi optimal. Kandidat yang telah terpilih di satu langkah tidak akan pernah dipertimbangkan lagi pada langkah berikutnya. Biasanya kandidat `x` dipetakan dengan sebuah nilai numerik dan fungsi seleksi akan memilih `x` dengan nilai terbesar (atau terkecil, tergantung situasi).

- Fungsi kelayakan (feasible)

    Fungsi yang memeriksa apakah suatu kandidat yang telah dipilh dapat memberikan solusi yang layak. Dalam hal ini, kandidat serta himpunan solusi yang sudah terbentuk tidak melanggar Constraint yang ada. Kandidat yang layak dimasukkan ke dalam himpunan solusi, sedangkan kandidat yang tidak layak akan dibuang dan tidak pernah dipertimbangkan lagi.

- Fungsi obyektif

    Fungsi yang memaksimumkan (atau meminimumkan) nilai solusi.

Langkah umum:

- inisialisasi `S` sebagai himpunan kosong.
- gunakan fungsi `selection()` untuk memilih kandidat dari `c`.
- hapus `c` dari himpunan kandidat.
- gunakan fungsi `feasible()` untuk periksa apakah kandidat yang dipilih serta himpunan solusi memberikan solusi yang layak / feasible. Jika tidak, buang kandidat tersebut.
- gunakan fungsi `objective()` untuk periksa apakah solusi sudah lengkap. Jika ya, berhenti. Jika tidak, ulangi dari langkah 2.

## Penggunaan

Strategi ini digunakan apabila:

* masalah memenuhi `greedy choice property`: solusi optimal secara global dapat diraih dengan memilih pilihan optimal di setiap langkah.
* masalah memiliki `optimal substructure`: solusi optimal untuk keseluruhan masalah mengandung solusi optimal untuk subproblem.

## Catatan

## Karakteristik

* tidak ada pelacakan terhadap opsi yang telah dipilih sehingga tidak mungkin melakukan perbandingan terhadap kombinasi pilihan yang ada.