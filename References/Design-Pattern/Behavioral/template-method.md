# Programming Reference

Template Method (Behavioral pattern).

Menangguhkan langkah-langkah algoritma ke dalam subclass.

## Tujuan

* mendefinisikan kerangka algoritma di superclass namun menangguhkan langkah-langkah algoritma ke subclass tanpa mengganti struktur.

## Struktur

Class yang terlibat:

* AbstractClass: mendeklarasikan method sebagai langkah-langkah algoritma. 
* ConcreteClass: override semua langkah di template method.

## Penggunaan

Desain ini digunakan ketika:

* perilaku umum di kalangan subclass harus difaktorkan dan dilokalisasikan ke dalam class umum untuk menghindari duplikasi.
* mengendalikan ekstensi subclass.

## Catatan

* mengubah algoritma menjadi template-method perlu untuk menentukan langkah mana yang umum dan langkah mana yang spesifik terhadap suatu class.
* Template Method menggunakan inheritance untuk membedakan bagian-bagian algoritma. [Strategy](strategy.md) menggunakan delegasi untuk membuat variasi algoritma.
* Strategy memodifikasi logic dari objek secara individual. Template Method memodifikasi logic dari keseluruhan class.
* [Factory Method](../Creational/factory-method.md) adalah spesialisasi dari Template Method.

## Karakteristik

