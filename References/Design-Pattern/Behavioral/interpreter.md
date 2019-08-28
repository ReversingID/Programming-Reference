# Programming Reference

Interpreter (Behavioral pattern).

Menyertakan elemen bahasa ke dalam program.

## Tujuan

* mendefinisikan representasi sebuah grammar dan interpreter untuk sebuah language.
* memetakan domain ke language, language ke grammar, dan grammar ke hierarchical object-oriented design.

## Struktur

Class yang terlibat:

* Context: merangkum informasi spesifik terkait sebuah interpretasi.
* Expression: representasi sebuah ekspresi bahasa.
* TerminalExpression: node yang merepresentasikan sebuah nilai.
* CompoundExpression: node yang merepresentasikan sebuah expression majemuk.
* Evaluator: mengevaluasi sebuah ekspresi sehingga menghasilkan nilai. (opsional).

## Penggunaan

Desain ini digunakan ketika:

* grammar sederhana (untuk grammar yang complex, ada pendekatan lain yang lebih baik).
* efisiensi bukanlah 

## Catatan

* Interpreter dapat menggunakan [State](state.md) untuk mendefinisikan parsing context.
* Abstract Syntax Tree (AST) pada Interpreter merupakan [Composite](../Structural/composite.md) sehingga [Iterator](iterator.md) dan [Visitor](visitor.md) dapat berlaku.
* simbol terminal (TerminalExpression) dapat dibagi sebagai Flyweight.

## Karakteristik

