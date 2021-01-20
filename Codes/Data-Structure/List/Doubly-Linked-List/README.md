## Linked List

### Doubly Linked List

Senarai dengan setiap node memiliki dua tautan, satu menuju elemen penerus (successor) dan satu menuju elemen pendahulu (predecessor). Hal ini berarti penelusuran dapat dilakukan dua arah yakni maju (dari awalhingga akhir) dan mundur (dari akhir ke awal).

Terdapat beberapa variasi yang memungkinkan, yakni:

- __head__, sebuah plain linked-list dengan sebuah pointer khusus untuk menunjuk posisi HEAD atau node mula-mula.
- __head & tail__, sebuah plain linked-list dengan pointer menunjuk ke posisi mula-mula (HEAD) dan posisi akhir (TAIL).
- __self-pointed__, node akhir pada senarai akan menunjuk ke diri sendiri sebagai penanda (bahwa node tersebut merupakan node akhir).
- __circular__, sebuah plain linked-list dengan node awal dan node akhir saling menunjuk, TAIL menunjuk HEAD sebagai node penerus dan HEAD menunjuk TAIL sebagai pendahulu.

## Reversing Notes