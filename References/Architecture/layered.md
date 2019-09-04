# Programming Reference

Layered Architecture

## Definisi

Membagi sistem ke dalam lapisan-lapisan dimana setiap lapisan memiliki tanggung jawab tertentu dan memberikan layanan ke service di lapisan lebih tinggi.

## Struktur

Tidak ada batasan lapisan, namun terdapat beberapa lapisan yang umum ada:

* Presentation (UI): menampilkan desain grafis aplikasi dan mengandung kode untuk menangani interaksi dari user.
* Application: memberi abstraksi dan melakukan koordinasi antara `presentation` dan `application`.
* Business (Domain): mendefinisikan model dan logic terkait dari problem bisnis yang ingin dipecahkan.
* Persistence (data access): memberi abstraksi akses terhadap media penyimpanan (database) untuk dapat membaca dan memanipulasi data tanpa tergantung kepada teknologi.
* Database: mendefinisikan teknologi penyimpanan yang digunakan untuk menyimpan dan mengolah data.

Mungkin terdapat variasi tergantung kepada kompleksitas aplikasi. 

Tidak menutup kemungkinan dua layer dapat dikombinasikan menjadi satu, misal `ActiveRecord` yang mengombinasikan lapisan `business` dan `persistence`.

## Penggunaan

Arsitektur ini ideal digunakan untuk:

* aplikasi standard line-of-business yang melakukan proses lebih dari sekedar operasi CRUD.

## Karakteristik

Keuntungan:

* sederhana dan familiar.
* memberi kemudahan dalam menulis aplikasi yang terorganisir.

Kekurangan:

* cenderung mengarah ke aplikasi monolitik dan susah untuk dipisah di kemudian hari.
* terkadang diperlukan kode untuk mengakses hal yang ada di layer berbeda
