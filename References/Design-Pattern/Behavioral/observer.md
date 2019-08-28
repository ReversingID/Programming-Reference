# Programming Reference

Observer (Behavioral pattern).

Cara untuk memberikan notifikasi setiap ada perubahan kepada beberapa class.

## Tujuan

* Mendefinisikan dependensi one-to-many sehingga apabila terjadi perubahan pada suatu objek maka semua objek yang dependen terhadapnya akan menerima notifikasi update secara otomatis. 

## Struktur

Class yang terlibat:

- Publisher/Subject: class yang bertindak sebagai generator suatu informasi atau event.
- Subscriber/Observer: class yang menunggu adanya event melalui sebuah callback.

## Penggunaan

Desain ini digunakan ketika:

* terdapat objek yang bergantung kepada objek lain.
* perubahan di satu objek membutuhkan perubahan di objek lain secara segera tapi tidak tau berapa banyak objek yang perlu diubah.

## Catatan

* [Chain of Responsibility](chain-of-responsibility.md), [Command](command.md), [Mediator](mediator.md), dan Observer menangani masalah decouple sender dan receiver dengan trade-off berbeda. 

    - Chain of Responsibility melewatkan request ke receiver yang disusun berantai.
    - Command umumnya merinci hubungan sender-receiver dengan subclass.
    - Mediator memiliki reference ke setiap sender dan receiver secara tak langsung.
    - Observer mendefinisikan interface yang sangat decouple sehingga membuat beberapa receiver dapat dikonfigurasi saat runtime.

* Mediator dan Observer saling bersaing. Perbedaan antara keduanya adalah Observer menyebar (distribusi) komunikasi dengan mengenalkan konsep publisher dan subscriber sementara Mediator mengenkapsulasi komunikasi antar objek. Observer lebih mudah untuk di-reuse.
* Mediator dapat menggunakan pola Observer untuk secara dinamis mendaftarkan Colleague dan berkomunikasi dengan mereka.

## Karakteristik

* umumnya observer akan definisikan sebuah callback yang akan dipanggil oleh subject ketika ada event.
* subject bersifat independen sementara observer bersifat dependan terhadap subject.
* observer register diri sendiri ke subject.
* subject dapat push informasi ke observer, atau observer pull informasi dari subject.