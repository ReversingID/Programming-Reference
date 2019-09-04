# Programming Reference

Serverless

## Definisi

Menggunakan infrastruktur pihak ketiga (Function as a Service / FaaS) dengan fasilitas untuk menjalankan custom-code di lingkungan terkontrol sehingga fungsi-fungsi inti berjalan di pihak ketiga.

## Struktur

## Penggunaan

Arsitektur ini ideal digunakan untuk:

* aplikasi yang hanya terdiri dari business logic yang simple.

## Karakteristik

Sifat umum:

* stateless
* berorientasi fungsi minimalistik, fungsi dengan ukuran kecil dan dapat bekerja cepat di setiap pemanggilan dengan minimnya dependensi terhadap fungsi lain.

Keuntungan:

* menghilangkan kebutuhan untuk alokasi dan pemeliharaan lingkungan pemroses (processing environment) seperti server.

Kekurangan:

* aplikasi yang kompleks butuh dipecah menjadi fungsi-fungsi kecil agar dapat secara efektif digunakan di layanan Function as a Service.
* kehilangan kemungkinan untuk melakukan optimisasi server.
* kurang efektif mengelola local-state.