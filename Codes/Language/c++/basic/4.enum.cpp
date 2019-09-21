/*
    Enumeration
    Archive of Reversing.ID
    Programming Language (C++)

    Enumerasi dan penggunaannya.
*/

#include <iostream>


enum month_t 
{
    Jan, Feb, Mar, Apr, May, Jun, 
    Jul, Aug, Sep, Oct, Nov, Dec
};


int main(int argc, char* argv[])
{
    month_t month;

    month = Aug;    // seharusnya bernilai 7

    std::cout << "Month: " << month << std::endl;

    // cetak semua bulan
    std::cout << "Month 'Jan' = " << Jan << std::endl;
    std::cout << "Month 'Feb' = " << Feb << std::endl;
    std::cout << "Month 'Mar' = " << Mar << std::endl;
    std::cout << "Month 'Apr' = " << Apr << std::endl;
    std::cout << "Month 'May' = " << May << std::endl;
    std::cout << "Month 'Jun' = " << Jun << std::endl;
    std::cout << "Month 'Jul' = " << Jul << std::endl;
    std::cout << "Month 'Aug' = " << Aug << std::endl;
    std::cout << "Month 'Sep' = " << Sep << std::endl;
    std::cout << "Month 'Oct' = " << Oct << std::endl;
    std::cout << "Month 'Nov' = " << Nov << std::endl;
    std::cout << "Month 'Dec' = " << Dec << std::endl;


    return 0;
}