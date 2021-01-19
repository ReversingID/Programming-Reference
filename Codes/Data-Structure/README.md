# Programming Reference

Data Structure

## Overview

Bagian ini akan membahas tentang `struktur data` secara umum dengan menyertakan sudut pandang Reverse Engineering dalam pembahasannya. Materi ini diharapkan dapat memberikan pemahaman dalam melakukan analisis, terutama dalam mengidentifikasi struktur data.

Hampir seluruh struktur data diturunkan dari dua pendekatan: `Array` (penyimpanan sekuensial) dan `Linked-List` (penyimpanan berantai). Struktur data yang lebih kompleks seperti `Stack`, `Queue`, `Heap`, `Tree`, `Graph`, dsb menggunakan `Array` atau `Linked-List` di implementasinya.

Meski masing-masing struktur data memiliki operasi yang unik namun secara garis besar operasi struktur data merupakan operasi penelusuran (akses elemen) serta perubahan struktur (add, delete, get value, modify).

## General Instruction

Setiap topik memiliki source code dalam bahasa pemrograman tertentu. Masing-masing source code akan memiliki instruksi kompilasi secara manual. Lakukan kompilasi, amati hasil kompilasi, dan identifikasi operasi-operasi struktur data. Gunakan source sebagai perbandingan untuk mengidentifikasi fungsi/method yang sesuai.

## Reverse Engineering

Sebagian algoritma memanfaatkan struktur data untuk mengelola data secara efisien. Identifikasi struktur data diperlukan untuk memahami alur algoritma. 

Source code yang dikompilasi menjadi [instruksi tingkat rendah](https://github.com/ReversingID/LowLevelCode-Reference) (assembly dan bytecode) akan memberikan tantangan tersendiri. Karakteristik struktur data menjadi kabur dimana hanya terdapat data dan operasi terkait yang dapat diamati. Identifikasi kemudian dilakukan dengan mengamati ruang memory yang dialokasikan serta operasi-operasi yang terjadi. Dalam beberapa kasus, nama fungsi akan hilang atau berubah sebagai efek dari kompilasi atau obfuscation. Dengan demikian, analisis harus dilakukan dari awal untuk setiap operasi.