# Programming Reference

Event Sourcing

## Definisi

Menyimpan event yang terjadi ke model, alih-alih menyimpan kondisi terkini model ke database. Ketika dibutuhkan informasi tentang model, maka seluruh event yang tersimpan (terkait model tersebut) akan diambil dan diterapkan kembali ke objek baru. Hal ini disebut sebagai `rehydrating`.

## Struktur

## Penggunaan

Arsitektur ini ideal digunakan untuk:

* sistem yang perlu memublikasi event ke sistem eksternal.
* aaplikasi yang kan dibangun dengan CQRS.
* aplikasi yang memiliki domain kompleks.
* memerlukan audit-log terhadap perubahan data.

## Karakteristik

Keuntungan:

* dapat menyediakan audit-log dimana setiap event merepresentasikan manipulasi data pada suatu saat.

Kekurangan:

* membutuhkan penelusuran terhadap keseluruhan data ketika akan terjadi perubahan di database.
* perlu memiliki penanganan data tertentu jika terjadi perubahan struktur di database.