# Programming Reference

Visitor (Behavioral pattern).

Mendefinisikan operasi baru terhadap class tanpa melakukan perubahan.

## Tujuan

* Memisahkan algoritma dari objek yang dioperasikan.
* Merepresentasikan operasi yang akan dilakukan ke elemen struktur data.
* Mendefinisikan operasi baru tanpa mengubah class yang dioperasikan.
* Double dispatch.

## Struktur

Class yang terlibat:

* Visitor: interface yang mendeklarasikan sekelompok method dan menerima elemen konkret.
* ConcreteVisitor: implementasi beberapa versi yang disesuaikan dengan kasus pada concrete element.
* Element: interface yang mendeklarasikan method untuk menerima visitor.
* ConcreteElement: implementasi penerima visitor dan mengarahkan call ke method di visitor.

## Penggunaan

Desain ini digunakan ketika:

* struktur objek memiliki banyak tipe objek dengan interfaceberbeda dan perlu dilakukan operasi terhadap objek tersebut tanpa bergantung kepada concrete class.
* banyak operasi berbeda dan tak berkaitan yang perlu dilakukan terhadap objek di struktur dan perlu untuk menghindari "mencemari" class dengan operasi tersebut.
* class jarang berubah namun operasi baru terhadap struktur akan sering mengalami perubahan.

## Catatan

* Abstract Syntax Tree (AST) pada [Interpreter](interpreter.md) merupakan [Composite](../Structural/composite.md) sehingga [Iterator](iterator.md) dan Visitor dapat berlaku.
* Iterator dapat menjelajahi Composite. Visitor dapat menerapkan operasi ke Composite.
* Visitor mirip [Command](command.md) namun lebih powerful karena dapat menginisiasi apapun yang sesuai dengan objek yang ditemui.

## Karakteristik

* terdapat method visit() sebagai callback yang akan dipanggil oleh tiap elemen.
* terdapat method accept() pada elemen (di setiap hirarki) yang akan memanggil visit() di visitor.
* method-overload pada fungsi visit() dengan parameter tiap tipe element.