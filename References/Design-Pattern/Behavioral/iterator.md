# Programming Reference

Iterator (Behavioral pattern).

Akses elemen sebuah koleksi secara sekuensial / berurutan tanpa mengekspos representasi di belakang.

## Tujuan

* memberikan akses ke element dari kumpulan objek tanpa mengekspos representasi.
* polymorphic traversal.

## Struktur

Class yang terlibat:

* Collection/Aggregate: kumpulan objek dengan mekanisme penyimpanan tertentu.
* Iterator: interface untuk objek yang dapat melakukan akses elemen secara sekuensial tanpa mengekspos mekanisme penyimpanan Collection.
* ConcreteCollection: 
* ConcreteIterator: 


## Penggunaan

Desain ini digunakan ketika:

## Catatan

* Abstract Syntax Tree (AST) pada [Interpreter](interpreter.md) merupakan [Composite](../Structural/composite.md) sehingga Iterator dan [Visitor](visitor.md) dapat berlaku.
* Iterator dapat menjelajahi Composite. Visitor dapat menerapkan operasi ke Composite.
* [Memento](memento.md) umumnya digunakan bersamaan dengan Iterator. Iterator menggunakan Memento untuk menangkap state dari iterasi dan disimpan secara internal.

## Karakteristik

* traversal dilakukan searah, dimulai dari elemen pertama (first) dan dilanjutkan dengan elemen berikutnya (next).
