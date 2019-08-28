# Programming Reference

Singleton (Creational pattern).

Singleton adalah pola dimana hanya terdapat satu instance dari sebuah class dan tidak diperbolehkan adanya instansiasi tambahan.

## Tujuan

- Memastikan class hanya memiliki (maksimal) satu instance selama runtime.
- Menyediakan mekanisme global untuk mengakses objek.

## Struktur

Class yang terlibat: N/A

## Penggunaan

Desain ini digunakan ketika:

- Aplikasi membutuhkan satu, dan hanya satu, instance objek.

## Karakteristik

- Tidak ada cara secara eksplisit untuk menciptakan instance baru.
    - Konstruktor didefinisikan sebagai private method.
    - Terdapat sebuah method untuk mendapatkan instance.
- Instance serta method untuk mengakses instance didefinisikan sebagai static.
- Lazy initialization diberlakukan (penciptaan objek dilakukan ketika instance diakses pertama kali).

## Catatan

- [Abstract Factory](abstract-factory.md), [Builder](builder.md), dan [Prototype](prototype.md) dapat menggunakan Singleton dalam implementasinya.
- [Facade](../Structural/facade.md) seringkali diimplementasikan sebagai Singleton karena hanya ada satu objek Facade yang dibutuhkan.
- Object sejenis State umumnya Singleton.
- Seringkali Singleton disalahartikan sebagai pengganti global variable.
- Seringkali Singleton tidak diperlukan.