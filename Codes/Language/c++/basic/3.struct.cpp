/*
    Struct
    Archive of Reversing.ID
    Programming Language (C++)

    Struct dan penggunaannya.
*/

#include <iostream>
#include <cstring>


struct book_t 
{
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
};


int main( ) 
{
   book_t Book1;        // Deklarasi Book1 dengan tipe Book
   book_t Book2;        // Deklarasi Book2 dengan tipe Book
 
   // spesifikasi book 1
   strcpy( Book1.title, "C/C++ Programming");
   strcpy( Book1.author, "Rakai Ady Wikradinata"); 
   strcpy( Book1.subject, "C Programming Tutorial");
   Book1.book_id = 6495407;

   // spesifikasi book 2
   strcpy( Book2.title, "Little Playground of Reverse Engineering");
   strcpy( Book2.author, "Satria Ady Pradana");
   strcpy( Book2.subject, "Reverse Engineering Tutorial");
   Book2.book_id = 6495700;
 
   // cetak informasi book 1
   std::cout << "Book 1 title : "  << Book1.title << std::endl;
   std::cout << "Book 1 author : "  << Book1.author << std::endl;
   std::cout << "Book 1 subject : "  << Book1.subject << std::endl;
   std::cout << "Book 1 book_id : "  << Book1.book_id << std::endl;

   // cetak informasi book 2
   std::cout << "Book 2 title : "  << Book2.title << std::endl;
   std::cout << "Book 2 author : "  << Book2.author << std::endl;
   std::cout << "Book 2 subject : "  << Book2.subject << std::endl;
   std::cout << "Book 2 book_id : "  << Book2.book_id << std::endl;

   return 0;
}