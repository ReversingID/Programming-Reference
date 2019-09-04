# Programming Reference

Microkernel

## Definisi

Disebut pula dengan Plug-in.

Membagi aplikasi menjadi bagian inti dan sekelompok modul yang dapat dipasang dan dilepas tanpa mengganggu sistem secera keseluruhan. Microkernel menyediakan entrypoint dan flow aplikasi secara umum tanpa perlu mengetahui apa yang dilakukan oleh plugin.

## Struktur

Microkernel terdiri dari bagian inti dan plugin.

![Microkernel](_imgs_/mikrokernel.png)

## Penggunaan

Arsitektur ini ideal digunakan untuk:

* aplikasi yang mengambil data dari beragam sumber, mentransformasikan data tersebut, dan menuliskan data ke beberapa tujuan berbeda.
* aplikasi workflow.
* aplikasi penjadwalan task atau job.

## Karakteristik

Keuntungan

* menawarkan fleksibilitas tinggi serta kemudahan untuk perluasan aplikasi.
* microkernel dan plugin dapat dikembangkan secara terpisah.

Kekurangan

* susah untuk menentukan bagian mana yang termasuk ke dalam bagian microkernel dan tidak.
* API yang predefined (terdefinisi di awal) bukan merupakan hal yang cocok untuk plugin.