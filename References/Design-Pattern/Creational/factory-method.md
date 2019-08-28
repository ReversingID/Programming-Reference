# Programming Reference

Factory Method (Creational pattern).

Factory Method adalah pola dimana terdapat sebuah method yang bertugas / bertanggung jawab untuk menciptakan object.

Method atau function apapun yang mengembalikan instance dari class atau class turunan.

## Tujuan

* Mendefinisikan interface untuk menciptakan objek, namun instansiasi diserahkan kepada subclass.
* Mengganti konstruksi objek secara langsung dengan pemanggilan terhadap method di factory sehingga objek-objek yang beragam (namun dalam satu kelompok sama) dapat diciptakan dengan fleksibel.
* Instantiasi class dari hirarki tanpa perlu melakukan hardcode nama class dan implementasinya. 

## Struktur 

Class yang terlibat:

* Product: mendefinisikan interface untuk tipe-tipe objek yang diciptakan oleh factory method. 
* ConcreteProduct: mengimplementasikan interface Product.
* Creator: mendelarasikan factory method, yang mengembalikan objek bertipe AbstractProduct.
* ConcreteCreator: override factory method untuk mengembalikan instance dari Product konkret.

## Penggunaan

Desain ini digunakan ketika:

## Karakteristik


## References

- [Refactoring.Guru](https://refactoring.guru/design-patterns/factory-method)
- [SourceMaking](https://sourcemaking.com/design_patterns/factory_method)