# Programming Reference

Strategy (Behavioral pattern).

Mengenkapsulasi algoritma ke dalam class.

## Tujuan

* Mendefinisikan sekelompok algoritma, enkapsulasi sebagai class, dan membuat masing-masing dapat digunakan secara bergantian.
* Mengubur detail algoritma di class turunan.

## Struktur

Class yang terlibat:

* Context: menyimpan reference ke salah satu strategy kemudian mendelegasikan tugas ke strategy, alih-alih dieksekusi secara langsung.
* Strategy: interface yang berlaku umum bagi semua strategy.
* ConcreteStrategy: implementasi beragam algoritma yang dapat digunakan. 

## Penggunaan

Desain ini digunakan ketika:

* banyak class berkaitan namun berbeda di perilaku.
* hanya perlu sedikit variasi di algoritma.
* algoritma memerlukan data yang tidak perlu diketahui client.

## Catatan

## Karakteristik