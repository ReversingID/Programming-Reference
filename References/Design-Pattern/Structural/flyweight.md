# Programming Reference

Flyweight (Structural pattern).

Meminimalisir penggunaan memory dengan cara berbagi data sebanyak mungkin pada objek serupa.

## Tujuan

* Memperbanyak sumber data yang dimiliki bersama oleh beberapa objek.

## Struktur

Class yang terlibat:

* FlyweightFactory: mengelola object pool berisi flyweight. 
* Flyweight: class berisi sebagian dari objek asal (yang di-refactor) 

## Penggunaan

Desain ini digunakan ketika:

## Catatan

Karena objek flyweight dapat digunakan di beragam konteks, perlu dipastikan bahwa state tidak mengalami perubahan. Flyweight hanya dapat menginisialisasi sekali melalui parameter konstruktor. Tidak boleh ada data yang terekspos ke objek lain.

Untuk memudahkan akses ke beragam flyweight, factory method dapat digunakan untuk mengelola object pool dari flyweight. Method menerima state yang diinginkan dari client dan kemudian objek flyweight yang sesuai akan diberikan jika ada.

## Karakteristik