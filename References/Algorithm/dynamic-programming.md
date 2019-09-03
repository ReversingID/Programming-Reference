# Programming Reference

Dynamic Programming.

## Definisi

Menyelesaikan masalah dengan memecah masalah kompleks menjadi beberapa subproblem dan menyimpan hasil dari subproblem untuk menghindari perhitungan ulang pemanggilan yang sama.

## Struktur

Terdapat dua pendekatan Dynamic Programming:

* `memoization` (top-down)
* `tabulation` (bottom-up)

Keduanya menyimpan solusi dari subproblem.

## Penggunaan

Strategi ini digunakan apabila:

* masalah memiliki `overlapping subproblem`: tumpang tindih, subproblem yang lebih kecil dievaluasi berkali-kali ketika mengevaluasi problem yang lebih besar.
* masalah memiliki `optimal substructure`: solusi optimal untuk keseluruhan masalah mengandung solusi optimal untuk subproblem.

## Catatan

* [Divide and Conquer](divide-and-conquer.md) serta Dynamic Programming membagi problem menjadi subproblem dan menyelesaikannya.

## Karakteristik

* umumnya memecahkan masalah optimisasi.
* pendekatan memoization umumnya bersifat rekursif dengan lookup table.
* pendekatan tabulation bersifat akumulatif dengan implementasi sebagai iterasi.