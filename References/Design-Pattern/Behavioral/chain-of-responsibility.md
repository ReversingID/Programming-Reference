# Programming Reference

Chain of Responsibility (Behavioral pattern).

Cara melewatkan request antara objek berantai. Ketika menerima request, setiap handler akan memutuskan untuk memproses request atau meneruskan ke handler lain.

## Tujuan

* menghindari coupling antara pengirim dan penerima request ketika terdapat lebih dari satu handler alternatif.
* memberikan kesempatan pada setiap handler untuk menangani request.
* membentuk single processing pipeline yang berisi banyak kemungkinan handler.

## Struktur

Class yang terlibat:

* Handler: 
* ConcreteHandler:

## Penggunaan

Desain ini digunakan ketika:

* lebih dari satu objek dapat menangani sebuah request dan handler harus ditentukan secara otomatis.
* perlu membuat request ke satu dari beberapa objek tanpa perlu menyebutkan penerima secara eksplisit.
* sekelompok objek dapat menangani request secara dinamis.

## Catatan

* Chain of Responsibility, [Command](command.md), [Mediator](mediator.md), dan [Observer](observer.md) menangani masalah decouple sender dan receiver dengan trade-off berbeda. 

    - Chain of Responsibility melewatkan request ke receiver yang disusun berantai.
    - Command umumnya merinci hubungan sender-receiver dengan subclass.
    - Mediator memiliki reference ke setiap sender dan receiver secara tak langsung.
    - Observer mendefinisikan interface yang sangat decouple sehingga membuat beberapa receiver dapat dikonfigurasi saat runtime.

* Chain of Responsibility dapat menggunakan Command untuk merepresentasikan request sebagai objek.
* Chain of Responsibility umumnya diterapkan bersama dengan [Composite](../Structural/composite.md).

## Karakteristik

* terdapat objek yang disusun secara berantai dengan pointer menuju objek berikutnya.
* terdapat sebuah fungsi umum yang digunakan untuk melakukan penanganan event.
* mungkin terdapat sebuah fungsi yang digunakan untuk melakukan pemeriksaan kondisi.