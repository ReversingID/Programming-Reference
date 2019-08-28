# Programming Reference

Command (Behavioral pattern).

Mengenkapsulasi request berupa command sebagai objek yang berisi segala informasi terkait request. 

## Tujuan

* enkapsulasi request sebagai objek.
* mendefinisikan object-oriented callback.

## Struktur

Class yang terlibat:

* Invoker/Sender: bertanggung jawab untuk menginisiasi request.
* Command: mendeklarasikan method untuk eksekusi command.
* ConcreteCommand: implementasikan beragam request.
* Receiver: implementasi business logic.

## Penggunaan

Desain ini digunakan ketika:

* ingin parameterize objek dengan action yang akan dilakukan.
* ingin specify, queue, dan execute request di waktu berbeda.
* mendukung mekanisme undo.
* mendukung logging perubahan sehingga operasi yang sama dapat diterapkan saat system crash.

## Catatan

* [Chain of Responsibility](chain-of-responsibility.md), Command, [Mediator](mediator.md), dan [Observer](observer.md) menangani masalah decouple sender dan receiver dengan trade-off berbeda. 

    - Chain of Responsibility melewatkan request ke receiver yang disusun berantai.
    - Command umumnya merinci hubungan sender-receiver dengan subclass.
    - Mediator memiliki reference ke setiap sender dan receiver secara tak langsung.
    - Observer mendefinisikan interface yang sangat decouple sehingga membuat beberapa receiver dapat dikonfigurasi saat runtime.
    
* Chain of Responsibility dapat menggunakan Command untuk merepresentasikan request sebagai objek.
* Command dapat menggunakan [Memento](memento.md) untuk memelihara state yang dibutuhkan untuk operasi undo.
* MacroCommand dapat diimplementasikan dengan [Composite](../../Structural/composite.md).
* Command yang harus disalin sebelum dimasukkan ke dalam history dapat diimplementasikan sebagai [Prototype](../../Structural/prototype.md).

## Karakteristik

* command akan meneruskan request dengan memanggil receiver yang sesuai.
* setiap command hanya memiliki satu receiver sebagai handler.