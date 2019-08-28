# Programming Reference

State (Behavioral pattern).

Suatu atribut yang dapat digunakan untuk mengubah perilaku objek.

## Tujuan

* Memberi kemampuan objek untuk mengubah perilaku ketika internal-state berubah.
* object-oriented state machine.

## Struktur

Class yang terlibat:

* Context: menyimpan reference ke salah satu objek state dan mendelegasikan semua tugas berkaitan dengan state. Berkomunikasi dengan state objek melalui interface state.
* State: mendeklarasikan method untuk melakukan tugas spesifik state.
* ConcreteState: 

## Penggunaan

Desain ini digunakan ketika:

* perilaku objek bergantung kepada state dan harus memberikan reaksi yang tepat sesuai dengan state saat ini.
* operasi memiliki conditional statement yang sangat besar dan bergantung kepada state objek.

## Catatan

* State umumnya [Singleton](../Creational/singleton.md)
* [Flyweight](../Structural/flyweight.md) menjelaskan kapan dan bagaimana objek State dapat dibagi.
* [Interpreter](interpreter.md) dapat menggunakan State untuk mendefinisikan parsing-context.
* [Strategy](strategy.md) memiliki 2 implementasi berbeda salah satunya mirip dengan State. Perbedaannya adalah Strategy bersifat statis (bind-once).

## Karakteristik

* context menyimpan reference ke state terkini.