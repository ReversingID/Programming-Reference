# Programming Reference

Open repository of programming topic for reverse engineering purpose.

### Software Design Patterns

_Design Pattern_ atau _Software Design Pattern_ adalah sebuah istilah yang mengacu kepada solusi umum untuk menyelesaikan permasalahan dalam konteks perancangan dan pengembangan perangkat lunak. Software design-pattern dapat dipandang sebagai sebuah template yang mendeskripsikan solusi sebuah permasalahan atau acuan dalam menyelesaikan masalah yang seragam.

Menggunakan design pattern dapat membantu dalam pengembangan projek yang besar agar menjadi lebih tertata rapi secara struktural dan dapat dengan mudah dikembangkan. 

Konsep design-pattern memberikan istilah-istilah standard di kalangan software development dan spesifik terhadap skenario tertentu. Konsep-konsep ini juga berkembang sepanjang waktu dan terus mengalami perbaikan. Bagi seorang pengembang perangkat lunak, pemahaman dan penguasaan design-pattern ini dapat memudahkan dalam komunikasi menggunakan istilah yang umum diketahui dan dipahami. Dengan menggunakan arsitektur umum, pengembangan perangkat lunak dapat menjadi lebih terstruktur.

Dalam reverse-engineering sebuah perangkat lunak yang kompleks, pemahaman terhadap design-pattern pun membantu. Pemahaman konsep ini berguna untuk dengan cepat mengetahui arsitektur yang digunakan sebuah perangkat lunak dalam pandangan global. Hal ini tentu perlu ditopang dengan pemahaman terhadap komponen-komponen di level yang lebih rendah.

![Design Pattern - Periodic Table](_imgs_/periodic_table.png)

### Klasifikasi Design-Pattern

Software design-pattern merupakan sebuah adopsi dari hal serupa dalam dunia arsitektur. Umumnya konsep design-pattern merujuk kepada desain interaksi antar objek dalam perangkat lunak. Kita dapat mengklasifikasikan beberapa desain ke dalam tiga kategori besar:

* Creational
* Structural
* Behavioral

_Creational_ adalah pola-pola yang berkaitan dengan mekanisme penciptaan objek atau pembuatan instance. Beberapa solusi di dalam kategori ini menitikberatkan kepada pembuatan interface yang fleksibel dan konsisten untuk menciptakan objek secara berulang-ulang dengan menghilangkan detail yang tidak perlu ketika menciptakan instance objek.

_Behavioral_ adalah pola-pola desain yang berkaitan dengan perilaku objek dan komunikasi antar objek. Pola desain ini menitikberatkan kepada peningkatan fleksibilitas dalam komunikasi antar objek.

_Structural_ adalah pola-pola desain yang menyederhanakan hubungan (relationship) antar entitas. Hubungan antar objek dapat berupa komposisi antar kelas maupun peletakan objek-objek dalam suatu struktur tertentu. 

### Creational Pattern (Overview)

* Abstract Factory: membuat sebuah instance dari beberapa kelompok kelas.
* Builder: memisahkan antara object construction dengan representasinya.
* Factory Method: membuat instance dari beberapa kelas.
* Object Pool: menghindari akuisisi / rilis resource berbiaya tinggi (dalam segi waktu / space) dengan cara menggunakan ulang objek yang tak digunakan.
* Prototype: fully-initialized instance untuk disalin maupun diklon
* Singleton: kelas dengan hanya satu instance yang boleh ada selama runtime.

### Behavioral Pattern (Overview)

* Chain of Responsibility: metode untuk passing request antara serangkaian objek.
* Command: mengenkapsulasi sebuah request sebagai sebuah objek.
* Interpreter: mengimplementasikan elemen bahasa ke dalam program.
* Mediator: mendefinisikan komunikasi yang disederhanakan antara kelas-kelas.
* Memento: capture dan restore insternal state sebuah objek.
* Observer: mekanisme untuk memberikan pemberitahuan (notifikasi) kepada beberapa kelas apabila terjadi suatu perubahan.
* State: mengubah kelakuan sebuah objek ketika state (keadaan) berubah.
* Strategy: mengenkapsulasi sebuah algoritma ke dalam kelas.
* Template Method: mengalokasikan langkah-langkah algoritma ke subclass.
* Visitor: mendefinisikan operasi baru untuk kelas tanpa melakukan perubahan.

### Structural Pattern (Overview)

* Adapter: menyamakan interface antara dua kelas berbeda.
* Bridge: memisahkan interface sebuah objek dengan implementasinya.
* Composite: struktur 
* Decorator: menambahkan responsibility atau kapabilitas ke objek secara dinamis.
* Facade: sebuah kelas yang merepresentasikan keseluruhan subsistem
* Flyweight: instance yang digunakan untuk melakukan sharing secara efisien.
* Proxy: sebuah objek yang merepresentasikan objek lain secara transparan (tak diketahui oleh client).

### Referensi

* Design Patterns: Elements of Reusable Object-Oriented Software.
* Code Complete: A Practical Handbook of Software Construction.
* Pattern-Oriented Software Architecture, volume 1: A System of Patterns.
* Pattern-Oriented Software Architecture, volume 2: Patterns for Concurrent and networked Objects.
* Patterns of Enterprise Application Architecture.
* Enterprise Integration Patterns: Designing, Building, and Deploying Messaging Solutions.