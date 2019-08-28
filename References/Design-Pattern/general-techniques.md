# Programming Reference

General techniques / mechanism for code reuse.

## Inheritance

Dynamic / runtime polymorphism.

Keuntungan:

- Dapat mengganti implementasi saat runtime.
- Menyimpan objek berbeda (pointer, smart pointer, atau reference) dalam kontainer yang sama.
- Menunda method call ke implementasi spesifik dan memperbolehkan client-code bekerja dengan banyak implementasi berbeda saat runtime.

Kerugian:

- Class harus diturunkan dari base yang sama jika perlu dilakukan modifikasi.
- Objek hanya dapat dikembalikan dari factory function sebagai pointer atau dibungkus smart pointer.
- Lebih lambat daripada static polymorphism (template dan overload functions).

## Delegation

Menggunakan objek lain untuk mengimplementasikan beberapa fungsionalitas dan meneruskan method call alih-alih mewariskan object class.

## Static Polymorphism

Template dan overload functions atau overload methods.

Template dapat menghilangkan overhead akibat virtual method call dengan melakukan method-resolving saat compile (alih-alih saat runtime).

## Type Erasure

## Free Functions

C++ adalah bahasa multiparadigma dan tidak semua kebutuhan perlu direpresentasikan sebagai class. Function dapat digunakan untuk memperluas kemampuan class tanpa perlu melakukan modifikasi.

## Higher Order Functions / Higher Order Methods / Lambda

Lambda function dapat digunakan untuk:
- menambah perilaku ke objek saat runtime.
- membuat algoritma generik
- fungsi
- menyederhanakan event handling
- callback