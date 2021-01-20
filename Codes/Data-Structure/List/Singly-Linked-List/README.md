## Linked List

Singly Linked-List implementation and reversing.

### Overview

Senarai dengan setiap node hanya memiliki satu tautan menuju elemen penerus (successor). Hal ini berarti penelusuran hanya dapat dilakukan satu arah yakni dari awal (node mula) hingga akhir.

Terdapat beberapa variasi yang memungkinkan, yakni:

- __head__, sebuah plain linked-list dengan sebuah pointer khusus untuk menunjuk posisi HEAD atau node mula-mula.
- __head & tail__, sebuah plain linked-list dengan pointer menunjuk ke posisi mula-mula (HEAD) dan posisi akhir (TAIL).
- __self-pointed__, node akhir pada senarai akan menunjuk ke diri sendiri sebagai penanda (bahwa node tersebut merupakan node akhir).
- __sentinel-first__, sebuah sentinel (node fiktif) sengaja diletakkan di awal untuk menghindari adanya kasus list kosong.
- __sentinel-last__, sebuah sentinel (node fiktif) sengaja diletakkan di akhir untuk menyeragamkan penanganan terhadap kasus list kosong.
- __self-sentinel__, sebuah sentinel yang menunjuk ke diri sendiri (self-pointed).
- __circular__, sebuah plain linked-list dengan node akhir menunjuk ke node awal, TAIL menunjuk HEAD sebagai node penerus.

## Reversing Notes