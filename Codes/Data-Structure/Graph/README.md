# Programming Reference

Graph implementation and reversing.

### Overview

`Graph` adalah struktur data nonlinier yang terdiri atas himpunan `node` (simpul) yang dihubungkan oleh `edge` (sisi).

Terdapat dua cara mengekspresikan `Graph`, yaitu: `adjacency list` dan `adjacency matrix`. 

`Adjacency matrix` (matrix tetangga) adalah array dua dimensi yang digunakan untuk menyimpan informasi koneksi antarsimpul dan dapat melakukan penelusuran dengan sangat cepat. Namun sebagai konsekuensinya, ukuran memory yang harus disediakan menjadi besar. Jika graph relatif renggang (sparse), maka akan terdapat banyak ruang yang terbuang.

`Adjacency list` merupakan sebuah linked-list, dimana setiap simpul memiliki Array yang menyimpan koneksi ke simpul lain. Pendekatan ini lebih fleksibel dan dapat menghemat ruang memory yang digunakan.

### Reversing Notes

### References

Definisi, karakteristik, variasi, dan informasi lain tentang Graph: