# Programming Reference

Memento (Behavioral pattern).

Save dan restore state dari object tanpa mengekspos detail implementasi.

## Tujuan

* Menyimpan internal state sebuah objek secara eksternal tanpa menyalahi enkapsulasi.

## Struktur

Class yang terlibat:

* Originator: menghasilkan snapshot state dan mengembalikan dari state yang diinginkan.
* Memento: value object yang bertindak sebagai snapshot dari Originator. Umumnya merupakan objek immutable.
* Caretaker: menyimpan history dari memento dan dapat mengunjungi history untuk melakukan restorasi.

## Penggunaan

Desain ini digunakan ketika:

* snapshot keadaan objek harus disimpan (save) dan dapat dikembalikan (restore) suatu saat.
* direct interface untuk mendapatkan state berpotensi mengekspos detail implementasi dan merusak enkapsulasi objek.

## Catatan

* [Command](command.md) dan Memento bertindak sebagai magic-token yang dipertukarkan dan pada akhirnya akan dieksekusi. Pada Command, token merepresentasikan sebuah request; sementara pada Memento, token merepresentasikan internal state dari suatu objek pada saat tertentu.
* [Command](command.md) dapat menggunakan Memento untuk memelihara state yang dibutuhkan untuk operasi undo.
* Memento umumnya digunakan bersamaan dengan [Iterator](iterator.md). Iterator menggunakan Memento untuk menangkap state dari iterasi dan disimpan secara internal.

## Karakteristik

* state yang disimpan oleh Memento dapat berupa sebagian maupun keseluruhan informasi / field.