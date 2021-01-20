## Linked List

Xor Linked-List implementation and reversing.

### Overview

Senarai dengan setiap node memiliki satu tautan yang mengarah ke elemen penerus (successor) dan pendahulu (predecessor) sekaligus. Alamat yng disimpan pada tautan merupakan alamat hasil operasi XOR antara alamat penerus dan pendahulu.

Hal ini berarti struktur Xor-Linked List dapat menyimpan tautan secara efisien namun perlu operasi ekstra untuk mendapatkan alamat node lain.

Terdapat beberapa variasi yang memungkinkan, yakni:

- __head__, sebuah plain linked-list dengan sebuah pointer khusus untuk menunjuk posisi HEAD atau node mula-mula.
- __head & tail__, sebuah plain linked-list dengan pointer menunjuk ke posisi mula-mula (HEAD) dan posisi akhir (TAIL).
- __circular__, sebuah plain linked-list dengan node awal dan node akhir saling menunjuk, TAIL menunjuk HEAD sebagai node penerus dan HEAD menunjuk TAIL sebagai pendahulu.

## Reversing Notes

Xorlist memiliki dua field yaitu `data` dan `link`. Nilai alamat yang disimpan dalam `link` merupakan hasil operasi XOR. Nilai ini tidak secara eksplisit terindikasi sebagai sebuah alamat.