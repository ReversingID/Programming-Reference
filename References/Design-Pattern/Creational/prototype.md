# Programming Reference

Prototype (Creational pattern).

Membuat objek baru berdasarkan sebuah objek yang ada sebagai purwarupa (prototype) dan melakukan cloning terhadapnya.

## Tujuan

* Menetapkan jenis objek yang diciptakan menggunakan instance purwarupa (prototype). Penciptaan objek dilakukan dengan menyalin prototype tersebut.
* Menjadikan sebuah instance sebagai basis untuk instance berikutnya.

## Struktur

Pola prototype mendelegasikan penciptaan objek kepada objek tersebut melalui mekanisme clone. Pola ini mendeklarasikan interface untuk semua objek agar mendukung fungsi clone.

Class yang terlibat:

* Prototype: interface yang mendefinisikan fungsi clone()
* ConcretePrototype: class yang mengimplementasikan clone() sebagai cara untuk menyalin data dari objek original ke objek baru.

Terdapat varian dimana didefinisikan sebuah Registry.

* Registry: menyimpan beberapa objek purwarupa yang telah siap disalin.

## Penggunaan

Desain ini digunakan ketika:

* inisialisasi objek membutuhkan biaya tinggi dan menciptakan objek dari awal sebisa mungkin dihindari.

## Catatan

* Factory Method menciptakan instance dengan inheritance, prototype dengan delegation.
* Abstract Factory umumnya diimplementasikan dengan Factory method, namun bisa juga dengan Prototype.

## Karakteristik

* Terdapat method clone() pada product.
* Registry mengelola cache dari objek purwarupa. Registry dapat dienkapsulasi sebagai Factory baru.
