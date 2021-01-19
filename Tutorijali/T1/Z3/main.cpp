//TP 2018/2019: Tutorijal 1, Zadatak 2 - zadatak je kopira iz zadatka 2 sa ovog tutorijala jer sam ga tu slucajno uradio
#include <iostream>
#include <cmath>
#include <iomanip>



int main ()
{
    
    double a,b;
    std::cout << "Unesite pocetnu i krajnju vrijednost: ";
    
    do {
        std::cin >> a >> b;
    } while((a<0) || (b<0) || (a>9999) || (b>9999) || (a>b));
    
    std::cout << std::endl << "+---------+----------+----------+-----------+";
    std::cout << std::endl << "| Brojevi | Kvadrati | Korijeni | Logaritmi |";
    std::cout << std::endl << "+---------+----------+----------+-----------+" << std::endl;
    
    for(int i=a;i<=b;i++) {
        std::cout << "| " << std::left << std::setw(8) << i << "|" << std::right << std::setw(9) << i * i << " |"
        << std::right << std::setw(9) << std::setprecision(3) << std::fixed << sqrt(i) << " |" << std::right << std::setw(10)
        << std::setprecision(5) << std::fixed << log(i) << " |" << std::endl;
    }
    
    std::cout << "+---------+----------+----------+-----------+";

	return 0;
}