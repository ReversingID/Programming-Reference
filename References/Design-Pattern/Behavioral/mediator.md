# Programming Reference

Mediator (Behavioral pattern).

Mendefinisikan komunikasi yang disederhanakan antar class.

## Tujuan

* mendefinisikan objek yang mengenkapsulasi mekanisme interaksi antar objek.
* mendesain perantara untuk decouple banyak peers.
* menyertakan model hubungan many-to-many antara peers.

## Struktur

Class yang terlibat:

* Colleague: entitas yang dapat berperan sebagai Producer (menghasilkan data) maupun Consumer (mengambil data).
* ConcreteColleague: implementasi Colleague
* Mediator: memfasilitasi hubungan antar Colleague.
* ConcreteMediator: implementasi Mediator

## Penggunaan

Desain ini digunakan ketika:

* sekelompok objek berkomunikasi dengan cara rumit namun terdefinisi dengna baik.
* susah untuk penggunaan kembali objek karena ia merujuk dan berkomunikasi dengan banyak objek lain.
* perilaku yang disebarkan ke beberapa class harus customizable tanpa melakukan banyak subclass.

## Catatan

* [Chain of Responsibility](chain-of-responsibility.md), [Command](command.md), Mediator, dan [Observer](observer.md) menangani masalah decouple sender dan receiver dengan trade-off berbeda. 

    - Chain of Responsibility melewatkan request ke receiver yang disusun berantai.
    - Command umumnya merinci hubungan sender-receiver dengan subclass.
    - Mediator memiliki reference ke setiap sender dan receiver secara tak langsung.
    - Observer mendefinisikan interface yang sangat decouple sehingga membuat beberapa receiver dapat dikonfigurasi saat runtime.

* Mediator dan Observer saling bersaing. Perbedaan antara keduanya adalah Observer menyebar (distribusi) komunikasi dengan mengenalkan konsep publisher dan subscriber sementara Mediator mengenkapsulasi komunikasi antar objek. Observer lebih mudah untuk di-reuse.
* Mediator dapat menggunakan pola Observer untuk secara dinamis mendaftarkan Colleague dan berkomunikasi dengan mereka.
* Mediator mirip dengan [Facade](../Structural/facade.md) dalam hal ia mengabstraksi fungsionalitas dari class yang telah ada. Mediator melakukan sentralisasi komunikasi antara objek Colleague (dengan multidirectional protocol). Sementara Facade mendefinisikan interface sederhana ke subsystem sehingga tidak menambah fungsionalitas baru.

## Karakteristik

* menyimpan daftar referensi ke berbagai objek sejenis.
* umumnya masing-masing objek dapat secara aktif mengirim pesan melalui Mediator.